#include "modes.h"
#include <iostream>

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
    std::cout << "Welcome to the STC Restaurant"<<"\n";
    std::cout <<"            The Menu          "<<"\n";
    print_menu(menu);
    std::cout <<"Please introduce yourself"<<"\n";
}
