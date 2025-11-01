#pragma once
#include "restaurant_bot.h"
#include "shared_data.h"
#include <string>

// Common functions
void print_menu(const Menu& menu);
void introduce_bot(const Menu& menu);

// AI Suggestion mode functions
taste_balance get_user_taste_preference();
void ai_suggestion_mode(Restaurant_Bot::User& user);

// Manual menu mode functions  
void manual_menu_mode(Restaurant_Bot::User& user);

// User creation function
Restaurant_Bot::User get_user_info();
