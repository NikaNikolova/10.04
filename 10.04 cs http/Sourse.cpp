#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")

using namespace std;

void fetchTemperature(const string& url, const string& city) {
    const string filePath = "temperature_data.txt";

    // Сохраняем данные о погоде в файл
    HRESULT result = URLDownloadToFile(nullptr, url.c_str(), filePath.c_str(), 0, nullptr);
    if (result != S_OK) {
        cerr << "Error: Unable to download weather data for " << city << endl;
        return;
    }

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find("data-temperature-f=\"");
        if (pos != string::npos) {
            pos += 21; // move past the initial part of the tag
            size_t endPos = line.find("\"", pos);
            string temperature = line.substr(pos, endPos - pos);
            cout << "Current temperature in " << city << " is " << temperature << "°F" << endl;
            break;
        }
    }
    file.close();
}

int main() {
    struct City {
        string url;
        string name;
    };

    vector<City> cities = {
        {"https://www.gismeteo.ua/weather-odessa-4982/", "Odessa"},
        {"https://meteofor.com.ua/ru/weather-kyiv-4944/", "Kyiv"},
        {"https://meteofor.com.ua/ru/weather-lviv-4949", "Lviv"},
        {"https://meteofor.com.ua/ru/weather-kharkiv-5053/", "Kharkiv"},
        {"https://meteofor.com.ua/ru/weather-sumy-4936/", "Sumy"},
        {"https://meteofor.com.ua/ru/weather-dnipro-5077/", "Dnipro"},
        {"https://meteofor.com.ua/ru/weather-zaporizhia-5093/", "Zaporizhzhia"},
        {"https://meteofor.com.ua/ru/weather-kryvyi-rih-4978/", "Kryviy Rih"},
        {"https://meteofor.com.ua/ru/weather-vinnytsia-4962/", "Vinnytsia"},
        {"https://meteofor.com.ua/ru/weather-poltava-4957/", "Poltava"},
        {"https://meteofor.com.ua/ru/weather-chernihiv-4923/", "Chernihiv"}
    };

    for (const auto& city : cities) {
        fetchTemperature(city.url, city.name);
    }

    return 0;
}
