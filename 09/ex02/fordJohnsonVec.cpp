/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fordJohnsonVec.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:30:00 by mknoll            #+#    #+#             */
/*   Updated: 2025/12/19 15:10:21 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <algorithm>
#include <cmath>

// Comparison function for pairs (C++98 compatible)
bool comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.second < b.second;
}

// Jacobsthal sequence: J(0)=0, J(1)=1, J(n)=J(n-1)+2*J(n-2)
int jacobsthal(int n)
{
    if (n == 0) 
        return 0;
    if (n == 1) 
        return 1;
    return (jacobsthal(n-1) + 2 * jacobsthal(n-2));
}

// Generate Jacobsthal insertion sequence
std::vector<int> generateJacobsthalSequence(int size)
{
    std::vector<int> sequence;
    int j = 3; // Start from J(3) = 5
    int lastJ = jacobsthal(2); // J(2) = 1
    
    while (lastJ < size)
    {
        int currentJ = jacobsthal(j);
        // Add numbers from currentJ down to lastJ+1
        for (int i = std::min(currentJ, size); i > lastJ; --i)
            sequence.push_back(i);
        lastJ = currentJ;
        j++;
    }
    return sequence;
}

// Ford-Johnson merge-insert sort for std::vector
void fordJohnsonSortVector(std::vector<int>& vec)
{
    if (vec.size() <= 1) return;
    
    // Step 1: Group elements into pairs and sort each pair
    std::vector<std::pair<int, int> > pairs;
    bool hasOddElement = vec.size() % 2 == 1;
    int oddElement = hasOddElement ? vec.back() : 0;
    
    // Create pairs and sort them
    size_t pairCount = hasOddElement ? vec.size() - 1 : vec.size();
    for (size_t i = 0; i < pairCount; i += 2)
    {
        int first = vec[i];
        int second = vec[i + 1];
        if (first > second)
            pairs.push_back(std::make_pair(second, first));
        else
            pairs.push_back(std::make_pair(first, second));
    }
    
    // Step 2: Sort pairs by their larger elements (second element)
    std::sort(pairs.begin(), pairs.end(), comparePairs);
    
    // Step 3: Build main chain with larger elements
    std::vector<int> mainChain;
    std::vector<int> pendantElements;
    
    // First element of first pair goes to main chain
    if (!pairs.empty())
        mainChain.push_back(pairs[0].first);
    // All larger elements go to main chain
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        mainChain.push_back(pairs[i].second);
        // Skip first pair's smaller element (already in main chain)
        if (i != 0) 
            pendantElements.push_back(pairs[i].first);
    }
    
    // Step 4: Insert pendant elements using Jacobsthal sequence
    std::vector<int> insertionOrder = generateJacobsthalSequence(pendantElements.size());
    
    // Insert all pendant elements using the Jacobsthal order where possible
    std::vector<bool> inserted(pendantElements.size(), false);
    
    // First, insert elements according to Jacobsthal sequence
    for (size_t i = 0; i < insertionOrder.size(); ++i) 
    {
        int index = insertionOrder[i];
        if (index > 0 && index <= (int)pendantElements.size()) 
        {
            int element = pendantElements[index - 1]; // Convert to 0-based index
            std::vector<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), element);
            mainChain.insert(pos, element);
            inserted[index - 1] = true;
        }
    }
    
    // Insert any remaining pendant elements that weren't covered by Jacobsthal sequence
    for (size_t i = 0; i < pendantElements.size(); ++i) 
    {
        if (!inserted[i]) 
        {
            int element = pendantElements[i];
            std::vector<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), element);
            mainChain.insert(pos, element);
        }
    }
    
    // Step 5: Insert odd element if it exists
    if (hasOddElement) {
        std::vector<int>::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), oddElement);
        mainChain.insert(pos, oddElement);
    }
    
    // Replace original vector with sorted result
    vec = mainChain;
}
