/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonyguay <anthonyguay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/13 16:18:57 by anthonyguay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int	main(void)
{
    std::cout << "test swap\n" << std::endl;
    {
        int i = 12;
        int j = 43;
        std::cout << "before swap (i,j) = (" << i << "," << j << ")" << std::endl;
        swap(i, j);
        std::cout << "after swap (i,j) = (" << i << "," << j << ")\n" << std::endl;
    }
    {
        float i = 12.5123;
        float j = 43.123542;
        std::cout << "before swap (i,j) = (" << i << "," << j << ")" << std::endl;
        swap(i, j);
        std::cout << "after swap (i,j) = (" << i << "," << j << ")" << std::endl;
    }
    
    std::cout << "\ntest min\n" << std::endl;
    std::cout << "Min = " << min(12, 54) << std::endl;

    std::cout << "\ntest max\n" << std::endl;
    std::cout << "Max = " << max(12, 54) << std::endl;
    
    // std::cout << "\nPDF test's\n" << std::endl;
    int a = 2;
    int b = 3;
    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
    std::string c = "chaine1";
    std::string d = "chaine2";
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	return (0);
}
