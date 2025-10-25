/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:10:47 by esraa             #+#    #+#             */
/*   Updated: 2025/10/25 18:22:00 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <sequence of positive integers>" << std::endl;
        return 1;
    }

	PmergeMe pm;
	for(int i = 1; i < argc; ++i)
	{
		char *endptr;
		long val = std::strtol(argv[i], &endptr, 10);
		if (*endptr != '\0')
        {
            	std::cerr << "Error: invalid input => " << argv[i] << std::endl;
            	return 1;
        }
		if (val > static_cast<long>(std::numeric_limits<unsigned int>::max()))
        {
            std::cerr << "Error: number too large => " << val << std::endl;
            return 1;
        }

        if (!pm.addNumber(static_cast<int>(val)))
        {
            std::cerr << "Error adding number => " << val << std::endl;
            return 1;
        }
	}

	pm.sortAndMeasure();
	return 0;
}