/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classWeapon.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:38:42 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 12:35:04 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLASSWEAPON_HPP
# define CLASSWEAPON_HPP

#include <string>

class Weapon
{
	
	public:

		Weapon(std::string	type);
		~Weapon();
		std::string const & getType(void);
		void				setType(std::string type);

	private:

		std::string	type;
};

#endif
