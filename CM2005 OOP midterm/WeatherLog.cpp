#pragma once

#include "CSVReader.hpp"
#include "WeatherLog.hpp"
#include "WeatherDataEntry.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

WeatherLog::WeatherLog(std::string fileName){
	entries = CSVReader::readCSV(fileName);
}

std::vector<WeatherDataEntry> WeatherLog::filterByCountry(std::string c){
	std::vector<WeatherDataEntry> countryTemps;
	for (WeatherDataEntry& wde : entries) {
		if (wde.country == c) {
			countryTemps.push_back(wde);
		}
	}
	return countryTemps;
};

std::vector<std::string> WeatherLog::getKnownCountries(){
	std::vector<std::string> countries;
	std::map<std::string,bool> countryMap;
	
	for (WeatherDataEntry& e : entries){
		countryMap[e.country] = true;
	}
	
	for (auto const& e: countryMap){
		countries.push_back(e.first);
	}
	
	return countries;
};

double WeatherLog::computeHigh(std::vector<WeatherDataEntry>& data){
	
	double highValue = -100.0;
	for(WeatherDataEntry& wde: data){
		if (wde.temperature > highValue){
			highValue = wde.temperature;
		}
	}
	return highValue;
}

double WeatherLog::computeHigh(std::vector<Candlestick>& data){
	
	double highValue = -100.0;
	for(Candlestick& c: data){
		if (c.High > highValue){
			highValue = c.High;
		}
	}
	return highValue;
}

double WeatherLog::computeLow(std::vector<WeatherDataEntry>& data){
	double lowValue = 100.0;
	for(WeatherDataEntry& wde: data){
		if (wde.temperature < lowValue){
			lowValue = wde.temperature;
		}
	}
	return lowValue;
}

double WeatherLog::computeLow(std::vector<Candlestick>& data){
	double lowValue = 100.0;
	for(Candlestick& c: data){
		if (c.Low < lowValue){
			lowValue = c.Low;
		}
	}
	return lowValue;
}


double WeatherLog::computeOpen(std::vector<WeatherDataEntry>& data){
	double sumTemp = 0.0;
	if (data.size( )== 0){
		return 0.0;
	}
	else {
		for (WeatherDataEntry& wde : data) {
			sumTemp = sumTemp + wde.temperature;
		}
		return sumTemp / data.size();
	}
}

double WeatherLog::computeOpen(std::vector<Candlestick>& data){
	double sumTemp = 0.0;
	if (data.size()== 0){
		return 0.0;
	}
	else {
		for (Candlestick& c : data) {
			sumTemp = sumTemp + c.Open;
		}
		return sumTemp / data.size();
	}
}

double WeatherLog::computeClose(std::vector<WeatherDataEntry>& data){
	double sumTemp = 0.0;
	for (WeatherDataEntry& wde : data) {
		sumTemp = sumTemp + wde.temperature;
	}
	return sumTemp / data.size();
}

double WeatherLog::computeClose(std::vector<Candlestick>& data){
	double sumTemp = 0.0;
	for (Candlestick& c : data) {
		sumTemp = sumTemp + c.Close;
	}
	return sumTemp / data.size();
}

std::vector<Candlestick> WeatherLog::buildCountryMontlySticks(std::vector<Candlestick>& daily, std::string starting, std::string ending) {
	std::vector<Candlestick> monthly;
	std::vector<Candlestick> filteredDaily;
	// filter starting and ending dates
	for (Candlestick& candle : daily) {
		if (candle.Date.substr(0,7) >= starting && candle.Date.substr(0,7) <= ending){
			filteredDaily.push_back(candle);
		}
	}
	
	std::cout << "Filtered by date" << filteredDaily.size() << std::endl;
	
	std::string currentDate = filteredDaily[0].Date.substr(0,7);
	std::string lastDate = filteredDaily.back().Date.substr(0,7);
	
	std::string nextDate;
	std::vector<Candlestick> prevDayCandlesticks;
	
	int lastSeenIndex = 0;
	
	while (currentDate <= lastDate){
		std::vector<Candlestick> currentSticks;
		
		for (int i = lastSeenIndex; i <= filteredDaily.size(); i ++){
			std::string elemDate = filteredDaily[i].Date.substr(0,7);
			if (elemDate == currentDate) {
				currentSticks.push_back(filteredDaily[i]);
			}
			else if (elemDate > currentDate){
				nextDate = filteredDaily[i].Date.substr(0,7);
				lastSeenIndex = i;
				break;
			} else {
				continue;
			}
		}
		
		Candlestick stick =
			Candlestick(
			   currentDate,
			   computeOpen(prevDayCandlesticks),
			   computeClose(currentSticks),
			   computeHigh(currentSticks),
			   computeLow(currentSticks)
			);
		
		monthly.push_back(stick);
		
		prevDayCandlesticks = currentSticks;
		currentDate = nextDate;
		
		if (currentDate == lastDate) {
			break;
		} else {
			continue;
		}
	}
	
	return monthly;
}

