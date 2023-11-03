#include <cstdlib> 
#include <ctime> 

#include "CustomerNPC.h"
#include "../ordering/Menu.h"

CustomerNPC::CustomerNPC(std::shared_ptr<Management> management) : CustomerTemplate("NPC",management){}

CustomerNPC::CustomerNPC(std::shared_ptr<Management> management,bool hasGuests,std::string DesiredSection) : CustomerTemplate("NPC",management){
    this->hasGuests = hasGuests;
    this->DesiredSection = DesiredSection;
    if(DesiredSection == "Private Section"){
        int numGuests = this->generateRandomAmmountOfGuests(1,10);
        for(int i = 0; i < numGuests; i++){
            std::shared_ptr<CustomerNPC> guest = std::make_shared<CustomerNPC>(management);
            this->addGuest(guest);
        }
    }else{
        int numGuests = this->generateRandomAmmountOfGuests(1,5);
        for(int i = 0; i < numGuests; i++){
            std::shared_ptr<CustomerNPC> guest = std::make_shared<CustomerNPC>(management);
            this->addGuest(guest);
        }
    }
}

CustomerNPC::~CustomerNPC(){}

std::unordered_map<std::string,int> CustomerNPC::generateBeverageOrder(Menu menu){
    // TODO: Implement way to automatically generate order
    std::unordered_map<std::string,int> order;
    return order;
}

std::unordered_map<std::string,int> CustomerNPC::generateFoodOrder(Menu menu){
    // TODO: Implement way to automatically generate order
    std::unordered_map<std::string,int> order;
    return order; 
}

int CustomerNPC::generateRandomAmmountOfGuests(int min, int max){
    srand(time(0)); 
    return min + rand() % (max - min + 1); 
}