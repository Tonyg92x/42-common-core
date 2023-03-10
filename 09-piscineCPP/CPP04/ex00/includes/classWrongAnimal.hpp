/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classWrongAnimal.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:35:40 by aguay             #+#    #+#             */
/*   Updated: 2022/08/03 10:37:47 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string.h>

class WrongAnimal
{
	public:

		//	Constructor's
		WrongAnimal(void);
		WrongAnimal(WrongAnimal const & rhs);

		//	Destructor's
		~WrongAnimal(void);

		//	Operator overload
		WrongAnimal &	operator=(WrongAnimal const & rhs);

		//	Methodes
		void		makeSound(void) const;
		std::string	getType(void) const;

	protected:

		std::string	_type;
		WrongAnimal(std::string type);
};
