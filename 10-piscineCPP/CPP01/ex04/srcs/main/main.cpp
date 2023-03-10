/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 15:49:52 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

int	main(int argc, char **argv)
{
	//	Arguments validation before running anything
	if (argc != 4)
	{std::cout << "The program require 3 armuments: ./ex04 filename string1 string2" << std::endl;return 1;}

	//	Open input/output files
	const std::string		file_name = argv[1];
	const std::string		str1 = argv[2];
	const std::string		str2 = argv[3];
	std::ifstream			i_file(file_name);
	if (!i_file.is_open())
	{std::cout << "Error while opening the file " << file_name << std::endl; return (1);}
	std::ofstream			o_file(file_name + ".replace");
	if (!o_file.is_open())
	{std::cout << "Error while opening the output file " << file_name << ".replace" << std::endl; return (1);}
	std::string				input;

	//	Line by line, modify the line and add its content to o_file
	while (!i_file.eof())
	{
		getline(i_file, input);
		while (true)
		{
			size_t	index = input.find(str1);
			if (index != std::string::npos)
			{
				input.erase(index, str1.size());
				input.insert(index, str2);
			}
			else
				break;
		}
		o_file << input << '\n';
	}
	//	Close opened files
	i_file.close();
	o_file.close();
	return (0);
}