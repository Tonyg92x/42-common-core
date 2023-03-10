/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:42:37 by jvigneau          #+#    #+#             */
/*   Updated: 2023/01/19 06:43:05 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class User;
class Channel;

class Operator : public User
{
	public:
		Operator();
		Operator(Operator const & rhs);
		~Operator();

		Operator& operator=(Operator const & rhs);

		void		kick(User& user);
		void		mode(Channel &channel);
		void		invite(User &user, Channel &channel);
		void		topic(Channel &channel);
};

#include "User.class.hpp"
#include "Channel.class.hpp"
