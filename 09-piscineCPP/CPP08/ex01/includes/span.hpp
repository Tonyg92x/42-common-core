/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:18:18 by aguay             #+#    #+#             */
/*   Updated: 2022/10/18 12:02:43 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <set>
#include <exception>

class Span
{
    public :

        //  Constructor
        Span(int i);
        Span(const Span& rhs);
        
            
        //  Destructor
        ~Span(void);
        
        //  Operator overload
        Span&   operator=(const Span& rhs);

        //  Methodes
        void            addnumber(int value);
        void            addRange(std::set<int>::iterator start, std::set<int>::iterator end);
        int             size(void) const;
        unsigned int    shortestSpan(void) const;
        unsigned int    longestSpan(void) const;
        std::set<int>   get_set(void) const;

        //  Exception
        class FullException : public std::exception
        {
             public:
                virtual const char  * what() const throw();
        };
        
    private :
    
        int             _size;
        std::set<int>   _set;
        Span(void);  
};
