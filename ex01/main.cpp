/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:18:28 by esraa             #+#    #+#             */
/*   Updated: 2025/10/21 22:06:27 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
        std::cerr << "Error" << std::endl;
        return 1;
    }
	RBN rbn(av[1]);
	double res = rbn.Evaluate();
	std::cout << res <<std::endl;
	return 0;
}