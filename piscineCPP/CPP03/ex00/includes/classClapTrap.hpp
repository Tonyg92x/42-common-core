/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classClapTrap.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 08:23:12 by aguay             #+#    #+#             */
/*   Updated: 2022/07/31 12:28:12 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSCLAPTRAP_HPP
# define CLASSCLAPTRAP_HPP

#include <string.h>
#include <iostream>

class ClapTrap
{
	public:

		//	Contructor's
		ClapTrap(void);
		ClapTrap(std::string name);
		ClapTrap(ClapTrap const & rhs);

		//	Destructor
		~ClapTrap(void);

		//	Operator overload
		ClapTrap &		operator=(ClapTrap const & rhs);

		//	Getter method's
		std::string		getName(void) const;
		unsigned int	getHitPoint(void) const;
		unsigned int	getEnergyPoint(void) const;
		unsigned int	getAttackDamage(void) const;

		//	Object method's
		void			attack(const std::string& target);
		void			takeDamage(unsigned int amount);
		void			beRepaired(unsigned int amount);


	private:

		std::string		_name;
		unsigned int	_hitPoint;
		unsigned int	_energyPoint;
		unsigned int	_attackDamage;
};

#endif
