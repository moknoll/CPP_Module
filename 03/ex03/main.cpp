/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:19:25 by mknoll            #+#    #+#             */
/*   Updated: 2025/12/11 13:30:30 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main(){
	
	// std::cout << "=== Testing ClapTrap ===" << std::endl;
	// ClapTrap Bob("Bob");
	// std::string Ross = "Ross";

	// Bob.attack(Ross);
	// Bob.beRepaired(10);
	// Bob.takeDamage(10);
	
	// std::cout << "\n=== Testing ScavTrap ===" << std::endl;
	// ScavTrap Joe("Joe");
	
	// Joe.attack(Ross);
	// Joe.beRepaired(15);
	// Joe.takeDamage(20);
	// Joe.guardGate();
	
	// std::cout << "\n=== Testing FragTrap ===" << std::endl;
	// FragTrap Alice("Alice");
	
	// Alice.attack(Ross);
	// Alice.beRepaired(25);
	// Alice.takeDamage(30);
	// Alice.highFivesGuys();

	std::cout << "\n=== Testing DiamondTrap ===" << std::endl; 
	DiamondTrap Tim; 
	
	Tim.whoAmI();
	Tim.attack("Enemy");
	Tim.guardGate();
	Tim.highFivesGuys();
	
	std::cout << "\n=== End of Tests ===" << std::endl;
	
	return (0);
}