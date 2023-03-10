/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:36:41 by aguay             #+#    #+#             */
/*   Updated: 2022/10/18 17:57:44 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
    public :
        typedef typename std::stack<T>::container_type::iterator iterator;

        //  Constructor
        MutantStack(void){};
        MutantStack(const MutantStack& rhs){*this = rhs;};

        //  Destructor
        ~MutantStack(void){};

        //  Operator overload
        MutantStack&    operator=(const MutantStack& rhs)
        {
            std::stack<T>::operator=(rhs);
            return (*this);
        };
        

        //  Methodes
        iterator begin(void){return std::stack<T>::c.begin();};
        iterator end(void){return std::stack<T>::c.end();};
};

