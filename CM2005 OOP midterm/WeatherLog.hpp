#pragma once

#include "WeatherDataEntry.hpp"
#include "CandleStick.hpp"
#include "CSVReader.hpp"
#include <vector>

class WeatherLog {
public:
	WeatherLog(std::string fileName);
	std::vector<std::string> getKnownCountries ();
	std::vector<Candlestick> buildCountryDailyCandleStick (std::string c);
	std::vector<Candlestick> buildCountryMontlySticks(std::vector<Candlestick>& daily, std::string starting, std::string ending);
	std::vector<Candlestick> buildCountryYearlySticks(std::vector<Candlestick>& daily, std::string starting, std::string ending);
	
private:
	
	static double computeHigh(std::vector<WeatherDataEntry>& data);
	static double computeHigh(std::vector<Candlestick>& data);
	static double computeLow(std::vector<WeatherDataEntry>& data);
	static double computeLow(std::vector<Candlestick>& data);
	static double computeOpen(std::vector<WeatherDataEntry>& data);
	static double computeOpen(std::vector<Candlestick>& data);
	static double computeClose(std::vector<WeatherDataEntry>& data);
	static double computeClose(std::vector<Candlestick>& data);
	
	std::vector<WeatherDataEntry> filterByCountry(std::string c);
	std::vector<WeatherDataEntry> entries;
};
