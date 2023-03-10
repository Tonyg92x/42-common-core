/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 13:32:42 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classHarl.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
		{std::cout << "Invalid number of arguments!!! I WANT TO SEE YOUR MANAGER!" << std::endl; return (1);}
	
	Harl	Karen;
	Karen.filter(argv[1]);
	return (0);
}