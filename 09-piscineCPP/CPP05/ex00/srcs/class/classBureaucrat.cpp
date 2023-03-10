/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classBureaucrat.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 09:20:11 by aguay             #+#    #+#             */
/*   Updated: 2022/09/30 14:32:33 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classBureaucrat.hpp"

Bureaucrat::Bureaucrat(void) : _name("Undefined"), _grade(150)
{
	std::cout << "Default Bureaucrat constructor called\n";
}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	this->_checkGrade(grade);
	this->_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const & rhs) : _name(rhs.getName())
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
		this->_grade = rhs.getGrade();
	return (*this);
}

void	Bureaucrat::decremGrade(void)
{
	this->_checkGrade(this->_grade + 1);
	this->_grade++;
}

void	Bureaucrat::incremGrade(void)
{
	this->_checkGrade(this->_grade - 1);
	this->_grade--;
}

std::string	Bureaucrat::getName(void) const
{
	return (this->_name);
}

size_t	Bureaucrat::getGrade(void) const
{
	return (this->_grade);
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
