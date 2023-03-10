/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classHarl.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:39:24 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 13:29:07 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSHARL_HPP
# define CLASSHARL_HPP

#include <string>
#include <iostream>

class Harl
{
	public:

		Harl(void);
		~Harl(void);
		void	complain(std::string level);
		void	filter(std::string level);
		int		getLevelCode(std::string level);

	private:

		void		debug(void);
		void		info(void);
		void		warning(void);
		void		error(void);
		
		std::string	levels[4];

		//	Pointer to those functions
		void (Harl::*fonctionPtr[4])();
};




#endif