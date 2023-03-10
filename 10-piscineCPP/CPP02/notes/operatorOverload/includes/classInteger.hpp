/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classInteger.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:30:42 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 14:36:22 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSINTEGER_HPP
# define CLASSINTEGER_HPP

#include <iostream>

class Integer
{
	public:

		Integer(int const n);
		~Integer(void);

		int	getValue(void) const;
		Integer &	operator=( Integer const & rhs);
		Integer		operator+( Integer const & rhs) const;

	private:

	int _n;
	
};

std::ostream & operator << (std::ostream & o, Integer const &rhs);

#endif