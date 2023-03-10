/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContactClass.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:17:40 by aguay             #+#    #+#             */
/*   Updated: 2022/06/16 17:31:23 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ContactClass.hpp"

//	Constructor
Contact::Contact(std::string info[5])
{
	Contact::setFirstName(info[0]);
	Contact::setLastName(info[1]);
	Contact::setNickName(info[2]);
	Contact::setPhoneNumber(info[3]);
	Contact::setDarkSecret(info[4]);
	return;
}

//	Deconstructor
Contact::~Contact(void)
{
	return ;
}

// Get methods
std::string Contact::getFirstName(void) const
{
	return (this->_FirstName);
}

std::string Contact::getLastName(void) const
{
	return (this->_LastName);
}

std::string Contact::getNickName(void) const
{
	return (this->_NickName);
}

std::string Contact::getPhoneNumber(void) const
{
	return (this->_PhoneNumber);
}

std::string Contact::getDarkSecret(void) const
{
	return (this->_DarkSecret);
}

//	Set methods
void	Contact::setFirstName(std::string FN)
{
	this->_FirstName = FN;
	return;
}

void	Contact::setLastName(std::string LN)
{
	this->_LastName = LN;
	return;
}

void	Contact::setNickName(std::string NN)
{
	this->_NickName = NN;
	return;
}

void	Contact::setPhoneNumber(std::string PN)
{
	this->_PhoneNumber = PN;
	return;
}

void	Contact::setDarkSecret(std::string DS)
{
	this->_DarkSecret = DS;
	return;
}
