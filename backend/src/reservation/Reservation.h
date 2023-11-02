#ifndef Reservation_H
#define Reservation_H

#include <string>
#include <vector>
#include <memory>

class Customer;
class Table;

class Reservation {
    std::shared_ptr<Customer> customer;
    std::shared_ptr<Table> table;

    public:
        Reservation(std::shared_ptr<Customer> Customer,std::shared_ptr<Table> table);
        ~Reservation();
        std::shared_ptr<Customer> getCustomer();
        std::shared_ptr<Table> getTable();

};

#endif