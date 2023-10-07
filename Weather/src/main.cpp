#include "lib/weather.h"
#include <conio.h>
#include <chrono>
#include <iostream>

const int kBUTTON_ESC = 27;
const int kBUTTON_N = 78;
const int kBUTTON_P = 80;
const int kBUTTON_PLUS = 187;
const int kBUTTON_MINUS = 189;

int main() {
    system("chcp 65001");
    system("cls");
    std::cout << "Please wait\n";

    WeatherAPI Weather;

    Weather.ParseConfig();
    Weather.GetCoordinates();

    Weather.GetWeather();
    Weather.PrintTable();

    auto start = std::chrono::steady_clock::now();

    while (!_kbhit()) {
        auto end = std::chrono::steady_clock::now();
        long long duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        if (duration >= Weather.GetReloadTime()) {
            std::cout << "Please wait\n";
            start = std::chrono::steady_clock::now();
            Weather.GetWeather();
            Weather.PrintTable();
        }
    }

    while (true) {
        int key = _getch();
        if (key == kBUTTON_ESC) {
            system("cls");
            std::cout << "Shutdown";
            break;
        }

        if (key == kBUTTON_N) {
            std::cout << "Please wait\n";
            Weather.SwitchCityNext();
            Weather.PrintTable();
        }

        if (key == kBUTTON_P) {
            std::cout << "Please wait\n";
            Weather.SwitchCityPrev();
            Weather.PrintTable();
        }

        if (key == kBUTTON_PLUS) {
            std::cout << "Please wait\n";
            Weather.IncreasingDays();
            Weather.PrintTable();
        }

        if (key == kBUTTON_MINUS) {
            std::cout << "Please wait\n";
            Weather.DecreasingDays();
            Weather.PrintTable();
        }

        while (!_kbhit()) {
            auto end = std::chrono::steady_clock::now();
            long long duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

            if (duration >= Weather.GetReloadTime()) {
                std::cout << "Please wait\n";
                start = std::chrono::steady_clock::now();
                Weather.GetWeather();
                Weather.PrintTable();
            }
        }
    }

    return 0;
}
