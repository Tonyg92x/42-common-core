/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:11 by aguay             #+#    #+#             */
/*   Updated: 2022/10/19 15:51:37 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

//  Constructor
Span::Span(void) : _size(0){};
Span::Span(int i) : _size(i){};
Span::Span(const Span& rhs) : _size(rhs.size()){*this = rhs;}

//  Destructor
Span::~Span(void){};

//  Operator overload
Span&   Span::operator=(const Span& rhs)
{
    if (this != &rhs)
    {
        this->_size = rhs.size();
        _set = rhs.get_set();
    }
    return (*this);
}

void    Span::addnumber(int value)
{
    if (_set.size() < static_cast<unsigned int>(_size))
        _set.insert(value);
    else
        throw (Span::FullException());
}

unsigned int Span::shortestSpan(void) const
{
    int                     petit = 99999999;
    int                     temp;

    for (std::set<int>::iterator ite = _set.begin(); ite != _set.end(); ite++)
    {
        if (ite != _set.begin())
        { 
            if (std::abs(*ite - temp) < petit)
                petit = std::abs(*ite - temp);
        }
        temp = *ite;
    }
    return (petit);
}

unsigned int Span::longestSpan(void) const
{
    int                     longest = 0;
    int                     temp;

    for (std::set<int>::iterator ite = _set.begin(); ite != _set.end(); ite++)
    {
        if (ite != _set.begin())
        { 
            if (std::abs(*ite - temp) > longest)
                longest = std::abs(*ite - temp);
        }
        temp = *ite;
    }
    return (longest);
}

void  Span::addRange(std::set<int>::iterator start, std::set<int>::iterator end)
{
    for (std::set<int>::iterator begin = start; begin != end; begin++)
        addnumber(*begin);
}

std::set<int>   Span::get_set(void) const {return (_set);}

int   Span::size(void) const {return _size;};

//  Exception
const char * Span::FullException::what() const throw()
{
    return ("\033[31mSpan is full");
}
