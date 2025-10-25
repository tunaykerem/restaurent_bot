#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "restaurant_bot.h"
#include <bits/stdc++.h>
//using namespace std;
#include <nlohmann/json.hpp>
//#include <json/value.h>
#include <fstream>
using json = nlohmann::json;
namespace Restaurant_Bot {

struct taste_balance {
    int sweet{};
    int sour{};
    int bitter{};
    int salty{};
    int savory{};
};

struct MenuItem {
    std::string name;
    int price{};
    taste_balance taste;
    void from_json(const json& j){
        name = j["name"];
        price = j["price"];
        taste.sweet = j["taste"]["sweet"];
        taste.sour = j["taste"]["sour"];
        taste.bitter = j["taste"]["bitter"];
        taste.salty = j["taste"]["salty"];
        taste.savory = j["taste"]["savory"];
    }
};

struct Starter : public MenuItem {
    std::string heat_level;
};

struct Salad : public MenuItem {
    bool toppings{};
    float topping_cost = 2.25f;
};

struct MainCourse : public MenuItem {
    bool vegetarian{};
};

struct Drink : public MenuItem {
    bool alcoholic{};
    bool carbonated{};
    float alcohol_cost = 2.5f;
    float carbonation_cost = 0.5f;
};

struct Appetizer : public MenuItem {
    bool after_main_course{};
};

struct Dessert : public MenuItem {
    bool chocolate{};
    float chocolate_cost = 1.5f;
};

struct Menu {
    std::vector<Starter> starters;
    std::vector<Salad> salads;
    std::vector<Appetizer> appetizers;
    std::vector<MainCourse> mainCourses;
    std::vector<Drink> drinks;
    std::vector<Dessert> desserts;
    float cost{};
    float overall_taste{};
};

struct User {
    std::string first_name;
    std::string last_name;
    std::string Gender;
    Menu menu;
    
    taste_balance tastePreference;
};

} // namespace Restaurant_Bot
