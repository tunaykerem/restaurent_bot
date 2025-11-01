#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
//using namespace std;
#include <nlohmann/json.hpp>
//#include <json/value.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using json = nlohmann::json;
namespace Restaurant_Bot {

struct taste_balance {
private:
    double sweet{1};
    double sour{1};
    double bitter{1};
    double salty{1};
    double savory{1};

public:
    // Getters
    double getSweet() const { return sweet; }
    double getSour() const { return sour; }
    double getBitter() const { return bitter; }
    double getSalty() const { return salty; }
    double getSavory() const { return savory; }
    
    // Setters
    void setSweet(double value) { sweet = value; }
    void setSour(double value) { sour = value; }
    void setBitter(double value) { bitter = value; }
    void setSalty(double value) { salty = value; }
    void setSavory(double value) { savory = value; }
    
    // Helper methods
    void add(double s_sweet, double s_sour, double s_bitter, double s_salty, double s_savory) {
        sweet += s_sweet;
        sour += s_sour;
        bitter += s_bitter;
        salty += s_salty;
        savory += s_savory;
    }
    
    // Calculate average taste values
    taste_balance average(double count) const {
        taste_balance avg;
        if (count > 0) {
            avg.setSweet(sweet / count);
            avg.setSour(sour / count);
            avg.setBitter(bitter / count);
            avg.setSalty(salty / count);
            avg.setSavory(savory / count);
        }
        return avg;
    }
    
    // Calculate distance from target taste_balance with weights
    double distance_from(const taste_balance& target, const taste_balance& weights, double extraWeight = 1.0) const {
        return std::sqrt(
            extraWeight * (
                std::pow(weights.getSweet() * sweet, 2) +
                std::pow(weights.getSour() * sour, 2) +
                std::pow(weights.getBitter() * bitter, 2) +
                std::pow(weights.getSalty() * salty, 2) +
                std::pow(weights.getSavory() * savory, 2)
            )
        );
    }
};

struct MenuItem {
private:
    std::string name;
    int price{};
    taste_balance taste;

public:
    virtual ~MenuItem() = default;  // Virtual destructor
    
    // Virtual Getters
    virtual std::string getName() const { return name; }
    virtual int getPrice() const { return price; }
    virtual taste_balance getTaste() const { return taste; }
    
    // Virtual Setters
    virtual void setName(const std::string& n) { name = n; }
    virtual void setPrice(int p) { price = p; }
    virtual void setTaste(const taste_balance& t) { taste = t; }
    
    virtual void from_json(const json& j){
        name = j["name"];
        price = j["price"];
        taste.setSweet(j["taste_balance"]["sweet"]);
        taste.setSour(j["taste_balance"]["sour"]);
        taste.setBitter(j["taste_balance"]["bitter"]);
        taste.setSalty(j["taste_balance"]["salty"]);
        taste.setSavory(j["taste_balance"]["savory"]);
    }
    
    // Virtual set function that child classes can override
    virtual void set() {
        std::cout << "Setting up base MenuItem: " << name << std::endl;
    }
    
    // Virtual update function that child classes can override
    virtual void update() {
        std::cout << "Updating base MenuItem: " << name << std::endl;
        std::cout << "Current price: " << price << std::endl;
    }
};

struct Starter : public MenuItem {
private:
    std::string heat_level;

public:
    // Getter and Setter
    std::string getHeatLevel() const { return heat_level; }
    void setHeatLevel(const std::string& level) { heat_level = level; }
    
    // Override set function with extra features for Starter
    void set() override {
        std::cout << "Setting up Starter: " << getName() << std::endl;
        std::cout << "how do you want your starter?(what heat level?)" << std::endl;
        std :: getline(std::cin, heat_level);
        // Add starter-specific setup here
        if (heat_level.empty()) {
            heat_level = "Medium"; // Default heat level
        }
        std::cout << "  Heat level set to: " << heat_level << std::endl;
    }
    
    // Override update function
    void update() override {
        std::cout << "Updating Starter: " << getName() << std::endl;
        std::cout << "Current heat level: " << heat_level << std::endl;
        std::cout << "Enter new heat level (or press Enter to keep current): ";
        std::string new_level;
        std::getline(std::cin, new_level);
        if (!new_level.empty()) {
            heat_level = new_level;
            std::cout << "Heat level updated to: " << heat_level << std::endl;
        }
    }
};

struct Salad : public MenuItem {
private:
    bool toppings{false};
    float topping_cost = 2.25f;

public:
    // Getters and Setters
    bool hasToppings() const { return toppings; }
    float getToppingCost() const { return topping_cost; }
    void setToppings(bool t) { toppings = t; }
    void setToppingCost(float cost) { topping_cost = cost; }
    
