#pragma once

#include "CSVReader.hpp"
#include "WeatherDataEntry.hpp"
#include "WeatherLog.hpp"

class WeatherMain {
public:
	WeatherMain();
	void init();
	static void printCandleStickGraph(const std::vector<Candlestick>&);
private:
	void mainMenu();
	void processUserInput(int userInput);
	void printAllData();
	void printCountrySticksGraph();
	int readUserInput();
	
	std::vector<std::string> countries;

	WeatherLog weatherData{"weatherData.csv"};
	
};
