/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:29:11 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 10:29:37 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassZombie.hpp"

Zombie* newZombie(std::string name)
{
	Zombie	*ZPtr;

	ZPtr = new Zombie(name);
	return (ZPtr);
}
