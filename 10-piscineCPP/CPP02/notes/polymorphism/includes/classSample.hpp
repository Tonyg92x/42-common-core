/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classSample.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:10:18 by aguay             #+#    #+#             */
/*   Updated: 2022/06/26 14:15:06 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSSAMPLE_HPP
# define CLASSSAMPLE_HPP

class Sample
{
	public:

		Sample(void);
		~Sample(void);

		void	bar(char const c) const;
		void	bar(int const n) const;
		void	bar(float const z) const;
		void	bar(Sample const & i) const;
	
	private:

		
};

#endif