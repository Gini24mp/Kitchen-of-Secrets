#include "Unhappy.h"
#include "VeryUnhappy.h"
#include "Neutral.h"

Unhappy::Unhappy(CustomerTemplate* customer) : SatisfactionState("Unhappy", customer, 0.2, 0.0){

}

void Unhappy::console(){
    this->customer->setMood(std::make_shared<Neutral>(this->customer));
}

void Unhappy::anger(){
    this->customer->setMood(std::make_shared<VeryUnhappy>(this->customer));
}