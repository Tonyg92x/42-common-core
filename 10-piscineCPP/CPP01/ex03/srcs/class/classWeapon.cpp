/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classWeapon.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:38:46 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 12:35:32 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classWeapon.hpp"

Weapon::Weapon(std::string type)
{
	setType(type);
}

Weapon::~Weapon()
{
}

std::string const &	Weapon::getType(void)
{
	return (this->type);
}

void	Weapon::setType(std::string type)
{
	this->type = type;
}
