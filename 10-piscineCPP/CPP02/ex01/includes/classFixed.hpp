/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classFixed.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:06:06 by aguay             #+#    #+#             */
/*   Updated: 2022/06/28 10:02:19 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSFIXED_HPP
# define CLASSFIXED_HPP

#include <iostream>

class Fixed
{
	public:

		Fixed(void);
		Fixed(Fixed const & src);
		Fixed(int const entier);
		Fixed(float const nbVirgule);
		~Fixed(void);

		int					getRawBits(void) const;
		void				setRawBits(int const raw);
		float				toFloat(void) const;
		int					toInt(void) const;
		Fixed &				operator=(Fixed const & rhs);
		
	private:

		int					_rawBits;
		static int const	bitFract = 8;
};

std::ostream &	operator<<(std::ostream & o, Fixed const & rhs);

#endif