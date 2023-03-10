/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassZombie.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 09:52:24 by aguay             #+#    #+#             */
/*   Updated: 2022/06/25 10:31:17 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLASSZOMBIE_HPP
# define CLASSZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie
{
	public:

		Zombie(std::string name);
		~Zombie(void);

		void			announce(void);
		std::string		get_name(void);

	private:

		std::string 	name;

		void			set_name(std::string name);
};

#endif