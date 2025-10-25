#include <iostream>
#include "restaurant_bot.h"
#include <bits/stdc++.h>
//using namespace std;
#include <nlohmann/json.hpp>
//#include <json/value.h>
#include <fstream>
using json = nlohmann::json;
using Handler = std::function<void(const json&)>;
using namespace Restaurant_Bot;
Menu menu;
std::vector<Handler> handlers = {
    [](const json& el){ Starter tmp; tmp.from_json(el); menu.starters.push_back(tmp); },
    [](const json& el){ Salad tmp; tmp.from_json(el); menu.salads.push_back(tmp); },
    [](const json& el){ MainCourse tmp; tmp.from_json(el); menu.mainCourses.push_back(tmp); },
    [](const json& el){ Drink tmp; tmp.from_json(el); menu.drinks.push_back(tmp); },
    [](const json& el){ Appetizer tmp; tmp.from_json(el); menu.appetizers.push_back(tmp); },
    [](const json& el){ Dessert tmp; tmp.from_json(el); menu.desserts.push_back(tmp); }
};
// Example usage of the Restaurant_Bot namespace in ana.cpp
int main(){
	

	

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
