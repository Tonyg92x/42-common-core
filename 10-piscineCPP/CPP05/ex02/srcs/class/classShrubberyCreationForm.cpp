/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classShrubberyCreationForm.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 08:14:49 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 10:24:05 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm("ShrubberyCreationForm", 145, 137){}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & rhs) : AForm("ShrubberyCreationForm", 145, 137){*this = rhs;}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137), _target(target){}

ShrubberyCreationForm::~ShrubberyCreationForm(void){}

ShrubberyCreationForm & ShrubberyCreationForm::operator=(ShrubberyCreationForm const & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

static void	executeOrder66(std::string file_name)
{
	std::fstream	my_file;

	my_file.open(file_name, std::ios::out);
	if (!my_file.is_open())
		std::cerr << "Failed to open the file " << file_name << std::endl;
	if (my_file.is_open())
	{
		my_file << "\n"
		<<"               ,@@@@@@@,\n"
		<<"       ,,,.   ,@@@@@@/@@,  .oo8888o.\n"
		<<"    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o'\n"
		<<"   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
		<<"   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
		<<"   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'\n"
		<<"   `&%\\ ` /%&'    |.|        \\ '|8'\n"
		<<"       |o|        | |         | |\n"
		<<"       |.|        | |         | |\n"
		<<"    \\_/._\\//__/__/  ,\\__//__\\/.  \\_//__/_\n"
		<<"==========================================\n\n";
		my_file.close();
	}
}

void	ShrubberyCreationForm::execute(const Bureaucrat& executor) const
{
	if (this->getSigned() == false)
		throw (ShrubberyCreationForm::FormNotSignedException());
	if (this->getGradeToExecute() < executor.getGrade())
    {
        std::cout << this->getName() << " couldn't execute bacause : ";
        throw (ShrubberyCreationForm::GradeTooLowException());
    }
		
	executeOrder66(this->_target + "_shru");
}
