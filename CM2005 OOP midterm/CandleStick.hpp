#pragma once
#include "WeatherDataEntry.hpp"
#include <string>

class Candlestick {
	
public:
	
	Candlestick(std::string _date,
				double _open,
				double _close,
				double _high,
				double _low
				);
	
	std::string Date;
	double Open;
	double High;
	double Low;
	double Close;
};

