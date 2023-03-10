/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/17 08:35:08 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ContactClass.hpp"
#include "PhoneBookClass.hpp"

static void	clean(std::string info[5])
{
	info[0] = "";
	info[1] = "";
	info[2] = "";
	info[3] = "";
	info[4] = "";
}

static bool	get_info(std::string info[5])
{
	// Get the user input of the contact info
	std::cout << "First name :\t\t";
	std::getline(std::cin, info[0]);
	if (info[0] == "")
	{
		std::cout << "Invalid First name\n" << std::endl;
		return (false);
	}
	std::cout << "Last Name :\t\t";
	std::getline(std::cin, info[1]);
	if (info[1] == "")
	{
		std::cout << "Invalid Last name\n" << std::endl;
		return (false);
	}
	std::cout << "Nick Name :\t\t";
	std::getline(std::cin, info[2]);
	if (info[2] == "")
	{
		std::cout << "Invalid nick name\n" << std::endl;
		return (false);
	}
	std::cout << "Phone Number :\t\t";
	std::getline(std::cin, info[3]);
	if (info[3] == "")
	{
		std::cout << "Invalid Phone Number\n" << std::endl;
		return (false);
	}
	std::cout << "Darkest Secret :\t";
	std::getline(std::cin, info[4]);
	if (info[4] == "")
	{
		std::cout << "JUST GIVE ME THE JUICEE\n" << std::endl;
		return (false);
	}
	std::cout << std::endl;
	return (true);
}

int	main(void)
{
	bool				appEngine = true;
	bool				valid_input = false;
	PhoneBookClass		rep;
	std::string			input;
	std::string			info[5];
	Contact				*contact[8];
	int					count = 0;

	std::cout << "\nWelcome in my Awesome PhoneBook App!" << std::endl << std::endl;
	while (appEngine)
	{
		std::cout << "Please chose an option" << std::endl;
		std::cout << "ADD\t: Add a contact to the phone book" << std::endl;
		std::cout << "SEARCH\t: Seach for a contact" << std::endl;
		std::cout << "EXIT\t: GUESS WHAT IS DOES!?" << std::endl << std::endl;
		std::getline(std::cin, input);
		if (input == "ADD")
		{
			if (get_info(info) == true)
			{
				if (count > 8)
					delete contact[rep.getIndex()];
				contact[rep.getIndex()] = new Contact(info);
				rep.addContact(contact[rep.getIndex()]);
				count++;
			}
			clean(info);
		}
		else if (input == "SEARCH")
		{
			if (count == 0)
			{
				std::cout << "There is 0 contact.\n" << std::endl;
				continue;;
			}
			while (valid_input == false)
			{
				rep.showRepertoire();
				std::cout << "Wich contact do you want to see (id)?" << std::endl;
				std::getline(std::cin, input);
				if ((int)input[0] - 48 < count && input[1] == '\0')
				{
					rep.getContact((int)input[0] - 48);
					valid_input = true;
				}
				else
					std::cout << input << " is an invalid index\n";
			}
			valid_input = false;
		}
		else if (input == "EXIT")
			appEngine = false;
	}
	for (int z = 0; z < 8; z++)
	{
		if (z < count)
			delete contact[z];
	}
	return (0);
}
