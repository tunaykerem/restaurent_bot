#include "modes.h"
#include <iostream>
#include <string>

using namespace Restaurant_Bot;

void manual_menu_mode(User& user){
    std::string action;
    std::cout<<"\n=== Manual Menu Mode ===\n";
    std::cout<<"Do you want to 'add', 'delete', or 'update' an item? (or 'q' to quit)"<<"\n";
    std::getline(std::cin, action);
    
    while(action != "q" && action != "Q"){
        if(action == "add" || action == "Add" || action == "ADD"){
            std::cout<<"What do you wanna eat?"<<"\n";
            std::string food;
            std::getline(std::cin, food);
            
            const auto* itemPtr = menu.findPtr(food);
            
            if (itemPtr != nullptr) {
                if (const Starter* starter = dynamic_cast<const Starter*>(itemPtr)) {
                    Starter mutableCopy = *starter;
                    mutableCopy.set();
                    user.getMenuRef().add(mutableCopy);
                } else if (const Salad* salad = dynamic_cast<const Salad*>(itemPtr)) {
                    Salad mutableCopy = *salad;
                    mutableCopy.set();
                    user.getMenuRef().add(mutableCopy);
                } else if (const Appetizer* appetizer = dynamic_cast<const Appetizer*>(itemPtr)) {
                    Appetizer mutableCopy = *appetizer;
                    mutableCopy.set();
                    user.getMenuRef().add(mutableCopy);
                } else if (const MainCourse* mainCourse = dynamic_cast<const MainCourse*>(itemPtr)) {
                    MainCourse mutableCopy = *mainCourse;
                    mutableCopy.set();
                    user.getMenuRef().add(mutableCopy);
                } else if (const Drink* drink = dynamic_cast<const Drink*>(itemPtr)) {
                    Drink mutableCopy = *drink;
                    mutableCopy.set();
                    user.getMenuRef().add(mutableCopy);
                } else if (const Dessert* dessert = dynamic_cast<const Dessert*>(itemPtr)) {
                    Dessert mutableCopy = *dessert;
                    mutableCopy.set();
                    user.getMenuRef().add(mutableCopy);
                }
                std::cout << "Added '" << food << "' to your menu.\n";
            } else {
                std::cout << "Item '" << food << "' not found in restaurant menu.\n";
            }
        }
        else if(action == "delete" || action == "Delete" || action == "DELETE"){
            std::cout<<"What do you want to remove?"<<"\n";
            std::string food;
            std::getline(std::cin, food);
            user.getMenuRef().remove(food);
        }
        else if(action == "update" || action == "Update" || action == "UPDATE"){
            std::cout<<"Which item do you want to update?"<<"\n";
            std::string food;
            std::getline(std::cin, food);
            
            const auto* itemPtr = user.getMenu().findPtr(food);
            
            if (itemPtr != nullptr) {
                if (const Starter* starter = dynamic_cast<const Starter*>(itemPtr)) {
                    Starter mutableCopy = *starter;
                    mutableCopy.update();
                    user.getMenuRef().remove(food);
                    user.getMenuRef().add(mutableCopy);
                } else if (const Salad* salad = dynamic_cast<const Salad*>(itemPtr)) {
                    Salad mutableCopy = *salad;
                    mutableCopy.update();
                    user.getMenuRef().remove(food);
                    user.getMenuRef().add(mutableCopy);
                } else if (const Appetizer* appetizer = dynamic_cast<const Appetizer*>(itemPtr)) {
                    Appetizer mutableCopy = *appetizer;
                    mutableCopy.update();
                    user.getMenuRef().remove(food);
                    user.getMenuRef().add(mutableCopy);
                } else if (const MainCourse* mainCourse = dynamic_cast<const MainCourse*>(itemPtr)) {
                    MainCourse mutableCopy = *mainCourse;
                    mutableCopy.update();
                    user.getMenuRef().remove(food);
                    user.getMenuRef().add(mutableCopy);
                } else if (const Drink* drink = dynamic_cast<const Drink*>(itemPtr)) {
                    Drink mutableCopy = *drink;
                    mutableCopy.update();
                    user.getMenuRef().remove(food);
                    user.getMenuRef().add(mutableCopy);
                } else if (const Dessert* dessert = dynamic_cast<const Dessert*>(itemPtr)) {
                    Dessert mutableCopy = *dessert;
                    mutableCopy.update();
                    user.getMenuRef().remove(food);
                    user.getMenuRef().add(mutableCopy);
                }
                std::cout << "Updated '" << food << "' in your menu.\n";
            } else {
                std::cout << "Item '" << food << "' not found in your menu.\n";
            }
        }
        else{
            std::cout<<"Invalid action. Please type 'add', 'delete', 'update', or 'q'."<<"\n";
        }
        std::cout<<"Do you want to 'add', 'delete', or 'update' an item? (or 'q' to quit)"<<"\n";
        std::getline(std::cin, action);
    }
}
