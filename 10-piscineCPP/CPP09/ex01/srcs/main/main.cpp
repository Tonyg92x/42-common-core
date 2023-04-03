/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@42student.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2023/03/21 18:18:37 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

bool    isNum(char c)
{
    if (c < 58 && c > 47)
        return (true);
    return (false);
}
int	main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error\n" << std::endl;
        exit (1);
    }

    std::stack<int>     pile;
    std::string         input = argv[1];
    int                 value0;
    int                 value1;
    int                 result;

    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] != '+' && input[i] != '-' && input[i] != '/' && input[i] != '*' && input[i] != ' ' && !isNum(input[i]))
        {
            std::cout << "Error\n" << std::endl;
            exit (1);
        }
    }

    for (size_t i = 0; i < input.size(); i++)
    {
        if (isNum(input[i]))
            pile.push(input[i] - 48);
        else if (input[i] != ' ')
        {
            if (pile.size() < 2)
            {
                std::cout << "Error\n" << std::endl;
                exit (1);
            }
            value0 = pile.top();
            pile.pop();
            value1 = pile.top();
            pile.pop();

            switch (input[i])
            {
                case '+':
                    result = value1 + value0;
                    break;
                case '-':
                    result = value1 - value0;
                    break;
                case '/':
                    result = value1 / value0;
                    break;
                case '*':
                    result = value1 * value0;
                    break;
                default:
                    break;
            }
            pile.push(result);
        }
    }
    if (pile.size() == 1)
        std::cout << pile.top() << std::endl;
    else
        std::cout << "Error: missing one operand." << std::endl;
    return (0);
}
