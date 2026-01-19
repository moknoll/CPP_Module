/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:51:52 by mknoll            #+#    #+#             */
/*   Updated: 2026/01/19 15:19:13 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PMergeMe.hpp"
#include <iostream> 
#include <exception>
#include <cstdlib>
#include <sys/time.h>
#include <algorithm>
#include <unistd.h>
#include <climits>
#include <cmath>
#include <iterator>

PMergeMe::PMergeMe() {}

PMergeMe::PMergeMe(const PMergeMe &other) : vecContainer(other.vecContainer), dequeContainer(other.dequeContainer){}

PMergeMe &PMergeMe::operator=(const PMergeMe &other)
{
	if (this != &other)
	{
		vecContainer = other.vecContainer;
		dequeContainer = other.dequeContainer;
	}
	return *this;
}

PMergeMe::~PMergeMe() {}


// fills both containers with the same integers from argv
void PMergeMe::fillContainers(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		int num = std::atoi(argv[i]);
		vecContainer.push_back(num);
		dequeContainer.push_back(num);
	}
}

void PMergeMe::printBeforeSort()
{
	std::cout << "Before: ";
	if (vecContainer.size() > 5)
	{
		for (size_t i = 0; i < 5; i++)
		{
			std::cout << vecContainer[i] << " ";
		}
		std::cout << "[...]";	
	}
	else
	{
	for (size_t i = 0; i < vecContainer.size(); i++)
		{
			std::cout << vecContainer[i] << " ";
		}
	}
	std::cout << std::endl;
}

// Sort both containers and print performance comparison
void PMergeMe::sortAndPrint()
{
	long long vecStart, vecEnd;
	// long long dequeStart, dequeEnd;
	
	// Sort and time std::vector
	vecStart = get_time_us();
	fordJohnsonSortVector(vecContainer);
	vecEnd = get_time_us();

	// dequeStart = get_time_us();
	// fordJohnsonSortDeque(dequeContainer);
	// dequeEnd = get_time_us();
	
	// Print sorted result
	std::cout << "After: ";
	if (vecContainer.size() > 5)
	{
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << vecContainer[i] << " ";
		}
		std::cout << "[...]";
	}
	else
	{
		for (size_t i = 0; i < vecContainer.size(); i++)
		{
			std::cout << vecContainer[i] << " ";
		}
	}
	std::cout << std::endl;
	
	// Show Performance comparison between vector and deque sorting
	std::cout << "Time to process a range of " 
			  << vecContainer.size() << " elements with std::vector : " 
			  << (vecEnd - vecStart) << " ms" << std::endl;
	// std::cout << "Time to process a range of " << dequeContainer.size() 
	// 		  << " elements with std::deque : " << (dequeEnd - dequeStart) << " ms" << std::endl;
}


//helper functions
int check_args(int argc, char *argv[])
{
	// Check for minimum number of arguments
	if(argc < 2)
		throw std::runtime_error("Not enough arguments");
	else if (argc >= 2)
	{
		// Check each argument for validity
		for (int i = 1; i < argc;i++)
		{
			std::string arg = argv[i];
			for (size_t j = 0; j < arg.length(); j++)
			{
				if (!isdigit(arg[j]))
				{
					throw std::runtime_error("Argument is not valid");
				}
				else if(atoi(argv[i]) < 0 || atoi(argv[i]) > INT_MAX)
				{
					throw std::runtime_error("Not a valid positive integer");
				}
			}	
		}
	}
	return 1;
}

// Get current time in microseconds since epoch 
long long get_time_us()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	// Return microseconds for higher precision
	return (time.tv_sec * 1000000) + time.tv_usec;
}