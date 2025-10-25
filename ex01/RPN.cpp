/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:50:53 by esraa             #+#    #+#             */
/*   Updated: 2025/10/21 22:05:27 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RBN::RBN() :expression("") {}
RBN::RBN(const std::string &expr) : expression(expr) {}
RBN::RBN(const RBN& other)
{
	*this = other;
}
RBN& RBN::operator = (const RBN& other)
{
	if (this != &other)
	{
		expression = other.expression;
		stack = other.stack;
	}
	return *this;
}
RBN::~RBN(){}

bool RBN::IsValidValue(const std::string &value)
{
	if(value.empty())
		return false;
	return (value.size() == 1 && std::isdigit(value[0]));
}
bool RBN::IsOperator(const std::string &token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}
double RBN::Compute(double num1, double num2, const std::string &op)
{
	if (op == "+")
		return (num1 + num2);
	else if (op == "-")
		return (num1 - num2);
	else if (op == "*")
		return (num1 * num2);
	else if (op == "/")
	{
		if (num2 == 0)
		{
			std::cerr<<("Error: Division by zero") <<std::endl;
			exit(1);
		}
		return (num1 / num2);
	}
	else 
	{
		std::cerr << "Error: Unknown operator" << std::endl;
		exit(1);
	}
}
double RBN::Evaluate()
{
	std::istringstream ss(expression);
	std::string token;

	while(ss >> token)
	{
		if (IsValidValue(token))
			stack.push(static_cast<double>(token[0] - '0'));
		else if (IsOperator(token))
		{
			if (stack.size() < 2) // at least two numbers in stack
			{
				std::cerr << "Error" << std::endl;
				exit(1);
			}
			double num2 = stack.top();// 3 - 5 num2 = 5 //the top of stack
			stack.pop(); // delete the top
			double num1 = stack.top();
			stack.pop();
			double res = Compute(num1, num2, token);
			stack.push(res);
		}
		else
		{
			std::cerr <<"Error"<< std::endl;
			exit(1);
		}
	}
		if (stack.size() != 1)
		{
			std::cerr << "Error" << std::endl;
			exit(1);
		}
	return stack.top();
}
		

