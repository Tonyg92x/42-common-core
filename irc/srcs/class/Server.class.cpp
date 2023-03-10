/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:21:11 by aguay             #+#    #+#             */
/*   Updated: 2023/02/02 09:45:00 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"

//  =============== Identity control                    ===============//

Server::Server(int port, std::string password) : _port(port), _password(password)
{
    this->createSocket();
    this->setupSocketAddress();
    this->bindAddrSock();
    this->_runLoop = true;
}

int Server::getPort(void) const {return (this->_port);}

std::string Server::getPassword(void) const {return (this->_password);}

Server::Server(Server const & rhs)
{
    *this = rhs;
}

Server &        Server::operator=(Server const & rhs)
{
    this->_port = rhs.getPort();
    this->_password = rhs.getPassword();
    return (*this);
}

Server::~Server(void)
{
    for (intUserMapIt it = this->_activeUsers.begin(); it != this->_activeUsers.end(); it++)
    {
        if (it->second)
        {
            User * client = it->second;
            close(client->getUserFd());
            delete client;
        }
    }
    this->_activeUsers.clear();

    //  Free all inactive user allocated memory
    for (strUserMapIt it = this->_inactiveUsers.begin(); it != this->_inactiveUsers.end(); it++)
    {
        if (it->second)
            delete it->second;
    }
    this->_inactiveUsers.clear();

    //  Destroy all channel data
    for (channelMapIt it = this->_channels.begin(); it != this->_channels.end(); it++)
    {
        if (it->second)
            delete it->second;
    }
    this->_channels.clear();
};

//  =============== Server loop                         ===============//

void                            Server::start(void)
{
    //  Start listening on the master socket
    this->startListening();

    //  zero out fd_set and add master socket
    FD_ZERO(&_current_sockets);
    FD_SET(_masterSocket, &_current_sockets);

    //  Variable for server loop
    int     newFd;              //  int to store lvalue of new connection's

    while (_runLoop)
    {
        //  Copy the current_sockets because select is destructive
        _ready_sockets = _current_sockets;
        std::cout << BLUE << "\nPort: "<< GREEN << _port << BLUE << " Waiting for a request\n" << NORMAL << std::endl;

        /*          SELECT
            Args:
                1) look for x number of fd's
                2) the fd set address for reading
                3) the fd set address for writing
                4) the fd set address for errors
                5) Timeout value (if you want to stop waiting after x ms)
        */
        if (select(FD_SETSIZE, &_ready_sockets, NULL, NULL, NULL) < 0)
            throw selectFailed();
        
        std::string strRequest;
        bool        commandComplete;
        ssize_t receivedCode;

        for (int i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &_ready_sockets))
            {                
                //  New request entered
                if (i == _masterSocket)
                {
                    //  Accept new connection here
                    newFd = accept(i, (sockaddr *) NULL, NULL);

                    if (newFd < 4)
                        std::cout << "Error on reading the new connection" << std::endl;
                    else
                    {
                        //  Add fd to fd_set
                        FD_SET(newFd, &_current_sockets);

                        //  Create a new User with that fd -> will delete it if he already has logged
                        _activeUsers.insert(std::pair<int, User *>(newFd, new User(newFd)));

                        std::cout << GREEN << "New connection accepted on socket " << newFd << NORMAL << std::endl;
                    }
                }
                else
                {
                    intUserMapIt it = _activeUsers.find(i);

                    if (it == _activeUsers.end())
                    {
                        User * tempUser = new User(i);
                        this->sendClient("221", tempUser, "Closing Link\r\n");
                        delete tempUser;
                        FD_CLR(i, &_current_sockets);
                    }
                    else
                    {
                        User * client = it->second;
                        memset(_receivedLine, 0, MAXLINE);
                        receivedCode = recv(i, _receivedLine, MAXLINE - 1, 0);

                        if (receivedCode == 0)  // if client closed connection
                            this->disconnectClient(client);
                        else if (receivedCode == -1)
                        {
                            std::cout << RED << "Error: " << BLUE << "on receiving data from " << CYAN << client->getNickname() << NORMAL << std::endl;
                            this->sendClient("400", client, "Failed to process request\r\n");
                        }
                        else
                        {
                            strRequest = requestToString(_receivedLine);

                            for (size_t i = 0; i <= strRequest.size(); i++)
                            {
                                if (strRequest[i] == '\r')
                                    commandComplete = true;
                            }

                            if (commandComplete)
                            {
                                if (client->getIncompleteRequest() != "")
                                    strRequest = client->getIncompleteRequest() + strRequest;

                                for (size_t i = 0; i < strRequest.size(); i++)
                                {
                                    if ((int) strRequest[i] == 4)
                                        strRequest.erase(i, 1);
                                }
                                parseRequest(strRequest, client);
                                client->setIncompleteRequest("");
                            }
                            else
                                client->setIncompleteRequest(client->getIncompleteRequest() + strRequest);
                            commandComplete = false;
                        }
                    }
                }
            }
        }
    }
};

//  =============== Command's                           ===============//

//  PASS command
void                            Server::commandPASS(std::string request, User *client)
{
    if (!client)
        return;

    //  If the password is already verified, code here
    if (client->getPasswordStatus() == true)
    {
        std::cout << BLUE << "Password is already validated for " << CYAN << client->getNickname() << std::endl;
        return;
    }

    //  Get the password received
    std::string password = request.substr(0, request.find_first_of('\n'));

    //  If the password is invalid code here
    if (password != _password)
    {
        std::cout << RED << "Error: " << NORMAL << "Password invalid." << std::endl;
        this->sendClient("464", client, "Password Incorect\r\n");
        this->disconnectClient(client);
        return;
    }
    else
        client->setPasswordStatus(true);
}

//  NICK command
void                            Server::commandNICK(std::string request, User *client)
{
    if (!client)
        return;

    if (client->getPasswordStatus() == false)
    {
        this->sendClient("503", client, "Command out of sequence, this server require a password\r\n");
        this->disconnectClient(client);
        return;
    }

    std::string nickname = request.substr(0, request.find_first_of(13));
    std::string userList;
    std::string message;
    strVec      userVec;
    User *      tempClient;

    if (parseNickname(nickname, client) == false)
        return ;
    else if (getActiveUser(nickname) && !client->getAuthenticated())
    {
        message = "Nickname is already in use";
        sendClient("433", client, message  + "\r\n");
        std::cout << RED << "Error: " << BLUE << message << NORMAL << std::endl;
        disconnectClient(client);
        return; 
    }
    else if (client->getAuthenticated() && getActiveUser(nickname))
    {
        message = "Nickname is already in use";
        sendClient("433", client, "Nickname is already in use \r\n");
        std::cout << RED << "Error: " << BLUE << message << NORMAL << std::endl;
    }
    else if (client->getAuthenticated())
    {
        std::string oldNickName = client->getNickname();
        client->setNickname(nickname);
        std::cout << CYAN << oldNickName << BLUE << " changed her nickname for " << CYAN << nickname << NORMAL << std::endl;
        message = ':' + oldNickName + " NICK :" + nickname + "\r\n";
        send(client->getUserFd(), message.c_str(), message.size(), SIGPROTECTION);
        channelMapIt it = _channels.begin();
        channelMapIt end = _channels.end();
        while (it != end)
        {
            it->second->changeNickname(nickname, client, oldNickName);
            userList = it->second->getClientList();
            userVec = this->parseArg(userList);
            for (strVecIt it0 = userVec.begin(); it0 != userVec.end(); it0++)
            {
                tempClient = this->getActiveUser(*it0);
                if (tempClient != client)
                    send(tempClient->getUserFd(), message.c_str(), message.size(), SIGPROTECTION);
            }
            userVec.clear();
            it++;
        }
    }
    else
        client->setNickname(nickname);
}

