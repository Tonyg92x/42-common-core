/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classRobotomyRequestForm.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 09:33:59 by aguay             #+#    #+#             */
/*   Updated: 2022/08/08 12:57:39 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "classAForm.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

class RobotomyRequestForm : public AForm
{
	public:
		RobotomyRequestForm(RobotomyRequestForm const & rhs);
		RobotomyRequestForm(std::string target);
		virtual ~RobotomyRequestForm(void);

		RobotomyRequestForm &	operator=(RobotomyRequestForm const & rhs);
		virtual void execute(const Bureaucrat& executor) const;

	private:
		const std::string	_target;
		RobotomyRequestForm(void);
};
