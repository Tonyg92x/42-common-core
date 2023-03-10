/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 11:41:57 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classClapTrap.hpp"
#include "classScavTrap.hpp"
#include "classFragTrap.hpp"

void	display_status(ScavTrap &ref);
void	display_status(FragTrap &ref);

int	main(void)
{
	FragTrap	robot3("\033[33mCorrecter wanna be\033[0m");
	display_status(robot3);
	robot3.highFivesGuys();

	std::cout << "\033[32m\nLet's add more Frag!\033[0m\n" << std::endl;

	FragTrap	robot4;
	FragTrap	robot5 = robot3;

	std::cout << "\033[31m\nAttack minions!\n\033[0m" << std::endl;
	robot3.attack("ta mere");
	robot4.attack("ma mere");
	robot5.attack("la mere a undefefined");

	std::cout << "\033[32m\nLet's see updates\n\033[0m" << std::endl;
	
	display_status(robot3);
	display_status(robot4);
	display_status(robot5);

	std::cout << "\033[32m\nYay! Correction or module done! High five?\033[0m\n" << std::endl;
	robot3.highFivesGuys();
	robot4.highFivesGuys();
	robot5.highFivesGuys();

	std::cout << "\n" << std::endl;
	return (0);
}

void	display_status(ScavTrap &ref)
{
	std::cout << ref.getName() << " has " << ref.getHitPoint()
		<< " hitpoint and has " << ref.getEnergyPoint() << " energy point."
		<< std::endl;
	return;
}

void	display_status(FragTrap &ref)
{
	std::cout << ref.getName() << " has " << ref.getHitPoint()
		<< " hitpoint and has " << ref.getEnergyPoint() << " energy point."
		<< std::endl;
	return;
}
