/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:34:45 by aguay             #+#    #+#             */
/*   Updated: 2022/10/17 13:33:44 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <exception>

template <typename T>
bool  easyfind(T const container, int value)
{
    if (std::find(container.begin(), container.end(), value) != container.end()++)
        return (true);
    return (false);
}