//  USER command
void                            Server::commandUSER(std::string request, User *client)
{
    if (!client)
        return;

    // If the PASS command didnt succeeded or no pass is entered
    if (client->getPasswordStatus() == false)
    {
        this->sendClient("503", client, "Command out of sequence, this server require a password\r\n");
        this->disconnectClient(client);
        return;
    }

    // If the client is already authentified, send a ERR_ALREADYREGISTRED error
    if (client->getAuthenticated() == true)
    {
        std::string errorMessage = ":Unauthorized command (already regsistered)";
        sendClient("462", client, errorMessage + "\r\n");
        std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
        return;
    }
    // Parse Username
    std::string username = request.substr(0, request.find_first_of((char) 32));

    request = parseUsername(request, client);
    if (request == "")
        return;

    User * inactiveClient = getInactiveUser(client->getUsername());

    //  If it does, delete the client created at first request
    if (inactiveClient)
    {
        if (inactiveClient->getUsername() != username)
        {
            std::string errorMessage = "Nickname is already in use";
            sendClient("433", client, errorMessage + "\r\n");
            std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
            disconnectClient(client);
            return; 
        }
        int fd = client->getUserFd();
        inactiveClient->setUserFd(fd);
        inactiveClient->setPasswordStatus(true);
        inactiveClient->setAuthenticated(true);
        _inactiveUsers.erase(client->getNickname());
        delete client;
        _activeUsers.erase(fd);
        _activeUsers.insert(std::pair<int, User *>(fd, inactiveClient));
        FD_CLR(fd, &_current_sockets);
        FD_SET(fd, &_current_sockets);
        this->sendLogo(inactiveClient);
        this->sendWelcomeMessage(inactiveClient);
        this->sendClient("001", inactiveClient, "Welcome back!\n" + inactiveClient->getNickname() + '!' + inactiveClient->getUsername() + '@' + ServerHostname + "\r\n");\
        return ;
    }
    // Parse the mode and unused char
    request = parseModeAndUnused(request, client);
    if (request == "")
        return ;
    // Parse the real name
    if (parseRealname(request, client) == false)
        return ;

    std::cout << NORMAL << "User " << CYAN << client->getUsername();
    std::cout << NORMAL << " nickname " << CYAN << client->getNickname();
    std::cout << NORMAL << " creation " << GREEN << "successfull." << NORMAL << std::endl;
    client->setAuthenticated(true);
    this->sendLogo(client);
    this->sendWelcomeMessage(client);
    this->sendClient("001", client, "Welcome!\n" + client->getNickname() + '!' + client->getUsername() + '@' + ServerHostname + "\r\n");
}

//  CAP command
void                            Server::commandCAP(std::string request, User *client)
{
    std::string command = request.substr(0, request.find_first_of(" \r\n"));

    if (command == "LS")
        this->sendClient("", client, "CAP LS\r\n");
    else if (command == "REQ")
    {
        this->sendClient("", client, "CAP NAK multi-prefix tls away-notify extended-join account-notify account-tag intent self-message cap-notify chghost invite-notify server-time userhost-in-names batch znc.in/server-time-iso znc.in/self-message znc.in/batch znc.in/playback\r\n");
        this->sendClient("", client, "CAP END\r\n");
    }
    return;
}

//  JOIN command
void                            Server::commandJOIN(std::string request, User *client)
{
    if (!client)
        return;

    if (client->getChannelNumber() >= 10)
    {
        std::cout << RED << "Error: " << BLUE << "Maximum 10 channels per client" << NORMAL << std::endl;
        this->sendClient("473", client, "Maximum of 10 channel's joined by user.\r\n");
        return;
    }

    strVec channels = this->parseArg(request);
    std::string channelname;

    for (strVecIt it = channels.begin(); it != channels.end(); it++)
    {
        channelname = *it;

        if (this->parseChannelname(channelname))
        {
            channelMapIt it = this->_channels.find(channelname);

            if (it != this->_channels.end())    // Channel exist, join it
            {
                Channel * channel = it->second;

                if (channel->getModeK() == true)
                {
                    if (request.size() == channelname.size())
                    {
                        std::cout << RED << "Error: " << CYAN << client->getNickname() << BLUE << " tryed to join without a key (+k)" << NORMAL << std::endl;
                        this->sendClient("473", client, channelname + " :Cannot join channel +k (need a key).\r\n");
                        return ;
                    }
                    else
                    {
                        std::string key = request.substr(request.find_first_of(" \r\n") + 1, request.npos);
                        key = key.substr(0, key.find_first_of(" \r\n"));
                        if (channel->keyValid(key))
                        {
                            channel->connect(client);
                            if (channel->clientInChannel(client))
                            {
                                client->joinChannel(channel);
                                std::cout << CYAN << client->getNickname() << BLUE << ": joined " << YELLOW << channel->getChannelname() << NORMAL << std::endl;
                                this->commandTOPIC(channelname, client);
                                this->commandNAMES(channelname, client);
                                this->commandMODE(channel->getChannelname(), client);
                                return ;
                            }
                        }
                        else
                        {
                            std::cout << RED << "Error: " << BLUE << "key invalid" << std::endl;
                            this->sendClient("473", client, channelname + " :Cannot join channel +k key is invalid.\r\n");
                            return;
                        }
                    }
                }
                else
                {
                    if (channel->clientInChannel(client) == false)
                    {
                        channel->connect(client);
                        if (channel->clientInChannel(client))
                        {
                            client->joinChannel(channel);
                            std::cout << CYAN << client->getNickname() << BLUE << ": joined " << YELLOW << channel->getChannelname() << NORMAL << std::endl;
                            this->commandTOPIC(channelname, client);
                            this->commandNAMES(channelname, client);
                            this->commandMODE(channel->getChannelname(), client);
                            return ;
                        }
                    }
                    else
                    {
                        std::cout << CYAN << client->getNickname() << BLUE << ": is already in " << YELLOW << channel->getChannelname() << NORMAL << std::endl;
                        this->commandTOPIC(channelname, client);
                        this->commandNAMES(channelname, client);
                        this->commandMODE(channel->getChannelname(), client);
                        return ;
                    }
                }
            }
            else // Channel dosent exist, so lets create it
            {
                this->_channels.insert(std::pair<std::string, Channel *>(channelname, new Channel(channelname, client)));
                Channel * channel = getChannel(channelname);

                if (channel)
                {
                    std::cout << CYAN << client->getNickname() << BLUE << ": created " << YELLOW << channelname << NORMAL << std::endl;

                    this->commandTOPIC(channelname, client);

                    this->commandNAMES(channelname, client);
                    this->commandMODE(channel->getChannelname(), client);

                    client->joinChannel(channel);
                    return;
                }
            }
        }
        else
        {
            this->sendClient("479", client, channelname + " : is a invalid channel name.\r\n");
            std::cout << CYAN << client->getNickname() << BLUE << ": " << YELLOW << channelname << BLUE << " is a invalid channel name." << NORMAL << std::endl;
        }
    }
}

//  PART command
void                            Server::commandPART(std::string request, User *client)
{
    if (!client)
        return;

    std::string channelname = request.substr(0, request.find_first_of(" \r\n"));
    std::string response;

    if (parseChannelname(channelname))
    {
        channelMapIt it = _channels.find(channelname);

        if (it != _channels.end()) // Channel exist
        {
            if (it->second->clientInChannel(client))
            {
                client->leaveChannel(channelname);
                it->second->disconnect(client);
                std::cout << CYAN << client->getNickname() << BLUE << " has left the channel " << YELLOW << channelname << NORMAL << std::endl;
                if (it->second->getUserNumber() < 1) // If the channel is empty, delete it
                {
                    delete it->second;
                    this->_channels.erase(channelname);
                    std::cout << YELLOW << channelname << BLUE << ": deleted: channel is empty" << NORMAL << std::endl;
                    return;
                }
            }
            else
            {
                std::cout << CYAN << client->getNickname() << BLUE << " is not in the channel " << YELLOW << channelname << NORMAL << std::endl;
                this->sendClient("442", client, channelname + " :You're not on that channel\r\n");
            }
        }
        else
        {
            std::cout << YELLOW << channelname << BLUE << ": the channel dosen't exist." << NORMAL << std::endl;
            this->sendClient("403", client, channelname + "  :No such channel\r\n");
        }
    }
    else
    {
        std::cout << YELLOW << channelname << BLUE << ": the channel dosen't exist." << NORMAL << std::endl;
        this->sendClient("403", client, channelname + "  :No such channel\r\n");
    }

    //  Reason argument -> Sorry client, I dont give a fuck about the reason :)
}

