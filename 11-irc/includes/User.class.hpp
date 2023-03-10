/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:29:39 by jvigneau          #+#    #+#             */
/*   Updated: 2023/01/29 19:12:01 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"

class Channel;

class User {
    public :
        User(int fd);
        User(User const & rhs);
        User& operator=(User const &rhs);
        virtual ~User(void);


    //  =============== Getter's                            ===============//
    public:
        int                                     getUserFd(void) const;
        std::string                             getUsername(void) const;
        std::string                             getNickname(void) const;
        std::string                             getMode(void) const;
        std::string                             getRealname(void) const;
        std::string                             getUnused(void) const;
        bool                                    getPasswordStatus(void) const;
        bool                                    getAuthenticated(void) const;
        ssize_t                                 getChannelNumber(void) const;
        std::string                             getIncompleteRequest(void) const;

    //  =============== Setter's                            ===============//
    public:
        void                                    setUsername(std::string const & name);
        void                                    setNickname(std::string const & nickName);
        void                                    setMode(std::string const & mode);
        void                                    setRealname(std::string const & realName);
        void                                    setUnused(std::string const & unused);
        void                                    setPasswordStatus(bool status);
        void                                    setUserFd(int fd);
        void                                    setAuthenticated(bool value);
        void                                    setIncompleteRequest(std::string newIncomplete);

    //  =============== Methodes                            ===============//
    public:
        void                                    joinChannel(Channel * theChannel);
        void                                    leaveChannel(std::string channelname);
        void                                    disconnectAllChannels(void);

    private :
        int                                     _userFd;
        std::string                             _nickname;
        std::string                             _username;
        std::string                             _mode;
        std::string                             _unused;
        std::string                             _realname;
        std::map<std::string, Channel *>        _channelList;
        std::string                             _incompleteRequest;
        ssize_t                                 _channelNumber;
        bool                                    _isAuthenticated;
        bool                                    _passwordStatus;
        User(void);
};

#include "Channel.class.hpp"
