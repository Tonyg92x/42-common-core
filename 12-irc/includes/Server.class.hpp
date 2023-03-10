/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:00:54 by aguay             #+#    #+#             */
/*   Updated: 2023/02/02 09:05:42 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"

class User;
class Channel;

class Server
{
    //  =============== Public methodes                 ===============//

    public:
        Server(int port, std::string password);
        ~Server(void);
        Server(Server const & rhs);

        Server                              &operator=(Server const & rhs);

        int                                 getPort(void) const;
        std::string                         getPassword(void) const;
        void                                start(void);

    //  =============== Attributs                       ===============//

    private:
        int                                 _port;
        int                                 _runLoop;
        std::string                         _password;
        int                                 _masterSocket;
        struct sockaddr_in                  _servAddr;
        uint8_t                             _receivedLine[MAXLINE + 1];
        fd_set                              _current_sockets;
        fd_set                              _ready_sockets;
        std::map<int, User *>               _activeUsers;
        std::map<std::string, User *>       _inactiveUsers;
        std::map<std::string, Channel *>    _channels;
        bool                                _runRequestClient;

    //  =============== Construction setup-validation   ===============//
    private:
        void                                createSocket(void);
        void                                setupSocketAddress(void);
        void                                bindAddrSock(void);
        void                                startListening(void);

    //  =============== Methodes                        ===============//
    private:
    
        //  Parsing
        void                                parseRequest(std::string request, User *client);
        std::string                         parseUsername(std::string request, User *client);
        std::string                         parseModeAndUnused(std::string request, User *client);
        bool                                parseRealname(std::string request, User *client);
        bool                                parseNickname(std::string nickname, User *client);
        bool                                parseChannelname(std::string channelname);
        strVec                              parseModeCommand(std::string request, std::vector<std::string> params, User *client);
        std::string                         requestToString(uint8_t *request) const;
        strVec                              parseArg(std::string requestArg);
        bool                                modeCodeValid(std::string modeCode);
        bool                                modeLetterValid(char c);
        bool                                modeNeedArg(char c);

        //  Tools
        void                                disconnectClient(User * client);
        User *                              getInactiveUser(std::string nickname);
        User *                              getActiveUser(std::string nickname);
        Channel *                           getChannel(std::string channelname);
        std::string                         getActiveUsers(void);
        void                                joinChannel(User * client, Channel * channel);
        void                                sendLogo(User *client);
        void                                sendWelcomeMessage(User *client);
        void                                sendGoodByeMessage(User *client);

        //  Command's
        void                                commandCAP(std::string request, User *client);
        void                                commandHELP(std::string request, User *client);
        void                                commandINVITE(std::string request, User *client);
        void                                commandISON(std::string request, User *client);
        void                                commandJOIN(std::string request, User *client);
        void                                commandKICK(std::string request, User *client);
        void                                commandLIST(std::string request, User *client);
        void                                commandMODE(std::string request, User *client);
        void                                commandMODEChannel(std::vector<std::string> params, User *client);
        void                                commandNAMES(std::string request, User *client);
        void                                commandNICK(std::string request, User *client);
        void                                commandNOTFOUND(User *client);
        void                                commandNOTICE(std::string request, User *client);
        void                                commandPART(std::string request, User *client);
        void                                commandPASS(std::string request, User *client);
        void                                commandPING(std::string request, User *client);
        void                                commandPONG(std::string request, User *client);
        void                                commandPRIVMSG(std::string request, User *client);
        void                                commandQUIT(std::string request, User *client);
        void                                commandTOPIC(std::string request, User *client);
        void                                commandUSER(std::string request, User *client);

        //  Send response
        void                                sendClient(std::string messageCode, User *client, std::string message);
        void                                sendMessage(User * sender, User * receiver, std::string message);
        void                                serverSendMessage(User * client, std::string message);
        void                                sendNotice(User * sender, User * receiver, std::string message);
        
    //  =============== Exception                       ===============//
    private:
        class   socketCreationFailed : public std::exception
        {
            public:
                virtual const char  * what() const throw()
                {
                    return ("\033[31mSocket creation failed.\033[0m");
                }
        };

        class   bindingFailed : public std::exception
        {
            public:
                virtual const char  * what() const throw()
                {
                    return ("\033[31mSocket address and socketfd binding failed.\033[0m");
                }
        };

        class   listeningFailed : public std::exception
        {
            public:
                virtual const char  * what() const throw()
                {
                    return ("\033[31mListening on socket failed.\033[0m");
                }
        };

        class   readingSocket : public std::exception
        {
            public:
                virtual const char  * what() const throw()
                {
                    return ("\033[31mReading the socket failed.\033[0m");
                }
        };

        class   selectFailed : public std::exception
        {
            public:
                virtual const char  * what() const throw()
                {
                    return ("\033[31mSelect call failed.\033[0m");
                }
        };
};

#include "User.class.hpp"
#include "Channel.class.hpp"
