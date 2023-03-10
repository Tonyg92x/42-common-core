/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:02:02 by aguay             #+#    #+#             */
/*   Updated: 2022/06/28 13:09:06 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <bitset>
#include <climits>

int main()
{
    union
    {
        float input; // assumes sizeof(float) == sizeof(int)
        int   output;
    } data;

    data.input = 2.125;

    std::bitset<sizeof(float) * CHAR_BIT> bits(data.output);
    std::cout << bits << std::endl;

    // or
    std::cout << "BIT 4: " << bits[4] << std::endl;
    std::cout << "BIT 7: " << bits[7] << std::endl;
}