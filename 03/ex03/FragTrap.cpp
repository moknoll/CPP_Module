/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:33:27 by mknoll            #+#    #+#             */
/*   Updated: 2025/12/11 13:28:43 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap(){
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout<< "FragTrap default constructor called" << std::endl; 
}

FragTrap::FragTrap( std:: string name ) : ClapTrap(name){
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << name << " constructor called" << std::endl;
	std::cout << "Hit Points: " << this->hitPoints << std::endl;
	std::cout << "Energy Points: " << this->energyPoints << std::endl;
	std::cout << "Attack Damage: " << this->attackDamage << std::endl;
}

FragTrap::~FragTrap(){
	std::cout << "FragTrap Destructor called" <<std::endl;
}

FragTrap::FragTrap( const FragTrap &obj) : ClapTrap(obj)
{
	std:: cout << "FragTrap Copy constructor called" << std::endl;
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	return ;
}

FragTrap &FragTrap::operator=( const FragTrap &obj)
{
	std:: cout << "FragTrap Copy assignement Operator called" << std::endl;
	if (this != &obj)
	{
		ClapTrap::operator=(obj);
		this->hitPoints = 100;
		this->energyPoints = 100;
		this->attackDamage = 30;
	}
	return *this;
}

void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << this->name << " requests a positive high five!" << std::endl;
}

int FragTrap::getDamage() {
	return this->attackDamage;
}