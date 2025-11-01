#include "modes.h"
#include <iostream>
#include <string>

using namespace Restaurant_Bot;

int main() {
    // Load the menu from JSON file
    initializeMenu("menu.json");
    
    // Welcome message and show menu
    introduce_bot(menu);
    
    // Get user information
    std::string firstName, lastName;
    std::cout << "\n=== User Information ===\n";
    std::cout << "Please introduce yourself\n";
    std::cout << "Enter your first name: ";
    std::getline(std::cin, firstName);
    std::cout << "Enter your last name: ";
    std::getline(std::cin, lastName);
    
    User user;
    user.setFirstName(firstName);
    user.setLastName(lastName);
    
    // Ask user which mode they prefer
    std::cout << "\n=== Mode Selection ===\n";
    std::cout << "Would you like AI-powered suggestions based on your taste? (yes/no): ";
    std::string modeChoice;
    std::getline(std::cin, modeChoice);
    
    if (modeChoice == "yes" || modeChoice == "Yes" || modeChoice == "YES") {
        // AI Suggestion Mode
        ai_suggestion_mode(user);
    } else {
        // Manual Menu Mode
        manual_menu_mode(user);
    }
    
    // Display final order
    std::cout << "\n========================================\n";
    std::cout << "         FINAL ORDER SUMMARY\n";
    std::cout << "========================================\n";
    std::cout << "Customer: " << user.getFirstName() << " " << user.getLastName() << "\n";
    std::cout << "Total Items: " << user.getMenu().getItemCount() << "\n";
    std::cout << "Total Cost: $" << user.getMenu().getCost() << "\n";
    std::cout << "----------------------------------------\n";
    
    std::cout << "\n=== Your Menu Items ===\n";
    for (const auto& [name, location] : user.getMenu().getItemLocationMap()) {
        std::cout << "'" << name << "' -> " << location.first 
                  << " [" << location.second << "]" << std::endl;
    }
    
    std::cout << "========================================\n";
    std::cout << "Thank you for using our Restaurant Bot!\n";
    std::cout << "========================================\n";
    
    return 0;
}
