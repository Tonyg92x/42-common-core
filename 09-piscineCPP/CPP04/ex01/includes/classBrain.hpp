/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classBrain.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:48:49 by aguay             #+#    #+#             */
/*   Updated: 2022/08/03 14:40:34 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string.h>
#include <iostream>

class	Brain
{
	public:

		Brain(void);
		Brain(Brain const &rhs);
		~Brain(void);
		Brain &	operator=(Brain const &rhs);

		std::string	get_idea(size_t index) const;
		void		set_idea(size_t index, std::string lidea);

	private:
		std::string	ideas[100];
		void		init_ideas(void);
};