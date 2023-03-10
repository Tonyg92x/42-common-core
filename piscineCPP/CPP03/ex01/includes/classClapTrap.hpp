/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classClapTrap.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 08:23:12 by aguay             #+#    #+#             */
/*   Updated: 2022/09/28 11:13:23 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSCLAPTRAP_HPP
# define CLASSCLAPTRAP_HPP

#include <string.h>
#include <iostream>

class ClapTrap
{
	public:

		ClapTrap(void);
		ClapTrap(std::string name);
		ClapTrap(ClapTrap const & rhs);
		~ClapTrap(void);

		ClapTrap &		operator=(ClapTrap const & rhs);

		void			attack(const std::string& target);
		void			attack(ClapTrap & rhs);
		void			takeDamage(unsigned int amount);
		void			beRepaired(unsigned int amount);

		//	Getter's
		std::string		getName(void) const;
		unsigned int	getHitPoint(void) const;
		unsigned int	getEnergyPoint(void) const;
		unsigned int	getAttackDamage(void) const;

		//	Setter's
		void			setName(const std::string name);
		void			setHitPoint(unsigned int amount);
		void			setEnergyPoint(unsigned int amount);
		void			setAttackDamage(unsigned int amount);

	protected:
		std::string		_name;
		unsigned int	_hitPoint;
		unsigned int	_energyPoint;
		unsigned int	_attackDamage;
};

#endif
