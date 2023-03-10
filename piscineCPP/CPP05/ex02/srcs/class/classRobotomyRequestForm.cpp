/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classRobotomyRequestForm.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 09:34:03 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 10:28:16 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classRobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void) : AForm("RobotomyRequestForm", 72, 45){}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & rhs) : AForm("RobotomyRequestForm", 72, 45){*this = rhs;}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45), _target(target){}

RobotomyRequestForm::~RobotomyRequestForm(void){}

RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm const & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

static void	executeOrder66(std::string target)
{
	std::cout << "bzzzzzz cling cling cling" << std::endl;
	srand(time(0));
	sleep(1);
	if (rand() % 2 == 0)
		std::cout << target << "\033[32m a ete robotise avec success\033[0m" << std::endl;
	else
		std::cout << target << "\033[31m robotisation a echoue\033[0m" << std::endl;
}

void	RobotomyRequestForm::execute(const Bureaucrat& executor) const
{
	if (this->getSigned() == false)
		throw (RobotomyRequestForm::FormNotSignedException());
	if (this->getGradeToExecute() < executor.getGrade())
    {
         std::cout << this->getName() << " couldn't execute bacause : ";
         throw (RobotomyRequestForm::GradeTooLowException());
    }
	executeOrder66(this->_target);
}
