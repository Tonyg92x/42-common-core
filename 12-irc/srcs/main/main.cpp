/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvigneau <jvigneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2023/01/28 13:27:15 by jvigneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"
#include "Server.class.hpp"
#include "User.class.hpp"
#include "Channel.class.hpp"

Server *ptr;

void sig_handler(int sigNum)
{
    if (sigNum == SIGINT)
    {
        Server porte = *ptr;
        porte.~Server();
        exit (0);
    }
}

int main(int argNb, char **args)
{
    // Get the input in a vector
    std::vector<std::string> input;
    for (int i = 1; i < argNb; i++)
        input.push_back(args[i]);

    //  Validate input entry
    if (!validateInput(input))
        return (1);

    //  Create the server and start it
    try
    {
        Server porte(std::stoi(input[0]), input[1]);
        ptr = &porte;
        signal(SIGINT, sig_handler);
        porte.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (1);
    }

    return (0);
}
