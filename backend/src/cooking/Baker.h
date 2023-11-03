#ifndef BAKER_H
#define BAKER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "Kitchen.h"
#include "StationChef.h"

class Baker : public StationChef {
    public:
        Baker(std::shared_ptr<Engine> engine, std::shared_ptr<Kitchen> kitchen);
        ~Baker();
        void prepareOrder(std::shared_ptr<Order> order) override;
        void setNextChef() override;
        virtual void sendEvent();
        virtual void receiveEvent(std::string event);
};

#endif