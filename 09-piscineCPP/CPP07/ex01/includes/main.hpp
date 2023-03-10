#pragma once

#include <iostream>
#include <string.h>

template <typename T>
void    iter(T* array, unsigned long length, void (*f)(const T&))
{
    for (unsigned long i = 0; i < length; i++)
        f(array[i]);
}

template <typename T>
void    print(const T & x)
{
    std::cout << x << std::endl;
}
