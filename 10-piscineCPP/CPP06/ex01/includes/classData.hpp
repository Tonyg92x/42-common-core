/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classData.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:34:30 by aguay             #+#    #+#             */
/*   Updated: 2022/10/10 13:23:01 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class   Data
{

    public:

        //  Constructor's
        Data(void);
        Data(Data const & rhs);

        //  Destructor's
        ~Data(void);

        //  Operator overload
        Data &	operator=(Data const & rhs);

        //  Methode
        const void  *get_ptr();
        
    private:
    
        const void  *_ptr;
};



