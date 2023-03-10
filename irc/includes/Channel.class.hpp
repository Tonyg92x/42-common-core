/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigneau <jvigneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 06:27:16 by aguay             #+#    #+#             */
/*   Updated: 2023/02/01 16:21:10 by jvigneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"

class User;

class Channel
{
    public:
        Channel(std::string channelName, User * owner);
        ~Channel(void);

    //  =============== Getter's                        ===============//
    public:
        std::string                         getChannelname(void) const;
        ssize_t                             getUserNumber(void) const;
        std::string                         getClientList(void);
        std::string                         getTopic(void) const;
        bool                                getModeP(void) const;
        bool                                getModeS(void) const;
        bool                                getModeI(void) const;
        bool                                getModeT(void) const;
        bool                                getModeN(void) const;
        bool                                getModeM(void) const;
        bool                                getModeL(void) const;
        bool                                getModeK(void) const;

    //  =============== Setter's                        ===============//
    public:
        void                                setModeP(bool value);
        void                                setModeS(bool value);
        void                                setModeI(bool value);
        void                                setModeT(bool value);
        void                                setModeN(bool value);
        void                                setModeM(bool value);
        void                                setModeL(bool value);
        void                                setModeK(bool valued);

    //  =============== Public methodes                 ===============//
    public:
        void                                connect(User * client);
        void                                disconnect(User * client);
        bool                                clientInChannel(User * client);
        bool                                clientIsInBanList(User *client);
        bool                                clientIsOp(User * client);
        bool                                clientIsOwner(User *client);
        bool                                clientHasWriteRight(User * client);
        void                                sendToAll(User * sender, std::string message);
        void                                sendNoticeToAll(User * sender, std::string message);
        void                                sendActionMessageToAll(std::string action, User * executor);
        void                                setTopic(User * setter, std::string topic);
        void                                setUserLimit(User * setter, int limit);
        void                                setKey(User * setter, std::string key);
        void                                addOp(User * newOp);
        void                                revokeOp(User * oldOp);
        void                                removeFromBanList(std::string username);
        bool                                keyValid(std::string key);
        void                                inviteUser(User * inviter, User * invited);
        void                                sendModeChange(void);
        void                                addToBanList(std::string realname, User *client);
        std::string                         getModeList(void);
        void                                changeNickname(std::string nickname, User *client, std::string oldNickname);

    //  =============== Private methodes                ===============//
    private:
        bool                                isUser(std::string nickname);
        bool                                isOperator(std::string nickname);
        bool                                isWriteRight(std::string nickname);
        bool                                isInvited(User * user);
        void                                sendClient(std::string messageCode, User * client, std::string message);
        void                                sendMessage(User *sender, User *receiver, std::string message);
        void                                sendActionMessage(std::string action, User * executor, User * receiver);
        void                                sendNotice(User * sender, User * receiver, std::string message);
        void                                addToUser(User * client);
        void                                addToOp(User * client);
        void                                addToWriteRight(User * client);
        void                                removeUser(User * client);
        void                                removeOp(std::string nickname);
        void                                removeWriteRight(std::string nickname);

    //  =============== Attributs                       ===============//
    private:
        std::string                         _channelname;
        User *                              _owner;
        ssize_t                             _nbUser;
        int                                 _userLimit;
        std::string                         _topic;
        std::string                         _key;
        strUserMap                          _users;
        strUserMap                          _operators;
        strUserMap                          _writeRight;
        strUserMap                          _inviteList;
        strUserMap                          _banList;


        // std::map<std::string, std::string>  _userModeInChannel;

    //  =============== Channel mode                    ===============//
    private:
        bool                                _modeP; // private channel flag;
        bool                                _modeS; // secret channel flag;
        bool                                _modeI; // invite-only channel flag;
        bool                                _modeT; // topic settable by channel operator only flag;
        bool                                _modeN; // no messages to channel from clients on the outside;
        bool                                _modeM; // moderated channel (message send only per op or visible user);
        bool                                _modeL; // set the user limit to channel;
        bool                                _modeK; // set a channel key (password).

    //  =============== Hidden canonical form           ===============//
    private:
        Channel();
        Channel(Channel const & rhs);
        Channel                             &operator=(Channel const & rhs);
};

#include "User.class.hpp"
