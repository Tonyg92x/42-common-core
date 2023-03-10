/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 10:55:07 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classClapTrap.hpp"
#include <iostream>

static void display_status(ClapTrap &ref)
{
	std::cout << ref.getName() << " has " << ref.getHitPoint()
		<< " hitpoint (s) and has " << ref.getEnergyPoint() << " energy point (s)."
		<< std::endl;
	return;
}

int	main(void)
{
	ClapTrap	robot = ClapTrap("Roboto");

	display_status(robot);
	robot.takeDamage(5);
	display_status(robot);
	robot.attack("bob");
	robot.beRepaired(60);
	display_status(robot);
	robot.takeDamage(10);
	robot.attack("bob");
	display_status(robot);
	robot.takeDamage(10);
	robot.attack("bob");
	display_status(robot);
	robot.takeDamage(10);
	robot.attack("bob");
	display_status(robot);
	robot.takeDamage(10);
	robot.attack("bob");
	display_status(robot);
	robot.takeDamage(10);
	robot.attack("bob");
	display_status(robot);
	robot.takeDamage(10);
	robot.attack("bob");
	display_status(robot);
	robot.takeDamage(10);
	robot.attack("bob");
	display_status(robot);
	return (0);
}
