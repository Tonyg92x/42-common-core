/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:20:00 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 14:28:14 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classSample.hpp"

//	Learning Ad-hoc polymorphism

int	main(void)
{
	Sample	exemple;

	exemple.bar('a');
	exemple.bar(12);
	exemple.bar((float)3.14);
	exemple.bar(exemple);
	return (0);
}