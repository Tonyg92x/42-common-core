/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 06:34:30 by aguay             #+#    #+#             */
/*   Updated: 2023/01/29 19:16:56 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.class.hpp"

//  =============== Identity control                    ===============//

User::User(int fd) : _userFd(fd)
{
    this->_username = "";
    this->_nickname = "";
    this->_mode = "";
    this->_realname = "";
    this->_unused = "*";
    this->_incompleteRequest = "";
    this->_passwordStatus = false;
    this->_isAuthenticated = false;
    this->_channelNumber = 0;
};

User::User(User const & rhs) : _userFd(rhs.getUserFd()) {*this = rhs;}

User & User::operator=(User const & rhs)
{
    if (this != &rhs)
    {
        this->_username = rhs.getUsername();
        this->_nickname = rhs.getNickname();
        this->_mode = rhs.getMode();
        this->_realname = rhs.getRealname();
        this->_unused = rhs.getUnused();
    }
    return (*this);
}

//  TODO: make sure everything is free when destroyed
User::~User(void) {_channelList.clear();}


//  =============== Methodes                            ===============//

void            User::joinChannel(Channel * theChannel)
{
    if (!theChannel)
        return;

    this->_channelList.insert(std::pair<std::string, Channel *>(theChannel->getChannelname(), theChannel));
    this->_channelNumber++;
}

void            User::leaveChannel(std::string channelname)
{
    this->_channelList.erase(channelname);
    this->_channelNumber--;
}

void            User::disconnectAllChannels(void)
{
    for (channelMapIt it = this->_channelList.begin(); it != this->_channelList.end(); it++)
    {
        if (it->second)
            it->second->disconnect(this);
    }
}

//  =============== Getter's                            ===============//

std::string     User::getUsername(void) const {return (this->_username);}

std::string     User::getNickname(void) const
{
    if (this->_nickname == "")
        return(std::to_string(this->getUserFd()));
    return (this->_nickname);
}

std::string     User::getMode(void) const {return (this->_mode);}

std::string     User::getRealname(void) const {return (this->_realname);}

std::string     User::getUnused(void) const {return (this->_unused);}

int             User::getUserFd(void) const {return (this->_userFd);}

bool            User::getPasswordStatus(void) const {return (this->_passwordStatus);}

bool            User::getAuthenticated(void) const { return (this->_isAuthenticated);}

ssize_t         User::getChannelNumber(void) const { return (this->_channelNumber);}

std::string     User::getIncompleteRequest(void) const {return (this->_incompleteRequest);}

//  =============== Setter's                            ===============//

void            User::setAuthenticated(bool value) {this->_isAuthenticated = value;}

void            User::setUsername(std::string const & name) {this->_username = name;}

void            User::setNickname(std::string const & nickname) {this->_nickname = nickname;}

void            User::setMode(std::string const & mode) {this->_mode = mode;}

void            User::setRealname(std::string const & realname) {this->_realname = realname;}

void            User::setUnused(std::string const & unused) {this->_unused = unused;}

void            User::setPasswordStatus(bool status) {this->_passwordStatus = status;}

void            User::setUserFd(int fd) {this->_userFd = fd;}

void            User::setIncompleteRequest(std::string newIncomplete)
{
    this->_incompleteRequest = newIncomplete;
}
