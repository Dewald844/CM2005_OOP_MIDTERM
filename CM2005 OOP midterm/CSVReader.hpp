#pragma once

#include <vector>
#include <string>
#include "WeatherDataEntry.hpp"

class CSVReader {
    public:
        CSVReader();

        static std::vector<std::string> tokenise(std::string csvLine, char separator);
		static std::vector<WeatherDataEntry> readCSV(std::string csvFile);

    private:
        static WeatherDataEntry stringsToWDS(std::string dateTime, std::string country, std::string temp);
};
