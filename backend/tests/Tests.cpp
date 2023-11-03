#include <gtest/gtest.h>
#include <memory>

#include "./includes/customercare_all.cpp"
#include "./includes/reservation_all.cpp"
#include "./includes/inventory_all.cpp"
#include "./includes/ordering_all.cpp"
#include "./includes/cooking_all.cpp"
#include "./includes/management_all.cpp"

TEST(CustomerTest, ConstructorTest) {
    std::shared_ptr<Management> management = std::make_shared<Management>();
    std::shared_ptr<Customer>  customer = std::make_shared<Customer>(management);
    customer->setManagement(management);

    EXPECT_EQ(customer->getName(), "Main Character");
    EXPECT_EQ(customer->getMood()->getStateName(), "Happy");
    EXPECT_FALSE(customer->IsReadyToOrder());
    EXPECT_EQ(customer->getTotalBill(), 0);
    EXPECT_EQ(customer->getManagement(), management);
}

TEST(CustomerTest, MoodChange) {
    std::shared_ptr<Management> management = std::make_shared<Management>();
    std::shared_ptr<Customer>  customer = std::make_shared<Customer>(management);
    customer->setManagement(management);

    EXPECT_EQ(customer->getName(), "Main Character");
    EXPECT_EQ(customer->getMood()->getStateName(), "Happy");
    EXPECT_FALSE(customer->IsReadyToOrder());
    EXPECT_EQ(customer->getTotalBill(), 0);
    EXPECT_EQ(customer->getManagement(), management);

    customer->anger();
    EXPECT_EQ(customer->getMood()->getStateName(), "Neutral");

    customer->anger();
    EXPECT_EQ(customer->getMood()->getStateName(), "Unhappy");

    customer->console();
    EXPECT_EQ(customer->getMood()->getStateName(), "Neutral");

    customer->anger();
    EXPECT_EQ(customer->getMood()->getStateName(), "Unhappy");
    
}

TEST(CustomerTest, ReservationTest) {
    std::shared_ptr<Management> management = std::make_shared<Management>();
    Customer*  customer1 = new Customer(management);
    Customer*  customer2 = new Customer(management);

    customer1->setManagement(management);
    customer2->setDesiredSection("General Section");
    customer1->requestReservation();

    customer2->setManagement(management);
    customer2->setDesiredSection("Private Section");
    customer2->requestReservation();

    EXPECT_NE(customer1->getReservation(), nullptr);

    EXPECT_NE(customer2->getReservation(), nullptr);
    
}

TEST(CustomerTest, SeatingTest) {
    std::shared_ptr<Management> management = std::make_shared<Management>();
    Customer*  customer1 = new Customer(management);
    Customer*  customer2 = new Customer(management);
    CustomerNPC* customer3 = new CustomerNPC(management,true,"General Section");
    CustomerNPC* customer4 = new CustomerNPC(management,true,"Private Section");

    customer1->setManagement(management);
    customer1->setDesiredSection("General Section");
    customer1->requestReservation();

    customer2->setManagement(management);
    customer2->setDesiredSection("Private Section");
    customer2->requestReservation();

    customer3->setManagement(management);
    customer3->requestReservation();

    customer4->setManagement(management);
    customer4->requestReservation();

    EXPECT_NE(customer1->getReservation(), nullptr);

    EXPECT_NE(customer2->getReservation(), nullptr);

    EXPECT_NE(customer3->getReservation(), nullptr);

    EXPECT_NE(customer4->getReservation(), nullptr);

    customer1->requestToBeSeated();

    customer2->requestToBeSeated();

    customer3->requestToBeSeated();

    customer4->requestToBeSeated();

    std::shared_ptr<Section> privateSection = management->getPrivateSection();

    std::shared_ptr<Section> generalSection = management->getPrivateSection();

    std::shared_ptr<Table> table1 = customer1->getReservation()->getTable();

    std::shared_ptr<Table> table2 = customer2->getReservation()->getTable();

    std::shared_ptr<Table> table3 = customer3->getReservation()->getTable();

    std::shared_ptr<Table> table4 = customer4->getReservation()->getTable();

    EXPECT_EQ(table1->getIsReserved(), true);
    EXPECT_EQ(table2->getIsReserved(), true);
    EXPECT_EQ(table3->getIsReserved(), true);
    EXPECT_EQ(table4->getIsReserved(), true);

    EXPECT_EQ(table1->getIsOccupied(), true);
    EXPECT_EQ(table2->getIsOccupied(), true);
    EXPECT_EQ(table3->getIsOccupied(), true);
    EXPECT_EQ(table4->getIsOccupied(), true);

    std::vector<std::shared_ptr<CustomerTemplate>> customersPri = privateSection->getAllCustomers();
    std::vector<std::shared_ptr<CustomerTemplate>> customersGen = generalSection->getAllCustomers();

    bool flag = false;

    for(int i=0;i<(int)customersGen.size();i++){
        if(customersGen[i]->getName()=="Main Character"){
            flag = true;
        }
    }

    EXPECT_EQ(flag, true);

    flag = false;

    for(int i=0;i<(int)customersPri.size();i++){
        if(customersPri[i]->getName()=="Main Character"){
            flag = true;
        }
    }

    EXPECT_EQ(flag, true);

    flag = false;

    for(int i=0;i<(int)customersGen.size();i++){
        if(customersGen[i]->getName()=="NPC"){
            flag = true;
        }
    }

    EXPECT_EQ(flag, true);

    flag = false;

    for(int i=0;i<(int)customersPri.size();i++){
        if(customersPri[i]->getName()=="NPC"){
            flag = true;
        }
    }

    EXPECT_EQ(flag, true);

}