    // Override set function with extra features for Salad
    void set() override {
        
        std::cout << "Setting up Salad: " << getName() << std::endl;
        std::cout << "Do you want to add toppings? (yes/no)" << std::endl;
        std::string response;
        std::getline(std::cin, response);
        toppings = (response == "yes");
        if (toppings) {
            std::cout << "  Adding toppings (+" << topping_cost << " cost)" << std::endl;
            setPrice(getPrice() + topping_cost);
        }
    }
    
    // Override update function
    void update() override {
        std::cout << "Updating Salad: " << getName() << std::endl;
        std::cout << "Current toppings: " << (toppings ? "Yes" : "No") << std::endl;
        std::cout << "Do you want to change toppings? (yes/no): ";
        std::string response;
        std::getline(std::cin, response);
        if (response == "yes") {
            bool old_toppings = toppings;
            std::cout << "Add toppings? (yes/no): ";
            std::getline(std::cin, response);
            toppings = (response == "yes");
            if (toppings && !old_toppings) {
                setPrice(getPrice() + topping_cost);
            } else if (!toppings && old_toppings) {
                setPrice(getPrice() - topping_cost);
            }
        }
    }
};

struct MainCourse : public MenuItem {
private:
    bool vegetarian{false};

public:
    // Getter and Setter
    bool isVegetarian() const { return vegetarian; }
    void setVegetarian(bool v) { vegetarian = v; }
    
    // Override set function with extra features for MainCourse
    void set() override {
        std::cout << "Setting up Main Course: " << getName() << std::endl;
        std::cout << "Do you want a vegetarian option? (yes/no)" << std::endl;
        std::string response;
        std::getline(std::cin, response);
        vegetarian = (response == "yes");
        if (vegetarian) {
            std::cout << "  This is a vegetarian option" << std::endl;
        }
    }
    
    // Override update function
    void update() override {
        std::cout << "Updating Main Course: " << getName() << std::endl;
        std::cout << "Current option: " << (vegetarian ? "Vegetarian" : "Non-vegetarian") << std::endl;
        std::cout << "Do you want to change to " << (vegetarian ? "non-vegetarian" : "vegetarian") << "? (yes/no): ";
        std::string response;
        std::getline(std::cin, response);
        if (response == "yes") {
            vegetarian = !vegetarian;
            std::cout << "Changed to " << (vegetarian ? "vegetarian" : "non-vegetarian") << std::endl;
        }
    }
};

struct Drink : public MenuItem {
private:
    bool alcoholic{false};
    bool carbonated{false};
    float alcohol_cost = 2.5f;
    float carbonation_cost = 0.5f;

public:
    // Getters and Setters
    bool isAlcoholic() const { return alcoholic; }
    bool isCarbonated() const { return carbonated; }
    float getAlcoholCost() const { return alcohol_cost; }
    float getCarbonationCost() const { return carbonation_cost; }
    void setAlcoholic(bool a) { alcoholic = a; }
    void setCarbonated(bool c) { carbonated = c; }
    void setAlcoholCost(float cost) { alcohol_cost = cost; }
    void setCarbonationCost(float cost) { carbonation_cost = cost; }
    
    // Override set function with extra features for Drink
    void set() override {
        std::cout << "Setting up Drink: " << getName() << std::endl;
        std::cout << "Do you want alcohol? (yes/no)" << std::endl;
        std::string response;
        std::getline(std::cin, response);
        alcoholic = (response == "yes");
        if (alcoholic) {
            std::cout << "  Adding alcohol (+" << alcohol_cost << " cost)" << std::endl;
            setPrice(getPrice() + alcohol_cost);
        }
        std::cout << "Do you want carbonation? (yes/no)" << std::endl;
        std::getline(std::cin, response);
        carbonated = (response == "yes");
        if (carbonated) {
            std::cout << "  Adding carbonation (+" << carbonation_cost << " cost)" << std::endl;
            setPrice(getPrice() + carbonation_cost);
        }
    }
    
