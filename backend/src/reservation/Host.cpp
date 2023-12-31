#include "Host.h"
#include "Table.h"
#include "Section.h"
#include "Reservation.h"
#include "../customercare/CustomerTemplate.h"

Host::Host(std::shared_ptr<Section> section, std::shared_ptr<Reservation> reservation, std::shared_ptr<CustomerTemplate> customer) {
    this->section = section;
    this->reservation = reservation;
    this->customer = customer;
}

Host::~Host() {

}

std::shared_ptr<Section> Host::getSection() {
    return this->section;
}

void Host::setSection(std::shared_ptr<Section> section) {
    this->section = section;
}

std::shared_ptr<Reservation> Host::getReservation() {
    return this->reservation;
}


void Host::setReservation(std::shared_ptr<Reservation> reservation) {
    this->reservation = reservation;
}

std::shared_ptr<CustomerTemplate> Host::getCustomer() {
    return this->customer;
}

void Host::setCustomer(std::shared_ptr<CustomerTemplate> customer) {
    this->customer = customer;
}

void Host::seatCustomer() {
    for(int i =0; i<(int)this->section->getTables().size();i++){
        if(this->section->getTables()[i]==this->reservation->getTable()){
            std::shared_ptr<Table> table = this->section->getTables()[i];
            table->sitCustomer(customer);
            break;
        }
    }
}

