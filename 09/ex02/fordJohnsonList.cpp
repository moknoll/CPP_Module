/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fordJohnsonList.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:30:00 by mknoll            #+#    #+#             */
/*   Updated: 2025/12/19 15:15:04 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <vector>
#include <algorithm>
#include <cmath>

// Comparison function for pairs (C++98 compatible)
bool comparePairsList(const std::pair<int, int>& a, const std::pair<int, int>& b) 
{
    return a.second < b.second;
}

// Jacobsthal sequence: J(0)=0, J(1)=1, J(n)=J(n-1)+2*J(n-2)
int jacobsthalList(int n) 
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return (jacobsthalList(n-1) + 2 * jacobsthalList(n-2));
}

// Generate Jacobsthal insertion sequence
std::vector<int> generateJacobsthalSequenceList(int size)
{
    std::vector<int> sequence;
    int j = 3; // Start from J(3) = 5
    int lastJ = jacobsthalList(2); // J(2) = 1
    
    while (lastJ < size)
    {
        int currentJ = jacobsthalList(j);
        // Add numbers from currentJ down to lastJ+1
        for (int i = std::min(currentJ, size); i > lastJ; --i)
            sequence.push_back(i);
        lastJ = currentJ;
        j++;
    }
    return sequence;
}

// Helper function to get iterator at specific position in list
std::list<int>::iterator getIteratorAt(std::list<int>& lst, int position)
{
    std::list<int>::iterator it = lst.begin();
    std::advance(it, position);
    return it;
}

// Helper function to perform binary search insertion in list
void insertSorted(std::list<int>& mainChain, int element)
{
    if (mainChain.empty())
    {
        mainChain.push_back(element);
        return;
    }
    
    // For small lists, use linear search (more efficient for lists)
    if (mainChain.size() < 10)
    {
        std::list<int>::iterator it = mainChain.begin();
        while (it != mainChain.end() && *it < element)
            ++it;
        mainChain.insert(it, element);
        return;
    }
    
    // Binary search for larger lists (convert to vector temporarily)
    std::vector<int> temp(mainChain.begin(), mainChain.end());
    std::vector<int>::iterator pos = std::upper_bound(temp.begin(), temp.end(), element);
    int index = pos - temp.begin();
    
    std::list<int>::iterator it = mainChain.begin();
    std::advance(it, index);
    mainChain.insert(it, element);
}

// Ford-Johnson merge-insert sort for std::list
void fordJohnsonSortList(std::list<int>& lst)
{
    if (lst.size() <= 1) return;
    
    // Step 1: Group elements into pairs and sort each pair
    std::list<std::pair<int, int> > pairs;
    bool hasOddElement = lst.size() % 2 == 1;
    int oddElement = 0;
    
    std::list<int>::iterator it = lst.begin();
    
    // Create pairs and sort them
    while (it != lst.end())
    {
        int first = *it;
        ++it;
        
        if (it != lst.end())
        {
            int second = *it;
            ++it;
            
            if (first > second)

                pairs.push_back(std::make_pair(second, first));
            else
                pairs.push_back(std::make_pair(first, second));
            
        }
        else
        {
            oddElement = first;
            hasOddElement = true;
        }
    }
    
    // Step 2: Sort pairs by their larger elements (second element)
    pairs.sort(comparePairsList);
    
    // Step 3: Build main chain with larger elements
    std::list<int> mainChain;
    std::list<int> pendantElements;
    
    // First element of first pair goes to main chain
    if (!pairs.empty())
        mainChain.push_back(pairs.front().first);
    
    // All larger elements go to main chain, smaller ones (except first) to pendant
    std::list<std::pair<int, int> >::iterator pairIt = pairs.begin();
    for (; pairIt != pairs.end(); ++pairIt)
    {
        mainChain.push_back(pairIt->second);
        if (pairIt != pairs.begin()) // Skip first pair's smaller element (already in main)
            pendantElements.push_back(pairIt->first);
    }
    
    // Step 4: Insert pendant elements using Jacobsthal sequence
    if (!pendantElements.empty())
    {
        // Convert pendant list to vector for indexed access
        std::vector<int> pendantVec(pendantElements.begin(), pendantElements.end());
        std::vector<int> insertionOrder = generateJacobsthalSequenceList(pendantVec.size());
        
        std::vector<bool> inserted(pendantVec.size(), false);
        
        // First, insert elements according to Jacobsthal sequence
        for (size_t i = 0; i < insertionOrder.size(); ++i)
        {
            int index = insertionOrder[i];
            if (index > 0 && index <= (int)pendantVec.size())
            {
                int element = pendantVec[index - 1]; // Convert to 0-based index
                insertSorted(mainChain, element);
                inserted[index - 1] = true;
            }
        }
        
        // Insert any remaining pendant elements that weren't covered by Jacobsthal sequence
        for (size_t i = 0; i < pendantVec.size(); ++i)
        {
            if (!inserted[i])
            {
                int element = pendantVec[i];
                insertSorted(mainChain, element);
            }
        }
    }
    
    // Step 5: Insert odd element if it exists
    if (hasOddElement)
        insertSorted(mainChain, oddElement);
    
    // Replace original list with sorted result
    lst = mainChain;
}