//  MODE command
void                            Server::commandMODE(std::string request, User *client)
{
    if (!client)
        return;

    if (request.size() == 0)
    {
        this->sendClient("461", client, "MODE :Not enough parameters\r\n");
        std::cout << RED "Error: " << NORMAL << "MODE: not enough parameters" << std::endl;
        return;
    }

    strVec params;
    params = parseModeCommand(request, params, client);

    if (params.size() == 1)
    {
        Channel * channel = this->getChannel(params.at(0));

        if (!channel)
        {
            this->sendClient("461", client, "MODE :Channel not found \r\n");
            std::cout << RED "Error: " << NORMAL << "MODE: Channel not found" << std::endl;
            return;
        }

        if ((channel->getModeS() || channel->getModeP()) && !channel->clientInChannel(client))
        {
            this->sendClient("461", client, "MODE :Channel not found \r\n");
            std::cout << RED "Error: " << NORMAL << "MODE: Channel not found" << std::endl;
        }

        this->sendClient("324", client, channel->getChannelname() + " " + channel->getModeList() + " \r\n");
        return;
    }

    if (params.at(0) == "ERROR")
    {
        params.clear();
        return;
    }

    commandMODEChannel(params, client);
    return;
}

//  MODE command for channels
void                            Server::commandMODEChannel(strVec params, User *client)
{
    if (!client)
        return ;

    channelMapIt        it = this->_channels.find(params.at(0));
    Channel *           channel = it->second;
    std::string         tempStr;
    std::string         input;
    size_t              i = 1;
    char                action;
    bool                setTo;
    char                c;
    int                 userLimit;


    while (i < params.size())
    {
        tempStr = params.at(i);
        action = tempStr[0];

        if (action != '+' && action != '-')
        {
            std::cout << RED "Error: " << NORMAL << "MODE: Invalid input" << std::endl;
            this->sendClient("461", client, "MODE :invalid input\r\n");
            return;
        }
        if (!this->modeCodeValid(tempStr.substr(1, tempStr.npos)))
        {
            std::cout << RED "Error: " << NORMAL << "MODE: Invalid input" << std::endl;
            this->sendClient("461", client, "MODE :Invalid input\r\n");
            return;
        }

        if (action == '+')
            setTo = true;
        if (action == '-')
            setTo = false;

        input = "";
        for (size_t y = 1; y < tempStr.size(); y++)
        {
            c = tempStr[y];

            if (this->modeNeedArg(c))
            {
                if (i + 1 >= params.size())
                {
                    std::cout << RED << "Error: " << NORMAL << " mode command need an input" << std::endl;
                    this->sendClient("461", client, "MODE " + channel->getChannelname() + " :Not enough parameters\r\n");
                    return;
                }
                input = params.at(i + 1);
            }

            switch (c)
            {
                case 'p':
                {
                    channel->setModeP(setTo);
                    std::cout << CYAN << client->getNickname() << NORMAL << " set " << YELLOW << channel->getChannelname() << NORMAL << " mode private to " << setTo << std::endl;
                    break;
                }
                case 's':
                {
                    channel->setModeS(setTo);
                    std::cout << CYAN << client->getNickname() << NORMAL << " set " << YELLOW << channel->getChannelname() << NORMAL << " mode secret to " << setTo << std::endl;
                    break;
                }
                case 'i':
                {
                    channel->setModeI(setTo);
                    std::cout << CYAN << client->getNickname() << NORMAL << " set " << YELLOW << channel->getChannelname() << NORMAL << " mode invite only to " << setTo << std::endl;
                    break;
                }
                case 't':
                {
                    channel->setModeT(setTo);
                    std::cout << CYAN << client->getNickname() << NORMAL << " set " << YELLOW << channel->getChannelname() << NORMAL << " mode topic to " << setTo << std::endl;
                    break;
                }
                case 'n':
                {
                    channel->setModeN(setTo);
                    std::cout << CYAN << client->getNickname() << NORMAL << " set " << YELLOW << channel->getChannelname() << NORMAL << " mode n to " << setTo << std::endl;
                    break;
                }
                case 'm':
                {
                    channel->setModeM(setTo);
                    std::cout << CYAN << client->getNickname() << NORMAL << " set " << YELLOW << channel->getChannelname() << NORMAL << " mode m to " << setTo << std::endl;
                    break;
                }
                case 'l':
                {
                    if (setTo)
                    {
                        try
                        {
                            userLimit = stoi(input);
                            channel->setUserLimit(client, userLimit);
                            channel->setModeL(setTo);
                            std::cout << CYAN << client->getNickname() << NORMAL << " set " << YELLOW << channel->getChannelname() << NORMAL << " mode limite user number to " << userLimit << std::endl;
                        }
                        catch(std::exception e)
                        {
                            std::cout << RED << "Error: " << NORMAL << "the limit value must be a int." << std::endl;
                            this->sendClient("461", client, "MODE " + channel->getChannelname() + " :limite user value must be a integer\r\n");
                            return;
                        }
                    }
                    else
                    {
                        channel->setModeL(setTo);
                        std::cout << CYAN << client->getNickname() << NORMAL << " set " << YELLOW << channel->getChannelname() << NORMAL << " mode l to false." << std::endl;
                    }
                    break;
                }
                case 'k':
                {
                    if (setTo)
                    {
                        channel->setModeK(setTo);
                        channel->setKey(client, input);
                        std::cout << CYAN << client->getNickname() << BLUE << " set +k to " << input << NORMAL << std::endl;
                    }
                    else
                    {
                        channel->setModeK(setTo);
                        std::cout << CYAN << client->getNickname() << BLUE << " set +k to false" << NORMAL << std::endl;
                    }
                    break;
                }
                case 'o':
                {
                    User * nick = this->getActiveUser(input);

                    if (nick)
                    {
                        if (channel->clientInChannel(nick))
                        {
                            if (setTo)
                            {
                                channel->addOp(nick);
                                std::cout << CYAN << client->getNickname() << BLUE << " added " << CYAN << nick->getNickname();
                                std::cout << BLUE " to operator in channel " << YELLOW << channel->getChannelname() << NORMAL << std::endl; 
                            }
                            else
                            {
                                channel->revokeOp(nick);
                                std::cout << CYAN << client->getNickname() << BLUE << " revoked " << CYAN << nick->getNickname();
                                std::cout << BLUE " to operator in channel " << YELLOW << channel->getChannelname() << NORMAL << std::endl; 
                            }
                        }
                        else
                        {
                            std::cout << RED << "Error: " << NORMAL << "user is not in the channel" << std::endl;
                            this->sendClient("461", client, "MODE " + channel->getChannelname() + " :user is not in the channel \r\n");
                            return;
                        }
                    }
                    else
                    {
                        std::cout << RED << "Error: " << NORMAL << "mode o require the nickname of the user." << std::endl;
                        this->sendClient("461", client, "MODE " + channel->getChannelname() + " :nickname not active \r\n");
                        return;
                    }
                    break;
                }
                case 'b':
                {
                    if (setTo)
                    {
                        User *target = this->getActiveUser(input);
                        if (target)
                        {
                            if (channel->clientIsOwner(target) == true)
                            {
                                std::cout << RED << "You can't ban the owner of the channel... come on man!";
                                sendClient("441", client, "You can't ban the owner of the channel... come on man!\r\n");
                                return;
                            }
                            if (channel->clientIsInBanList(target) == true)
                            {
                                std::cout << RED << "The user is already banned from the channel" << NORMAL << std::endl;
                                sendClient("441", client, ":The user is already banned from the channel\r\n");
                                return ;
                            }
                            channel->sendToAll(client, ":" + client->getNickname() + " banned " + input + " from " + channel->getChannelname());

                            std::string response = ':' + client->getNickname() + '!' + client->getUsername() + "@ircserv PRIVMSG " + channel->getChannelname() + " " + ":" + client->getNickname() + " banned " + input + " from " + channel->getChannelname() + " \r\n";
                            if (send(client->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
                                std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << client->getNickname() << NORMAL << std::endl;
                            channel->addToBanList(target->getUsername(), target);
                            channel->disconnect(target) ;
                            target->leaveChannel(input);
                        }
                        else
                        {
                            std::cout << RED << "The user is not online" << NORMAL << std::endl;
                            sendClient("441", client, "The user is not online\r\n");
                            return;
                        }
                    }
                    else
                    {
                        //CHECKER POUR SI CEST PAS LE OWNER DU CHAN QUI BAN OU KICK VOIR SI CEST CHILL LAFFICHAGE
                        User *target = this->getActiveUser(input);
                        if (target)
                        {
                            if (channel->clientIsInBanList(target) == false)
                            {
                                std::cout << RED << "The user is not banned from the channel" << NORMAL << std::endl;
                                sendClient("441", client, ":The user is not banned from the channel\r\n");
                                return ;
                            }
                            channel->sendToAll(client, ":" + client->getNickname() + " unbanned " + input + " from " + channel->getChannelname());

                            commandINVITE(input + " " + channel->getChannelname(), client);
                            std::string response = ':' + client->getNickname() + '!' + client->getUsername() + "@ircserv PRIVMSG " + channel->getChannelname() + " " + ":" + client->getNickname() + " unbanned " + input + " from " + channel->getChannelname() + " \r\n";
                            if (send(client->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
                                std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << client->getNickname() << NORMAL << std::endl;
                            channel->removeFromBanList(target->getUsername());
                            channel->disconnect(target) ;
                            target->leaveChannel(input);
                        }
                        else
                        {
                            std::cout << RED << "The user is not online" << NORMAL << std::endl;
                            sendClient("441", client, "The user is not online\r\n");
                            return;
                        }
                    }
                    break;
                    }
                default:
                {
                    break;
                }
            }
        }
        channel->sendModeChange();
        if (input == "")
            i++;
        else
            i += 2;
    }
}

//  NOTICE command
void                            Server::commandNOTICE(std::string request, User *client)
{
    if (!client)
        return;

    std::string     cible = request.substr(0, request.find_first_of(" \r\n"));
    std::string     message = request.substr(cible.size() + 1, request.npos);

    if (cible[0] && cible[0] == '#')    // Message to channel
    {
        //  Validate that the channel exist and that the user can send message to it
        channelMapIt it = this->_channels.find(cible);

        if (it != _channels.end())
        {
            Channel * theChannel = it->second;

            std::cout << CYAN << client->getNickname() << BLUE << '@' << YELLOW << theChannel->getChannelname();
            std::cout << BLUE << ": " << NORMAL << message << std::endl;
            if (theChannel->getModeN() && !theChannel->clientInChannel(client))
            {
                this->sendClient("403", client, cible + " :Mode +n activated and you are not a channel member.\r\n");
                std::cout << RED << "Error: " << CYAN << client->getNickname() << BLUE << '@' << YELLOW << cible;
                std::cout << NORMAL << " can't send NOTICE to this channel (mode +n)" << std::endl;
            }
            else
                theChannel->sendNoticeToAll(client, message);
        }
        else
        {
            std::cout << RED << "Error: " << CYAN << client->getNickname() << BLUE << '@' << YELLOW << cible;
            std::cout << BLUE << ": " << NORMAL << message << std::endl;
            this->sendClient("403", client, cible + " :No such channel\r\n");
            std::cout << BLUE << "Channel " << YELLOW << cible << BLUE << " dosen't exist" << std::endl;
        }
    }
    else
    {
        //  Find the user to send the message
        User * receiver = this->getActiveUser(cible);

        if (receiver && receiver == client)
            std::cout << CYAN << client->getNickname() << BLUE << ": send a message to himself. What a weirdo!" << std::endl;
        if (receiver)
        {
            std::cout << CYAN << client->getNickname() << BLUE << '@' << YELLOW << receiver->getNickname();
            std::cout << BLUE << ": " << NORMAL << message << std::endl;
            this->sendNotice(client, receiver, message);
        }
        else
        {
            std::cout << RED << "Error: " << CYAN << cible << BLUE << ": is not a valid nickname associated to an active client." << std::endl;
            std::cout << CYAN << cible << BLUE << " might be offline" << NORMAL << std::endl;
            this->sendClient("401", client, cible + " :No such nick/channel\r\n");
        }
    }
}

//  TOPIC command 
void                            Server::commandTOPIC(std::string request, User *client)
{
    if (!client)
        return;

    std::string channel;
    std::string newTopic = "";

    channel = request.substr(0, request.find_first_of(' '));
    channelMapIt chanIt = this->_channels.find(channel);

    if (chanIt != this->_channels.end()) // If the channel exist
    {
        Channel * theChannel = chanIt->second;

        if (!theChannel)
            this->sendClient("403", client, channel + "  :No such channel\r\n");
        if (!theChannel->clientInChannel(client))
        {
            std::cout << RED << "Error: " << NORMAL << "user isn't a member of that channel." << std::endl;
            this->sendClient("442", client, theChannel->getChannelname() + " :Your'e not on that channel \r\n");
            return;
        }
        if (channel.size() < request.size())    //  Topic change request
        {
            if (theChannel->getModeT())
            {
                if (!theChannel->clientIsOp(client))
                {
                    std::cout << RED << "Error: " << NORMAL << "user is not an operator of that server and mode t is active." << std::endl;
                    this->sendClient("482", client, theChannel->getChannelname() + " :You're not channel operator \r\n");
                    return;
                }
            }
            newTopic = request.substr(channel.size() + 1, request.npos);
            std::cout << CYAN << client->getNickname() << BLUE << ": changed channel topic of " << YELLOW << theChannel->getChannelname();
            std::cout << BLUE << " to " << newTopic << NORMAL << std::endl;
            theChannel->setTopic(client, newTopic);
        }
        else    // Ask for channel topic information request
        {
            if ((theChannel->getModeS() || theChannel->getModeP()) && !theChannel->clientInChannel(client))
                this->sendClient("403", client, channel + "  :No such channel\r\n");
            else
                this->sendClient("332", client, channel + ": " + chanIt->second->getTopic() + " \r\n");
        }
    }
    else // Channel name error exception
    {
        this->sendClient("403", client, channel + "  :No such channel\r\n");
        std::cout << YELLOW << channel << BLUE << ": the channel dosen't exist." << NORMAL << std::endl;
    }
}

//  INVITE command
void                            Server::commandINVITE(std::string request, User *client)
{
    if (!client)
        return;

    strVec  arg = this->parseArg(request);

    if (arg.size() < 2)
    {
        std::cout << RED << "Error: " << NORMAL << "INVITE need at least two arguments like: INVITE <nickname> <channel>" << std::endl;
        this->sendClient("461", client, "INVITE :Not enough parameters \r\n");
        return;
    }

    std::string nickname = arg[0];
    std::string channelname = arg[1];

    User * invited = this->getActiveUser(nickname);

    if (!invited)
    {
        std::cout << RED << "Error: " << NORMAL << "INVITE first argument nickname not found." << std::endl;
        this->sendClient("461", client, "INVITE :Nickname not found. INVITE <nickname> <channel> \r\n");
        return;
    }

    Channel * channel = this->getChannel(channelname);

    if (!channel)
    {
        std::cout << RED << "Error: " << NORMAL << "INVITE first argument (channel which nickname is invited to) is not an active user." << std::endl;
        this->sendClient("461", client, "INVITE :Channel not found. INVITE <nickname> <channel>\r\n");
        return;
    }

    if (channel->clientInChannel(invited))
    {
        std::cout << RED << "Error: " << NORMAL << "User is already in the channel." << std::endl;
        this->sendClient("461", client, "INVITE :User alreadu in the channel \r\n");
        return;
    }

    if (!channel->clientIsOp(client))
    {
        std::cout << RED << "Error: " << NORMAL << "user can't invite: not an operator." << std::endl;
        this->sendClient("461", client, "INVITE :Permission denied \r\n");
        return;
    }

    std::string response = ':' + client->getNickname() + '!' + client->getUsername() + '@' + static_cast<std::string>(ServerHostname) + " INVITE " + invited->getNickname() + " :" + channelname + " \r\n";
    channel->inviteUser(client, invited);
    send(invited->getUserFd(), response.c_str(), response.size(), SIGPROTECTION);
    std::cout << CYAN << client->getNickname() << BLUE << " sent " << CYAN << nickname << BLUE << " an invitation to " << YELLOW << channelname << NORMAL << std::endl; 
}

//  KICK command 
void                            Server::commandKICK(std::string request, User *client)
{
    if (!client)
        return;
    strVec params = parseArg(request);
    std::string kickMessage = "";


    // Check si il y a assez de parametres
    if (params.size() < 2)
    {
        std::string errorMessage = ":Command needs more parameters";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("461", client, errorMessage);
        return;
    }
    // Check si le channel commance par un hashtag
    if (params.at(0)[0] != '#')
    {
        std::string errorMessage = ":Invalid parameter";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("461", client, errorMessage);
        return;
    }
    Channel *channel = getChannel(params.at(0));
    if (channel == NULL)
    {
        std::string errorMessage = ":Invalid parameter";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("403", client, errorMessage);
        return;
    }
    // Check si le target est connecter/existe
    User *target = getActiveUser(params.at(1));
    if (target == NULL)
    {
        std::string errorMessage = ":The user is not in the channel asked";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("441", client, errorMessage);
        return;
    }
    // Check si le client est ds le channel
    if (channel->clientInChannel(client) == false)
    {
        std::string errorMessage = ":You are not even in the channel";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("442", client, errorMessage);
        return ;
    }
    // Check si le client est Operator du channel
    if (channel->clientIsOp(client) == false)
    {
        std::string errorMessage = ":You are not a channel operator, therefore, you can't kick anyone";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("482", client, errorMessage);
        return;
    }
    // Check si le target est dans le channel
    if (channel->clientInChannel(target) == false)
    {
        std::string errorMessage = ":This user is not in the channel";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("441", client, errorMessage);
        return;
    }
    // Check pour pas te auto kicker
    if (client->getNickname() == params.at(1))
    {
        std::string errorMessage = ":You can't kick yourself!";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("441", client, errorMessage);
        return ;
    }
    // Check pour pas qun operator kick le owner
    if (channel->clientIsOp(target))
    {
        std::string errorMessage = ":You can't kick the owner of the channel... come on man!";
        std::cout << RED << "Error " << NORMAL << "KICK " + errorMessage << std::endl;
        errorMessage = errorMessage + "\r\n";
        sendClient("441", client, errorMessage);
        return;
    }
    // Check si un message de kick et lappend
    if (params.at(2).size() > 1)
    {
        int nbArgs = params.size();
        for (int i = 2; i < nbArgs; i++)
        {
            std::string temp = params.at(i);
            if (i == 2)
                temp = temp.erase(0, 1);
            kickMessage = kickMessage + " " + temp;
        }
        kickMessage = " because :" + kickMessage;
    }


    channel->sendToAll(client, ":" + client->getNickname() + " kicked " + params.at(1) + " from " + params.at(0) + kickMessage);
    kickMessage = ":" + client->getNickname() + " kicked " + params.at(1) + " from " + params.at(0) + kickMessage;
    
    std::string nickname;

    if (channel->clientIsOwner(client))
        nickname = "Owner~" + client->getNickname();
    else if (channel->clientIsOp(client))
        nickname = "Operator~" + client->getNickname();
    else if (channel->clientInChannel(client))
        nickname = "Member~" + client->getNickname();
    else
        nickname = client->getNickname();
    std::string response = ':' + nickname + '!' + client->getUsername() + "@ircserv PRIVMSG " + channel->getChannelname() + " " + kickMessage + " \r\n";
    if (send(client->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << client->getNickname() << NORMAL << std::endl;
   
    channel->disconnect(target) ;
    target->leaveChannel(params.at(0));
}

//  LIST command
void                            Server::commandLIST(std::string request, User *client)
{
    if (!client)
        return;

    Channel * channel;

    //  Option where we list all channels in the server
    if (request.size() == 0)
    {
        this->sendClient("321", client, "LIST START\r\n");
        for (channelMapIt it = this->_channels.begin(); it != this->_channels.end(); it++)
        {
            channel = it->second;

            if (!channel)
                continue;
            else if (channel->getModeS() && !channel->clientInChannel(client))
                continue;
            else if (channel->getModeP() && !channel->clientInChannel(client))
            {
                this->sendClient("322", client, "* \r\n");
                std::cout << YELLOW << channel->getChannelname() << BLUE << " private channel " << NORMAL << std::endl;
            }
            else
            {
                this->sendClient("322", client, channel->getChannelname() + ' ' + std::to_string(channel->getUserNumber()) + ' ' + channel->getTopic() + "\r\n");
                std::cout << YELLOW << channel->getChannelname() << BLUE << ' ' + std::to_string(channel->getUserNumber()) + ' ' + channel->getTopic() + "\r\n" << NORMAL << std::endl;
            }
        }
    }
    else
    {
        strVec inputArray = this->parseArg(request);

        if (*inputArray.begin() == "STOP")
        {
            inputArray.clear();
            return;
        }

        this->sendClient("321", client, "LIST START\r\n");
        for (strVecIt it = inputArray.begin(); it != inputArray.end(); it++)
        {
            Channel * channel = getChannel(*it);

            if (channel)
            {
                if (channel->getModeS() && !channel->clientInChannel(client))
                    continue;
                else if (channel->getModeP() && !channel->clientInChannel(client))
                {
                    this->sendClient("322", client, "* \r\n");
                    std::cout << YELLOW << channel->getChannelname() << BLUE << "private channel" << NORMAL << std::endl;
                }
                else
                {
                    this->sendClient("322", client, channel->getChannelname() + ' ' + std::to_string(channel->getUserNumber()) + ' ' + channel->getTopic() + "\r\n");
                    std::cout << YELLOW << channel->getChannelname() << BLUE << ' ' + std::to_string(channel->getUserNumber()) + ' ' + channel->getTopic() + "\r\n" << NORMAL << std::endl;
                }
            }
            else
            {
                this->sendClient("403", client, *it + " :No such channel\r\n");
                std::cout << BLUE << *it + " :No such channel" << NORMAL << std::endl;
            }
        }
        inputArray.clear();
    }
    this->sendClient("323", client, "LIST END\r\n");
}

//  NAMES command
void                            Server::commandNAMES(std::string request, User *client)
{
    if (!client)
        return;

    Channel * channel;
    std::string channelList = "";

    if (request.size() == 0) // List all visible channel active users
    {
        for (channelMapIt it = this->_channels.begin(); it != this->_channels.end(); it++)
        {
            channel = it->second;

            if (channel)
            {
                if ((channel->getModeS() || channel->getModeP()) && !channel->clientInChannel(client))
                    continue;
                else
                {
                    channelList += channel->getChannelname() + ' ';
                    this->sendClient("353", client, "= " + channel->getChannelname() + " :" + channel->getClientList() + " \r\n");
                }
            }
        }
    }
    else    // List all members of given channel (s)
    {
        strVec array = parseArg(request);

        for (strVecIt it = array.begin(); it != array.end(); it++)
        {
            channel = getChannel(*it);

            if (channel)
            {
                if ((channel->getModeS() || channel->getModeP()) && !channel->clientInChannel(client))
                    continue;
                else
                {
                    channelList += channel->getChannelname() + ' ';
                    this->sendClient("353", client, "= " + channel->getChannelname() + " :" + channel->getClientList() + " \r\n");
                }
            }
        }
        array.clear();
    }
    this->sendClient("366", client, channelList + ":End of /NAMES list");
}

//  PRIVMSG command
void                            Server::commandPRIVMSG(std::string request, User *client)
{
    if (!client)
        return;

    std::string     cible = request.substr(0, request.find_first_of(" \r\n"));
    std::string     message = request.substr(cible.size() + 1, request.npos);

    if (cible[0] && cible[0] == '#')    // Message to channel
    {
        //  Validate that the channel exist and that the user can send message to it
        channelMapIt it = this->_channels.find(cible);

        if (it != _channels.end())
        {
            Channel * theChannel = it->second;

            std::cout << CYAN << client->getNickname() << BLUE << '@' << YELLOW << theChannel->getChannelname();
            std::cout << BLUE << ": " << NORMAL << message << std::endl;
            if (theChannel->getModeN() && !theChannel->clientInChannel(client))
            {
                this->sendClient("403", client, cible + " :Mode +n activated and you are not a channel member.\r\n");
                std::cout << RED << "Error: " << CYAN << client->getNickname() << BLUE << '@' << YELLOW << cible;
                std::cout << NORMAL << " can't send PRIVMSG to this channel (mode +n)" << std::endl;
            }
            else
                theChannel->sendToAll(client, message);
        }
        else
        {
            std::cout << RED << "Error: " << CYAN << client->getNickname() << BLUE << '@' << YELLOW << cible;
            std::cout << BLUE << ": " << NORMAL << message << std::endl;
            this->sendClient("403", client, cible + " :No such channel\r\n");
            std::cout << BLUE << "Channel " << YELLOW << cible << BLUE << " dosen't exist" << std::endl;
        }
    }
    else
    {
        //  Find the user to send the message
        User * receiver = this->getActiveUser(cible);

        if (receiver && receiver == client)
            std::cout << CYAN << client->getNickname() << BLUE << ": send a message to himself. What a weirdo!" << std::endl;
        if (receiver)
        {
            std::cout << CYAN << client->getNickname() << BLUE << '@' << YELLOW << receiver->getNickname();
            std::cout << BLUE << ": " << NORMAL << message << std::endl;
            this->sendMessage(client, receiver, message);
        }
        else
        {
            std::cout << RED << "Error: " << CYAN << cible << BLUE << ": is not a valid nickname associated to an active client." << std::endl;
            std::cout << CYAN << cible << BLUE << " might be offline" << NORMAL << std::endl;
            this->sendClient("401", client, cible + " :No such nick/channel\r\n");
        }
    }
}

//  QUIT command
void                            Server::commandQUIT(std::string request, User *client)
{
    std::string quitMessage = ':' + client->getNickname() + " QUIT " + request + "\r\n";
    for (intUserMapIt it = this->_activeUsers.begin(); it != this->_activeUsers.end(); it++)
    {
        if (it->second)
            send(it->second->getUserFd(), quitMessage.c_str(), quitMessage.size(), SIGPROTECTION);
    }
    if (!client)
        return;

    disconnectClient(client);
}

//  PING command
void                            Server::commandPING(std::string request, User * client)
{
    if (!client)
        return;
    std::string server = request.substr(0, request.find_first_of(" \r\n"));
    this->sendClient("", client, "PONG" + server + "\r\n");
}

//  PONG command
void                            Server::commandPONG(std::string request, User * client)
{
    if (!client)
        return;

    if (!client)
        return;
    std::string server = request.substr(0, request.find_first_of(" \r\n"));
    this->sendClient("", client, "PONG" + server + "\r\n");
}

//  HELP command
void                            Server::commandHELP(std::string request, User * client)
{
    if (!client)
        return;
    (void) request;

    this->serverSendMessage(client, "Here is a list of all possible command");
    this->serverSendMessage(client, "INVITE -> Invite a user in a channel. ARG <nickname> <channel>");
    this->serverSendMessage(client, "ISON -> See if the nickname input is online.");
    this->serverSendMessage(client, "JOIN -> Join a channel ARG <channel> <password>");
    this->serverSendMessage(client, "KICK -> Remove a user from a channel. ARG <channel> <user> <reason>");
    this->serverSendMessage(client, "LIST -> List all visible channels.");
    this->serverSendMessage(client, "MODE -> Change options for a channel. ARG <(+/-)ipk> <input>");
    this->serverSendMessage(client, "NAMES -> See all members of a given channel. ARG <channel>");
    this->serverSendMessage(client, "NICK -> Change nickname. ARG <newNickname>");
    this->serverSendMessage(client, "NOTICE -> Send a notice message. ARG <cible> <message>");
    this->serverSendMessage(client, "PART -> Leave a channel. ARG <channel>");
    this->serverSendMessage(client, "PRIVMSG -> Send a message. ARG <cible> <message>");
    this->serverSendMessage(client, "QUIT -> Disconnect");
    this->serverSendMessage(client, "TOPIC -> Change the topic of a channgel. ARG <newTopic>");
}

//  ISON command
void                            Server::commandISON(std::string request, User *client)
{
    if (!client)
        return;

    User * utilisateur;
    strVec inputArray = this->parseArg(request);

    for (strVecIt it = inputArray.begin(); it != inputArray.end(); it++)
    {
        utilisateur = getActiveUser(*it);

        if (utilisateur)
        {
            this->sendClient("303", client, ':' + utilisateur->getNickname() + "\r\n");
            this->sendMessage(client, utilisateur, "JOIN chat with you.\r\n");
        }
    }
    inputArray.clear();
}

//  Command not found...
void                            Server::commandNOTFOUND(User *client)
{
    if (!client)
        return;
    sendClient("421", client, "Unknown command\r\n");
}

//  =============== Tools method's                      ===============//

//  Disconnect the client (passwordStatus of user false and close fd, remove fd_set)
void                            Server::disconnectClient(User * client)
{
    if (!client)
        return;

    int fd;
    client->disconnectAllChannels();
    std::cout << CYAN << client->getNickname() << BLUE << ": Disconnected" << NORMAL << std::endl;
    this->sendGoodByeMessage(client);
    this->sendClient("221", client, "Closing Link\r\n");
    if (client->getAuthenticated() == false)
    {
        fd = client->getUserFd();
        this->_activeUsers.erase(fd);
        delete client;
        FD_CLR(fd, &_current_sockets);
        close(fd);
    }
    else
    {
        this->_inactiveUsers.insert(std::pair<std::string, User *>(client->getNickname(), client));
        fd = client->getUserFd();
        client->setAuthenticated(false);
        client->setUserFd(-1);
        client->setPasswordStatus(false);
        this->_activeUsers.erase(fd);
        FD_CLR(fd, &_current_sockets);
        close(fd);
    }
    this->_runRequestClient = false;
}

//  Look in inactive client if the nick already exist
//  If it does, ret     urn the client * else return NULL
User *                          Server::getInactiveUser(std::string nickname)
{
    strUserMapIt it = _inactiveUsers.find(nickname);

    if (it != _inactiveUsers.end())
    {
        User * client = it->second;
        return (client);
    }
    return (NULL);
}

User *                          Server::getActiveUser(std::string nickname)
{
    for (intUserMapIt it = this->_activeUsers.begin(); it != _activeUsers.end(); it++)
    {
        if (it->second->getNickname() == nickname)
            return (it->second);
    }
    return NULL;
}

Channel *                       Server::getChannel(std::string channelname)
{
    channelMapIt it = this->_channels.find(channelname);

    if (it != this->_channels.end())
        return (it->second);
    return (NULL);
}

strVec                          Server::parseArg(std::string requestArg)
{
    strVec  inputArray;

    while (requestArg.size() > 0)
    {
        inputArray.push_back(requestArg.substr(0, requestArg.find_first_of(" ,\r\n")));
        if ((*(--inputArray.end())).size() == requestArg.size())
            break;
        requestArg = requestArg.substr(requestArg.find_first_of(" ,\r\n") + 1, requestArg.npos);
    }

    return (inputArray);
}

std::string                     Server::getActiveUsers(void)
{
    std::string activeUsers = "";

    for (intUserMapIt it = this->_activeUsers.begin(); it != this->_activeUsers.end(); it++)
    {
        if (it->second)
            activeUsers += it->second->getNickname() + ' ';
    }
    return (activeUsers);
}

void                            Server::joinChannel(User * client, Channel * channel)
{
    if (!client || !channel)
        return;

    std::string channelName = channel->getChannelname();
    std::string message;

    client->joinChannel(channel);
    channel->connect(client);

    if (channel->getUserNumber() == 1)
    {
        std::cout << CYAN << client->getNickname() << BLUE << ": created " << YELLOW << channelName << NORMAL << std::endl;
        this->serverSendMessage(client, "Channel joined");
    }
    else
    {
        std::cout << CYAN << client->getNickname() << BLUE << ": JOIN " << YELLOW << channelName << NORMAL << std::endl;
        channel->sendActionMessageToAll("JOIN", client);
    }
    this->commandTOPIC(channel->getChannelname(), client);
    this->commandNAMES(channel->getChannelname(), + client);
}

void                            Server::sendLogo(User * client)
{
    this->serverSendMessage(client, static_cast<std::string>(Logo6));
    this->serverSendMessage(client, static_cast<std::string>(Logo0));
    this->serverSendMessage(client, static_cast<std::string>(Logo1));
    this->serverSendMessage(client, static_cast<std::string>(Logo2));
    this->serverSendMessage(client, static_cast<std::string>(Logo3));
    this->serverSendMessage(client, static_cast<std::string>(Logo4));
    this->serverSendMessage(client, static_cast<std::string>(Logo5));
    this->serverSendMessage(client, static_cast<std::string>(Logo6));
}

void                            Server::sendWelcomeMessage(User *client)
{
    this->serverSendMessage(client, static_cast<std::string>(Logo6));
    this->serverSendMessage(client, static_cast<std::string>(Welcome0));
    this->serverSendMessage(client, static_cast<std::string>(Welcome1));
    this->serverSendMessage(client, static_cast<std::string>(Welcome2));
    this->serverSendMessage(client, static_cast<std::string>(Welcome3));
    this->serverSendMessage(client, static_cast<std::string>(Welcome4));
    this->serverSendMessage(client, static_cast<std::string>(Welcome5));
    this->serverSendMessage(client, static_cast<std::string>(Welcome6));
}

void                            Server::sendGoodByeMessage(User *client)
{
    this->serverSendMessage(client, static_cast<std::string>(Logo6));
    this->serverSendMessage(client, static_cast<std::string>(Goodbye0));
    this->serverSendMessage(client, static_cast<std::string>(Goodbye1));
    this->serverSendMessage(client, static_cast<std::string>(Goodbye2));
    this->serverSendMessage(client, static_cast<std::string>(Goodbye3));
    this->serverSendMessage(client, static_cast<std::string>(Goodbye4));
    this->serverSendMessage(client, static_cast<std::string>(Goodbye5));
    this->serverSendMessage(client, static_cast<std::string>(Goodbye6));
}

//  =============== Send response's                     ===============//

void                            Server::sendClient(std::string messageCode, User * client, std::string message)
{
    if (!client)
        return;

    std::string response = ":" + static_cast<std::string>(ServerHostname) + " " + messageCode + " " + client->getNickname() + " " + message + " \r\n";
    if (send(client->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending response to " << CYAN << client->getNickname() << NORMAL << std::endl;
}

void                            Server::sendMessage(User * sender, User * receiver, std::string message)
{
    if (!receiver || !sender || sender == receiver)
        return;

    std::cout << YELLOW << message << std::endl;
    std::string response = ':' + sender->getNickname() + '!' + sender->getUsername() + "@ircserv PRIVMSG " + receiver->getNickname() + " " + message + " \r\n";
    if (send(receiver->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << receiver->getNickname() << NORMAL << std::endl;
}

void                            Server::serverSendMessage(User * client, std::string message)
{
    if (!client)
        return;

    std::string response = "PRIVMSG " + client->getNickname() + " :" + message + "\r\n";
    if (send(client->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << client->getNickname() << NORMAL << std::endl;
}

void                            Server::sendNotice(User * sender, User * receiver, std::string message)
{
    if (!receiver || !sender || sender == receiver)
        return;

    std::string response = ':' + sender->getNickname() + '!' + sender->getUsername() + '@' + ServerHostname + " NOTICE " + receiver->getNickname() + " " + message + "\r\n";
    if (send(receiver->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << receiver->getNickname() << NORMAL << std::endl;
}

//  =============== Parsing Method's                    ===============//

void                            Server::parseRequest(std::string request, User *client)
{
    if (!client)
        return;

    //  Parse all requests in a request vector array
    strVec                      requestArray;
    std::string                 tempRequest;
    std::string                 COMMAND;
    std::string                 ARG;

    while (request.size() != 0)
    {
        tempRequest = request.substr(0, request.find_first_of('\r'));
        requestArray.push_back(tempRequest);
        if (tempRequest.size() == request.size())
            break;
        request = request.substr(tempRequest.size() + 2, request.npos);
    }

    //  For every request, parse it
    this->_runRequestClient = true;
    for (strVecIt it = requestArray.begin(); it != requestArray.end(); it++)
    {
        if (_runRequestClient == false)
            break;
        tempRequest = *it;
        COMMAND = tempRequest.substr(0, tempRequest.find_first_of(32));

        if (tempRequest.size() > COMMAND.size())
            ARG = tempRequest.substr(COMMAND.size() + 1, tempRequest.npos);
        else
            ARG = "";

        std::cout << CYAN << client->getNickname() << ": " << BLUE << COMMAND << NORMAL << ' ' << ARG << std::endl;

        //  If the command has a prefix, it is from a server.
        //  Since we don't do server to server connection, we drop it.
        if (COMMAND[0] == ':')
        {
            std::cout << RED << "Error: " << NORMAL << "Server to server not supported" << std::endl;
            this->commandNOTFOUND(client);
            return;
        }

        //  Call the right parsing method for all command that we could have
        if (COMMAND == "PASS")
            this->commandPASS(ARG, client);
        else if (COMMAND == "NICK")
            this->commandNICK(ARG, client);
        else if (COMMAND == "USER")
            this->commandUSER(ARG, client);
        else if (COMMAND == "CAP")
            this->commandCAP(ARG, client);
        else if (client->getAuthenticated() == false)
        {
            this->sendClient("503", client, "Command out of sequence\r\n");
            this->disconnectClient(client);
        }
        else if (COMMAND == "QUIT")
            this->commandQUIT(ARG, client);
        else if (COMMAND == "JOIN")
            this->commandJOIN(ARG, client);
        else if (COMMAND == "ISON")
            this->commandISON(ARG, client);
        else if (COMMAND == "PART")
            this->commandPART(ARG, client);
        else if (COMMAND == "HELP")
            this->commandHELP(ARG, client);
        else if (COMMAND == "MODE")
            this->commandMODE(ARG, client);
        else if (COMMAND == "TOPIC")
            this->commandTOPIC(ARG, client);
        else if (COMMAND == "INVITE")
            this->commandINVITE(ARG, client);
        else if (COMMAND == "KICK")
            this->commandKICK(ARG, client);
        else if (COMMAND == "LIST")
            this->commandLIST(ARG, client);
        else if (COMMAND == "NAMES")
            this->commandNAMES(ARG, client);
        else if (COMMAND == "PRIVMSG")
            this->commandPRIVMSG(ARG, client);
        else if (COMMAND == "NOTICE")
            this->commandNOTICE(ARG, client);
        else if (COMMAND == "WHO")
            this->commandPING(ARG, client);
        else if (COMMAND == "PING")
            this->commandPING(ARG, client);
        else if (COMMAND == "PONG")
            this->commandPING(ARG, client);
        else
            this->commandNOTFOUND(client);
    }
    requestArray.clear();
}

std::string                     Server::parseUsername(std::string request, User *client)
{
    std::string username = request.substr(0, request.find_first_of((char) 32));
    request = request.substr(username.size() + 1, request.npos);

    // check for empty username
    if (username == "") {
        std::string errorMessage = "USER : Username cannot be empty";
        sendClient("461", client, errorMessage + "\r\n");
        std::cout << RED << errorMessage << NORMAL << std::endl;
        disconnectClient(client);
        return "";
    }

    // check that each character are valid
    for (unsigned long x = 0; x < username.size(); x++) {
        if (isprint(username[x]) == 0 || isdigit(request[0]) == 0
            || username[x] < 32 || username[x] > 126) {
            std::string errorMessage = "USER : Username contains invalid character";
            Server::sendClient("461", client, errorMessage + "\r\n");
            std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
            disconnectClient(client);
            return "";
        }
    }

    // check that the size is valid
    if (username.size() > 25) {
        std::string errorMessage = "USER : Username is too long";
        sendClient("461", client, errorMessage);
        std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
        disconnectClient(client);
        return "";
    }
    //when everything is valid
    else
        client->setUsername(username);
    return request;
}

std::string                     Server::parseModeAndUnused(std::string request, User *client)
{
    std::string mode = request.substr(0, request.find_first_of((char) 32));
    request = request.substr(mode.size() + 1, request.npos);

    if (mode.size() > 1 || isdigit(mode[0]) == 0) {
        std::string errorMessage = "Error: Invalid User mode";
        sendClient("461", client, errorMessage + "\r\n");
        std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
        disconnectClient(client);
        return "";
    }
    else
        client->setMode(mode);

    //  3) Parse unused
    std::string unused = request.substr(0, request.find_first_of((char) 32));
    request = request.substr(unused.size() + 1, request.npos);

    if (unused.size() > 1 || unused[0] != '*') {
        std::string errorMessage = "Error: Invalid unused parameter";
        sendClient("461", client, errorMessage + "\r\n");
        std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
        disconnectClient(client);
        return "";
    }
    else 
        client->setUnused(unused);
    return request;
}

bool                            Server::parseRealname(std::string request, User *client)
{
     std::string realname = request.substr(0, request.find_first_of(13));

    if (isdigit(request[0])) {
        std::string errorMessage = "Error: The information provided for the User are erroneous; be sure not to include any spaces or unallowed characters";
        sendClient("461", client, errorMessage);
        std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
        disconnectClient(client);

        return false;
    }
    client->setRealname(realname);
    return true;
}

bool                            Server::parseNickname(std::string nickname, User *client)
{
    if (nickname.size() > 15 || nickname.size() < 1) {
        std::string errorMessage = "The nickname cannot be empty, nor cant it be bigger than 15 characters long";
        sendClient("432", client, errorMessage + "\r\n");
        disconnectClient(client);
        std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
        return false;
    }
    if (isdigit(nickname[0])) {
        std::string errorMessage = "The nickname cannot begin with a number";
        sendClient("432", client, errorMessage + "\r\n");
        disconnectClient(client);
        std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
        return false;
    }
    for (unsigned long i = 0; i < nickname.size(); i++) {
        if ((isalpha(nickname[i]) == 0)
                && (isdigit(nickname[i]) == 0)
                && nickname[i] != '-'
                && nickname[i] != '_'
                && nickname[i] != '['
                && nickname[i] != ']') {
            std::string errorMessage = "The nickname can only contain letters, numbers, \'-\', \'_\', \']\' or \'[\'";
            sendClient("432", client, errorMessage + "\r\n");
            disconnectClient(client);
            std::cout << RED << "Error: " << BLUE << errorMessage << NORMAL << std::endl;
            return false;
        }
    }
    return true;
}

bool                            Server::parseChannelname(std::string channelname)
{
    if (channelname[0] && channelname[0] != '#')
    {
        std::cout << RED << "Error:" << BLUE << " channel name must start with a #" << std::endl;
        return (false);
    }

    if (channelname.size() > 200 || channelname.size() < 5)
    {
        std::cout << RED << "Error:" << BLUE << " channel name must be between 5 and 200 characters" << std::endl;
        return (false);
    }

    if (channelname.find_first_of(" ,") != channelname.npos)
    {
        std::cout << RED << "Error: " << BLUE << channelname[channelname.find_first_of(" ,")] << " is not a valid character in a channel name." << std::endl;
        return (false);
    }
    return (true);
}

strVec                          Server::parseModeCommand(std::string request, strVec params, User *client)
{
    std::istringstream ss(request);
    std::string temp;

    while (getline(ss, temp, ' '))
    {
        params.push_back(temp);
    }

    if (params.size() == 1)
        return (params);

    if (params.at(0)[0] != '#')
    {
        this->sendClient("403", client, params.at(0) + " :No # as first character\r\n");
        std::cout << RED "Error: " << NORMAL << "not a channel (no #)" << std::endl;
        params.at(0) = "ERROR";
        return params;
    }
    
    if (!this->parseChannelname(params.at(0)))
    {
        this->sendClient("403", client, params.at(0) + " :invalid channel parsing\r\n");
        std::cout << RED "Error: " << NORMAL << "channel name invalid" << std::endl;
        params.at(0) = "ERROR";
        return params;
    }

    channelMapIt it = this->_channels.find(params.at(0));
    if (it == this->_channels.end() || !it->second)
    {
        this->sendClient("403", client, params.at(0) + " :No such channel\r\n");
        std::cout << RED << "Error: " << NORMAL << "MODE channel dosen't exist on the server" << std::endl;
        params.at(0) = "ERROR";
        return params;
    }

    if (!it->second->clientIsOp(client))
    {
        this->sendClient("482", client, it->second->getChannelname() + ":You're not channel operator\r\n");
        std::cout << RED "Error: " << NORMAL << "MODE: user is not an operator." << std::endl;
        params.at(0) = "ERROR";
        return params;
    }

    if (params.at(1)[0] != '+' && params.at(1)[0] != '-')
    {
        std::cout << RED "Error: " << NORMAL << "MODE: Invalid mode (no - / +)" << std::endl;
        this->sendClient("461", client, "MODE :invalid mode input (no -/+)\r\n");
        params.at(0) = "ERROR";
        return params;
    }

    return params;
}

//  Take the uint8_t request and return a string of it
std::string                     Server::requestToString(uint8_t *request) const
{
    std::string     strRqu((char *)request);
    return (strRqu);
}

bool                            Server::modeCodeValid(std::string modeCode)
{
    int         requireInputCount = 0;
    std::string letters = "";

    for (size_t i = 0; i < modeCode.size(); i++)
    {
        if (!this->modeLetterValid(modeCode[i]))
            return (false);
        if (this->modeNeedArg(modeCode[i]))
            requireInputCount++;
        if (letters.find_first_of("pitnmlkbos") != letters.npos)
            return (false);
        letters += modeCode[i];
    }
    if (requireInputCount > 1)
        return (false);
    return (true);
}

bool                            Server::modeNeedArg(char c)
{
    if (c == 'b' || c == 'o' || c == 'k' || c == 'l')
        return (true);
    return (false);
}

bool                            Server::modeLetterValid(char c)
{
    if (c == 'p' || c == 'i' || c == 't' || c == 'n' || c == 'm' || c == 'l' || c == 'k' || c == 'b' || c == 'o' || c == 's')
        return (true);
    return (false);
}

//  =============== Master socket creation              ===============//

//  Create the socketFD (listenFD)
void                            Server::createSocket(void)
{
    //  AF_INET -> IPV4 / SOCK_STREAM -> connection stream fast / 0 -> TCP requests
    int     socketFD = socket(AF_INET, SOCK_STREAM, 0);

    //  Set socket option
    int i = 1;
    setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));
    setsockopt(socketFD, SIGPROTECTION, SO_REUSEADDR, &i, sizeof(int));

    //  Throw error if it occurs.
    if (socketFD < 0)
    {
        std::cout << RED << "Error: " << BLUE << "on socket creation" << NORMAL << std::endl;
        throw socketCreationFailed();
    }
    this->_masterSocket = socketFD;
}

//  Setup socket address data
void                            Server::setupSocketAddress(void)
{
    //  Set all the address to 0 to avoid unterminated by NULL
    bzero(&_servAddr, sizeof(_servAddr));

    //  IPV4 socket type
    _servAddr.sin_family = AF_INET;

    //  Accept any addresses
    _servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //  Setup the port of the socket
    _servAddr.sin_port = htons(_port);
}

//  Bind the address with the listen FD
void                            Server::bindAddrSock(void)
{
    int bindResponse = bind(_masterSocket, (struct sockaddr *) &_servAddr, sizeof(_servAddr));

    //  If it failed, throw an exception
    if (bindResponse < 0)
    {
        std::cout << RED << "Error: " << BLUE << "on binding address to socket" << NORMAL << std::endl;
        throw bindingFailed();
    }
}

//  Start socket listening
void                            Server::startListening(void)
{
    int socketResponse = listen(_masterSocket, 10);

    if (socketResponse < 0)
    {
        std::cout << RED << "Error: " << BLUE << "on starting the listening on master socket." << NORMAL << std::endl;
        throw listeningFailed();
    }
}
