/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classFragTrap.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 07:38:31 by aguay             #+#    #+#             */
/*   Updated: 2022/08/01 08:06:06 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classClapTrap.hpp"

#ifndef CLASSFRAGTRAP_HPP
# define CLASSFLAGTRAP_HPP

class FragTrap : public ClapTrap
{
	public:

	//	Constructor's
	FragTrap(void);
	FragTrap(std::string name);
	FragTrap(FragTrap const & rhs);
	
	//	Destructor's
	~FragTrap(void);

	//	Overload operator's
	FragTrap & operator=(FragTrap const & rhs);

	//	Method's
	void	highFivesGuys(void);
};

#endif