    // Override update function
    void update() override {
        std::cout << "Updating Drink: " << getName() << std::endl;
        std::cout << "Current: " << (alcoholic ? "Alcoholic" : "Non-alcoholic") 
                  << ", " << (carbonated ? "Carbonated" : "Non-carbonated") << std::endl;
        
        std::cout << "Change alcohol? (yes/no): ";
        std::string response;
        std::getline(std::cin, response);
        if (response == "yes") {
            bool old_alcoholic = alcoholic;
            std::cout << "Make it alcoholic? (yes/no): ";
            std::getline(std::cin, response);
            alcoholic = (response == "yes");
            if (alcoholic && !old_alcoholic) {
                setPrice(getPrice() + alcohol_cost);
            } else if (!alcoholic && old_alcoholic) {
                setPrice(getPrice() - alcohol_cost);
            }
        }
        
        std::cout << "Change carbonation? (yes/no): ";
        std::getline(std::cin, response);
        if (response == "yes") {
            bool old_carbonated = carbonated;
            std::cout << "Make it carbonated? (yes/no): ";
            std::getline(std::cin, response);
            carbonated = (response == "yes");
            if (carbonated && !old_carbonated) {
                setPrice(getPrice() + carbonation_cost);
            } else if (!carbonated && old_carbonated) {
                setPrice(getPrice() - carbonation_cost);
            }
        }
    }
};

struct Appetizer : public MenuItem {
private:
    bool after_main_course{};

public:
    // Getter and Setter
    bool isAfterMainCourse() const { return after_main_course; }
    void setAfterMainCourse(bool after) { after_main_course = after; }
    
    // Override set function with extra features for Appetizer
    void set() override {
        std::cout << "Setting up Appetizer: " << getName() << std::endl;
        std::cout << "Is this appetizer served after the main course? (yes/no)" << std::endl;
        std::string response;
        std::getline(std::cin, response);
        after_main_course = (response == "yes");
        if (after_main_course) {
            std::cout << "  This appetizer is served after the main course" << std::endl;
        }
    }
    
    // Override update function
    void update() override {
        std::cout << "Updating Appetizer: " << getName() << std::endl;
        std::cout << "Served: " << (after_main_course ? "After main course" : "Before main course") << std::endl;
        std::cout << "Change serving time? (yes/no): ";
        std::string response;
        std::getline(std::cin, response);
        if (response == "yes") {
            after_main_course = !after_main_course;
            std::cout << "Now served: " << (after_main_course ? "After main course" : "Before main course") << std::endl;
        }
    }
};

struct Dessert : public MenuItem {
private:
    bool chocolate{false};
    float chocolate_cost = 1.5f;

public:
    // Getters and Setters
    bool hasChocolate() const { return chocolate; }
    float getChocolateCost() const { return chocolate_cost; }
    void setChocolate(bool c) { chocolate = c; }
    void setChocolateCost(float cost) { chocolate_cost = cost; }
    
    // Override set function with extra features for Dessert
    void set() override {
        std::cout << "Setting up Dessert: " << getName() << std::endl;
        std::cout << "Do you want extra chocolate? (yes/no)" << std::endl;
        std::string response;
        std::getline(std::cin, response);
        chocolate = (response == "yes");
        if (chocolate) {
            std::cout << "  Adding extra chocolate (+" << chocolate_cost << " cost)" << std::endl;
            setPrice(getPrice() + chocolate_cost);
        }
    }
    
    // Override update function
    void update() override {
        std::cout << "Updating Dessert: " << getName() << std::endl;
        std::cout << "Current chocolate: " << (chocolate ? "Yes" : "No") << std::endl;
        std::cout << "Change chocolate option? (yes/no): ";
        std::string response;
        std::getline(std::cin, response);
        if (response == "yes") {
            bool old_chocolate = chocolate;
            std::cout << "Add extra chocolate? (yes/no): ";
            std::getline(std::cin, response);
            chocolate = (response == "yes");
            if (chocolate && !old_chocolate) {
                setPrice(getPrice() + chocolate_cost);
            } else if (!chocolate && old_chocolate) {
                setPrice(getPrice() - chocolate_cost);
            }
        }
    }
};

struct Menu {
private:
    std::vector<Starter> starters;
    std::vector<Salad> salads;
    std::vector<Appetizer> appetizers;
    std::vector<MainCourse> mainCourses;
    std::vector<Drink> drinks;
    std::vector<Dessert> desserts;
    std::map<std::string, std::pair<std::string, int>> itemLocationMap;
    float cost{0};
    int item_count{0};
    taste_balance overall_taste{};

public:
    // Getters
    const std::vector<Starter>& getStarters() const { return starters; }
    const std::vector<Salad>& getSalads() const { return salads; }
    const std::vector<Appetizer>& getAppetizers() const { return appetizers; }
    const std::vector<MainCourse>& getMainCourses() const { return mainCourses; }
    const std::vector<Drink>& getDrinks() const { return drinks; }
    const std::vector<Dessert>& getDesserts() const { return desserts; }
    const std::map<std::string, std::pair<std::string, int>>& getItemLocationMap() const { return itemLocationMap; }
    float getCost() const { return cost; }
    int getItemCount() const { return item_count; }
    taste_balance getOverallTaste() const { return overall_taste; }
    
