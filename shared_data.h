#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <nlohmann/json.hpp>
#include "restaurant_bot.h"

using json = nlohmann::json;
using Handler = std::function<void(const json&)>;
using namespace Restaurant_Bot;

// Declare as extern so they can be shared across files
extern Menu menu;
extern std::vector<Handler> handlers;

// Function to initialize the menu from JSON file
void initializeMenu(const std::string& filename);
void initializeMenuInstance(Menu& menuInstance, const std::string& filename);
