#include <iostream>
#include "restaurant_bot.h"
#include <bits/stdc++.h>
//using namespace std;
#include <nlohmann/json.hpp>
//#include <json/value.h>
#include <fstream>
using json = nlohmann::json;
using Handler = std::function<void(const json_t&)>;
std::vector<Handler> handlers = {
    [&](const json_t& el){ Starter tmp; tmp.from_json(el); menu.starters.push_back(std::move(tmp)); },
    [&](const json_t& el){ Salad tmp; tmp.from_json(el); menu.salads.push_back(std::move(tmp)); },
    [&](const json_t& el){ MainCourse tmp; tmp.from_json(el); menu.mainCourses.push_back(std::move(tmp)); },
    [&](const json_t& el){ Drink tmp; tmp.from_json(el); menu.drinks.push_back(std::move(tmp)); },
    [&](const json_t& el){ Appetizer tmp; tmp.from_json(el); menu.appetizers.push_back(std::move(tmp)); },
    [&](const json_t& el){ Dessert tmp; tmp.from_json(el); menu.desserts.push_back(std::move(tmp)); }
};
// Example usage of the Restaurant_Bot namespace in ana.cpp
int main(){
	using namespace Restaurant_Bot;

	Menu menu;

	Starter s;

    std::ifstream menu_file("menu.json");

    json menu_data;
    menu_file >> menu_data;
    int hangi = 0;
    for(auto& item : menu_data){
        if(hangi >= handlers.size()) break;
        for(auto& element : item){
            handlers[hangi](element);
        }
        hangi++;
    }
    std::cout << menu_data;
}
