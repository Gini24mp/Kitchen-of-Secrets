#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <memory>

// #include "GameComponent.h"
#include "ReservationSystem.h"

using namespace std; 

class Table {
protected:
    int tableID;
    int xCoord;
    int yCoord;
    bool isOccupied;
    int seat;
    ReservationSystem* reservation;
    
public:
    Table(Engine* engine, int tableID, int seat);
    ~Table();
    int getTableID();
    void setTableID(int tableID);
    virtual void addReservation(ReservationSystem* reservation, int seat) = 0;
    void placeTable(int xCoord, int yCoord);
    bool getIsOccupied();
    void setIsOccupied(bool isOccupied);
    // virtual void sendNotification() = 0;
    // virtual void receiveNotification(std::string message) = 0;
};

#endif