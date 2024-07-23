cmake_minimum_required(VERSION 3.28)
project(CM2005_OOP_midterm)

set(CMAKE_CXX_STANDARD 14)

include_directories("CM2005 OOP midterm")

add_executable(CM2005_OOP_midterm
        "CM2005 OOP midterm/CandleStick.cpp"
        "CM2005 OOP midterm/CandleStick.hpp"
        "CM2005 OOP midterm/CSVReader.cpp"
        "CM2005 OOP midterm/CSVReader.hpp"
        "CM2005 OOP midterm/main.cpp"
        "CM2005 OOP midterm/weatherData.csv"
        "CM2005 OOP midterm/WeatherDataEntry.cpp"
        "CM2005 OOP midterm/WeatherDataEntry.hpp"
        "CM2005 OOP midterm/WeatherLog.cpp"
        "CM2005 OOP midterm/WeatherLog.hpp"
        "CM2005 OOP midterm/WeatherMain.cpp"
        "CM2005 OOP midterm/WeatherMain.hpp")
