/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:51:59 by mknoll            #+#    #+#             */
/*   Updated: 2026/01/12 11:08:06 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PMergeMe.hpp"
#include <iostream> 
#include <exception>

int main(int argc, char *argv[])
{
	try
	{
		if (check_args(argc, argv))
		{
		 	PMergeMe pMergeMe;
		 	pMergeMe.fillContainers(argc, argv);
		 	pMergeMe.printBeforeSort();
		 	pMergeMe.sortAndPrint();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
}