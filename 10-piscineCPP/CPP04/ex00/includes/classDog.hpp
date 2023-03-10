/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classDog.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:49:32 by aguay             #+#    #+#             */
/*   Updated: 2022/08/03 15:15:45 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "classAnimal.hpp"

class Dog : public AAnimal
{
	public:

		//	Constructor's
		Dog(void);
		Dog(Dog const & rhs);
		
		//	Destructor's
		virtual ~Dog(void);

		//	Operator overload
		Dog &	operator=(Dog const & rhs);

		//	Getter
		virtual std::string	getType(void) const;
		
		//	Methodes
		virtual void	makeSound(void) const;
};
