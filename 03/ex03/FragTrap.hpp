/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:33:30 by mknoll            #+#    #+#             */
/*   Updated: 2025/12/11 13:28:47 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAG_TRAP_HPP
#define FRAG_TRAP_HPP

#include "ScavTrap.hpp"

class FragTrap: virtual public ClapTrap{
	public:
		FragTrap();
		~FragTrap();
		FragTrap( std::string name );
		FragTrap ( const FragTrap &obj);
		FragTrap &operator=(const FragTrap &obj);

		void highFivesGuys(void);
		int getDamage();
		
};

#endif 