/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classBureaucrat.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 09:19:59 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 09:28:10 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string.h>
#include <iostream>

class AForm;

class Bureaucrat
{
	public:
		Bureaucrat(void);
		Bureaucrat(std::string name, int grade);
		Bureaucrat(Bureaucrat const & rhs);
		~Bureaucrat(void);

		Bureaucrat &	operator=(Bureaucrat const & rhs);
		std::string		getName(void) const;
		int				getGrade(void) const;
		void			incremGrade(void);
		void			decremGrade(void);
		void			signForm(AForm & rhs);

		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

	private:
		std::string	_name;
		int			_grade;
		void		_checkGrade(int grade) const;
};

std::ostream&	operator<<(std::ostream& COUT, const Bureaucrat& rhs);
