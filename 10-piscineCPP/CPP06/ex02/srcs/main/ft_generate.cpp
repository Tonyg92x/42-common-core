/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:57:09 by aguay             #+#    #+#             */
/*   Updated: 2022/10/10 14:30:54 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include <sys/time.h>
#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void)
{
    Base *x;
    struct timeval  tp;
    gettimeofday(&tp, NULL);

    if (tp.tv_usec < 333333)
        x = new A;
    else if (tp.tv_usec > 666666)
        x = new C;
    else
        x = new B;
    
    return (x);
}

