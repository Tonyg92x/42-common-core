/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBookClass.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:16:24 by aguay             #+#    #+#             */
/*   Updated: 2022/09/26 07:28:03 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOKCLASS_HPP
# define PHONEBOOKCLASS_HPP

#include "ContactClass.hpp"
#include <iostream>

class PhoneBookClass
{
	public:

		PhoneBookClass(void);
		~PhoneBookClass(void);

		static int		getNbInst(void);
		static int		getIndex(void);
		void			getContact(int index) const;
		void			addContact(Contact *cont);
		void			showRepertoire(void);


	private:

		Contact			*_repertoire[8];
		static size_t	_nbInst;
		static int		_index;

		void			setRepertoire(Contact *cont, int index);
};
#endif
