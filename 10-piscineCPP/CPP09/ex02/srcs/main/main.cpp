/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@42student.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2023/03/24 10:52:25 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

class MergeSortException : public std::exception
{
    public:
        const char* what() const throw()
        {
            return "Error";
        }
};

int main(int argc, char* argv[])
{
    std::vector<int>    numbers;
    std::vector<int>    sortedVector;
    std::deque<int>     sortedDeque;
    struct timeval      start;
    struct timeval      end;

    try
    {
        if (argc < 2)
            throw MergeSortException();

        for (int i = 1; i < argc; ++i)
        {
            int number = std::atoi(argv[i]);
            if (number < 1)
                throw MergeSortException();
            numbers.push_back(number);
        }

        // Display the unsorted sequence
        std::cout << "Before: ";
        for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
            std::cout << *it << ' ';
        std::cout << std::endl; 

        // Sort the vector
        sortedVector = numbers;
        gettimeofday(&start, NULL);
        mergeInsertSort(sortedVector);
        gettimeofday(&end, NULL);
        float elapsed_time = end.tv_usec - start.tv_usec;

        // Display the sorted vector
        std::cout << "After: ";
        for (std::vector<int>::iterator it = sortedVector.begin(); it != sortedVector.end(); it++)
            std::cout << *it << ' ';
        std::cout << std::endl; 

        // Display the time of the process.
        std::cout << "Time to process a range of " << numbers.size() << " elements with std::vector:\t" << elapsed_time << " ms" << std::endl;

        // Sort the sequence using std::deque
        sortedDeque.assign(numbers.begin(), numbers.end());
        gettimeofday(&start, NULL);
        mergeInsertSort(sortedDeque);
        gettimeofday(&end, NULL);
        elapsed_time = end.tv_usec - start.tv_usec;

        //  Display the time of the process.
        std::cout << "Time to process a range of " << numbers.size() << " elements with std::deque:\t" << elapsed_time << " ms" << std::endl;
    }
    catch (const MergeSortException& ex)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    return 0;
}