    // Non-const getters for modification (used internally)
    std::vector<Starter>& getStartersRef() { return starters; }
    std::vector<Salad>& getSaladsRef() { return salads; }
    std::vector<Appetizer>& getAppetizersRef() { return appetizers; }
    std::vector<MainCourse>& getMainCoursesRef() { return mainCourses; }
    std::vector<Drink>& getDrinksRef() { return drinks; }
    std::vector<Dessert>& getDessertsRef() { return desserts; }
    std::map<std::string, std::pair<std::string, int>>& getItemLocationMapRef() { return itemLocationMap; }
    
    // Find and return pointer to the actual item (preserves type)
    const MenuItem* findPtr(const std::string& itemName) const {
        auto it = itemLocationMap.find(itemName);
        if (it != itemLocationMap.end()) {
            const std::string& category = it->second.first;
            int index = it->second.second;

            if (category == "Starter" && index < starters.size()) {
                return &starters[index];
            } else if (category == "Salad" && index < salads.size()) {
                return &salads[index];
            } else if (category == "Appetizer" && index < appetizers.size()) {
                return &appetizers[index];
            } else if (category == "MainCourse" && index < mainCourses.size()) {
                return &mainCourses[index];
            } else if (category == "Drink" && index < drinks.size()) {
                return &drinks[index];
            } else if (category == "Dessert" && index < desserts.size()) {
                return &desserts[index];
            }
        }
        return nullptr;
    }
    
    Restaurant_Bot::MenuItem find(const std::string& itemName) const {
        auto it = itemLocationMap.find(itemName);
        if (it != itemLocationMap.end()) {
            const std::string& category = it->second.first;
            int index = it->second.second;

            if (category == "Starter" && index < starters.size()) {
                return starters[index];
            } else if (category == "Salad" && index < salads.size()) {
                return salads[index];
            } else if (category == "Appetizer" && index < appetizers.size()) {
                return appetizers[index];
            } else if (category == "MainCourse" && index < mainCourses.size()) {
                return mainCourses[index];
            } else if (category == "Drink" && index < drinks.size()) {
                return drinks[index];
            } else if (category == "Dessert" && index < desserts.size()) {
                return desserts[index];
            } else {
                throw std::out_of_range("Index out of range for category: " + category);
            }
        } else {
            throw std::invalid_argument("Item not found in menu: " + itemName);
        }
    }
    void set_taste(const MenuItem& item, int multiplier) {
        taste_balance itemTaste = item.getTaste();
        overall_taste.add(
            itemTaste.getSweet() * multiplier,
            itemTaste.getSour() * multiplier,
            itemTaste.getBitter() * multiplier,
            itemTaste.getSalty() * multiplier,
            itemTaste.getSavory() * multiplier
        );
    }
    void add(const MenuItem& item) {
        set_taste(item, 1);
        item_count++;
        cost += item.getPrice();
        
        if (const Starter* starter = dynamic_cast<const Starter*>(&item)) {
            starters.push_back(*starter);
            int index = starters.size() - 1;
            itemLocationMap[starter->getName()] = {"Starter", index};
        } else if (const Salad* salad = dynamic_cast<const Salad*>(&item)) {
            salads.push_back(*salad);
            int index = salads.size() - 1;
            itemLocationMap[salad->getName()] = {"Salad", index};
        } else if (const Appetizer* appetizer = dynamic_cast<const Appetizer*>(&item)) {
            appetizers.push_back(*appetizer);
            int index = appetizers.size() - 1;
            itemLocationMap[appetizer->getName()] = {"Appetizer", index};
        } else if (const MainCourse* mainCourse = dynamic_cast<const MainCourse*>(&item)) {
            mainCourses.push_back(*mainCourse);
            int index = mainCourses.size() - 1;
            itemLocationMap[mainCourse->getName()] = {"MainCourse", index};
        } else if (const Drink* drink = dynamic_cast<const Drink*>(&item)) {
            drinks.push_back(*drink);
            int index = drinks.size() - 1;
            itemLocationMap[drink->getName()] = {"Drink", index};
        } else if (const Dessert* dessert = dynamic_cast<const Dessert*>(&item)) {
            desserts.push_back(*dessert);
            int index = desserts.size() - 1;
            itemLocationMap[dessert->getName()] = {"Dessert", index};
        } else {
            std::cerr << "Unknown MenuItem type!" << std::endl;
        }
        
    }
    void remove(const std::string& itemName) {
        auto it = itemLocationMap.find(itemName);
        if (it != itemLocationMap.end()) {
            const std::string& category = it->second.first;
            int index = it->second.second;

            if (category == "Starter" && index < starters.size()) {
                set_taste(starters[index], -1); // Adjust taste balance
                cost -= starters[index].getPrice();
                starters.erase(starters.begin() + index);
            } else if (category == "Salad" && index < salads.size()) {
                set_taste(salads[index], -1); // Adjust taste balance
                cost -= salads[index].getPrice();
                salads.erase(salads.begin() + index);
            } else if (category == "Appetizer" && index < appetizers.size()) {
                set_taste(appetizers[index], -1); // Adjust taste balance
                cost -= appetizers[index].getPrice();
                appetizers.erase(appetizers.begin() + index);
            } else if (category == "MainCourse" && index < mainCourses.size()) {
                set_taste(mainCourses[index], -1); // Adjust taste balance
                cost -= mainCourses[index].getPrice();
                mainCourses.erase(mainCourses.begin() + index);
            } else if (category == "Drink" && index < drinks.size()) {
                set_taste(drinks[index], -1); // Adjust taste balance
                cost -= drinks[index].getPrice();
                drinks.erase(drinks.begin() + index);
            } else if (category == "Dessert" && index < desserts.size()) {
                set_taste(desserts[index], -1); // Adjust taste balance
                cost -= desserts[index].getPrice();
                desserts.erase(desserts.begin() + index);
            } else {
                std::cerr << "Index out of range for category: " << category << std::endl;
                return;
            }

            item_count--;
            itemLocationMap.erase(it);
        } else {
            std::cerr << "Item not found in menu: " << itemName << std::endl;
        }
        
    }
    
