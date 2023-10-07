#include "Weather.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

const size_t kMIN_DAYS = 1;
const size_t kMAX_DAYS = 10;
const int kCOUNT_TIME_INTERVALS = 4;

void WeatherAPI::ParseConfig() {

    std::ifstream config("C:/projects/labwork-10-Kassandras29/config.json");
    nlohmann::json data_c = nlohmann::json::parse(config);

    for (std::string city : data_c["cites"]) {
        cites_.push_back(city);
    }
    days_i_ = data_c["days"].get<int>();
    reload_ = data_c["reload"].get<long long>();
    api_key_ = data_c["api"].get<std::string>();
}

void WeatherAPI::GetCoordinates() {

    for (std::string city : cites_) {
        cpr::Response r = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                                   cpr::Parameters{{"name", city}},
                                   cpr::Header{{"X-Api-Key", api_key_}});

        if (r.status_code != 200) {
            system("cls");

            std::cout << "Need to connect to WiFi";
            exit(0);
        }

        nlohmann::json data_r = nlohmann::json::parse(r.text);

        coordinates_.emplace_back(std::to_string(data_r[0]["latitude"].get<float>()),
                                  std::to_string(data_r[0]["longitude"].get<float>()));
    }

}

void WeatherAPI::GetWeather() {

    dates_.clear();
    weather_info_.clear();

    for (int c = 0; c < cites_.size(); ++c) {

        WeatherInfo temp;

        days_s_ = std::to_string(days_i_);
        cpr::Response w = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                   cpr::Parameters{{"latitude",      coordinates_[c].first},
                                                   {"longitude",     coordinates_[c].second},
                                                   {"hourly",        "temperature_2m"},
                                                   {"hourly",        "relativehumidity_2m"},
                                                   {"hourly",        "apparent_temperature"},
                                                   {"hourly",        "precipitation_probability"},
                                                   {"forecast_days", days_s_}});

        nlohmann::json data_w = nlohmann::json::parse(w.text);

        for (int i = 0; i < days_i_; ++i) {

            if (dates_.size() < days_i_) {
                std::string temp_date;
                for (int d = 0; d < 10; ++d) {
                    temp_date += data_w["hourly"]["time"][24 * i].get<std::string>()[d];
                }
                dates_.push_back(temp_date);
            }

            temp.temperature.push_back(data_w["hourly"]["temperature_2m"][5 + 24 * i].get<float>());
            temp.temperature.push_back(data_w["hourly"]["temperature_2m"][11 + 24 * i].get<float>());
            temp.temperature.push_back(data_w["hourly"]["temperature_2m"][17 + 24 * i].get<float>());
            temp.temperature.push_back(data_w["hourly"]["temperature_2m"][23 + 24 * i].get<float>());

            temp.apparent_temperature.push_back(data_w["hourly"]["apparent_temperature"][5 + 24 * i].get<float>());
            temp.apparent_temperature.push_back(data_w["hourly"]["apparent_temperature"][11 + 24 * i].get<float>());
            temp.apparent_temperature.push_back(data_w["hourly"]["apparent_temperature"][17 + 24 * i].get<float>());
            temp.apparent_temperature.push_back(data_w["hourly"]["apparent_temperature"][23 + 24 * i].get<float>());

            temp.relative_humidity.push_back(data_w["hourly"]["relativehumidity_2m"][5 + 24 * i].get<float>());
            temp.relative_humidity.push_back(data_w["hourly"]["relativehumidity_2m"][11 + 24 * i].get<float>());
            temp.relative_humidity.push_back(data_w["hourly"]["relativehumidity_2m"][17 + 24 * i].get<float>());
            temp.relative_humidity.push_back(data_w["hourly"]["relativehumidity_2m"][23 + 24 * i].get<float>());

            temp.precipitation_probability.push_back(
                    data_w["hourly"]["precipitation_probability"][5 + 24 * i].get<float>());
            temp.precipitation_probability.push_back(
                    data_w["hourly"]["precipitation_probability"][11 + 24 * i].get<float>());
            temp.precipitation_probability.push_back(
                    data_w["hourly"]["precipitation_probability"][17 + 24 * i].get<float>());
            temp.precipitation_probability.push_back(
                    data_w["hourly"]["precipitation_probability"][23 + 24 * i].get<float>());

        }

        weather_info_.insert(std::make_pair(c, temp));

    }

}

void WeatherAPI::PrintTable() {

    system("cls");
    std::cout << cites_[count_city_] << ":\n";

    for (int i = 0; i < count_days_; ++i) {

        std::cout << std::setw(23) << dates_[i] << '\n';
        std::cout << "———————————————————————————————————————————————————————\n";
        std::cout << std::setw(10) << "Morning" << std::setw(4) << "|";
        std::cout << std::setw(11) << "Afternoon" << std::setw(3) << "|";
        std::cout << std::setw(10) << "Evening" << std::setw(4) << "|";
        std::cout << std::setw(9) << "Night\n";

        auto it = weather_info_.begin();

        for (int c = 0; c < count_city_; ++c) {
            ++it;
        }

        for (int j = 0; j < kCOUNT_TIME_INTERVALS; ++j) {
            std::cout << std::setw(7) << it->second.temperature[kCOUNT_TIME_INTERVALS * i + j]
            << " °C" << std::setw(4) << "|";
        }
        std::cout << " Temperature" << '\n';

        for (int j = 0; j < kCOUNT_TIME_INTERVALS; ++j) {
            std::cout << std::setw(7) << it->second.apparent_temperature[kCOUNT_TIME_INTERVALS * i + j]
                      << " °C" << std::setw(4) << "|";
        }
        std::cout << " Apparent Temperature" << '\n';

        for (int j = 0; j < kCOUNT_TIME_INTERVALS; ++j) {
            std::cout << std::setw(7) << it->second.relative_humidity[kCOUNT_TIME_INTERVALS * i + j]
                      << " %" << std::setw(5) << "|";
        }
        std::cout << " Relative Humidity" << '\n';

        for (int j = 0; j < kCOUNT_TIME_INTERVALS; ++j) {
            std::cout << std::setw(7) << it->second.precipitation_probability[kCOUNT_TIME_INTERVALS * i + j]
                      << " %" << std::setw(5) << "|";
        }
        std::cout << " Precipitation Probability" << '\n' << '\n';

    }

}

long long WeatherAPI::GetReloadTime() const {
    long long reload_time = reload_;
    return reload_time;
}

void WeatherAPI::IncreasingDays() {
    if (count_days_ + 1 <= kMAX_DAYS) ++count_days_;
}

void WeatherAPI::DecreasingDays() {
    if (count_days_ - 1 >= kMIN_DAYS) --count_days_;
}

void WeatherAPI::SwitchCityNext() {
    if (count_city_ + 1 < cites_.size()) ++count_city_;
    else count_city_ = 0;
}

void WeatherAPI::SwitchCityPrev() {
    if ((int) count_city_ - 1 >= 0) --count_city_;
    else count_city_ = cites_.size() - 1;
}
