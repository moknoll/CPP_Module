/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:26:27 by mknoll            #+#    #+#             */
/*   Updated: 2025/12/08 11:03:12 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <exception>

RPN::RPN() {} 

RPN::RPN(char *string) 
{
	parseOperations(string);
}

RPN::~RPN() {}

int RPN::isOperator(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/')
		return 1; 
	return 0;
}

int RPN::isValid(char c)
{
	if(isdigit(c) || isOperator(c))
		return 1; 
	return 0;
}

void RPN::parseOperations(char *str)
{
	size_t i = 0;

	// fill the vector with characters 
	while(str[i])
	{
		if (str[i] == ' ')
    	{
      		i++;
        	continue;
   	 	}
		// skip whitespaces
		if (str[i] == ' ')
			i++;
		if (!isValid(str[i]))
			throw std::runtime_error("Invalid character in string!");
		_tokens += str[i];
		i++;
	}
}

int RPN::ADD(int a, int b) const 
{
	return a + b;
}

int RPN::SUBTRACT(int a, int b)const 
{
	return a - b; 
}

int RPN::MULT(int a, int b) const 
{
	return a * b;
}

int RPN::DIVIDE(int a, int b) const 
{
	if (b == 0)
		throw std::runtime_error("Division by zero!");
	return a / b; 
}

void RPN::calculation()
{
	
	for (size_t i = 0; i < _tokens.size(); i++)
	{
		char current = _tokens[i];
		if(!isOperator(current))
		{
			// convert character digit to integer
			int digit = current - '0';
			
			if (digit < 0 || digit > 9)
				throw std::runtime_error("Invalid digit");
			_numbers.push(digit);
		}
		else
		{
			// Operator found - need 2 operands
			if(_numbers.size() < 2)
				throw std::runtime_error("Not enough operands");
			
			// pop two operands 
			int b = _numbers.top(); 
			_numbers.pop();
			
			int a = _numbers.top(); 
			_numbers.pop();
			
			int result; 
			switch(current)
			{
				case '+': 
					result = ADD(a,b);
					break;
				case '-': 
					result = SUBTRACT(a,b);
					break;
				case '*':
					result = MULT(a,b); 
					break; 
				case '/': 
					result = DIVIDE(a,b);
					break;
			}	
			// push result to stack
			_numbers.push(result);
		}
	}
	
	// Final result should be single value on stack
	if(_numbers.size() != 1)
		throw std::runtime_error("Invalid RPN expression");
	std::cout << _numbers.top() << std::endl;
}