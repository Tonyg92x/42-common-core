/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:16:26 by aguay             #+#    #+#             */
/*   Updated: 2023/02/02 09:10:17 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  =============== Autorised fonctions import  ===============//

# ifndef SIGPROTECTION
#  define SIGPROTECTION SO_NOSIGPIPE
# endif

#pragma once

#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>       //  We can use an other fonction for poll

//  =============== C++ 98 import               ===============//

#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <vector>
#include <stdbool.h>
#include <stdio.h>
#include <sstream>

//  =============== Colors import               ===============//

#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define PINK "\033[35m"
#define GREY "\033[37m"
#define CYAN "\033[36m"
#define UNDERLINE "\033[4m"
#define NORMAL "\033[0m"

//  =============== Define                      ===============//

//  Buffer size
#define MAXLINE 4096 // Max size of a IRC message is 512 byte

#define strUserMap std::map<std::string, User *>
#define strUserMapIt std::map<std::string, User *>::iterator

#define intUserMap std::map<int, User *>
#define intUserMapIt std::map<int, User *>::iterator

#define channelMap std::map<std::string, Channel *>
#define channelMapIt std::map<std::string, Channel *>::iterator

#define strVec std::vector<std::string>
#define strVecIt std::vector<std::string>::iterator

//  Change this to change hostname of the IRC server
#define ServerHostname "ircserv"

#define Logo0 "███╗   ███╗ █████╗ ███████╗██╗  ██╗██╗  ██╗     ██████╗██╗  ██╗ █████╗ ████████╗"
#define Logo1 "████╗ ████║██╔══██╗██╔════╝██║  ██║██║ ██╔╝    ██╔════╝██║  ██║██╔══██╗╚══██╔══╝"
#define Logo2 "██╔████╔██║███████║███████╗███████║█████╔╝     ██║     ███████║███████║   ██║   "
#define Logo3 "██║╚██╔╝██║██╔══██║╚════██║██╔══██║██╔═██╗     ██║     ██╔══██║██╔══██║   ██║   "
#define Logo4 "██║ ╚═╝ ██║██║  ██║███████║██║  ██║██║  ██╗    ╚██████╗██║  ██║██║  ██║   ██║   "
#define Logo5 "╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   "
#define Logo6 "                                                                                "

#define Welcome0 "██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗"
#define Welcome1 "██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝"
#define Welcome2 "██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  "
#define Welcome3 "██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  "
#define Welcome4 "╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗"
#define Welcome5 " ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝"
#define Welcome6 "                                                              "

#define Goodbye0 " ██████╗  ██████╗  ██████╗ ██████╗ ██████╗ ██╗   ██╗███████╗"
#define Goodbye1 "██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝██╔════╝"
#define Goodbye2 "██║  ███╗██║   ██║██║   ██║██║  ██║██████╔╝ ╚████╔╝ █████╗  "
#define Goodbye3 "██║   ██║██║   ██║██║   ██║██║  ██║██╔══██╗  ╚██╔╝  ██╔══╝  "
#define Goodbye4 "╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝██████╔╝   ██║   ███████╗"
#define Goodbye5 " ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝ ╚═════╝    ╚═╝   ╚══════╝"
#define Goodbye6 "                                                            "



//  =============== Input Protection fonctions  ===============//

bool    validateInput(const std::vector<std::string> input);











