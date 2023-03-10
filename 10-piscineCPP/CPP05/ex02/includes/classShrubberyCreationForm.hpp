/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classShrubberyCreationForm.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 08:14:36 by aguay             #+#    #+#             */
/*   Updated: 2022/08/05 11:21:34 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "classAForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
	public:
		ShrubberyCreationForm(ShrubberyCreationForm const & rhs);
		ShrubberyCreationForm(std::string target);
		virtual ~ShrubberyCreationForm(void);

		ShrubberyCreationForm &	operator=(ShrubberyCreationForm const & rhs);
		virtual void execute(const Bureaucrat& executor) const;

	private:
		const std::string	_target;
		ShrubberyCreationForm(void);
};
