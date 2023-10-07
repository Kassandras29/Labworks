#pragma once
#include <string>
#include <vector>
#include <map>

struct WeatherInfo {

    std::vector<float> temperature;
    std::vector<float> apparent_temperature;
    std::vector<float> relative_humidity;
    std::vector<float> precipitation_probability;

};

class WeatherAPI {
public:

    WeatherAPI() = default;

    void ParseConfig();
    void GetCoordinates();
    void GetWeather();
    void PrintTable();
    long long GetReloadTime() const;
    void IncreasingDays();
    void DecreasingDays();
    void SwitchCityNext();
    void SwitchCityPrev();

private:
    std::vector <std::string> cites_;
    size_t count_city_ = 0;
    std::vector <std::pair<std::string, std::string>> coordinates_;
    int days_i_{};
    int count_days_ = 4;
    std::string days_s_;
    long long reload_{};
    std::string api_key_;
    std::vector<std::string> dates_;
    std::map<int, WeatherInfo> weather_info_;

};
