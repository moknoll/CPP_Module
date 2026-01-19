/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FordJohnson.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:06:00 by mknoll            #+#    #+#             */
/*   Updated: 2026/01/19 15:18:43 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PMergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

// Jacobsthal number generator
int jacobsthal(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

// Ford-Johnson sort for std::vector
void fordJohnsonSortVector(std::vector<int>& vec)
{
    if (vec.size() <= 1)
        return;
    
    int m = vec.size() / 2;
	std::cout << "Number of pairs : " << m << std::endl;

    std::vector<int> W;
    std::vector<int> L;
	std::vector<int> main;
    
	// Step 1: Pairwise comparison and splitting into W and L
    for(int i = 0; i < m; i++)
    {
        if (vec[2*i] > vec[2*i + 1])
           std::swap(vec[2*i], vec[2*i + 1]);
        W.push_back(vec[2*i + 1]);
        L.push_back(vec[2*i]);    
    }
	// If odd, add the last unpaired element to L
    if (vec.size() % 2 == 1)
	{
        L.push_back(vec[vec.size() - 1]);
		std::cout << "Unpaired element added to L: " << vec[vec.size() - 1] << std::endl;
	}
    // Step 2: Sort the larger elements recursively
    fordJohnsonSortVector(W);
    
    std::cout << "Sorted larger elements (W): ";
    for (size_t i = 0; i < W.size(); i++)
    {
        std::cout << W[i] << " ";
    }
    std::cout << std::endl;
    
	// Step 3: Binary Insertion of smaller elements into sorted
	main = W; // Start with sorted larger elements

	if (!L.empty())
		main.insert(main.begin(), L[0]); // Insert first element of L

	for (size_t i = 1; i < L.size(); i++)
	{
		int oddElem = L[i];
		int j = 0;
		// Find position using Jacobsthal sequence
		while (j < static_cast<int>(main.size()))
		{
			int pos = jacobsthal(j);
			if (pos >= static_cast<int>(main.size()) || main[pos] >= oddElem)
				break;
			j++;
		}
		main.insert(main.begin() + j, oddElem);
	}
	vec = main;
}