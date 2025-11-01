#include <iostream>
#include "restaurant_bot.h"
#include "shared_data.h"
#include <bits/stdc++.h>
//using namespace std;
#include <nlohmann/json.hpp>
#include <functional>
//#include <json/value.h>
#include <fstream>
using json = nlohmann::json;
using Handler = std::function<void(const json&)>;
using namespace Restaurant_Bot;

// menu yu global yaptım ki handler lar erişebilsin
// menu degiskenini atadim
// her bir handler icerisinde tmp objesi olusturup from_json ile doldurup menu ya ekliyorum
// her bir tur icin kendi handler fonksiyonunu yazdim
// sirayla atayabilsin diye vectrore atadim
Menu menu;

std::vector<Handler> handlers = {
    [](const json& el){ 
        Appetizer tmp; 
        tmp.from_json(el); 
        int index = menu.getAppetizersRef().size();
        menu.getAppetizersRef().push_back(tmp); 
        menu.getItemLocationMapRef()[tmp.getName()] = {"Appetizer", index};
    },
    [](const json& el){ 
        Dessert tmp; 
        tmp.from_json(el); 
        int index = menu.getDessertsRef().size();
        menu.getDessertsRef().push_back(tmp); 
        menu.getItemLocationMapRef()[tmp.getName()] = {"Dessert", index};
    },
    [](const json& el){ 
        Drink tmp; 
        tmp.from_json(el); 
        int index = menu.getDrinksRef().size();
        menu.getDrinksRef().push_back(tmp); 
        menu.getItemLocationMapRef()[tmp.getName()] = {"Drink", index};
    },
    [](const json& el){ 
        MainCourse tmp; 
        tmp.from_json(el); 
        int index = menu.getMainCoursesRef().size();
        menu.getMainCoursesRef().push_back(tmp); 
        menu.getItemLocationMapRef()[tmp.getName()] = {"MainCourse", index};
    },
    [](const json& el){ 
        Salad tmp; 
        tmp.from_json(el); 
        int index = menu.getSaladsRef().size();
        menu.getSaladsRef().push_back(tmp); 
        menu.getItemLocationMapRef()[tmp.getName()] = {"Salad", index};
    },
    [](const json& el){ 
        Starter tmp; 
        tmp.from_json(el); 
        int index = menu.getStartersRef().size();
        menu.getStartersRef().push_back(tmp); 
        menu.getItemLocationMapRef()[tmp.getName()] = {"Starter", index};
    }

};

// Function to initialize menu from JSON file
void initializeMenu(const std::string& filename) {
    initializeMenuInstance(menu, filename);
}

// Function to initialize any Menu instance from JSON file
void initializeMenuInstance(Menu& menuInstance, const std::string& filename) {
    std::ifstream menu_file(filename);
    
    if (!menu_file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }
    
    json menu_data;
    menu_file >> menu_data;
    
    // Create handlers specific to this menu instance
    std::vector<Handler> localHandlers = {
        [&menuInstance](const json& el){ 
            Appetizer tmp; 
            tmp.from_json(el); 
            int index = menuInstance.getAppetizersRef().size();
            menuInstance.getAppetizersRef().push_back(tmp); 
            menuInstance.getItemLocationMapRef()[tmp.getName()] = {"Appetizer", index};
        },
        [&menuInstance](const json& el){ 
            Dessert tmp; 
            tmp.from_json(el); 
            int index = menuInstance.getDessertsRef().size();
            menuInstance.getDessertsRef().push_back(tmp); 
            menuInstance.getItemLocationMapRef()[tmp.getName()] = {"Dessert", index};
        },
        [&menuInstance](const json& el){ 
            Drink tmp; 
            tmp.from_json(el); 
            int index = menuInstance.getDrinksRef().size();
            menuInstance.getDrinksRef().push_back(tmp); 
            menuInstance.getItemLocationMapRef()[tmp.getName()] = {"Drink", index};
        },
        [&menuInstance](const json& el){ 
            MainCourse tmp; 
            tmp.from_json(el); 
            int index = menuInstance.getMainCoursesRef().size();
            menuInstance.getMainCoursesRef().push_back(tmp); 
            menuInstance.getItemLocationMapRef()[tmp.getName()] = {"MainCourse", index};
        },
        [&menuInstance](const json& el){ 
            Salad tmp; 
            tmp.from_json(el); 
            int index = menuInstance.getSaladsRef().size();
            menuInstance.getSaladsRef().push_back(tmp); 
            menuInstance.getItemLocationMapRef()[tmp.getName()] = {"Salad", index};
        },
        [&menuInstance](const json& el){ 
            Starter tmp; 
            tmp.from_json(el); 
            int index = menuInstance.getStartersRef().size();
            menuInstance.getStartersRef().push_back(tmp); 
            menuInstance.getItemLocationMapRef()[tmp.getName()] = {"Starter", index};
        }
    };
    
    int hangi = 0;
    for(auto& item : menu_data){
        if(hangi >= localHandlers.size()) break;
        for(auto& element : item){
            localHandlers[hangi](element);
        }
        hangi++;
    }
    
    menu_file.close();
    std::cout << "Menu loaded successfully from " << filename << std::endl;
}

// Example usage of the Restaurant_Bot namespace in girdi.cpp

