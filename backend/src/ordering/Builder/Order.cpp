/**
 * The function "listItems" prints out the complete order with the item names and their corresponding
 * prices.
 */
#include "Order.h"

void Order::listItems() const
{ 
    std::cout<<"Your complete order is: "<<std::endl;
    for(const auto& item:items)
    {
        std::cout<<item.first<< " :R"<<item.second<<std::endl;
    } 
    std::cout<<std:: endl;
}