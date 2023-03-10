/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classForm.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:22:20 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 09:28:10 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classForm.hpp"
#include "classBureaucrat.hpp"

AForm::AForm(void) :  _name("Undifined"), _signed(false), _gradeToSign(1), _gradeToExecute(1){};

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute) : _name(name),
	_signed(false), _gradeToSign(checkGrade(gradeToSign)), _gradeToExecute(checkGrade(gradeToExecute)){}

AForm::AForm(AForm const & rhs) : _name(rhs.getName()), _gradeToSign(rhs.getGradeToSign()),
	_gradeToExecute(rhs.getGradeToExecute())
{
	*this = rhs;
}

AForm::~AForm(void)
{
	return ;
}

AForm &	AForm::operator=(AForm const & rhs)
{
	if (this != &rhs)
		this->_signed = rhs.getSigned();
	return (*this);
}

std::string	AForm::getName(void) const
{
	return (this->_name);
}

bool	AForm::getSigned(void) const
{
	return (this->_signed);
}

int	AForm::getGradeToSign(void) const
{
	return (this->_gradeToSign);
}

int	AForm::getGradeToExecute(void) const
{
	return (this->_gradeToExecute);
}

void	AForm::beSigned(const Bureaucrat & rhs)
{
	this->checkGradeSign(rhs);
	this->_signed = true;
}

void	AForm::checkGradeSign(Bureaucrat const & rhs)
{
	if (rhs.getGrade() > this->getGradeToSign())
    {
        std::cout << rhs.getName() << " couldn’t sign " << this->getName()
            << " because ";
        throw (AForm::GradeTooLowException());
    }
		
}

void	AForm::checkGradeExec(Bureaucrat const & rhs)
{
	if (rhs.getGrade() > this->getGradeToExecute())
		throw (AForm::GradeTooLowException());
}

std::ostream&	operator<<(std::ostream& COUT, const AForm& rhs)
{
	COUT << rhs.getName() << ", form grade to sign " << rhs.getGradeToSign()
		<< ", form grade to execute " << rhs.getGradeToExecute() << 
        " is " << rhs.getSigned();
	return (COUT);
}

const char	*AForm::GradeToHighException::what() const throw()
{
	return ("\033[31mGrade to high\033[0m");
}

const char	*AForm::GradeTooLowException::what() const throw()
{
	return ("\033[31mGrade to low\033[0m");
}

int	AForm::checkGrade(int grade)
{
	if (grade < 1)
		throw GradeToHighException();
	else if (grade > 150)
		throw GradeToHighException();
    else
	    return (grade);
}
