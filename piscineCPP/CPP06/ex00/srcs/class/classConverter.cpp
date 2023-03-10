/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classConverter.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:29:14 by aguay             #+#    #+#             */
/*   Updated: 2022/10/03 15:51:15 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classConverter.hpp"

Converter::Converter(void){};

Converter::Converter(std::string str) : _strValue(str), _type(this->set_type(str)){};

Converter::Converter(Converter const & rhs){*this = rhs;}

Converter::~Converter(void){};

Converter & Converter::operator=(Converter const & rhs)
{
	if (this != &rhs)
    {
        this->_strValue = rhs.getStrValue();
        this->_type = rhs.getType();
    }
	return (*this);
}

std::string Converter::set_type(std::string str)
{
    if (str == "inf" || str == "-inf" || str == "+inf"
        || str == "nan" || str == "nanf"
        || str == "inff" || str == "-inff" || str == "+inff")
        return ("literal");
    if (str.length() - 1  == 0 && !std::isdigit(str[0]))
        return ("char");
    if (str.find('.') != str.npos)
    {
        if (str[str.length() - 1] == 'f')
            return ("float");
        else
            return ("double");
    }
    else
        return ("int");
    return (str);
}

char	Converter::toChar(void) const
{
    const std::string   str = static_cast<const std::string>(this->getStrValue());
    const std::string   type = static_cast<const std::string>(this->getType());

    if (type == "literal")
        throw (Converter::NotDisplayableException());
    if (type == "char" || (type == "int" && !std::isdigit(str[0])))
    {
        char c = static_cast<char>(str[0]);
        if (c < 33 || c > 126)
		    throw (Converter::NotDisplayableException());
        return (c);
    }
    else
    {
        try
        {
            long    value = static_cast<long>(std::stol(str, 0, 10));

             if (value < 33 || value > 126)
                throw(Converter::NotDisplayableException());
            return (value);
        }
        catch(const std::exception& e)
        {
            throw(Converter::NotDisplayableException());
        }
    }
    return (32);
}

int	Converter::toInt(void) const
{
    const std::string str = static_cast<const std::string>(this->getStrValue());

    if (this->_type == "literal")
        throw(Converter::NotDisplayableException());
    else if (this->_type == "char")
        return (static_cast<int>(this->_strValue[0]));
    else
    {
        try
        {
            long    value = static_cast<long>(std::stol(str, 0, 10));
            return (static_cast<int>(value));
        }
        catch(const std::exception& e)
        {
            throw(Converter::NotDisplayableException());
        }
    }
    return (0);
}

float	Converter::toFloat(void) const
{
    const std::string   str = static_cast<const std::string>(this->getStrValue());
    const std::string   type = static_cast<const std::string>(this->getType());


    if (type == "literal")
    {
        if (str == "nan" || str == "nanf")
            std::cout << "nanf";
        else if (str == "inf" || str == "inff")
            std::cout << "inff";
        else if (str == "+inf" || str == "+inff")
            std::cout << "+inff";
        else if (str == "-inf" || str == "-inff")
            std::cout << "-inff";
        throw (Converter::ExitException());
    }
    else
    {
        if (type == "char")
            return (static_cast<float>(str[0]));
        try
        {
            float   value = static_cast<float>(std::stof(str, 0));
            return  (value);
        }
        catch(const std::exception& e)
        {
            throw (Converter::NotDisplayableException());
        }
    }
	return (0);
}

double	Converter::toDouble(void) const
{
	const std::string   str = static_cast<const std::string>(this->getStrValue());
    const std::string   type = static_cast<const std::string>(this->getType());


    if (type == "literal")
    {
        if (str == "nan" || str == "nanf")
            std::cout << "nan";
        else if (str == "inf" || str == "inff")
            std::cout << "inf";
        else if (str == "+inf" || str == "+inff")
            std::cout << "+inf";
        else if (str == "-inf" || str == "-inff")
            std::cout << "-inf";
        throw (Converter::ExitException());
    }
    else
    {
        if (type == "char")
            return (static_cast<float>(str[0]));
        try
        {
            double   value = static_cast<float>(std::stod(str, 0));
            return  (value);
        }
        catch(const std::exception& e)
        {
            throw (Converter::NotDisplayableException());
        }
    }
	return (0);
}

const char *    Converter::UpCastImpossibleException::what() const throw()
{
    return ("\033[31mCouldn't convert\033[33m : Upcast impossible\033[0m");
}

const char *    Converter::DownCastImpossibleException::what() const throw()
{
    return ("\033[31mCouldn't convert\033[33m : Downcast impossible\033[0m");
}

const char *    Converter::NotDisplayableException::what() const throw()
{
    return ("\033[31mCouldn't convert\033[33m : NotDisplayable\033[0m");
}

const char *    Converter::ExitException::what() const throw()
{
    return ("");
}

std::string	Converter::getStrValue(void) const {return (this->_strValue);}

std::string Converter::getType(void) const {return (this->_type);}
