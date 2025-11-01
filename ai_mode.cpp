#include "modes.h"
#include <iostream>
#include <string>

using namespace Restaurant_Bot;

taste_balance get_user_taste_preference() {
    taste_balance pref;
    std::cout << "\n=== Taste Preference Setup ===\n";
    std::cout << "Do you want a 'balanced' menu or 'custom' taste preferences? ";
    std::string choice;
    std::getline(std::cin, choice);
    
    if (choice == "balanced" || choice == "Balanced" || choice == "BALANCED") {
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
        
        std::cin.ignore();
    }
    
    return pref;
}

void ai_suggestion_mode(User& user) {
    taste_balance userPref = get_user_taste_preference();
    user.setTastePreference(userPref);
    
    std::cout << "\n=== AI Suggestion Mode ===\n";
    std::cout << "Now I'll suggest items for each category. You can accept or request a new suggestion.\n";
    std::string response;
    
    // 1. Starter
    bool starterApproved = false;
    while (!starterApproved) {
        Starter selectedStarter = menu.getBestStarter(userPref);
        
        // Calculate score for feedback
        auto categoryWeights = Menu::getWeightsForCategory("Starter");
        double score = selectedStarter.getTaste().distance_from(userPref, categoryWeights.weights, categoryWeights.extraWeight);
        
        std::cout << "\n--- STARTER SUGGESTION ---\n";
        std::cout << "Item: " << selectedStarter.getName() << " ($" << selectedStarter.getPrice() << ")\n";
        std::cout << "Taste: Sweet=" << selectedStarter.getTaste().getSweet() 
                  << ", Sour=" << selectedStarter.getTaste().getSour()
                  << ", Bitter=" << selectedStarter.getTaste().getBitter()
                  << ", Salty=" << selectedStarter.getTaste().getSalty()
                  << ", Savory=" << selectedStarter.getTaste().getSavory() << "\n";
        std::cout << "Match Score: " << score << "\n";
        std::cout << "Is this okay? (yes/no/skip): ";
        std::getline(std::cin, response);
        
        if (response == "yes" || response == "Yes" || response == "YES") {
            // Call set() to customize the item before adding
            selectedStarter.set();
            user.getMenuRef().add(selectedStarter);
            std::cout << "Added to your menu!\n";
            // Update weights based on positive feedback
            Menu::updateWeightsFromFeedback("Starter", selectedStarter, true, score, userPref, 0.1);
            starterApproved = true;
        } else if (response == "skip" || response == "Skip" || response == "SKIP") {
            std::cout << "Skipping starter.\n";
            starterApproved = true;
        } else {
            // Update weights based on negative feedback
            Menu::updateWeightsFromFeedback("Starter", selectedStarter, false, score, userPref, 0.1);
            std::cout << "Generating a new starter suggestion...\n";
        }
    }
    
    // 2. Salad
    bool saladApproved = false;
    while (!saladApproved) {
        Salad selectedSalad = menu.getBestSalad(userPref);
        
        // Calculate score for feedback
        auto categoryWeights = Menu::getWeightsForCategory("Salad");
        double score = selectedSalad.getTaste().distance_from(userPref, categoryWeights.weights, categoryWeights.extraWeight);
        
        std::cout << "\n--- SALAD SUGGESTION ---\n";
        std::cout << "Item: " << selectedSalad.getName() << " ($" << selectedSalad.getPrice() << ")\n";
        std::cout << "Taste: Sweet=" << selectedSalad.getTaste().getSweet() 
                  << ", Sour=" << selectedSalad.getTaste().getSour()
                  << ", Bitter=" << selectedSalad.getTaste().getBitter()
                  << ", Salty=" << selectedSalad.getTaste().getSalty()
                  << ", Savory=" << selectedSalad.getTaste().getSavory() << "\n";
        std::cout << "Match Score: " << score << "\n";
        std::cout << "Is this okay? (yes/no/skip): ";
        std::getline(std::cin, response);
        
        if (response == "yes" || response == "Yes" || response == "YES") {
            // Call set() to customize the item before adding
            selectedSalad.set();
            user.getMenuRef().add(selectedSalad);
            std::cout << "Added to your menu!\n";
            // Update weights based on positive feedback
            Menu::updateWeightsFromFeedback("Salad", selectedSalad, true, score, userPref, 0.1);
            saladApproved = true;
        } else if (response == "skip" || response == "Skip" || response == "SKIP") {
            std::cout << "Skipping salad.\n";
            saladApproved = true;
        } else {
            // Update weights based on negative feedback
            Menu::updateWeightsFromFeedback("Salad", selectedSalad, false, score, userPref, 0.1);
            std::cout << "Generating a new salad suggestion...\n";
        }
    }
    
    // 3. Main Course
    bool mainCourseApproved = false;
    while (!mainCourseApproved) {
        MainCourse selectedMainCourse = menu.getBestMainCourse(userPref);
        
        // Calculate score for feedback
        auto categoryWeights = Menu::getWeightsForCategory("MainCourse");
        double score = selectedMainCourse.getTaste().distance_from(userPref, categoryWeights.weights, categoryWeights.extraWeight);
        
        std::cout << "\n--- MAIN COURSE SUGGESTION ---\n";
        std::cout << "Item: " << selectedMainCourse.getName() << " ($" << selectedMainCourse.getPrice() << ")\n";
        std::cout << "Taste: Sweet=" << selectedMainCourse.getTaste().getSweet() 
                  << ", Sour=" << selectedMainCourse.getTaste().getSour()
                  << ", Bitter=" << selectedMainCourse.getTaste().getBitter()
                  << ", Salty=" << selectedMainCourse.getTaste().getSalty()
                  << ", Savory=" << selectedMainCourse.getTaste().getSavory() << "\n";
        std::cout << "Match Score: " << score << "\n";
        std::cout << "Is this okay? (yes/no/skip): ";
        std::getline(std::cin, response);
        
        if (response == "yes" || response == "Yes" || response == "YES") {
            // Call set() to customize the item before adding
            selectedMainCourse.set();
            user.getMenuRef().add(selectedMainCourse);
            std::cout << "Added to your menu!\n";
            // Update weights based on positive feedback
            Menu::updateWeightsFromFeedback("MainCourse", selectedMainCourse, true, score, userPref, 0.1);
            mainCourseApproved = true;
        } else if (response == "skip" || response == "Skip" || response == "SKIP") {
            std::cout << "Skipping main course.\n";
            mainCourseApproved = true;
        } else {
            // Update weights based on negative feedback
            Menu::updateWeightsFromFeedback("MainCourse", selectedMainCourse, false, score, userPref, 0.1);
            std::cout << "Generating a new main course suggestion...\n";
        }
    }
    
    // 4. Drink
    bool drinkApproved = false;
    while (!drinkApproved) {
        Drink selectedDrink = menu.getBestDrink(userPref);
        
        // Calculate score for feedback
        auto categoryWeights = Menu::getWeightsForCategory("Drink");
        double score = selectedDrink.getTaste().distance_from(userPref, categoryWeights.weights, categoryWeights.extraWeight);
        
        std::cout << "\n--- DRINK SUGGESTION ---\n";
        std::cout << "Item: " << selectedDrink.getName() << " ($" << selectedDrink.getPrice() << ")\n";
        std::cout << "Taste: Sweet=" << selectedDrink.getTaste().getSweet() 
                  << ", Sour=" << selectedDrink.getTaste().getSour()
                  << ", Bitter=" << selectedDrink.getTaste().getBitter()
                  << ", Salty=" << selectedDrink.getTaste().getSalty()
                  << ", Savory=" << selectedDrink.getTaste().getSavory() << "\n";
        std::cout << "Match Score: " << score << "\n";
        std::cout << "Is this okay? (yes/no/skip): ";
        std::getline(std::cin, response);
        
        if (response == "yes" || response == "Yes" || response == "YES") {
            // Call set() to customize the item before adding
            selectedDrink.set();
            user.getMenuRef().add(selectedDrink);
            std::cout << "Added to your menu!\n";
            // Update weights based on positive feedback
            Menu::updateWeightsFromFeedback("Drink", selectedDrink, true, score, userPref, 0.1);
            drinkApproved = true;
        } else if (response == "skip" || response == "Skip" || response == "SKIP") {
            std::cout << "Skipping drink.\n";
            drinkApproved = true;
        } else {
            // Update weights based on negative feedback
            Menu::updateWeightsFromFeedback("Drink", selectedDrink, false, score, userPref, 0.1);
            std::cout << "Generating a new drink suggestion...\n";
        }
    }
    
    // 5. Appetizer
    bool appetizerApproved = false;
    while (!appetizerApproved) {
        Appetizer selectedAppetizer = menu.getBestAppetizer(userPref);
        
        // Calculate score for feedback
        auto categoryWeights = Menu::getWeightsForCategory("Appetizer");
        double score = selectedAppetizer.getTaste().distance_from(userPref, categoryWeights.weights, categoryWeights.extraWeight);
        
        std::cout << "\n--- APPETIZER SUGGESTION ---\n";
        std::cout << "Item: " << selectedAppetizer.getName() << " ($" << selectedAppetizer.getPrice() << ")\n";
        std::cout << "Taste: Sweet=" << selectedAppetizer.getTaste().getSweet() 
                  << ", Sour=" << selectedAppetizer.getTaste().getSour()
                  << ", Bitter=" << selectedAppetizer.getTaste().getBitter()
                  << ", Salty=" << selectedAppetizer.getTaste().getSalty()
                  << ", Savory=" << selectedAppetizer.getTaste().getSavory() << "\n";
        std::cout << "Match Score: " << score << "\n";
        std::cout << "Is this okay? (yes/no/skip): ";
        std::getline(std::cin, response);
        
        if (response == "yes" || response == "Yes" || response == "YES") {
            // Call set() to customize the item before adding
            selectedAppetizer.set();
            user.getMenuRef().add(selectedAppetizer);
            std::cout << "Added to your menu!\n";
            // Update weights based on positive feedback
            Menu::updateWeightsFromFeedback("Appetizer", selectedAppetizer, true, score, userPref, 0.1);
            appetizerApproved = true;
        } else if (response == "skip" || response == "Skip" || response == "SKIP") {
            std::cout << "Skipping appetizer.\n";
            appetizerApproved = true;
        } else {
            // Update weights based on negative feedback
            Menu::updateWeightsFromFeedback("Appetizer", selectedAppetizer, false, score, userPref, 0.1);
            std::cout << "Generating a new appetizer suggestion...\n";
        }
    }
    
    // 6. Dessert
    bool dessertApproved = false;
    while (!dessertApproved) {
        Dessert selectedDessert = menu.getBestDessert(userPref);
        
        // Calculate score for feedback
        auto categoryWeights = Menu::getWeightsForCategory("Dessert");
        double score = selectedDessert.getTaste().distance_from(userPref, categoryWeights.weights, categoryWeights.extraWeight);
        
        std::cout << "\n--- DESSERT SUGGESTION ---\n";
        std::cout << "Item: " << selectedDessert.getName() << " ($" << selectedDessert.getPrice() << ")\n";
        std::cout << "Taste: Sweet=" << selectedDessert.getTaste().getSweet() 
                  << ", Sour=" << selectedDessert.getTaste().getSour()
                  << ", Bitter=" << selectedDessert.getTaste().getBitter()
                  << ", Salty=" << selectedDessert.getTaste().getSalty()
                  << ", Savory=" << selectedDessert.getTaste().getSavory() << "\n";
        std::cout << "Match Score: " << score << "\n";
        std::cout << "Is this okay? (yes/no/skip): ";
        std::getline(std::cin, response);
        
        if (response == "yes" || response == "Yes" || response == "YES") {
            // Call set() to customize the item before adding
            selectedDessert.set();
            user.getMenuRef().add(selectedDessert);
            std::cout << "Added to your menu!\n";
            // Update weights based on positive feedback
            Menu::updateWeightsFromFeedback("Dessert", selectedDessert, true, score, userPref, 0.1);
            dessertApproved = true;
        } else if (response == "skip" || response == "Skip" || response == "SKIP") {
            std::cout << "Skipping dessert.\n";
            dessertApproved = true;
        } else {
            // Update weights based on negative feedback
            Menu::updateWeightsFromFeedback("Dessert", selectedDessert, false, score, userPref, 0.1);
            std::cout << "Generating a new dessert suggestion...\n";
        }
    }
    
    std::cout << "\n=== AI Suggestion process completed! ===\n";
    std::cout << "Would you like to modify your menu? (yes/no): ";
    std::getline(std::cin, response);
    
    if (response == "yes" || response == "Yes" || response == "YES") {
        manual_menu_mode(user);
    }
}
