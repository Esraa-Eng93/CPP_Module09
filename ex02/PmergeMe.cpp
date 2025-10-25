/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:11:43 by esraa             #+#    #+#             */
/*   Updated: 2025/10/25 19:00:20 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		vect = other.vect;
		deq = other.deq;
	}
	return *this;
}

bool PmergeMe::addNumber(int n)
{
	if (n < 0)
		return false;
	unsigned int un = static_cast<unsigned int>(n);
	vect.push_back(un);
	deq.push_back(un);
	return true;
}
void PmergeMe::printBefore() const
{
	std::cout << "Before: ";
	for (unsigned int i = 0; i < vect.size(); ++i)
		std::cout << vect[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::printAfter() const
{
	std::cout << "After: ";
	for (unsigned int i = 0; i < vect.size(); ++i)
		std::cout << vect[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::mergeInsertVector(std::vector<unsigned int> &v, int left, int right)
{
	if (right - left <= 10) // we use insert for small group of item becuase merege is better for large item
	{
		for (int i = left + 1 ; i <= right ; ++i)//we start from vect [1] to compare it with vect [0]
		{
			unsigned int key = v[i];
			int j = i - 1;
			while (j >= left && v[j] > key)
			{
				v[j + 1] = v[j];
				--j;
			}
			v[j + 1] = key;
		}
		return;
	}
	int mid = (left + right) /2;
	mergeInsertVector(v, left, mid); // تقسيم النصفين فرزهم بشكل recursive
	mergeInsertVector(v, mid + 1, right);

	// دمج النصفين المرتبين داخل نفس الـ vector
	//std::inplace_merge(first, middle, last);
	std::inplace_merge(v.begin() + left, v.begin() + mid + 1, v.begin() + right + 1);
}

void PmergeMe::mergeInsertDeque(std::deque<unsigned int> &d, int left, int right)
{
	if (right - left <= 10) // we use insert for small group of item becuase merege is better for large item
	{
		for (int i = left + 1 ; i <= right ; ++i)//we start from vect [1] to compare it with vect [0]
		{
			unsigned int key = d[i];
			int j = i - 1;
			while (j >= left && d[j] > key)
			{
				d[j + 1] = d[j];
				--j;
			}
			d[j + 1] = key;
		}
		return;
	}
	int mid = (left + right) /2;
	mergeInsertDeque(d, left, mid); // تقسيم النصفين فرزهم بشكل recursive
	mergeInsertDeque(d, mid + 1, right);

	// دمج النصفين المرتبين داخل نفس الـ vector
	//std::inplace_merge(first, middle, last);
	std::inplace_merge(d.begin() + left, d.begin() + mid + 1, d.begin() + right + 1);
}

void PmergeMe::sortAndMeasure()
{
	if (vect.empty() || deq.empty())
		return;
	printBefore();
	clock_t start = clock(); //give me time in ticks (small part in second)
	mergeInsertVector(vect, 0, vect.size() -1);
	clock_t end = clock();
	double VectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000; // CONVERT IT TO MICROMILLI SECOND TO NOTICE SMALL DIFEERNCE.	
	std::cout << std::fixed << std::setprecision(5);
	start = clock();
	mergeInsertDeque(deq, 0, deq.size() - 1);
	end = clock();
	double DequeTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	std::cout << std::fixed << std::setprecision(5);
	printAfter();
	std::cout<< "Time to process a range of " << vect.size() 
			<< " elements with std::vector : " << VectorTime << " us" << std::endl;
	std::cout<< "Time to process a range of " << deq.size() 
			<< " elements with std::deque : " << DequeTime << " us" << std::endl;
}