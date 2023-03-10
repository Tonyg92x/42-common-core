/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 10:31:37 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassZombie.hpp"
#include <iostream>

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

int	main(void)
{
	Zombie *ptr;

	ptr = newZombie("HeapZombie");
	(*ptr).announce();
	randomChump("StackZombie");
	std::cout << "Deleting the memory allocated of zombie : " << (*ptr).get_name() << std::endl;
	delete ptr;
	return (0);
}