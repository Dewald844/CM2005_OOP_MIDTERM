#pragma once
#include <string>
#include <vector>

class WeatherDataEntry {

public:
    WeatherDataEntry (
		std::string dateTime
        , std::string country
	    , double temperature
    );
	
	std::string dateTime;
	std::string country;
	double temperature;
};
