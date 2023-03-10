/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputProtection.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:25:29 by aguay             #+#    #+#             */
/*   Updated: 2023/01/14 10:28:43 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"

//  Validate input strings -> return true = valid / return false = invalid
bool    validateInput(const std::vector<std::string> input)
{
    if (input.size() != 2)
    {
         std::cout << RED << "Error" << NORMAL << ": expected arg for this binary: ./ircserv port password" << std::endl;
        return (false);
    }

    //  Get the port number on which the service should be lunched
    int port = stoi(input[0]);

    //  Look it the port number is valid
    if (port < 1)
    {
        std::cout << RED << "Error" << NORMAL << ": Negative port is invalid. Please use one between 1024 and 65535." << std::endl;
        return (false);
    }
    if (port < 1024)
    {
        std::cout << RED << "Error" << NORMAL << ": port from 1 to 1023 require root access. Please use one between 1024 and 65535." << std::endl;
        return (false);
    }
    if (port > 65535)
    {
        std::cout << RED << "Error" << NORMAL << ": the maximum value for a port is 65535. Please use one between 1024 and 65535." << std::endl;
        return (false);
    }

    //  TODO: add password validation

    return (true);
}
