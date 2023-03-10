/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 15:41:39 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classClapTrap.hpp"
#include "classScavTrap.hpp"

static void display_status(ScavTrap &ref)
{
	std::cout << ref.getName() << " has " << ref.getHitPoint()
		<< " hitpoint and has " << ref.getEnergyPoint() << " energy point."
		<< std::endl;
	return;
}


int	main(void)
{
	//	Constructor test's
	std::cout << "\nConstructor test's\n" << std::endl;
	ScavTrap	robot0("roberto");
	ScavTrap	robot1;
	ScavTrap	robot2(robot0);
	ScavTrap	robot3 = robot2;

	//	Guard test's
	std::cout << "\nGuard test's\n" << std::endl;
	robot0.guardGate();
	robot1.guardGate();
	robot2.guardGate();

	std::cout << "\nPolymorphism attack test's\n" << std::endl;

	//	Polymorphism attack test's
	robot0.attack(robot2);
	display_status(robot0);
	display_status(robot2);

	std::cout << "\nDestructor test's\n" << std::endl;
	return (0);
}
