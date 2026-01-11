/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:26:29 by mknoll            #+#    #+#             */
/*   Updated: 2025/12/08 14:49:16 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <string>
#include <stack>

class RPN
{
	private: 
	std::stack<int> _numbers;
	std::string _tokens;
	
	public: 
		RPN();
		RPN(char *str);
		RPN(const RPN &obj);
		RPN &operator=(const RPN& obj);
		~RPN();
	
		void calculation();
		void parseOperations(char *str);
		int isValid(char c);
		int isOperator(char c);

		int ADD(int a, int b) const;
		int SUBTRACT(int a, int b) const; 
		int MULT(int a, int b) const; 
		int DIVIDE(int a, int b) const;
};

#endif