#include "CandleStick.hpp"

Candlestick::Candlestick(std::string _date,
						 double _open,
						 double _close,
				         double _high,
				         double _low):
Date(_date),
Open(_open),
Close(_close),
High(_high),
Low(_low){ }
