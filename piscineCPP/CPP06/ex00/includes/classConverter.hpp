/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classConverter.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:29:25 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 15:30:10 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string.h>

class	Converter
{
	public:
		Converter(std::string);
		Converter(Converter const & rhs);
		~Converter(void);

		Converter &	operator=(Converter const & rhs);
		std::string	getStrValue(void) const;
        std::string getType(void) const;
		char		toChar(void) const;
		int			toInt(void) const;
		float		toFloat(void) const;
		double		toDouble(void) const;
        std::string set_type(std::string str);

        class   UpCastImpossibleException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class   DownCastImpossibleException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class   NotDisplayableException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class   ExitException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

	private:
		std::string	_strValue;
        std::string _type;
		Converter(void);
};
