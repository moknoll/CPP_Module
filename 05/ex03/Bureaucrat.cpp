/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:39:17 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/12/03 11:59:08 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

// Constructors
Bureaucrat::Bureaucrat() : _name("default"), _grade(150)
{
    std::cout << "Default Constructor called for Bureaucrat" << std::endl; 
    return; 
}

Bureaucrat::~Bureaucrat()
{
    std::cout << "Destructor called for Bureaucrat" << std::endl; 
    return ;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name), _grade(grade)
{
    if (grade < 1)
    {
        throw GradeTooHighException(); 
    }
    else if (grade > 150)
    {
        throw GradeTooLowException(); 
    }
    return ; 
}

Bureaucrat::Bureaucrat(const Bureaucrat& obj) : _name(obj._name), _grade(obj._grade)
{
    std::cout << "Copy Constructor called for Bureaucrat" << std::endl; 
    return ; 
}

// Bureaucrat &Bureaucrat:: operator=(const Bureaucrat &obj)
// {
//     std::cout << "Copy Assignment constructor called for Bureaucrat" << std::endl; 
//     if (this != &obj)
//     {
//         this->_grade; 
//     }
//     return *this; 
// }

// Getters
const std::string &Bureaucrat::getName() const 
{
    return _name;
}

int Bureaucrat::getGrade() const
{
    return _grade; 
}

//Grade modification
void Bureaucrat::incrementGrade()
{
    if (_grade <= 1)
        throw GradeTooHighException();
    _grade--;
}

void Bureaucrat::decrementGrade()
{
    if (_grade >= 150)
        throw GradeTooLowException();
    _grade++;
}

void Bureaucrat::signForm(AForm &f) const
{
    try
    {
        f.beSigned(*this); 
        std::cout << this->getName() << " signs " << f.getName() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << this->getName() << " cannot sign " << f.getName()
                  << " because " << e.what() << std::endl;
    }
}

//Exception Classes 
const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade is too low!";
}

//Stream overload
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
    os << b.getName() << ", bureaucrat grade " << b.getGrade();
    return os;
}