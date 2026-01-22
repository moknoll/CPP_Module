/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FordJohnsonDeque.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:49:02 by mknoll            #+#    #+#             */
/*   Updated: 2026/01/22 14:53:25 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PMergeMe.hpp"
#include <iostream>
#include <deque>
#include <algorithm>
#include <utility>

int jacobsthalDeque(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return jacobsthalDeque(n - 1) + 2 * jacobsthalDeque(n - 2);
}


// Ford-Johnson sort for std::vector
void fordJohnsonSortDeque(std::deque<int>& deq)
{
    if (deq.size() <= 1)
        return;
    
    int m = deq.size() / 2;

    std::deque<int> winners;
	std::deque< std::pair<int, int> > pairs;

	// Step 1: Pairwise comparison and splitting into W and L
    for(int i = 0; i < m; i++)
    {
        int a = deq[2 * i];
		int b = deq[2 * i + 1];
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
		winners.push_back(b); // Larger element to W  
    }
	
	// If odd, add the last unpaired element to L
    bool hasOdd = (deq.size() % 2 != 0);
	int unpaired = hasOdd ? deq.back() : -1;
	
    // Step 2: Sort the larger elements recursively
    fordJohnsonSortDeque(winners);
    
	// Step 3: Binary Insertion of smaller elements into sorted
	std::deque<int> main = winners; // Start with sorted larger elements

	// Generate Jacobsthal order
	std::deque<unsigned int> order;
	int k = 1;
	while (true)
	{
		unsigned int jaco = jacobsthalDeque(k);
		if (jaco > pairs.size() -1)
			break;
		bool exists = false;
		for(size_t t = 0; t < order.size(); t++)
		{
			if (order[t] == jaco)
			{
				exists = true;
				break;
			}
		}
		if(!exists)
			order.push_back(jaco);
		k++;
	}
	
	// Add remaining indices
	for(size_t i = 0; i < pairs.size(); i++)
	{
		bool exists = false;
		for(size_t t = 0; t < order.size(); t++)
		{
			if (order[t] == i)
			{
				exists = true;
				break;
			}
		}
		if(!exists)
			order.push_back(i);
	}
	
	// Binary Insert
	for (size_t i = 0; i < order.size(); i++)
	{
		std::pair<int, int> p = pairs[order[i]];
		// until winner found larger than p.second
		std::deque<int>::iterator wpos = std::find(main.begin(), main.end(), p.second);
		// Insert p.first before wpos
		std::deque<int>::iterator pos = std::lower_bound(main.begin(), wpos, p.first);
		main.insert(pos, p.first);
	}

	// If odd, insert unpaired element
	if (hasOdd)
	{
		std::deque<int>::iterator pos = std::lower_bound(main.begin(), main.end(), unpaired);
		main.insert(pos, unpaired);
	}
	
	// Copy back to original vector
	deq = main;
}