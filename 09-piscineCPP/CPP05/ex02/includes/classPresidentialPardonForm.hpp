/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classPresidentialPardonForm.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 09:34:00 by aguay             #+#    #+#             */
/*   Updated: 2022/08/05 11:14:26 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "classAForm.hpp"

class PresidentialPardonForm : public AForm
{
	public:
		PresidentialPardonForm(PresidentialPardonForm const & rhs);
		PresidentialPardonForm(std::string target);
		virtual ~PresidentialPardonForm(void);

		virtual void				execute(Bureaucrat const & executor) const;
		PresidentialPardonForm &	operator=(PresidentialPardonForm const & rhs);

	private:
		const std::string	_target;
		PresidentialPardonForm(void);
};
