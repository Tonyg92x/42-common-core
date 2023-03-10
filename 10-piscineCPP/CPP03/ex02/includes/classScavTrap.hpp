/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classScavTrap.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:21:09 by aguay             #+#    #+#             */
/*   Updated: 2022/07/04 14:49:41 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSSCAVTRAP_HPP
# define CLASSSCAVTRAP_HPP

#include "classClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	public:

		ScavTrap(void);
		ScavTrap(std::string name);
		ScavTrap(ScavTrap const & rhs);
		~ScavTrap(void);

		ScavTrap & operator=(ScavTrap const & rhs);

		void	guardGate(void) const;
};

#endif