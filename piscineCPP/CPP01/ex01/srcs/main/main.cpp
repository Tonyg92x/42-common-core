/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 10:50:16 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassZombie.hpp"
#include <iostream>

Zombie* zombieHorde(int N, std::string name);

int	main(void)
{
	Zombie	*ptr;

	ptr = zombieHorde(3, "Philipe");
	for (int i = 0; i < 3; i++)
		ptr[i].announce();
	delete [] ptr;
	return (0);
}