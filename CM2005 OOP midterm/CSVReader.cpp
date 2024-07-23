#include "CSVReader.hpp"

#include <iostream>
#include <fstream>

CSVReader::CSVReader(){};

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
	std::vector<std::string> tokens;
	signed int start, end;
	std::string token;
	start = csvLine.find_first_not_of(separator, 0);
	do{
		end = csvLine.find_first_of(separator, start);
		if (start == csvLine.length() || start == end) break;
		if (end >= 0) token = csvLine.substr(start, end - start);
		else token = csvLine.substr(start, csvLine.length() - start);
		tokens.push_back(token);
	start = end + 1;
	} while(end > 0);

	return tokens;
}

WeatherDataEntry CSVReader::stringsToWDS(std::string dateTime, std::string country, std::string temp){
	try{
		double temperature = std::stod(temp);
		return WeatherDataEntry(dateTime, country, temperature);
	}catch (const std::exception& e){
		std::cout << "Error trying to parse :" << country << "temp : " << temp << std::endl;
		throw;
	}
}

std::vector<WeatherDataEntry> CSVReader::readCSV(std::string csvFile){
	std::vector<WeatherDataEntry> weather;

	std::ifstream file(csvFile);
	std::string line;
	
	std::cout << "Loading data file ..." << std::endl;

	if (file.is_open()) {
        // This only skips over the first line which is the headers;
        std::getline(file, line);
		while (std::getline(file, line)){
			try {
				std::vector<std::string> tokenisedLine = tokenise(line, ',');
				weather.push_back(stringsToWDS(tokenisedLine[0], "AT", tokenisedLine[1]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "BE", tokenisedLine[2]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "BG", tokenisedLine[3]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "CH", tokenisedLine[4]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "CZ", tokenisedLine[5]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "DE", tokenisedLine[6]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "DK", tokenisedLine[7]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "EE", tokenisedLine[8]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "ES", tokenisedLine[9]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "FI", tokenisedLine[10]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "FR", tokenisedLine[11]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "GB", tokenisedLine[12]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "GR", tokenisedLine[13]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "HR", tokenisedLine[14]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "HU", tokenisedLine[15]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "IE", tokenisedLine[16]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "IT", tokenisedLine[17]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "LT", tokenisedLine[18]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "LU", tokenisedLine[19]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "LV", tokenisedLine[20]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "NL", tokenisedLine[21]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "NO", tokenisedLine[22]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "PL", tokenisedLine[23]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "PT", tokenisedLine[24]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "RO", tokenisedLine[25]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "SE", tokenisedLine[26]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "SI", tokenisedLine[27]));
				weather.push_back(stringsToWDS(tokenisedLine[0], "SK", tokenisedLine[28]));
			} catch (const std::exception& e) {
				std::cout << "Error trying to parse line :" << line << std::endl;
			}

		}
	}


	std::cout << "Data read : " << weather.size() << std::endl;
	return weather;
}
