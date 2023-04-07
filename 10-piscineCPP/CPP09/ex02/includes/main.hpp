#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <sys/time.h>


/*  Insert sort algorith
*/
template <typename Container>
void    insertSort(Container& container)
{
    typename    Container::iterator it = container.begin();
    typename    Container::iterator end = container.end();
    int         x, y;

    while (it != end)
    {
        x = *it;
        it++;
        if (it == end)
            break;
        y = *it;
        if (x > y)
        {
            *it = x;
            it--;
            *it = y;
            it = container.begin();
        }
    }
}

/*  Insert Merge sort algorithm

    It use the merge sort algorithm, but add a insert algorithm
    to containers which are smaller than a given point, in this case 10.
    It avoids spliting in two multiple time since you don't have to reach
    the container size of one for each container.
*/
template <typename Container>
void    mergeInsertSort(Container& container)
{
    if (container.size() <= 1)
        return;

    if (container.size() < 10)
    {
        insertSort(container);
        return;
    }

    // Split the container into two halves
    typename Container::iterator middle = container.begin();
    std::advance(middle, container.size() / 2);
    Container left(container.begin(), middle);
    Container right(middle, container.end());

    // Recursively sort each half
    mergeInsertSort(left);
    mergeInsertSort(right);

    // Merge the two sorted halves into a new container
    Container result;
    std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(result));

    // Assign the sorted elements back to the original container
    container.assign(result.begin(), result.end());
}
