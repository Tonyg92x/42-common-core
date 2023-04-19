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

class invalidValueException : public std::exception
{
    public:
        const char* what() const throw()
        {
            return "Error";
        }
};

bool    validDate(std::string date)
{
    try
    {
        for (unsigned long i = 0; i < date.size(); i++)
        {
            if ((date[i] > 47 && date[i] < 58) || date[i] == '-' || date[i] == ' ')
                continue;
            else
                return (false);
        }
        int year = std::stoi(date.substr(0, date.find_first_of("-\0")));
        date = date.substr(date.find_first_of("-\0") + 1, std::string::npos);
        int month = std::stoi(date.substr(0, date.find_first_of("-\0")));
        date = date.substr(date.find_first_of("-\0") + 1, std::string::npos);
        int day = std::stoi(date);
        if (year < 1 || month < 1 || day < 1)
            return (false);
        if (year > 2022 || month > 12 || day > 31)
            return (false);
        if (month == 2 && day > 28)
            return (false);
        if (month <= 7 && month % 2 == 0 && day > 30)
            return (false);
        if (month > 7 && month % 2 != 0 && day > 30)
            return (false);
    }
    catch(const std::exception& e)
    {
        return (false);
    }
    return (true);
}

std::string removeWS(std::string str)
{
    unsigned long x = str.find_first_of(' ');
    while (x != str.npos)
    {
        str.erase(x, 1);
        x = str.find_first_of(' ');
    }
    return (str);
}

bool    validValue(double value)
{
    if (value < 0)
        throw invalidValueException();
    else if (value > 1000)
        throw invalidValueException();
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
        line = removeWS(line);
        date = line.substr(0, line.find_first_of(",|"));
        if (validDate(date))
        {
            try
            {
                value = line.substr(line.find_first_of('|') + 1, std::string::npos);
                for (unsigned int i = 0; i < value.size(); i++)
                {
                    if ((line[i] < 48 || line[i] > 57) && line[i] != '.')
                        throw invalidValueException();
                }
                nbBit = std::stod(value);
                if (validValue(nbBit))
                {
                    it = DB.find(date);
                    if (it == DB.end())
                    {
                        it = DB.lower_bound(date);
                        if (it != DB.begin())
                            it--;
                    }
                    std::cout << date << " => " << value << " = " << nbBit * it->second << std::endl;
                }
                else
                    throw invalidValueException();
            }
            catch(const std::exception& e)
            {
                std::cout << "Error: bad input => " << line << std::endl;
            }
        }
        else if (date != "date" && date != "")
            std::cout << "Error: invalid date => " << date << std::endl;

    }
    inputFile.close();
    return (0);
}
