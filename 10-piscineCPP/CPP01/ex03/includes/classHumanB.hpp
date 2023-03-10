/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classHumanB.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:26:35 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 13:02:52 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSHUMANB_HPP
# define CLASSHUMANB_HPP

#include <string>
#include <iostream>
#include "classWeapon.hpp"

class HumanB
{
	public:

		HumanB(std::string name);
		~HumanB(void);

		void		attack(void);
		void		setWeapon(Weapon& arme);
		std::string	getName(void);
		Weapon		getWeapon(void);

	private:

		std::string	name;
		Weapon		*arme;
};

#endif
