/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esraa <esraa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:31:11 by esraa             #+#    #+#             */
/*   Updated: 2025/10/21 18:36:15 by esraa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if(this != &other)
		this->database = other.database;
	return (*this);
}
BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::loadDatabase(const std::string &dbFile)
{
		std::ifstream file(dbFile.c_str());
		if(!file.is_open())
			throw FileNotOpened();
		std::string line;
		std::getline(file, line); // skip header
		while (std::getline(file, line))
		{
			
			if (line.empty())
            	continue;
			std::stringstream ss(line);
			std::string date, ex_rate;
			if (!std::getline(ss,date,',') || !std::getline(ss, ex_rate))
				continue;
			float rate = atof(ex_rate.c_str());
			if (rate < 0)
				continue;
			database[date] = rate;
		}
		file.close();
}
void BitcoinExchange::processInput(const std::string &inputFile)
// Process input file with "date | value"
{
	std::ifstream file(inputFile.c_str());
		if(!file.is_open())
			throw FileNotOpened();
		std::string line;
		std::getline(file, line); // skip header
		while (std::getline(file, line))
		{
			if (line.empty())
            	continue;
			try 
			{
			size_t sep = line.find('|');
			if(sep == std::string::npos)
				throw BadInput();
			if (sep == 0 || line[sep - 1] != ' ' || sep + 1 >= line.size() || line[sep + 1] != ' ')
    		throw BadInput();
			std::string date = line.substr(0, sep - 1);
			std::string value_str = line.substr(sep + 2);
			float val = atof(value_str.c_str());
			if(!isValidDate(date))
				throw BadInput();
			if(!isValidValue(value_str))
				throw BadInput();
			if (val < 0)
				throw NotPositiveNumber();
			else if (val > 1000)
					throw TooLargeNumber();			
			float rate = getExchangeRate(date);
			std::cout << date << " => " << val << " = " << val * rate << std::endl;
		}
		catch (const BadInput &)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
		}
		
		catch (const std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); i++)
	{
		if ( i == 4 || i == 7)
			continue;
		if(!isdigit(date[i]))
		 return false;
	}
	int year = atoi(date.substr(0, 4).c_str());
	(void) year;
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    return true;
}
bool BitcoinExchange::isValidValue(const std::string &value)
{
	for (size_t i = 0; i < value.size(); ++i)
	{
		if (!isdigit(value[i]) && value[i] != '.' && value[i] != '-')
			return false;
	}
	return true;
} 
float BitcoinExchange::getExchangeRate(const std::string &date)
{
	if (database.count(date)) // is date is there or not
	  	return database[date];
	// find closet lower date
	std::map<std::string, float>::iterator it = database.lower_bound(date);
	if (it == database.begin() && it->first != date)
		throw BadInput(); // for oldest date
    if (it == database.end() || it->first != date) 
        --it;
    return it->second;
}

 const char* BitcoinExchange::FileNotOpened::what() const throw()
 {
	return ("Error: could not open file."); 
 }

 const char* BitcoinExchange::TooLargeNumber::what() const throw()
 {
	return "Error: too large a number.";
 }
 
 const char* BitcoinExchange::NotPositiveNumber::what() const throw()
 {
	return "Error: not a positive number."; 
 }
const char* BitcoinExchange::BadInput::what() const throw()
{
    return ("Error: BadInput.");
}

 