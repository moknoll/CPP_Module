/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:15:03 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/12/11 13:32:40 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
    // this->hitPoints = FragTrap::hitPoints; 
    //this->energyPoints = ScavTrap::energyPoints; 
    std::Cout 
    this->attackDamage = FragTrap::getDamage();
    std::cout << "Default Constructor called" << std::endl;
    std::cout << "Hit Points: " << this->hitPoints << std::endl;
	std::cout << "Energy Points: " << this->energyPoints << std::endl;
	std::cout << "Attack Damage: " << this->attackDamage << std::endl;

    return ; 
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap Destructor called" << std::endl; 
    return ; 
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name")
{
    this->name = name;
    // this->hitPoints = FragTrap::hitPoints; 
    // this->energyPoints = ScavTrap::energyPoints; 
    // this->attackDamage = FragTrap::attackDamage;   
    std::cout << "DiamondTrap " << name << " constructed" << std::endl;
    std::cout << "Hit Points: " << this->hitPoints << std::endl;
	std::cout << "Energy Points: " << this->energyPoints << std::endl;
	std::cout << "Attack Damage: " << this->attackDamage << std::endl;
    return ; 
}

DiamondTrap::DiamondTrap( const DiamondTrap &obj) : ClapTrap(obj.name + "_clap_name")
{
	std:: cout << "DiamondTrap Copy constructor called" << std::endl;
	this->name = obj.name;
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 30;
	return ;
}

DiamondTrap &DiamondTrap::operator=( const DiamondTrap &obj)
{
	std:: cout << "DiamondTrap Copy assignement Operator called" << std::endl;
	if (this != &obj)
	{
		ClapTrap::operator=(obj);
		this->name = obj.name;
		this->hitPoints = 100;
		this->energyPoints = 50;
		this->attackDamage = 30;
	}
	return *this;
}


void DiamondTrap::attack(const std::string& target)
{
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
    std::cout << "DiamondTrap name: " << this->name
              << ", ClapTrap name: " << ClapTrap::name << std::endl; 
    return ; 
}
