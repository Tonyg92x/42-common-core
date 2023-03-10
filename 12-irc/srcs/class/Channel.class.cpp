/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigneau <jvigneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 07:09:30 by aguay             #+#    #+#             */
/*   Updated: 2023/02/01 16:22:46 by jvigneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.class.hpp"

//  =============== Identity control                    ===============//

Channel::Channel(std::string channelname, User * owner)
{
    if (!owner)
        return;

    this->_owner = owner;
    this->_channelname = channelname;
    this->_nbUser = 0;
    this->_key = "";
    this->_topic = ": no topic";

    this->addToOp(owner);
    this->addToUser(owner);
    this->addToWriteRight(owner);

    this->_userLimit = 9999999;
    this->_modeP = false;   // Private
    this->_modeS = false;   // Secret
    this->_modeI = false;   // Invite
    this->_modeT = false;   // Topic lock
    this->_modeN = false;   // message visibility
    this->_modeM = false;   // Only allow op to speak
    this->_modeL = false;   // Set a user limit for the channel
    this->_modeK = false;   // Key mode
    this->sendActionMessage("JOIN", owner, owner);
}

Channel::~Channel(void) {};

//  =============== Getter's                            ===============//

std::string     Channel::getChannelname(void) const {return (this->_channelname);}

ssize_t         Channel::getUserNumber(void) const {return (this->_nbUser);}

std::string     Channel::getClientList(void)
{
    std::string list = "";

    for (std::map<std::string, User *>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
        list += it->second->getNickname() + " ";

    return (list);
}

std::string     Channel::getTopic(void) const {return (this->_topic);}

bool            Channel::getModeP(void) const {return (this->_modeP);}

bool            Channel::getModeS(void) const {return (this->_modeS);}

bool            Channel::getModeI(void) const {return (this->_modeI);}

bool            Channel::getModeT(void) const {return (this->_modeT);}

bool            Channel::getModeN(void) const {return (this->_modeN);}

bool            Channel::getModeM(void) const {return (this->_modeM);}

bool            Channel::getModeL(void) const {return (this->_modeL);}

bool            Channel::getModeK(void) const {return (this->_modeK);}

//  =============== Setter's                            ===============//

void            Channel::setModeP(bool value) {this->_modeP = value;}

void            Channel::setModeS(bool value) {this->_modeS = value;}

void            Channel::setModeI(bool value) {this->_modeI = value;}

void            Channel::setModeT(bool value) {this->_modeT = value;}

void            Channel::setModeN(bool value) {this->_modeN = value;}

void            Channel::setModeM(bool value) {this->_modeM = value;}

void            Channel::setModeL(bool value) {this->_modeL = value;}

void            Channel::setModeK(bool value) {this->_modeK = value;}

void            Channel::setTopic(User * setter, std::string topic)
{
    if (!setter)
        return; //  TODO: send fail response ?

    if (this->_modeT && !this->clientIsOp(setter))
        return; //  TODO: send error if T mode is active and not op
    this->_topic = topic;
    for (strUserMapIt it = this->_users.begin(); it != this->_users.end(); it++)
        this->sendClient("332", it->second, this->getChannelname() + ": " + topic + " \r\n");
}

void            Channel::setKey(User * setter, std::string key)
{
    if (!setter)
        return;

    if (!this->_modeK)
        return; //  TODO: send mode k not active ?

    //  TODO: add strongh key policy?
    if (this->clientIsOp(setter))
        this->_key = key;
}

void            Channel::inviteUser(User * inviter, User * invited)
{
    if (!inviter || !invited || inviter == invited)
        return;

    if (!this->clientIsOp(inviter) || !this->clientIsOp(inviter))
        return;

    this->_inviteList.insert(std::pair<std::string, User *>(invited->getNickname(), invited));
}

void            Channel::addOp(User * newOp)
{
    if (!newOp)
        return;
    this->addToOp(newOp);
}

void            Channel::revokeOp(User * oldOp)
{
    if (!oldOp)
        return;
    this->removeOp(oldOp->getNickname());
}

//  =============== Tools                               ===============//

void            Channel::connect(User * client)
{
    if (!client)
    {
        std::cout << RED << "Error: " << NORMAL << "client pointer protection at channel connect" << std::endl;
        return; 
    }
    if (this->_modeS)
    {
        if (!this->isInvited(client))
        {
            std::cout << RED << "Error: " << NORMAL << "mode secret activated and user not invited" << std::endl;
            this->sendClient("473", client, this->getChannelname() + " :No such channel\r\n");
            return;
        }
        this->_inviteList.erase(client->getNickname());
        this->addToUser(client);
        this->sendActionMessageToAll("JOIN", client);
        return;
    }
    if (clientIsInBanList(client))
    {
         if (!this->isInvited(client))
        {
            std::cout << RED << "Error: " << NORMAL << "You are banned on this channel :( " << std::endl;
            this->sendClient("473", client, this->getChannelname() + " :Cannot join channel (banned) \r\n");
            return;
        }
    }

    if (this->_modeL)
    {
        if (this->_nbUser >= this->_userLimit)
        {
            std::cout << RED << "Error: " << NORMAL << "mode l activated and user limit reached" << std::endl;
            this->sendClient("473", client, this->getChannelname() + " :Cannot join channel (+l) \r\n");
            return;
        }
    }
    if (this->_modeI || this->_modeP)
    {
        if (!this->isInvited(client))
        {
            std::cout << RED << "Error: " << NORMAL << "mode i activated and user is not invited" << std::endl;
            this->sendClient("473", client, this->getChannelname() + " :Cannot join channel (+i) \r\n");
            return;
        }
        this->_inviteList.erase(client->getNickname());
        this->addToUser(client);
        this->sendActionMessageToAll("JOIN", client);
        return;
    }
    this->addToUser(client);
    this->sendActionMessageToAll("JOIN", client);
}

//  Delete the user of the list of users
void            Channel::disconnect(User * client)
{
    if (this->clientInChannel(client))
    {
        this->sendActionMessageToAll("PART ", client);
        this->removeUser(client);
    }
}

void            Channel::sendToAll(User * sender, std::string message)
{
    if (!sender)
        return;
    for (strUserMapIt it = this->_users.begin(); it != this->_users.end(); it++)
    {
        this->sendMessage(sender, it->second, message);
    }
}

void            Channel::sendNoticeToAll(User * sender, std::string message)
{
    if (!sender)
        return;
    for (strUserMapIt it = this->_users.begin(); it != this->_users.end(); it++)
    {
        this->sendNotice(sender, it->second, message);
    }
}

void            Channel::sendActionMessageToAll(std::string action, User * executor)
{
    if (!executor)
        return;

    for (strUserMapIt it = this->_users.begin(); it != this->_users.end(); it++)
    {
        if (it->second)
            this->sendActionMessage(action, executor, it->second);
    }
}

void            Channel::sendModeChange(void)
{
    for (strUserMapIt it = this->_users.begin(); it != this->_users.end(); it++)
    {
        if (it->second)
            this->sendClient("324", it->second, this->getChannelname() + " " + this->getModeList() + " \r\n");
    }
}

bool            Channel::keyValid(std::string key)
{
    if (key != this->_key)
        return (false);
    return (true);
}

bool            Channel::clientIsOwner(User * client)
{
    if (client == _owner)
        return true;
    return false;

}
bool            Channel::clientInChannel(User * client)
{
    if (!client)
        return (false);

    strUserMapIt it = _users.find(client->getNickname());

    if (it != _users.end())
        return (true);
    return (false);
}

bool            Channel::clientIsOp(User * client)
{
    if (!client)
        return (false);

    strUserMapIt op = this->_operators.find(client->getNickname());

    if (op != this->_operators.end())
        return (true);
    return (false);
}

bool            Channel::clientHasWriteRight(User * client)
{
    if (!client)
        return (false);

    strUserMapIt wriRight = this->_writeRight.find(client->getNickname());

    if (wriRight != this->_writeRight.end())
        return (true);
    return (false);
}

std::string     Channel::getModeList(void)
{
    std::string retour = "+";

    if (this->getModeP())
        retour += 'p';
    if (this->getModeS())
        retour += 's';
    if (this->getModeI())
        retour += 'i';
    if (this->getModeT())
        retour += 't';
    if (this->getModeN())
        retour += 'n';
    if (this->getModeM())
        retour += 'm';
    if (this->getModeL())
        retour += 'l';
    if (this->getModeK())
        retour += 'k';

    if (retour.size() == 1)
        retour = "none";
    return (retour);
}

//  =============== Private methodes                    ===============//

bool            Channel::isUser(std::string nickname)
{
    strUserMapIt it = _users.find(nickname);

    if (it != _users.end())
        return (true);
    return (false);
}

bool            Channel::isOperator(std::string nickname)
{
    strUserMapIt it = _operators.find(nickname);

    if (it != _operators.end())
        return (true);
    return (false);
}

bool            Channel::isWriteRight(std::string nickname)
{
    strUserMapIt it = _operators.find(nickname);

    if (it != _writeRight.end())
        return (true);
    return (false);
}

void            Channel::sendClient(std::string messageCode, User * client, std::string message)
{
    if (!client)
        return;

    std::string response = ":" + static_cast<std::string>(ServerHostname) + " " + messageCode + " " + client->getNickname() + " " + message;
    if (send(client->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending response to " << CYAN << client->getNickname() << NORMAL << std::endl;
}

void            Channel::sendMessage(User * sender, User * receiver, std::string message)
{
    if (!sender || !receiver || sender == receiver)
        return;

    std::string nickname;
    
    if (sender == this->_owner)
        nickname = "Owner~" + sender->getNickname();
    else if (this->isOperator(sender->getNickname()))
        nickname = "Operator~" + sender->getNickname();
    else if (this->isUser(sender->getNickname()))
        nickname = "Member~" + sender->getNickname();
    else
        nickname = sender->getNickname();
    std::string response = ':' + nickname + '!' + sender->getUsername() + "@ircserv PRIVMSG " + this->getChannelname() + " " + message + " \r\n";
    if (send(receiver->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << receiver->getNickname() << NORMAL << std::endl;
}

void            Channel::sendActionMessage(std::string action, User * executor, User * receiver)
{
    if (!executor || !receiver)
        return;
    
    std::string message = ':' + executor->getNickname() + ' ' + action + " " + this->getChannelname() + "\r\n";

    if (send(receiver->getUserFd(), message.c_str(), message.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << receiver->getNickname() << NORMAL << std::endl;
}

void            Channel::sendNotice(User * sender, User * receiver, std::string message)
{
    if (!receiver || !sender || sender == receiver)
        return;

    std::string nickname;
    
    if (sender == this->_owner)
        nickname = "Owner~" + sender->getNickname();
    else if (this->isOperator(sender->getNickname()))
        nickname = "Operator~" + sender->getNickname();
    else if (this->isUser(sender->getNickname()))
        nickname = "Member~" + sender->getNickname();
    else
        nickname = sender->getNickname();

    std::string response = ':' + nickname + '!' + sender->getUsername() + '@' + ServerHostname + " NOTICE " + receiver->getNickname() + " " + message + "\r\n";
    if (send(receiver->getUserFd(), response.c_str(), response.size(), SIGPROTECTION) < 0)
        std::cout << RED << "Error: " << BLUE << "on sending data to " << CYAN << receiver->getNickname() << NORMAL << std::endl;
}

void            Channel::changeNickname(std::string nickname, User *client, std::string oldNickname)
{
    if (!client)
        return;
    strUserMapIt it = _users.find(oldNickname);

    if (it != _users.end())
    {
        strUserMapIt itOp = _operators.find(oldNickname);

        if (itOp != _users.end())
        {
            _operators.insert(std::pair<std::string, User *>(nickname, client));
            _operators.erase(oldNickname);
        }

        this->_users.insert(std::pair<std::string, User *>(nickname, client));
        this->_users.erase(oldNickname);
    }
}

void            Channel::addToUser(User * client)
{
    if (!client)
        return;

    this->_users.insert(std::pair<std::string, User *>(client->getNickname(), client));
    this->_nbUser++;
}

void            Channel::addToOp(User * client)
{
    if (!client)
        return;

    this->_operators.insert(std::pair<std::string, User *>(client->getNickname(), client));
    this->sendToAll(client, "newOperator \r\n");
    std::string message = ':' + client->getNickname() + '!' + client->getUsername() + "@ircserv PRIVMSG " + this->getChannelname() + " " + "newOperator" + " \r\n";
    send(client->getUserFd(), message.c_str(), message.size(), SIGPROTECTION);
}

void            Channel::addToWriteRight(User * client)
{
    if (!client)
        return;

    this->_writeRight.insert(std::pair<std::string, User *>(client->getNickname(), client));
}

void            Channel::addToBanList(std::string username, User *client)
{
    if (!client)
        return;
    _banList.insert(std::pair<std::string, User *>(username, client));
}

bool            Channel::clientIsInBanList(User *client)
{
    strUserMapIt it = _banList.begin();
    strUserMapIt end = _banList.end();

    while (it != end)
    {
        if (it->second->getUsername() == client->getUsername())
            return true;
        it++;
    }
    return false;
}

void            Channel::removeUser(User * client)
{
    if (!client)
        return;

    std::string nickname = client->getNickname();
    this->_users.erase(client->getNickname());
    this->_nbUser--;

    if (this->isOperator(nickname))
        this->removeOp(nickname);
    if (this->isWriteRight(nickname))
        this->removeWriteRight(nickname);
}

void            Channel::removeFromBanList(std::string username)
{
    this->_banList.erase(username);
}

void            Channel::removeOp(std::string nickname)
{
    this->_operators.erase(nickname);

    if (this->_operators.size() < 1)
    {
        if (this->_users.size() < 1)
        {
            this->_nbUser = 0;
            return; // If there is no user in the channel, return and server will delete the channel
        }
        else
        {
            strUserMapIt it = this->_users.begin();
            User * newOp = it->second;

            if (newOp)
            {
                std::cout << CYAN << newOp->getNickname() << BLUE << ": has been promoted to operator in the channel " << YELLOW << this->getChannelname() << NORMAL << std::endl;
                this->addToOp(newOp);
            }
        }
    }

      //  If the user is the owner, pass ownership
    if (this->_owner->getUsername() == nickname)
    {
        if (this->_operators.size() > 0) 
        {
            // If there is another operator(s), passe ownership to the oldest one
            strUserMapIt it1 = this->_operators.begin();
            User *  newOwner = it1->second;

            if (newOwner) // Protection
            {
                this->_owner = newOwner;
                std::cout << CYAN << newOwner->getNickname() << BLUE << ": has been promoted to owner of the channel " << YELLOW << this->getChannelname() << NORMAL << std::endl;
                this->sendToAll(newOwner, "newOwner \r\n");
                std::string message = ':' + newOwner->getNickname() + '!' + newOwner->getUsername() + "@ircserv PRIVMSG " + this->getChannelname() + " " + "newOwner" + " \r\n";
                send(newOwner->getUserFd(), message.c_str(), message.size(), SIGPROTECTION);
            }
        }
        else    //  No op / owner error -> delete chan
        {
            this->_nbUser = 0;
            return;
        }
    }
}

void            Channel::setUserLimit(User * setter, int limit)
{
    if (!this->clientIsOp(setter))
        return;

    this->_userLimit = limit;
}

void            Channel::removeWriteRight(std::string nickname) {this->_writeRight.erase(nickname);}

bool            Channel::isInvited(User * user)
{
    strUserMapIt it = this->_inviteList.find(user->getNickname());

    if (it != this->_inviteList.end())
        return (true);
    return(false);
}
