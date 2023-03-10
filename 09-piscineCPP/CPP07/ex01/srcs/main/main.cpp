/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonyguay <anthonyguay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/13 16:50:25 by anthonyguay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int	main(void)
{
    std::cout << "\nTest int array\n" << std::endl;
    {
        int i[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        iter(i, 10, print);
    }
    std::cout << "\nTest float array\n" << std::endl;
    {
        float i[3] = {1.12, 2.541, 3.1456};
        iter(i, 3, print);
    }
    std::cout << "\nTest string array\n" << std::endl;
    {
        std::string i[3] = {"Sup!", "Anticonstitutionnellement", "Bob yo ca va"};
        iter(i, 3, print);
    }
	return (0);
}
