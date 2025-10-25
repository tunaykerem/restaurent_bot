#include <bits/stdc++.h>
//using namespace std;
namespace Restaurant_Bot{
    class taste_balance{
        public:
            int sweet;
            int sour;
            int bitter;
            int salty;
            int savory;
    };
    class MenuItem {
        public:
            std :: string name;
            int price;
            taste_balance taste;
    };
    class Starter : public MenuItem {
        public:
            std :: string heat_level;
    };
    class Salad : public MenuItem {
        public:
            bool toppings;
            float topping_cost=2.25;
    };
    class MainCourse : public MenuItem {
        public:
            bool vegetarian;
    };
    class Drink : public MenuItem {
        public:
            bool alcoholic;
            bool carbonated;
            float alcohol_cost=2.5;
            float carbonation_cost=0.5;
    };


    class Appetizer : public MenuItem {
        public:
            bool after_main_course;
    };
    class Dessert : public MenuItem {
        public:
            bool chocolate;
            float chocolate_cost=1.5;
    };
    class Menu{
        public:
            std :: vector<Starter>  starters;
            std :: vector<Appetizer> appetizers;
            std :: vector<MainCourse> mainCourses;
            std :: vector<Drink> drinks;
            std :: vector<Dessert> desserts;


    };
    class User{
        public:
            std :: string first_name;
            std :: string last_name;
            std :: string Gender;
            Menu menu;
            taste_balance tastePreference;
    };
    class Menu{
        public:
            std :: vector<Starter>  starters;
            std :: vector<Appetizer> appetizers;
            std :: vector<MainCourse> mainCourses;
            std :: vector<Drink> drinks;
            std :: vector<Dessert> desserts;
            float cost;
            float overall_taste;
    };
}
int main(){
    
}