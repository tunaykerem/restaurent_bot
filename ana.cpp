

#include <iostream>
#include "restaurant_bot.h"
#include "shared_data.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace Restaurant_Bot;

void print_menu(const Menu& menu){
    std::cout << "=== STARTERS ===\n";
    for(const auto& s : menu.getStarters()){
        std::cout << " - " << s.getName() << " (" << s.getPrice() << ")\n";
    }
    
    std::cout << "\n=== SALADS ===\n";
    for(const auto& sa : menu.getSalads()){
        std::cout << " - " << sa.getName() << " (" << sa.getPrice() << ")\n";
    }
    
    std::cout << "\n=== MAIN COURSES ===\n";
    for(const auto& m : menu.getMainCourses()){
        std::cout << " - " << m.getName() << " (" << m.getPrice() << ")\n";
    }
    
    std::cout << "\n=== DRINKS ===\n";
    for(const auto& d : menu.getDrinks()){
        std::cout << " - " << d.getName() << " (" << d.getPrice() << ")\n";
    }
    
    std::cout << "\n=== APPETIZERS ===\n";
    for(const auto& a : menu.getAppetizers()){
        std::cout << " - " << a.getName() << " (" << a.getPrice() << ")\n";
    }
    
    std::cout << "\n=== DESSERTS ===\n";
    for(const auto& ds : menu.getDesserts()){
        std::cout << " - " << ds.getName() << " (" << ds.getPrice() << ")\n";
    }
}
void introduce_bot(const Menu& menu){
    
    std :: cout << "Welcome to the STC Restautant"<<"\n";
    
    std :: cout <<"            The Menu          "<<"\n";

    print_menu(menu);

    std :: cout <<"Please introduce yourself"<<"\n";


}

void print_suggestion(const Menu::Suggestion& suggestion) {
    std::cout << "\n=== SUGGESTED MENU ===\n";
    std::cout << "Starter: " << suggestion.starter.getName() 
              << " ($" << suggestion.starter.getPrice() << ")\n";
    std::cout << "Salad: " << suggestion.salad.getName() 
              << " ($" << suggestion.salad.getPrice() << ")\n";
    std::cout << "Main Course: " << suggestion.mainCourse.getName() 
              << " ($" << suggestion.mainCourse.getPrice() << ")\n";
    std::cout << "Drink: " << suggestion.drink.getName() 
              << " ($" << suggestion.drink.getPrice() << ")\n";
    std::cout << "Appetizer: " << suggestion.appetizer.getName() 
              << " ($" << suggestion.appetizer.getPrice() << ")\n";
    std::cout << "Dessert: " << suggestion.dessert.getName() 
              << " ($" << suggestion.dessert.getPrice() << ")\n";
    
    std::cout << "\n--- Average Taste Profile ---\n";
    std::cout << "Sweet: " << suggestion.avgTaste.getSweet() << "\n";
    std::cout << "Sour: " << suggestion.avgTaste.getSour() << "\n";
    std::cout << "Bitter: " << suggestion.avgTaste.getBitter() << "\n";
    std::cout << "Salty: " << suggestion.avgTaste.getSalty() << "\n";
    std::cout << "Savory: " << suggestion.avgTaste.getSavory() << "\n";
    std::cout << "======================\n";
}

taste_balance get_user_taste_preference() {
    taste_balance pref;
    std::cout << "\n=== Taste Preference Setup ===\n";
    std::cout << "Do you want a 'balanced' menu or 'custom' taste preferences? ";
    std::string choice;
    std::getline(std::cin, choice);
    
    if (choice == "balanced" || choice == "Balanced" || choice == "BALANCED") {
        // Balanced means all taste values are equal (e.g., 5 for each)
        pref.setSweet(5);
        pref.setSour(5);
        pref.setBitter(5);
        pref.setSalty(5);
        pref.setSavory(5);
        std::cout << "Balanced taste profile selected (all values set to 5)\n";
    } else {
        std::cout << "Enter your preferred taste values (0-10 scale):\n";
        int value;
        
        std::cout << "Sweet (0-10): ";
        std::cin >> value;
        pref.setSweet(value);
        
        std::cout << "Sour (0-10): ";
        std::cin >> value;
        pref.setSour(value);
        
        std::cout << "Bitter (0-10): ";
        std::cin >> value;
        pref.setBitter(value);
        
        std::cout << "Salty (0-10): ";
        std::cin >> value;
        pref.setSalty(value);
        
        std::cout << "Savory (0-10): ";
        std::cin >> value;
        pref.setSavory(value);
        
        std::cin.ignore(); // Clear the newline
    }
    
    return pref;
}

