/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContactClass.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:16:19 by aguay             #+#    #+#             */
/*   Updated: 2022/06/16 17:30:43 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACTCLASS_HPP
# define CONTACTCLASS_HPP
#include <string.h>
#include <iostream>

class Contact
{
	public:

		//	Constructor and destructor
		Contact(std::string info[5]);
		~Contact(void);

		//	GetFunction
		std::string		getFirstName(void) const;
		std::string		getLastName(void) const;
		std::string		getNickName(void) const;
		std::string		getPhoneNumber(void) const;
		std::string		getDarkSecret(void) const;

		//	SetFunction
		void			setFirstName(std::string FN);
		void			setLastName(std::string LN);
		void			setNickName(std::string NN);
		void			setPhoneNumber(std::string PN);
		void			setDarkSecret(std::string DS);

	private:
		std::string		_FirstName;
		std::string		_LastName;
		std::string		_NickName;
		std::string		_PhoneNumber;
		std::string		_DarkSecret;
};
#endif