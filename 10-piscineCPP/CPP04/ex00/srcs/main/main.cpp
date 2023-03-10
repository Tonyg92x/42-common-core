/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 13:55:34 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classAnimal.hpp"
#include "classCat.hpp"
#include "classDog.hpp"
#include "classWrongAnimal.hpp"
#include "classWrongCat.hpp"

int	main(void)
{

	std::cout << "\n\033[31mBegin Test with virtual\033[0m" << std::endl;
	//	Test with virtual
	std::cout << "\nConstructor test's\n" << std::endl;
	const AAnimal* meta = new AAnimal();
	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();

	//	Test getType
	std::cout << "\nGet type test's\n" << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	std::cout << meta->getType() << std::endl;

	//	Make sound test
	std::cout << "\nmakesound test's\n" << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();
	std::cout << "\n";

	delete (i);
	delete(j);
	delete(meta);

	//	Test without virtual
	std::cout << "\n\033[31mEnd test with virtual\n\nBegin Test without virtual\n\033[0m" << std::endl;
	

	const WrongAnimal* Wmeta = new WrongAnimal();
	const WrongAnimal* Wi = new WrongCat();
	std::cout << Wi->getType() << " " << std::endl;
	std::cout << Wmeta->getType() << std::endl;
	Wi->makeSound(); //will output the cat sound!
	Wmeta->makeSound();

	delete Wmeta;
	delete Wi;

	//	So here we can see that the fonction is static, when we call a fonction, since its initialised const WrongAnimal,
	//	we get WrongAnimal fonction onstread of Wrong cat fonction. The destructor delete only the WrongAnimal so Wrong
	//	Cat will leak.
	return 0;
}