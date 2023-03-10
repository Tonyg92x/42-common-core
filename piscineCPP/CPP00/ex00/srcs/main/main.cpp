/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/16 10:52:43 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <iostream>

int	main(int argc, char **argv)
{
	std::string	strs[argc];

	//	Output if there is no entry
	if (argc == 1){std::cout << "LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl; return (0);}

	//	For every parameters entered, output every character to upper
	for (int i = 1; i < argc; i++)
	{
		strs[i - 1] = argv[i];
		for (int x = 0; x < (int)strs[i - 1].size(); x++)
			std::cout << (char)std::toupper(strs[i - 1][x]);
	}
	std::cout << std::endl;
	return (0);
}