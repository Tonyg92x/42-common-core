/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/10/18 12:10:29 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "span.hpp"

int	main(void)
{
	Span    i(5);

    i.addnumber(5);
    i.addnumber(3);
    i.addnumber(500);
    i.addnumber(-1);
    i.addnumber(4);

    std::set<int>           a = i.get_set();
    std::set<int>::iterator ite = a.begin();
    for (int x = 0; x < i.size(); x++)
        std::cout << *ite++ << std::endl;
    std::cout << "Longest span = " << i.longestSpan() << std::endl;
    std::cout << "Shortest span = " << i.shortestSpan() << std::endl;

    Span    x(1000);
    x.addRange(a.begin(), a.end());
    a = x.get_set();
    ite = a.begin();
    for (int x = 0; x < 5; x++)
        std::cout << *ite++ << std::endl;
	return (0);
}
