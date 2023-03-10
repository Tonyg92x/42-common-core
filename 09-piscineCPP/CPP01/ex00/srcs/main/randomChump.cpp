/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:29:51 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 10:30:13 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassZombie.hpp"

void randomChump(std::string name)
{
	Zombie	zom(name);
	zom.announce();
}
