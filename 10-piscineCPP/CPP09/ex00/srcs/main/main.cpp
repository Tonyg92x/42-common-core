/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@42student.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2023/03/21 17:43:11 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void    error(void) {std::cout <<  "\033[31mError\033[0m" << std::endl;exit(1);}

bool    validDate(std::string date)
{
    if (date.size() != 10)
        return (false);
    for (unsigned long i = 0; i < date.size(); i++)
    {
        if ((date[i] > 47 && date[i] < 58) || date[i] == '-')
            continue;
        else
            return (false);
    }
    return (true);
}

bool    validValue(double value)
{
    bool is_int = (std::floor((float) value) == value) && (std::ceil((float) value) == value);

    if (is_int)
    {
        if (value < 0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            return (false);
        }
        else if (value > 100)
        {
            std::cout << "Error: too large number." << std::endl;
            return (false);
        }
    }
    return (true);
}

int	main(int argc, char **argv)
{
    //  Wrong number of argument protection
    if (argc != 2)
        error();

    //  Get the file as argument an protection if it's not possible to read it.
    std::map<std::string, double>       DB;
    std::string                         inputFileName = argv[1];
    std::ifstream                       inputFile, dbFile;

    //  Look if the input file is openable, else error
    inputFile.open(inputFileName, std::ios::in);
    if (!inputFile.is_open())
        error();

    //  Store all csv values into a the map container.
    std::string                         line;
    std::string                         date;
    std::string                         value;

    dbFile.open("data.csv", std::ios::in);
    while (std::getline(dbFile, line))
    {
        if (line.size() > 11)
        {
            date = line.substr(0, line.find_first_of(", \n\0"));
            line = line.substr(date.size() + 1, std::string::npos);
            value = line.substr(0, std::string::npos);
            try{DB.insert(std::pair<std::string, double>(date, std::stod(value)));}catch(const std::exception& e){}
        }
    }
    dbFile.close();

    //  Parse every line of the input file and output the result
    double      nbBit;
    std::map<std::string, double>::iterator it;

    while (std::getline(inputFile, line))
    {
        date = line.substr(0, line.find_first_of(", \n\0"));
        if (validDate(date))
        {
            try
            {
                value = line.substr(date.size() + 3, std::string::npos);
                nbBit = std::stod(value);
                if (validValue(nbBit))
                {
                    it = DB.find(date);
                    if (it == DB.end())
                    {
                        it = DB.lower_bound(date);
                        it--;
                    }
                    std::cout << date << " => " << value << " = " << nbBit * it->second << std::endl;
                }
            }
            catch(const std::exception& e)
            {
                std::cout << "Error: bad input => " << line << std::endl;
            }
        }
    }
    return (0);
}
