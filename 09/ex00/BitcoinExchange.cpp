/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:26:36 by mknoll            #+#    #+#             */
/*   Updated: 2026/01/12 11:01:11 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

DatesAndPrices::DatesAndPrices() : fees() {}

// Constructor that loads database from file
DatesAndPrices::DatesAndPrices(std::string database) : fees()
{
   loadDatabase(database);
}

DatesAndPrices::DatesAndPrices(const DatesAndPrices &obj) : fees(obj.fees) {}

DatesAndPrices &DatesAndPrices::operator=(const DatesAndPrices &obj)
{
    if(this != &obj)
    {
        this->fees = obj.fees;  // Copy the entire map
    }
    return *this;
}

DatesAndPrices::~DatesAndPrices() {}


// Find price for a specific date (returns closest available date)
double DatesAndPrices::priceForDate(const std::string& date) const
{
    // Try to find exact date with iterator on map (fees)
    std::map<std::string, double>::const_iterator it = fees.find(date);
    if (it != fees.end()) 
        return it->second; // Exact date found
        
    // If exact date not found, find the closest earlier date
    it = fees.lower_bound(date);
    if (it != fees.begin())
    {
        --it;  // Get the previous date (closest earlier date)
        return it->second; // Closest earlier date found
    }
    
    // No valid date found
    throw std::runtime_error("No price data available for date: " + date);
}

void DatesAndPrices::loadDatabase(const std::string& filename)
{
    // Open file
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Could not open database file"); 

    std::string line; 
    bool isFirstline = true; 
    while(std::getline(file, line))
    {
        //Skip header line and empty lines
        if(line.empty() || isFirstline)
        {
            isFirstline = false; 
            continue; 
        }
        
        //Parse CSV line date,price
        std::stringstream ss(line); 
        std::string date; 
        std::string priceStr; 

        // Parse everything before ',' as date and after as price
        if(!std::getline(ss, date, ','))
            continue;
        if(!std::getline(ss, priceStr)) 
            continue; 
        // Convert price to a double
        double price = std::atof(priceStr.c_str()); 
        // store in map
        fees[date] = price; 
    }
    file.close(); 
}

void DatesAndPrices::printFees(const std::string &filename)
{
    std::ifstream file(filename.c_str()); 
    if(!file.is_open())
        throw std::runtime_error("Could not open file!"); 
    
    std::string line;
    bool isFirstline = true; 
    while(std::getline(file, line))
    {
        if(line.empty() || isFirstline)
        {
            isFirstline = false; 
            continue; 
        }

        // Parse every line with a new stringstream 
        std::stringstream ss(line); 
        std::string date; 
        std::string valueStr; 
        
        // Parse "date | value" Format
        if(!std::getline(ss, date, '|'))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if(!std::getline(ss, valueStr)) 
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        // Trim whitespace (important for " | " Format)
        date = trim(date);
        valueStr = trim(valueStr);

        // Validate date
        if(!isValidDate(date)) 
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }

        // Convert to double and check values 
        double value = std::atof(valueStr.c_str());
        if(!isValidValue(value)) 
        {
            if(value < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else if(value > 1000)
                std::cout << "Error: too large a number." << std::endl;
            continue;
        }
        // Find Price at date 
        double bitcoinPrice = priceForDate(date);
        // Print Price at date 
        std::cout << date << " => " << value << " = " << (value * bitcoinPrice) << std::endl;
    }
    file.close();
}

bool DatesAndPrices::isValidDate(const std::string& dateStr) const
{
    // Format needs to be 10 chars
    if (dateStr.length() != 10) 
        return false;
        
    // Check for '-' at the correct positions
    if (dateStr[4] != '-' || dateStr[7] != '-')
        return false;
    
    // Extract year, month, day
    std::string yearStr = dateStr.substr(0, 4);
    std::string monthStr = dateStr.substr(5, 2);
    std::string dayStr = dateStr.substr(8, 2);
    
    // Check that there are only numbers
    for (size_t i = 0; i < yearStr.length(); ++i) 
    {
        if (!std::isdigit(yearStr[i])) 
            return false;
    }
    for (size_t i = 0; i < monthStr.length(); ++i) 
    {
        if (!std::isdigit(monthStr[i])) 
            return false;
    }
    for (size_t i = 0; i < dayStr.length(); ++i) 
    {
        if (!std::isdigit(dayStr[i])) 
            return false;
    }
    
    // Covert to int 
    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());
    
    // Check Base
    if (year < 0 || month < 1 || month > 12 || day < 1) 
        return false;
    
    // Check max days for each month correctly + leap year 
    int maxDay;
    switch (month) 
    {
        case 2:  // february
            maxDay = 28;
            // leapyear-rule: dividable by 4 And not dividable by 100 or 400)
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
                maxDay = 29;
            break;
        case 4: case 6: case 9: case 11:  // april, june, september, november
            maxDay = 30; 
            break;
        default:  // Januar, march, may, july, august, october, december
            maxDay = 31; 
            break;
    }
    return (day <= maxDay);
}

// Helper function for value
bool DatesAndPrices::isValidValue(double value) const
{
    return (value >= 0.0 && value <= 1000.0);
}

// Helper function to trim whitespaces 
std::string DatesAndPrices::trim(const std::string& str) const
{
    // find first letter (not whitespace) 
    size_t start = 0;
    while (start < str.length() && (str[start] == ' ' || str[start] == '\t'))
        start++;
    
    // If whitespace -> empty String
    if (start == str.length())
        return "";
    
    // find the alse character from the back
    size_t end = str.length() - 1;
    while (end > start && (str[end] == ' ' || str[end] == '\t'))
        end--;     
    // return part between start and end
    return str.substr(start, end - start + 1);
}