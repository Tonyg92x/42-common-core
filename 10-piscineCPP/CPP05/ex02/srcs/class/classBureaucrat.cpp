/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classBureaucrat.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 09:20:11 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 10:03:32 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classBureaucrat.hpp"
#include "classAForm.hpp"

Bureaucrat::Bureaucrat(void) : _name("Undifined Bureaucrat"), _grade(150){};

Bureaucrat::Bureaucrat(std::string name, int grade)
{
	this->_checkGrade(grade);
	this->_name = name;
	this->_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const & rhs)
{
	*this = rhs;
}

Bureaucrat::~Bureaucrat(void)
{
	return;
}

Bureaucrat & Bureaucrat::operator=(Bureaucrat const & rhs)
{
	if (this != &rhs)
	{
		this->_grade = rhs.getGrade();
		this->_name = rhs.getName();
	}
	return (*this);
}

void	Bureaucrat::incremGrade(void)
{
	this->_checkGrade(this->_grade + 1);
	this->_grade++;
}

void	Bureaucrat::decremGrade(void)
{
	this->_checkGrade(this->_grade - 1);
	this->_grade--;
}

std::string	Bureaucrat::getName(void) const
{
	return (this->_name);
}

int	Bureaucrat::getGrade(void) const
{
	return (this->_grade);
}

void	Bureaucrat::signForm(AForm & rhs)
{
    if (rhs.getSigned() == 1)
    {
        std::cout << rhs.getName() << " couldn’t sign " << this->getName()
            << " because it's already signed." << std::endl;
        return ;
    }
	rhs.beSigned(*this);
	std::cout << this->_name << " signed " << rhs.getName() << std::endl;
}

std::ostream&	operator<<(std::ostream& COUT, const Bureaucrat& rhs)
{
	COUT << rhs.getName() << ", bureaucrat grade " << rhs.getGrade();
	return (COUT);
}

void	Bureaucrat::_checkGrade(int grade) const
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("\033[31mGrade to high (maximum 1)\033[0m");
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("\033[31mGrade to low (minimum 150)\033[0m");
}

void	Bureaucrat::executeForm(const AForm& form) const
{
	form.execute(*this);
	std::cout << this->_name << " executed " << form.getName() << std::endl;
}

