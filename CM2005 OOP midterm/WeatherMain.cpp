#include "WeatherMain.hpp"
#include "CSVReader.hpp"
#include "WeatherDataEntry.hpp"
#include "CandleStick.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

WeatherMain::WeatherMain() {}

void WeatherMain::init(){
	
	countries = weatherData.getKnownCountries();
	int userInput = 0;
	while(true){
		mainMenu();
		userInput = readUserInput();
		processUserInput(userInput);
	}
}

void WeatherMain::mainMenu(){
	std::cout << "+ ---------------------------- +" << std::endl;
	std::cout << "|           Main menu          |" << std::endl;
	std::cout << "+ ---------------------------- +" << std::endl;
	std::cout << "| 1 | print all countries      |" << std::endl;
	std::cout << "| 2 | print weather graph      |" << std::endl;
	std::cout << "+ ---------------------------- +" << std::endl;
	std::cout << std::endl;
}

int WeatherMain::readUserInput(){
	int userInput = 0;
	std::string line;
	std::cout << "Enter choice : " << std::endl;
	std::getline(std::cin, line);
	try{
		userInput = std::stoi(line);
	} catch (const std::exception& e) {
		std::cout << "Invalid input cannot parse to intager : " << line << std::endl;
	}
	return userInput;
}

void WeatherMain::processUserInput(int userInput){
	switch (userInput) {
		case 1:
			std::cout << "printing all countries" << std::endl;
			printAllData();
			break;
		
		case 2:
			printCountrySticksGraph();
			break;
		default:
			break;
	}
}

void WeatherMain::printAllData(){
	for (std::string c : countries) {
		std::cout << " < " << c << " > " ;
	}
	std::cout << std::endl;
}

void WeatherMain::printCountrySticksGraph(){
	std::string line;
	std::string incrementation;
	printAllData();
	std::cout << "Enter country to compute from the list above : " << std::endl;
	std::getline(std::cin, line);
	std::cout << "Computing all sticks for : " << line << std::endl;
	std::vector<Candlestick> sticks = weatherData.buildCountryDailyCandleStick(line);
	std::cout << "Select range incrementation (M : montly; Y : yearly)" << std::endl;
	std::getline(std::cin,incrementation);
	if (incrementation == "M") {
		std::string startingMonth;
		std::string endingMonth;
		std::cout << "Please enter a starting month and year between (1980-01 - 2019-12) : YYYY-MM =>" << std::endl;
		std::getline(std::cin, startingMonth);
		std::cout << "Please enter a ending month and year between (" << startingMonth << " - 2019-12) : YYYY-MM =>" << std::endl;
		std::getline(std::cin, endingMonth);
		std::vector<Candlestick> userDefinedCandles = weatherData.buildCountryMontlySticks(sticks, startingMonth, endingMonth);
		printCandleStickGraph(userDefinedCandles);
	} else if ( incrementation == "Y") {
		std::string startingYear;
		std::string endingYear;
		std::cout << "Please enter a starting year between (1980 - 2019) : YYYY=>" << std::endl;
		std::getline(std::cin, startingYear);
		std::cout << "Please enter a ending month and year between (" << startingYear << " - 2019) : YYYY=>" << std::endl;
		std::getline(std::cin, endingYear);
		std::vector<Candlestick> userDefinedCandles = weatherData.buildCountryYearlySticks(sticks, startingYear, endingYear);
		printCandleStickGraph(userDefinedCandles);
	}
}

void WeatherMain::printCandleStickGraph(const std::vector<Candlestick>& data) {
	
	// Printing out the dates of the starting and ending points
	std::cout << "Graph starting from : " << data[0].Date << " until : " << data.back().Date << std::endl;
	
	// Determine chart dimensions
	double minVal = 0, maxVal = 0;
	for (const Candlestick& candle : data) {
		minVal = std::min({minVal, candle.Low, candle.Open, candle.Close});
		maxVal = std::max({maxVal, candle.High, candle.Open, candle.Close});
	}
	
	// Generate the chart
	int chartHeight = maxVal - minVal + 1;
	// 2D array for x y values
	std::vector<std::vector<char>> chart(chartHeight, std::vector<char>(data.size(), ' '));
	
	for (size_t i = 0; i < data.size(); ++i) {
		const Candlestick& candle = data[i];
		double openPos = candle.Open - minVal;
		double closePos = candle.Close - minVal;
		double highPos = candle.High - minVal;
		double lowPos = candle.Low - minVal;
		// Mark the high to low range
		for (int j = lowPos; j <= highPos; ++j) {
			chart[j][i] = '|';
		}
		// Mark open and close positions
		chart[openPos][i] = 'O';
		chart[closePos][i] = 'X';
	}
	
	// Print the chart
	for (int i = chartHeight - 1; i >= 0; --i) {
		// To keep everything inline and pretty
		std::cout.precision(5);
		// if the Verticle value is positive do not set the width
		 if((i + minVal > 0)){
			std::cout << " " << i + minVal << " |";
		} else {
			std::cout << std::setw(2) << i + minVal << " |";
		}
		// Print out the candle symbol leaving a space on both sides
		for (size_t j = 0; j < data.size(); ++j) {
			std::cout << " " << chart[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	// Horizontal axis spacing
	std::cout << "       +";
	
	// Print the Horizontal axis line
	for (size_t i = 0; i < data.size(); ++i) {
		std::cout << "---";
	}
	
	// Horizontal axis spacing
	std::cout << std::endl << "        ";
	
	// Dates on the horizontal axis
	for (size_t i = 1; i <= data.size(); ++i) {
		std::cout << std::setw(2) << i % 31 << " ";
	}
	std::cout << std::endl;
}


