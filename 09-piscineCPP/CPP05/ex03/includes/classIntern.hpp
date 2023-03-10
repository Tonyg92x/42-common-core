/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classIntern.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:16:14 by aguay             #+#    #+#             */
/*   Updated: 2022/08/08 13:26:56 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "classBureaucrat.hpp"
#include "classShrubberyCreationForm.hpp"
#include "classPresidentialPardonForm.hpp"
#include "classRobotomyRequestForm.hpp"

class Intern : public Bureaucrat
{
	public:
		Intern(void);
		Intern(Intern const & rhs);
		~Intern(void);
		Intern & operator=(Intern const & rhs);

		AForm	*MakeForm(std::string formName, std::string Target);
};

