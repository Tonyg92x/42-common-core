/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/10 13:35:32 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include <iostream>

int	main(void)
{
	Data i;
    
    std::cout << "Adress of object data = " << &i << std::endl;
    std::cout << "Address of object data through serialize = " << serialize(&i) << std::endl;
    std::cout << "Address of object data through serialize then through deserialise = " << deserialize(serialize(&i)) << std::endl;;
    
    std:: cout << "In other word's -> " << &i << " = " << deserialize(serialize(&i)) << std::endl;
	return (0);
}
