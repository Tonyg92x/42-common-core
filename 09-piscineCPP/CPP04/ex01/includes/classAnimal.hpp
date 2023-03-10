/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 07:41:10 by aguay             #+#    #+#             */
/*   Updated: 2022/08/03 15:15:45 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string.h>

class AAnimal
{
	public:
		//	Constructor's
		AAnimal(void);
		AAnimal(AAnimal const & rhs);

		//	Destructor's
		virtual ~AAnimal(void);

		//	Operator overload
		AAnimal &	operator=(AAnimal const & rhs);

		//	Methodes
		virtual void		makeSound(void) const;
		virtual std::string	getType(void) const;

	protected:
		std::string	_type;
};