TEST(CustomerTest,Leave){
    std::shared_ptr<Management> management = std::make_shared<Management>();
    Customer*  customer1 = new Customer(management);
    Customer*  customer2 = new Customer(management);
    CustomerNPC* customer3 = new CustomerNPC(management,true,"General Section");
    CustomerNPC* customer4 = new CustomerNPC(management,true,"Private Section");

    customer1->setManagement(management);
    customer1->setDesiredSection("General Section");
    customer1->requestReservation();

    customer2->setManagement(management);
    customer2->setDesiredSection("Private Section");
    customer2->requestReservation();

    customer3->setManagement(management);
    customer3->requestReservation();

    customer4->setManagement(management);
    customer4->requestReservation();

    EXPECT_NE(customer1->getReservation(), nullptr);

    EXPECT_NE(customer2->getReservation(), nullptr);

    EXPECT_NE(customer3->getReservation(), nullptr);

    EXPECT_NE(customer4->getReservation(), nullptr);

    customer1->requestToBeSeated();

    customer2->requestToBeSeated();

    customer3->requestToBeSeated();

    customer4->requestToBeSeated();

    std::shared_ptr<Section> privateSection = management->getPrivateSection();

    std::shared_ptr<Section> generalSection = management->getPrivateSection();

    std::shared_ptr<Table> table1 = customer1->getReservation()->getTable();

    std::shared_ptr<Table> table2 = customer2->getReservation()->getTable();

    std::shared_ptr<Table> table3 = customer3->getReservation()->getTable();

    std::shared_ptr<Table> table4 = customer4->getReservation()->getTable();

    EXPECT_EQ(table1->getIsReserved(), true);
    EXPECT_EQ(table2->getIsReserved(), true);
    EXPECT_EQ(table3->getIsReserved(), true);
    EXPECT_EQ(table4->getIsReserved(), true);

    EXPECT_EQ(table1->getIsOccupied(), true);
    EXPECT_EQ(table2->getIsOccupied(), true);
    EXPECT_EQ(table3->getIsOccupied(), true);
    EXPECT_EQ(table4->getIsOccupied(), true);

    std::vector<std::shared_ptr<CustomerTemplate>> customersPri = privateSection->getAllCustomers();
    std::vector<std::shared_ptr<CustomerTemplate>> customersGen = generalSection->getAllCustomers();

    bool flag = false;

    for(int i=0;i<(int)customersGen.size();i++){
        if(customersGen[i]->getName()=="Main Character"){
            flag = true;
        }
    }

    EXPECT_EQ(flag, true);

    flag = false;

    for(int i=0;i<(int)customersPri.size();i++){
        if(customersPri[i]->getName()=="Main Character"){
            flag = true;
        }
    }

    EXPECT_EQ(flag, true);

    flag = false;

    for(int i=0;i<(int)customersGen.size();i++){
        if(customersGen[i]->getName()=="NPC"){
            flag = true;
        }
    }

    EXPECT_EQ(flag, true);

    flag = false;

    for(int i=0;i<(int)customersPri.size();i++){
        if(customersPri[i]->getName()=="NPC"){
            flag = true;
        }
    }

    EXPECT_EQ(flag, true);

    customer1->leave();

    customer2->leave();

    customer3->leave();

    customer4->leave();

    EXPECT_EQ(management->getPrivateSection()->getAllCustomers().size(), 0);
    EXPECT_EQ(management->getGeneralSection()->getAllCustomers().size(), 0);

}