    // Structure to hold a complete suggestion (one item from each category)
    struct Suggestion {
        Starter starter;
        Salad salad;
        MainCourse mainCourse;
        Drink drink;
        Appetizer appetizer;
        Dessert dessert;
        taste_balance avgTaste;
        double tasteScore{0.0};
    };
    
    // Get random item from each category
    Suggestion getRandomSuggestion() const {
        Suggestion suggestion;
        
        if (!starters.empty()) {
            int idx = std::rand() % starters.size();
            suggestion.starter = starters[idx];
        }
        if (!salads.empty()) {
            int idx = std::rand() % salads.size();
            suggestion.salad = salads[idx];
        }
        if (!mainCourses.empty()) {
            int idx = std::rand() % mainCourses.size();
            suggestion.mainCourse = mainCourses[idx];
        }
        if (!drinks.empty()) {
            int idx = std::rand() % drinks.size();
            suggestion.drink = drinks[idx];
        }
        if (!appetizers.empty()) {
            int idx = std::rand() % appetizers.size();
            suggestion.appetizer = appetizers[idx];
        }
        if (!desserts.empty()) {
            int idx = std::rand() % desserts.size();
            suggestion.dessert = desserts[idx];
        }
        
        // Calculate average taste
        taste_balance totalTaste;
        totalTaste.add(
            suggestion.starter.getTaste().getSweet() +
            suggestion.salad.getTaste().getSweet() +
            suggestion.mainCourse.getTaste().getSweet() +
            suggestion.drink.getTaste().getSweet() +
            suggestion.appetizer.getTaste().getSweet() +
            suggestion.dessert.getTaste().getSweet(),
            
            suggestion.starter.getTaste().getSour() +
            suggestion.salad.getTaste().getSour() +
            suggestion.mainCourse.getTaste().getSour() +
            suggestion.drink.getTaste().getSour() +
            suggestion.appetizer.getTaste().getSour() +
            suggestion.dessert.getTaste().getSour(),
            
            suggestion.starter.getTaste().getBitter() +
            suggestion.salad.getTaste().getBitter() +
            suggestion.mainCourse.getTaste().getBitter() +
            suggestion.drink.getTaste().getBitter() +
            suggestion.appetizer.getTaste().getBitter() +
            suggestion.dessert.getTaste().getBitter(),
            
            suggestion.starter.getTaste().getSalty() +
            suggestion.salad.getTaste().getSalty() +
            suggestion.mainCourse.getTaste().getSalty() +
            suggestion.drink.getTaste().getSalty() +
            suggestion.appetizer.getTaste().getSalty() +
            suggestion.dessert.getTaste().getSalty(),
            
            suggestion.starter.getTaste().getSavory() +
            suggestion.salad.getTaste().getSavory() +
            suggestion.mainCourse.getTaste().getSavory() +
            suggestion.drink.getTaste().getSavory() +
            suggestion.appetizer.getTaste().getSavory() +
            suggestion.dessert.getTaste().getSavory()
        );
        
        suggestion.avgTaste = totalTaste.average(6);
        return suggestion;
    }
    
