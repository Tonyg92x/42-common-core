/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/09/29 09:02:48 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classAnimal.hpp"
#include "classCat.hpp"
#include "classDog.hpp"

int	main(void)
{
	AAnimal	*tableau[10];

	std::cout << "\n\033[32mTest create 5 dog and 5 cat\033[0m\n" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			tableau[i] = new Dog;
		else
			tableau[i] = new Cat;
		std::cout << "\nCreation " << i << " is a " << tableau[i]->getType() << "\n"  << std::endl;
	}
	
	std::cout << "\n\n\033[32mTest done, now let's test destructor's\033[0m\n" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << tableau[i]->getType() << ": \033[34m";
		tableau[i]->makeSound();
		std::cout << "\n\033[0m" << std::endl;
		delete tableau[i];
	}

	std::cout << "\n\nConstructor test classe profonde" << std::endl;

	Dog	chien;

	std::cout << std::endl;
	Dog	chien2 = chien;
	
	std::cout << "\n\nDestructor proof\n" << std::endl;
	
	return 0;
}