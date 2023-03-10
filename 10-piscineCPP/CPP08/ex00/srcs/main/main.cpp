/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/17 13:45:44 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int	main(void)
{
	std::list<int>  lst1;

    std::cout << "\033[32mTest for list container\n\033[0m" << std::endl; 
    std::cout << "Lets insert numer from 0 to 15 in the list and then use easy find from -5 to 20" << std::endl;
    for (int i = 0; i < 15; i++)
        lst1.push_back(i);
    for (int i = -5; i < 21; i++)
    {
        if (easyfind(lst1, i))
            std::cout << "There is " << i << " in the list" << std::endl;
        else
            std::cout << "There isn't " << i << " in the list" << std::endl;
    }

    
    std::vector<float> vec1;

    std::cout << "\033[32m\nTest for vector container\n\033[0m" << std::endl; 
    std::cout << "Lets insert numer from 0 to 15 in the list and then use easy find from -5 to 20" << std::endl;
    for (float i = 0.f; i < 15; i++)
        vec1.push_back(i);
    for (float i = -5; i < 21; i++)
    {
        if (easyfind(vec1, i))
            std::cout << "There is " << i << " in the list" << std::endl;
        else
            std::cout << "There isn't " << i << " in the list" << std::endl;
    }

	return (0);
}
