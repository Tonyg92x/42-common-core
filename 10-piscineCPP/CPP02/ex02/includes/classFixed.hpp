/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classFixed.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:06:06 by aguay             #+#    #+#             */
/*   Updated: 2022/06/28 15:58:06 by aguay            ###   ########.fr       */
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

		//	Member fonctions
		int					getRawBits(void) const;
		void				setRawBits(int const raw);
		float				toFloat(void) const;
		int					toInt(void) const;

		//	Assignation operator overload
		Fixed &				operator=(Fixed const & rhs);

		//	Arithmetic Operator overload
		Fixed				operator+(Fixed const & rhs) const;
		Fixed				operator-(Fixed const & rhs) const;
		Fixed				operator*(Fixed const & rhs) const;
		Fixed				operator/(Fixed const & rhs) const;

		//	Boolean Algebra Operator overload
		bool				operator>(Fixed const &rhs) const;
		bool				operator>=(Fixed const &rhs) const;
		bool				operator<(Fixed const &rhs) const;
		bool				operator<=(Fixed const &rhs) const;
		bool				operator==(Fixed const &rhs) const;
		bool				operator!=(Fixed const &rhs) const;

		//	Prefix, postfix incrementation/decrementation
		Fixed				operator++(int);	// postfix
		Fixed &				operator++();		// prefix
		Fixed				operator--(int);	// postfix
		Fixed &				operator--();		// prefix

		//	Fonction non member
		static Fixed &		min(Fixed const &fixA, Fixed const &fixB);
		static Fixed &		min(Fixed &fixA, Fixed &fixB);
		static Fixed &		max(Fixed const &fixA, Fixed const &fixB);
		static Fixed &		max(Fixed &fixA, Fixed &fixB);

	private:

		int					_rawBits;
		static int const	bitFract = 8;
};

std::ostream &	operator<<(std::ostream & o, Fixed const & rhs);

#endif