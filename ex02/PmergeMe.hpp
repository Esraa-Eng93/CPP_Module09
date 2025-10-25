/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:11:59 by esraa             #+#    #+#             */
/*   Updated: 2025/10/25 18:42:36 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <limits>
#include <iomanip>

class PmergeMe
{
	private:
		std::vector<unsigned int> vect;
		std::deque<unsigned int> deq;

		void mergeInsertVector(std::vector<unsigned int> &v, int left, int right);
		void mergeInsertDeque(std::deque<unsigned int> &d, int left, int right);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		bool addNumber(int n);
		void printBefore() const;
		void printAfter() const;
		void sortAndMeasure();
};


#endif