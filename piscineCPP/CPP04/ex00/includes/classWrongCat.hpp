/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classWrongCat.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:39:04 by aguay             #+#    #+#             */
/*   Updated: 2022/08/03 10:40:23 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "classWrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
	public:

		//	Constructor's
		WrongCat(void);
		WrongCat(WrongCat const & rhs);
		
		//	Destructor's
		~WrongCat(void);

		//	Operator overload
		WrongCat &	operator=(WrongCat const & rhs);

		//	Getter
		std::string	getType(void) const;
		
		//	Methodes
		void	makeSound(void) const;
	
	protected:
	
		std::string	_type;
};