std::vector<Candlestick> WeatherLog::buildCountryYearlySticks(std::vector<Candlestick>& daily, std::string starting, std::string ending){
	std::vector<Candlestick> yearly;
	std::vector<Candlestick> filteredDaily;
	// filter starting and ending dates
	for (Candlestick& candle : daily) {
		if (candle.Date.substr(0,4) >= starting && candle.Date.substr(0,4) <= ending){
			filteredDaily.push_back(candle);
		}
	}
	
	std::string currentDate = filteredDaily[0].Date.substr(0,4);
	std::string lastDate = filteredDaily.back().Date.substr(0,4);
	
	std::string nextDate;
	std::vector<Candlestick> prevDayCandlesticks;
	
	int lastSeenIndex = 0;
	
	while (currentDate <= lastDate){
		std::vector<Candlestick> currentSticks;
		
		for (int i = lastSeenIndex; i <= filteredDaily.size(); i ++){
			std::string elemDate = filteredDaily[i].Date.substr(0,4);
			if (elemDate == currentDate) {
				currentSticks.push_back(filteredDaily[i]);
			}
			else if (elemDate > currentDate){
				nextDate = filteredDaily[i].Date.substr(0,4);
				lastSeenIndex = i;
				break;
			} else {
				continue;
			}
		}
		
		Candlestick stick =
			Candlestick(
			   currentDate,
			   computeOpen(prevDayCandlesticks),
			   computeClose(currentSticks),
			   computeHigh(currentSticks),
			   computeLow(currentSticks)
			);
		
		yearly.push_back(stick);
		
		prevDayCandlesticks = currentSticks;
		currentDate = nextDate;
		
		if (currentDate == lastDate) {
			break;
		} else {
			continue;
		}
	}
	
	return yearly;
}

std::vector<Candlestick> WeatherLog::buildCountryDailyCandleStick(std::string c) {
	
	std::vector<Candlestick> dailySticks;
	std::vector<WeatherDataEntry> countryDataStats = filterByCountry(c);
	
	std::cout << "Country entries : " << countryDataStats.size() << std::endl;
	
	std::string currentDate = countryDataStats[0].dateTime.substr(0,10);
	std::string lastDate = countryDataStats.back().dateTime.substr(0,10);
	
	std::string nextDate;
	std::vector<WeatherDataEntry> prevDayEntries;
	
	// Now the for loop only works in sets of 24 for each hour of the day
	int lastVisitedIndex = 0;
	
	while (currentDate <= lastDate){
		
		std::vector<WeatherDataEntry> currentDayEntries;
		// get all the entries for the current date
		
		for (int i = lastVisitedIndex; i <= countryDataStats.size(); i++) {
			
			std::string elemDate = countryDataStats[i].dateTime.substr(0,10);
			if (elemDate == currentDate) {
				currentDayEntries.push_back(countryDataStats[i]);
			} else if (elemDate > currentDate) {
				nextDate = countryDataStats[i].dateTime.substr(0,10);
				// this is to make sure we dont pass over the same data more than once as it has already been processed
				lastVisitedIndex = i;
				break;
			} else {
				continue;
			}
			
		}
		// Now build the Candle stick for the current day
		Candlestick stick = 
			 Candlestick(
				currentDate,
				computeOpen(prevDayEntries),
				computeClose(currentDayEntries),
				computeHigh(currentDayEntries),
				computeLow(currentDayEntries)
			);
		
		dailySticks.push_back(stick);
		prevDayEntries = currentDayEntries;
		currentDate = nextDate;
		
		if (currentDate == lastDate) {
			break;
		} else {
			continue;
		}
	}
	
	return dailySticks;
}