bool get_suggestion_mode(const Menu& restaurant_menu, User& user) {
    std::cout << "\n=== Menu Suggestion System ===\n";
    std::cout << "Would you like AI-powered suggestions based on your taste? (yes/no): ";
    std::string response;
    std::getline(std::cin, response);
    
    if (response == "yes" || response == "Yes" || response == "YES") {
        taste_balance userPref = get_user_taste_preference();
        user.setTastePreference(userPref);
        
        std::cout << "\nNow I'll suggest items for each category. You can accept or request a new suggestion.\n";
        
        // 1. Starter
        bool starterApproved = false;
        Starter selectedStarter;
        while (!starterApproved) {
            selectedStarter = restaurant_menu.getBestStarter(userPref);
            std::cout << "\n--- STARTER SUGGESTION ---\n";
            std::cout << "Item: " << selectedStarter.getName() << " ($" << selectedStarter.getPrice() << ")\n";
            std::cout << "Taste: Sweet=" << selectedStarter.getTaste().getSweet() 
                      << ", Sour=" << selectedStarter.getTaste().getSour()
                      << ", Bitter=" << selectedStarter.getTaste().getBitter()
                      << ", Salty=" << selectedStarter.getTaste().getSalty()
                      << ", Savory=" << selectedStarter.getTaste().getSavory() << "\n";
            std::cout << "Is this okay? (yes/no/skip): ";
            std::getline(std::cin, response);
            if (response == "yes" || response == "Yes" || response == "YES") {
                user.getMenuRef().add(selectedStarter);
                std::cout << "Added to your menu!\n";
                starterApproved = true;
            } else if (response == "skip" || response == "Skip" || response == "SKIP") {
                std::cout << "Skipping starter.\n";
                starterApproved = true;
            } else {
                std::cout << "Generating a new starter suggestion...\n";
            }
        }
        
        // 2. Salad
        bool saladApproved = false;
        Salad selectedSalad;
        while (!saladApproved) {
            selectedSalad = restaurant_menu.getBestSalad(userPref);
            std::cout << "\n--- SALAD SUGGESTION ---\n";
            std::cout << "Item: " << selectedSalad.getName() << " ($" << selectedSalad.getPrice() << ")\n";
            std::cout << "Taste: Sweet=" << selectedSalad.getTaste().getSweet() 
                      << ", Sour=" << selectedSalad.getTaste().getSour()
                      << ", Bitter=" << selectedSalad.getTaste().getBitter()
                      << ", Salty=" << selectedSalad.getTaste().getSalty()
                      << ", Savory=" << selectedSalad.getTaste().getSavory() << "\n";
            std::cout << "Is this okay? (yes/no/skip): ";
            std::getline(std::cin, response);
            if (response == "yes" || response == "Yes" || response == "YES") {
                user.getMenuRef().add(selectedSalad);
                std::cout << "Added to your menu!\n";
                saladApproved = true;
            } else if (response == "skip" || response == "Skip" || response == "SKIP") {
                std::cout << "Skipping salad.\n";
                saladApproved = true;
            } else {
                std::cout << "Generating a new salad suggestion...\n";
            }
        }
        
        // 3. Main Course
        bool mainCourseApproved = false;
        MainCourse selectedMainCourse;
        while (!mainCourseApproved) {
            selectedMainCourse = restaurant_menu.getBestMainCourse(userPref);
            std::cout << "\n--- MAIN COURSE SUGGESTION ---\n";
            std::cout << "Item: " << selectedMainCourse.getName() << " ($" << selectedMainCourse.getPrice() << ")\n";
            std::cout << "Taste: Sweet=" << selectedMainCourse.getTaste().getSweet() 
                      << ", Sour=" << selectedMainCourse.getTaste().getSour()
                      << ", Bitter=" << selectedMainCourse.getTaste().getBitter()
                      << ", Salty=" << selectedMainCourse.getTaste().getSalty()
                      << ", Savory=" << selectedMainCourse.getTaste().getSavory() << "\n";
            std::cout << "Is this okay? (yes/no/skip): ";
            std::getline(std::cin, response);
            if (response == "yes" || response == "Yes" || response == "YES") {
                user.getMenuRef().add(selectedMainCourse);
                std::cout << "Added to your menu!\n";
                mainCourseApproved = true;
            } else if (response == "skip" || response == "Skip" || response == "SKIP") {
                std::cout << "Skipping main course.\n";
                mainCourseApproved = true;
            } else {
                std::cout << "Generating a new main course suggestion...\n";
            }
        }
        
        // 4. Drink
        bool drinkApproved = false;
        Drink selectedDrink;
        while (!drinkApproved) {
            selectedDrink = restaurant_menu.getBestDrink(userPref);
            std::cout << "\n--- DRINK SUGGESTION ---\n";
            std::cout << "Item: " << selectedDrink.getName() << " ($" << selectedDrink.getPrice() << ")\n";
            std::cout << "Taste: Sweet=" << selectedDrink.getTaste().getSweet() 
                      << ", Sour=" << selectedDrink.getTaste().getSour()
                      << ", Bitter=" << selectedDrink.getTaste().getBitter()
                      << ", Salty=" << selectedDrink.getTaste().getSalty()
                      << ", Savory=" << selectedDrink.getTaste().getSavory() << "\n";
            std::cout << "Is this okay? (yes/no/skip): ";
            std::getline(std::cin, response);
            if (response == "yes" || response == "Yes" || response == "YES") {
                user.getMenuRef().add(selectedDrink);
                std::cout << "Added to your menu!\n";
                drinkApproved = true;
            } else if (response == "skip" || response == "Skip" || response == "SKIP") {
                std::cout << "Skipping drink.\n";
                drinkApproved = true;
            } else {
                std::cout << "Generating a new drink suggestion...\n";
            }
        }
        
        // 5. Appetizer
        bool appetizerApproved = false;
        Appetizer selectedAppetizer;
        while (!appetizerApproved) {
            selectedAppetizer = restaurant_menu.getBestAppetizer(userPref);
            std::cout << "\n--- APPETIZER SUGGESTION ---\n";
            std::cout << "Item: " << selectedAppetizer.getName() << " ($" << selectedAppetizer.getPrice() << ")\n";
            std::cout << "Taste: Sweet=" << selectedAppetizer.getTaste().getSweet() 
                      << ", Sour=" << selectedAppetizer.getTaste().getSour()
                      << ", Bitter=" << selectedAppetizer.getTaste().getBitter()
                      << ", Salty=" << selectedAppetizer.getTaste().getSalty()
                      << ", Savory=" << selectedAppetizer.getTaste().getSavory() << "\n";
            std::cout << "Is this okay? (yes/no/skip): ";
            std::getline(std::cin, response);
            if (response == "yes" || response == "Yes" || response == "YES") {
                user.getMenuRef().add(selectedAppetizer);
                std::cout << "Added to your menu!\n";
                appetizerApproved = true;
            } else if (response == "skip" || response == "Skip" || response == "SKIP") {
                std::cout << "Skipping appetizer.\n";
                appetizerApproved = true;
            } else {
                std::cout << "Generating a new appetizer suggestion...\n";
            }
        }
        
        // 6. Dessert
        bool dessertApproved = false;
        Dessert selectedDessert;
        while (!dessertApproved) {
            selectedDessert = restaurant_menu.getBestDessert(userPref);
            std::cout << "\n--- DESSERT SUGGESTION ---\n";
            std::cout << "Item: " << selectedDessert.getName() << " ($" << selectedDessert.getPrice() << ")\n";
            std::cout << "Taste: Sweet=" << selectedDessert.getTaste().getSweet() 
                      << ", Sour=" << selectedDessert.getTaste().getSour()
                      << ", Bitter=" << selectedDessert.getTaste().getBitter()
                      << ", Salty=" << selectedDessert.getTaste().getSalty()
                      << ", Savory=" << selectedDessert.getTaste().getSavory() << "\n";
            std::cout << "Is this okay? (yes/no/skip): ";
            std::getline(std::cin, response);
            if (response == "yes" || response == "Yes" || response == "YES") {
                user.getMenuRef().add(selectedDessert);
                std::cout << "Added to your menu!\n";
                dessertApproved = true;
            } else if (response == "skip" || response == "Skip" || response == "SKIP") {
                std::cout << "Skipping dessert.\n";
                dessertApproved = true;
            } else {
                std::cout << "Generating a new dessert suggestion...\n";
            }
        }
        
        std::cout << "\n=== Suggestion process completed! ===\n";
        return true;
    }
    return false;
}
Restaurant_Bot::User get_user_menu(const Menu& restaurant_menu, User user){
    std :: string action;
    std :: cout<<"Do you want to 'add', 'delete', or 'update' an item? (or 'q' to quit)"<<"\n";
    std :: getline(std::cin, action);
    while(action != "q" && action != "Q"){
        if(action == "add" || action == "Add" || action == "ADD"){
            std :: cout<<"What do you wanna eat?"<<"\n";
            std :: string food;
            std :: getline(std::cin, food);
            
            // Use findPtr to get pointer to actual item (preserves type)
            const auto* itemPtr = restaurant_menu.findPtr(food);
            
            if (itemPtr != nullptr) {
                // Create a mutable copy of the item to call set() on it
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
            std :: cout<<"What do you want to remove?"<<"\n";
            std :: string food;
            std :: getline(std::cin, food);
            user.getMenuRef().remove(food);
        }
        else if(action == "update" || action == "Update" || action == "UPDATE"){
            std :: cout<<"Which item do you want to update?"<<"\n";
            std :: string food;
            std :: getline(std::cin, food);
            
            // Find the item in user's menu
            const auto* itemPtr = user.getMenu().findPtr(food);
            
            if (itemPtr != nullptr) {
                // Create a mutable copy to call update() on it
                if (const Starter* starter = dynamic_cast<const Starter*>(itemPtr)) {
                    Starter mutableCopy = *starter;
                    mutableCopy.update();
                    // Remove old and add updated
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
            std :: cout<<"Invalid action. Please type 'add', 'delete', 'update', or 'q'."<<"\n";
        }
        std :: cout<<"Do you want to 'add', 'delete', or 'update' an item? (or 'q' to quit)"<<"\n";
        std :: getline(std::cin, action);
    }
    return user;
}

Restaurant_Bot::User get_user_info(const Menu& menu){
    User user;
    std :: cout<<"What is your first name?"<<"\n";
    std :: string firstName;
    std :: getline(std::cin, firstName);
    user.setFirstName(firstName);
    
    std :: cout<<"What is your last name?"<<"\n";
    std :: string lastName;
    std :: getline(std::cin, lastName);
    user.setLastName(lastName);

    std :: cout<<"What is your gender?"<<"\n";
    std :: string gender;
    std :: getline(std::cin, gender);
    user.setGender(gender);

    // First, offer AI suggestion system
    bool usedSuggestion = get_suggestion_mode(menu, user);
    
    // Then allow manual add/delete/update
    std::cout << "\nYou can now manually add, delete, or update items.\n";
    user = get_user_menu(menu, user);
    return user;
} 
int main(){
    // Initialize random seed for suggestions
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Initialize menu from girdi.cpp's shared data
    initializeMenu("menu.json");
    
    // Display loaded menu
    introduce_bot(menu);
    
    // Now you can access menu.itemLocationMap
    // std::cout << "\n=== Item Locations in Menu ===" << std::endl;
    // for (const auto& [name, location] : menu.itemLocationMap) {
    //     std::cout << "'" << name << "' -> " << location.first 
    //               << " [" << location.second << "]" << std::endl;
    // }
    
    // Example: Create a separate menu for a user
    User user = get_user_info(menu);
    
    // User's menu also has its own itemLocationMap
    std::cout << "\n=== User's Menu Items ===" << std::endl;
    for (const auto& [name, location] : user.getMenu().getItemLocationMap()) {
        std::cout << "'" << name << "' -> " << location.first 
                  << " [" << location.second << "]" << std::endl;
    }

    return 0;
}
