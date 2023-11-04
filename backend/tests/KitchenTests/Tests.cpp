#include <gtest/gtest.h>
#include <memory>

#include "../includes/customercare_all.cpp"
#include "../includes/reservation_all.cpp"
#include "../includes/inventory_all.cpp"
#include "../includes/ordering_all.cpp"
#include "../includes/cooking_all.cpp"
#include "../includes/management_all.cpp"

TEST(CusineTest, CuisineConstructorTest) {
    std::unordered_map<std::string, int> ingredients = {{"salt", 2}, {"pepper", 1}, {"garlic", 3}};
    Cuisine cusine(10.99, "Lemonade", "Gordon Ramsay", ingredients);
    EXPECT_EQ(cusine.getPrice(), 10.99);
    EXPECT_EQ(cusine.getName(), "Lemonade");
    EXPECT_EQ(cusine.getChef(), "Gordon Ramsay");
    EXPECT_EQ(cusine.getIngredients(), ingredients);

    std::unordered_map<std::string, int> ingredients2 = {{"basil", 1}, {"pine nuts", 2}, {"garlic", 3}};
    std::shared_ptr<Cuisine> Cusine2 = std::make_shared<Cuisine>(12.99, "Pesto Pasta", "Jamie Oliver", ingredients2);
    
    EXPECT_EQ(Cusine2->getPrice(), 12.99);
    EXPECT_EQ(Cusine2->getName(), "Pesto Pasta");
    EXPECT_EQ(Cusine2->getChef(), "Jamie Oliver");
    EXPECT_EQ(Cusine2->getIngredients(), ingredients2);

}

TEST(DrinksTest, DrinksConstructorTest) {
    std::unordered_map<std::string, int> ingredients = {{"lemon", 2}, {"sugar", 1}, {"water", 3}};
    Drink drink(false,10.99, "Lemonade", "Gordon Ramsay", ingredients);
    EXPECT_EQ(drink.getPrice(), 10.99);
    EXPECT_EQ(drink.getName(), "Lemonade");
    EXPECT_EQ(drink.getChef(), "Gordon Ramsay");
    EXPECT_EQ(drink.getIngredients(), ingredients);
    EXPECT_FALSE(drink.getIsAlcoholic());

    std::unordered_map<std::string, int> ingredients2 = {{"lemon", 1}, {"sugar", 2}, {"water", 3}, {"vodka", 1}};
    std::shared_ptr<Drink> drink2 = std::make_shared<Drink>(true,12.99, "Pesto Pasta", "Jamie Oliver", ingredients2);
    
    EXPECT_EQ(drink2->getPrice(), 12.99);
    EXPECT_EQ(drink2->getName(), "Pesto Pasta");
    EXPECT_EQ(drink2->getChef(), "Jamie Oliver");
    EXPECT_EQ(drink2->getIngredients(), ingredients2); 
    EXPECT_TRUE(drink2->getIsAlcoholic());   

}

TEST(KitchenTest,ConstructorTest){  
    //shared_ptr<Management> management
    std::shared_ptr<Management> management = std::make_shared<Management>();

    //kitchen
    std::shared_ptr<Kitchen> kitchen = std::make_shared<Kitchen>(management.get());
    
    //check magament
    EXPECT_EQ(kitchen->getManagement(), management.get());
    EXPECT_NE(kitchen->getManagement(), nullptr);
    EXPECT_NE(kitchen->getHeadChef(),nullptr);
    EXPECT_NE(kitchen->getDeputyHeadChef(),nullptr);
    EXPECT_EQ(kitchen->getMenu().size(),25);
    EXPECT_EQ(kitchen->getDrinksMenu().size(),10);
    EXPECT_EQ(kitchen->getCuisineMenu().size(),15);

}

TEST(KitchenTest,GetCusineAndDrinkTest){  
    //shared_ptr<Management> management
    std::shared_ptr<Management> management = std::make_shared<Management>();

    //kitchen
    std::shared_ptr<Kitchen> kitchen = std::make_shared<Kitchen>(management.get());
    
    //check magament
    EXPECT_FALSE(kitchen->getDrink("Witches' Brew Punch")->getIsAlcoholic());
    EXPECT_TRUE(kitchen->getDrink("Vampire's Kiss Martini")->getIsAlcoholic());
    EXPECT_EQ(kitchen->getCusine("Skeletal Ribs")->getPrice(),10.99);
    EXPECT_EQ(kitchen->getCusine("Pumpkin Patch Risotto")->getIngredients().size(),1);
}

TEST(KitchenTest,OrderingProcessTest){  
    std::shared_ptr<Management> management = std::make_shared<Management>();
    std::shared_ptr<Kitchen> kitchen = std::make_shared<Kitchen>(management.get());
    management->setKitchen(kitchen);
    Section* section = management->getGeneralSection().get();
    std::shared_ptr<Waiter> waiterPtr = std::make_shared<Waiter>(section, management.get());

    Customer*  customer1 = new Customer(management);

    CustomerNPC* customer3 = new CustomerNPC(management,true,"General Section");

    //seting up the main customer
    customer1->setManagement(management);
    customer1->setDesiredSection("General Section");
    customer1->requestReservation();
    customer1->requestToBeSeated();

    //seting up the NPC customer
    customer3->setManagement(management);
    customer3->requestReservation();
    customer3->requestToBeSeated();
    
    //SEETING UP DRINKS ORDER
    customer1->setBeverageOrder({{"Witches' Brew Punch",1},{"Vampire's Kiss Martini",2}});

    //seting up food order
    customer1->setFoodOrder({{"Vampire Garlic Bread",5},{"Werewolf Bites",4},{"Screaming Salad",3},{"Cursed Cauldron Curry",2}});
    
    //waiter going on rounds
    waiterPtr->doOrderRounds();

    //check for customer1 order;
    EXPECT_NE(customer1->getFinishedOrder(),nullptr);
    EXPECT_TRUE(customer1->getFinishedOrder()->IsFinished());

    //check for customer3 order;
    EXPECT_NE(customer3->getFinishedOrder(),nullptr);
    EXPECT_TRUE(customer3->getFinishedOrder()->IsFinished());

}

