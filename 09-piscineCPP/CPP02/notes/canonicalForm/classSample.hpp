/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classSample.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:10:18 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 16:40:37 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSSAMPLE_HPP
# define CLASSSAMPLE_HPP

#include <iostream>


/*	Une class canonique contient:

	1 Constructeur par default
	1 Constructeur par copie
	1 operateur = (assignation)
	1 destructeur (eventuellement virtuel)
	
*/
class Sample
{
	public:

		Sample(void);								// Constructeur par default
		Sample(int const n);
		Sample(Sample const & src);					// Constructeur par copie
		~Sample(void);								// Destructeur

		Sample & operator=(Sample const & rhs);		// Operateur d'assignation
		
		int getFoo(void) const;
	
	private:

		int _foo;
};

std::ostream & operator<<(std::ostream & o, Sample const & i);

#endif