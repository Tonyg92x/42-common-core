/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classHumanA.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:12:08 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 12:55:12 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classWeapon.hpp"

class HumanA
{
	public:

		HumanA(std::string name, Weapon& gun);
		~HumanA(void);

		void		attack(void);
		std::string	getName(void);
		Weapon		getWeapon(void);
		void		setWeapon(Weapon gun);

	private:

		Weapon&		arme;
		std::string	name;
};

