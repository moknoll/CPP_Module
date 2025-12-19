/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:02:26 by mknoll            #+#    #+#             */
/*   Updated: 2025/12/10 13:23:48 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP_HPP
#define CLAP_TRAP_HPP

#include <iostream>
#include <string> 

class ClapTrap{
	private:
		std::string name;
		int hitPoints;
		int energyPoints;
		int attackDamage;
	
	public:
		ClapTrap( );
		~ClapTrap();
		ClapTrap( std:: string name );
		ClapTrap( const ClapTrap &obj );
		ClapTrap &operator=(const ClapTrap &obj );
		
		void attack( const std::string& target);
		void takeDamage( unsigned int amount);
		void beRepaired(unsigned int amount);

};

#endif