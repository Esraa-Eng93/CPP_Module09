/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:25:39 by esraa             #+#    #+#             */
/*   Updated: 2025/10/21 18:17:37 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <cstdlib>



class BitcoinExchange
{
private:
    std::map<std::string, float> database;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadDatabase(const std::string &dbFile);      // Load bitcoin price database
    void processInput(const std::string &inputFile);   // Process input file with "date | value"
    bool isValidDate(const std::string &date);         // Validate date format YYYY-MM-DD
    bool isValidValue(const std::string &value);       // Validate value (0 < value <= 1000)
    float getExchangeRate(const std::string &date);    // Get exchange rate (closest lower date if not found)

    class FileNotOpened : public std::exception
    {
        const char* what() const throw();
    };

    class NotPositiveNumber : public std::exception
    {
        const char* what() const throw();
    };

    class TooLargeNumber : public std::exception
    {
        const char* what() const throw();
    };

    class BadInput : public std::exception
	{
		const char* what() const throw();
	};


};

#endif
