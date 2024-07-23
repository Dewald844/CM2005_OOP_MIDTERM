#include "WeatherDataEntry.hpp"

WeatherDataEntry::WeatherDataEntry(
  std::string _timeStamp
  , std::string _country
  , double _temperature
) :
	dateTime(_timeStamp),
	country(_country),
	temperature(_temperature)
{};
