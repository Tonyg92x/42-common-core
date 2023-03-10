/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classAForm.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:21:58 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 10:00:30 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string.h>
#include <iostream>
#include "classBureaucrat.hpp"

class AForm
{
	public:
    	AForm(void);
		AForm(std::string name, int GradeToSign, int GradeToExecute);
		AForm(AForm const & rhs);
		~AForm(void);

		AForm &		operator=(AForm const & rhs);
		std::string	getName(void) const;
		bool		getSigned(void) const;
		int			getGradeToSign(void) const;
		int			getGradeToExecute(void) const;
		void		beSigned(const Bureaucrat & rhs);

        virtual void	execute(Bureaucrat const & executor) const = 0;

		class	GradeToHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

        class FormNotSignedException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
	
	private:
		const std::string	_name;
		bool				_signed;
		const int			_gradeToSign;
		const int			_gradeToExecute;

		int		checkGrade(int	grade);
		void	checkGradeSign(Bureaucrat const & rhs);
		void	checkGradeExec(Bureaucrat const & rhs);
};

std::ostream&	operator<<(std::ostream& COUT, const AForm& rhs);
