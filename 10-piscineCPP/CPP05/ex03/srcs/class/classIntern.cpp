/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classIntern.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:18:13 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 13:04:02 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classIntern.hpp"

Intern::Intern(void) : Bureaucrat("none", 150){};

Intern::Intern(Intern const & rhs)
{
	*this = rhs;
}

Intern::~Intern(void){};

Intern & Intern::operator=(Intern const & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

static AForm	*makeShruberry(std::string formName, std::string target)
{
	std::cout << "Intern made " << formName << std::endl;
	return (new ShrubberyCreationForm(target));
}

static AForm	*makePresidential(std::string formName, std::string target)
{
	std::cout << "Intern made " << formName << std::endl;
	return (new PresidentialPardonForm(target));
}

static AForm	*makeRobotomy(std::string formName, std::string target)
{
	std::cout << "Intern made " << formName << std::endl;
	return (new RobotomyRequestForm(target));
}

AForm	*Intern::MakeForm(std::string formName, std::string target)
{
	if (formName.find("hrub", 0) != formName.npos)
		return (makeShruberry(formName, target));

	if (formName.find("obot", 0) != formName.npos)
		return (makeRobotomy(formName, target));

	if (formName.find("residen", 0) != formName.npos)
		return (makePresidential(formName, target));
	std::cerr << "What is that form name ...??" << std::endl;
	return (NULL);
}
