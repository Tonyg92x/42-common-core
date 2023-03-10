/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:06:31 by aguay             #+#    #+#             */
/*   Updated: 2022/08/03 15:15:45 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "classAnimal.hpp"
#include "classBrain.hpp"

class Cat : public AAnimal
{
	public:
		Cat(void);
		Cat(Cat const & rhs);
	
		virtual				~Cat(void);
		Cat &				operator=(Cat const & rhs);
		virtual std::string	getType(void) const;
		virtual void		makeSound(void) const;
		virtual void		get_idea(size_t index);
	
	private:
		Brain	*brain;
};
