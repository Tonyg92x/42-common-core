/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classPresidentialPardonForm.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 09:34:02 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 10:39:48 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "classPresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) : AForm("PresidentialPardonForm", 25, 5){}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const & rhs) : AForm("PresidentialPardonForm", 25, 5){*this = rhs;}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 25, 5), _target(target){}

PresidentialPardonForm::~PresidentialPardonForm(void){}

PresidentialPardonForm & PresidentialPardonForm::operator=(PresidentialPardonForm const & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

static void	executeOrder66(std::string target)
{
	std::cout << target << " a ete pardonne par Zaphod Beeblebrox" << std::endl;
}

void	PresidentialPardonForm::execute(const Bureaucrat& executor) const
{
	if (this->getSigned() == false)
		throw (PresidentialPardonForm::FormNotSignedException());
	if (this->getGradeToExecute() < executor.getGrade())
    {
        std::cout << this->getName() << " couldn't execute bacause : ";
        throw (PresidentialPardonForm::GradeTooLowException());
    }
	executeOrder66(this->_target);
}
