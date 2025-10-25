/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:18:34 by esraa             #+#    #+#             */
/*   Updated: 2025/10/21 21:08:19 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <algorithm>
#include <sstream>
#include <cstdlib>

#ifndef RBN_HPP
#define RBN_HPP

class RBN 
{
	private:
		std::string expression;
		std::stack<double> stack;

		bool IsValidValue(const std::string &value);
		bool IsOperator(const std::string &token);
		double Compute(double num1, double num2, const std::string &op);
	public:
		RBN();
		RBN(const std::string &expr);
		RBN(const RBN& other);
		RBN& operator = (const RBN& other);
		~RBN();
		
		double Evaluate();
};

#endif