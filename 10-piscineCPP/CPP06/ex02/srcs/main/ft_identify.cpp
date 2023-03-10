/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identify.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:57:06 by aguay             #+#    #+#             */
/*   Updated: 2022/10/10 14:49:07 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

void identify(Base& p)
{
    //  Is it A ?
    try
    {
        A &a = dynamic_cast<A &>(p);
        (void) a;
        std::cout << &p << " ref is a class A." << std::endl;
        return;
    }
    catch(const std::exception& e){}

    //  Ok.. Is it B then ?
    try
    {
        B &b = dynamic_cast<B &>(p);
        (void) b;
        std::cout << &p << " ref is a class B." << std::endl;
        return;
    }
    catch(const std::exception& e){}

    //  Ok.. Is it C ?
    try
    {
        C &c = dynamic_cast<C &>(p);
        (void) c;
        std::cout << &p << " ref is a class C." << std::endl;
        return;
    }
    catch(const std::exception& e){}

    std::cout << &p << " ref is a class Base." << std::endl;
}

void identify(Base* p)
{
    A *a = dynamic_cast<A *>(p);

    if (a)
    {
        std::cout << &p << " pointer is a class A." << std::endl;
        return;
    }

    B *b = dynamic_cast<B *>(p);

    if (b)
    {
        std::cout << &p << " pointer is a class B." << std::endl;
        return;
    }
    
    C *c = dynamic_cast<C *>(p);

    if (c)
    {
        std::cout << &p << " pointer is a class C." << std::endl;
        return;
    }
}
