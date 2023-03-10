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
#include "classBrain.hpp"

class Dog : public AAnimal
{
	public:
		Dog(void);
		Dog(Dog const & rhs);

		virtual				~Dog(void);
		Dog &				operator=(Dog const & rhs);
		virtual std::string	getType(void) const;
		virtual void		makeSound(void) const;
		virtual void		get_idea(size_t index);

	private:
		Brain *brain;
};