    // Get best suggestion matching target taste
    Suggestion getBestSuggestion(const taste_balance& targetTaste, int attempts = 100) const {
        // Use default weights (all 1.0) for overall suggestion
        taste_balance defaultWeights;
        
        Suggestion bestSuggestion = getRandomSuggestion();
        double bestScore = bestSuggestion.avgTaste.distance_from(targetTaste, defaultWeights);
        bestSuggestion.tasteScore = bestScore;
        
        for (int i = 1; i < attempts; i++) {
            Suggestion current = getRandomSuggestion();
            double currentScore = current.avgTaste.distance_from(targetTaste, defaultWeights);
            current.tasteScore = currentScore;
            
            if (currentScore > bestScore) {
                bestScore = currentScore;
                bestSuggestion = current;
            }
        }
        
        return bestSuggestion;
    }
    
    // Get best item for each category based on taste preference
    // Evaluates EVERY item in the category to find the absolute best match
    Starter getBestStarter(const taste_balance& targetTaste) const {
        if (starters.empty()) return Starter();
        
        auto categoryWeights = getWeightsForCategory("Starter");
        
        int bestIdx = 0;
        double bestScore = starters[0].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
        
        // Check every single starter
        for (size_t i = 1; i < starters.size(); i++) {
            double score = starters[i].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
            if (score > bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }
        return starters[bestIdx];
    }
    
    Salad getBestSalad(const taste_balance& targetTaste) const {
        if (salads.empty()) return Salad();
        
        auto categoryWeights = getWeightsForCategory("Salad");
        
        int bestIdx = 0;
        double bestScore = salads[0].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
        
        // Check every single salad
        for (size_t i = 1; i < salads.size(); i++) {
            double score = salads[i].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
            if (score > bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }
        return salads[bestIdx];
    }
    
    MainCourse getBestMainCourse(const taste_balance& targetTaste) const {
        if (mainCourses.empty()) return MainCourse();
        
        auto categoryWeights = getWeightsForCategory("MainCourse");
        
        int bestIdx = 0;
        double bestScore = mainCourses[0].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
        
        // Check every single main course
        for (size_t i = 1; i < mainCourses.size(); i++) {
            double score = mainCourses[i].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
            if (score > bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }
        return mainCourses[bestIdx];
    }
    
    Drink getBestDrink(const taste_balance& targetTaste) const {
        if (drinks.empty()) return Drink();
        
        auto categoryWeights = getWeightsForCategory("Drink");
        
        int bestIdx = 0;
        double bestScore = drinks[0].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
        
        // Check every single drink
        for (size_t i = 1; i < drinks.size(); i++) {
            double score = drinks[i].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
            if (score > bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }
        return drinks[bestIdx];
    }
    
    Appetizer getBestAppetizer(const taste_balance& targetTaste) const {
        if (appetizers.empty()) return Appetizer();
        
        auto categoryWeights = getWeightsForCategory("Appetizer");
        
        int bestIdx = 0;
        double bestScore = appetizers[0].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
        
        // Check every single appetizer
        for (size_t i = 1; i < appetizers.size(); i++) {
            double score = appetizers[i].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
            if (score > bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }
        return appetizers[bestIdx];
    }
    
    Dessert getBestDessert(const taste_balance& targetTaste) const {
        if (desserts.empty()) return Dessert();
        
        auto categoryWeights = getWeightsForCategory("Dessert");
        
        int bestIdx = 0;
        double bestScore = desserts[0].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
        
        // Check every single dessert
        for (size_t i = 1; i < desserts.size(); i++) {
            double score = desserts[i].getTaste().distance_from(targetTaste, categoryWeights.weights, categoryWeights.extraWeight);
            if (score > bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }
        return desserts[bestIdx];
    }
    
    // Structure to hold weights and extra weight
    struct CategoryWeights {
        taste_balance weights;
        double extraWeight{1.0};
    };
    
    // Load weights from weights.json for a specific category
    static CategoryWeights getWeightsForCategory(const std::string& category) {
        CategoryWeights result;
        
        std::ifstream file("weights.json");
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open weights.json, using default weights (all 1.0)" << std::endl;
            return result; // Returns default (all 1s)
        }
        
        try {
            json weightsData;
            file >> weightsData;
            
            // Map category names to JSON keys
            std::string jsonKey;
            if (category == "Starter") jsonKey = "starters";
            else if (category == "Salad") jsonKey = "salads";
            else if (category == "MainCourse") jsonKey = "main_courses";
            else if (category == "Drink") jsonKey = "drinks";
            else if (category == "Appetizer") jsonKey = "appetizers";
            else if (category == "Dessert") jsonKey = "desserts";
            else {
                std::cerr << "Unknown category: " << category << std::endl;
                return result;
            }
            
            if (weightsData.contains(jsonKey)) {
                if (weightsData[jsonKey].contains("taste_balance")) {
                    auto tb = weightsData[jsonKey]["taste_balance"];
                    result.weights.setSweet(tb["sweet"].get<double>()); // Keep 0-1 range
                    result.weights.setSour(tb["sour"].get<double>());
                    result.weights.setBitter(tb["bitter"].get<double>());
                    result.weights.setSalty(tb["salty"].get<double>());
                    result.weights.setSavory(tb["savory"].get<double>());
                }
                
                // Load extra weight if present
                if (weightsData[jsonKey].contains("extra_weight")) {
                    result.extraWeight = weightsData[jsonKey]["extra_weight"].get<double>();
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing weights.json: " << e.what() << std::endl;
        }
        
        file.close();
        return result;
    }
    
    // Update weights in weights.json for a specific category
    static bool updateWeightsForCategory(const std::string& category, const CategoryWeights& newWeights) {
        // Read the entire JSON file
        std::ifstream inFile("weights.json");
        if (!inFile.is_open()) {
            std::cerr << "Error: Could not open weights.json for reading" << std::endl;
            return false;
        }
        
        json weightsData;
        try {
            inFile >> weightsData;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing weights.json: " << e.what() << std::endl;
            inFile.close();
            return false;
        }
        inFile.close();
        
        // Map category names to JSON keys
        std::string jsonKey;
        if (category == "Starter") jsonKey = "starters";
        else if (category == "Salad") jsonKey = "salads";
        else if (category == "MainCourse") jsonKey = "main_courses";
        else if (category == "Drink") jsonKey = "drinks";
        else if (category == "Appetizer") jsonKey = "appetizers";
        else if (category == "Dessert") jsonKey = "desserts";
        else {
            std::cerr << "Unknown category: " << category << std::endl;
            return false;
        }
        
        // Update the weights for this category
        if (!weightsData.contains(jsonKey)) {
            weightsData[jsonKey] = json::object();
        }
        
        weightsData[jsonKey]["taste_balance"] = {
            {"sweet", newWeights.weights.getSweet()},
            {"sour", newWeights.weights.getSour()},
            {"bitter", newWeights.weights.getBitter()},
            {"salty", newWeights.weights.getSalty()},
            {"savory", newWeights.weights.getSavory()}
        };
        
        weightsData[jsonKey]["extra_weight"] = newWeights.extraWeight;
        
        // Write back to file
        std::ofstream outFile("weights.json");
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open weights.json for writing" << std::endl;
            return false;
        }
        
        outFile << std::setw(4) << weightsData << std::endl;
        outFile.close();
        
        std::cout << "Successfully updated weights for " << category << std::endl;
        return true;
    }
    
    // Update weights from user feedback using gradient descent
    // Formula: w_i = w_i + α(y - ŷ)x_i + β(user_pref_i - item_i)
    // where: y = user feedback (1 or 0), ŷ = current score, x_i = taste value, 
    //        user_pref_i = user's preference for taste i, α,β = learning rates
    static bool updateWeightsFromFeedback(
        const std::string& category,
        const MenuItem& item,
        bool userLiked,  // true = 1 (liked), false = 0 (disliked)
        double currentScore,
        const taste_balance& userPreference,  // User's taste preferences
        double learningRate = 0.1
    ) {
        // Get current weights for this category
        auto categoryWeights = getWeightsForCategory(category);
        
        // Calculate error from yes/no feedback: (y - ŷ)
        double y = userLiked ? 1.0 : 0.0;
        double globalError = y - currentScore;
        
        // Get item's taste values
        taste_balance itemTaste = item.getTaste();
        
        // Update each weight using BOTH yes/no feedback AND specific taste preferences
        // Formula: w_i = w_i + α(global_error) * item_i + β(user_pref_i - item_i)
        double beta = learningRate * 0.5; // Smaller learning rate for preference-based updates
        
        // For each taste dimension, calculate two types of errors:
        // 1. Global error (did they like it overall?)
        // 2. Specific taste error (how close is each taste to their preference?)
        
        double sweetError = (userPreference.getSweet() - itemTaste.getSweet()) / 10.0; // Normalize to 0-1
        double sourError = (userPreference.getSour() - itemTaste.getSour()) / 10.0;
        double bitterError = (userPreference.getBitter() - itemTaste.getBitter()) / 10.0;
        double saltyError = (userPreference.getSalty() - itemTaste.getSalty()) / 10.0;
        double savoryError = (userPreference.getSavory() - itemTaste.getSavory()) / 10.0;
        
        // Update weights combining both feedback types
        double newSweet = categoryWeights.weights.getSweet() + 
                         learningRate * globalError * itemTaste.getSweet() / 10.0 +
                         beta * sweetError;
        double newSour = categoryWeights.weights.getSour() + 
                        learningRate * globalError * itemTaste.getSour() / 10.0 +
                        beta * sourError;
        double newBitter = categoryWeights.weights.getBitter() + 
                          learningRate * globalError * itemTaste.getBitter() / 10.0 +
                          beta * bitterError;
        double newSalty = categoryWeights.weights.getSalty() + 
                         learningRate * globalError * itemTaste.getSalty() / 10.0 +
                         beta * saltyError;
        double newSavory = categoryWeights.weights.getSavory() + 
                          learningRate * globalError * itemTaste.getSavory() / 10.0 +
                          beta * savoryError;
        
        // Clamp weights to [0, 1] range to prevent them from going negative or too large
        newSweet = std::max(0.0, std::min(1.0, newSweet));
        newSour = std::max(0.0, std::min(1.0, newSour));
        newBitter = std::max(0.0, std::min(1.0, newBitter));
        newSalty = std::max(0.0, std::min(1.0, newSalty));
        newSavory = std::max(0.0, std::min(1.0, newSavory));
        
        // Update extra weight as well (using average of taste values as x)
        double avgTasteValue = (itemTaste.getSweet() + itemTaste.getSour() + 
                                itemTaste.getBitter() + itemTaste.getSalty() + 
                                itemTaste.getSavory()) / 50.0; // Normalize
        double newExtraWeight = categoryWeights.extraWeight + learningRate * globalError * avgTasteValue;
        newExtraWeight = std::max(0.1, std::min(2.0, newExtraWeight)); // Clamp to [0.1, 2.0]
        
        // Create updated weights
        CategoryWeights updatedWeights;
        updatedWeights.weights.setSweet(newSweet);
        updatedWeights.weights.setSour(newSour);
        updatedWeights.weights.setBitter(newBitter);
        updatedWeights.weights.setSalty(newSalty);
        updatedWeights.weights.setSavory(newSavory);
        updatedWeights.extraWeight = newExtraWeight;
        
        // Save to file
        bool success = updateWeightsForCategory(category, updatedWeights);
        
        if (success) {
            std::cout << "Weights updated based on your feedback!" << std::endl;
            std::cout << "Global error: " << globalError << ", Learning rate: " << learningRate << std::endl;
        }
        
        return success;
    }
    
    // Each menu has its own item location map
    
};

struct User {
private:
    std::string first_name;
    std::string last_name;
    std::string Gender;
    Menu menu;
    taste_balance tastePreference;

public:
    // Getters
    std::string getFirstName() const { return first_name; }
    std::string getLastName() const { return last_name; }
    std::string getGender() const { return Gender; }
    const Menu& getMenu() const { return menu; }
    Menu& getMenuRef() { return menu; }
    taste_balance getTastePreference() const { return tastePreference; }
    
    // Setters
    void setFirstName(const std::string& name) { first_name = name; }
    void setLastName(const std::string& name) { last_name = name; }
    void setGender(const std::string& gender) { Gender = gender; }
    void setTastePreference(const taste_balance& pref) { tastePreference = pref; }
};

} // namespace Restaurant_Bot
