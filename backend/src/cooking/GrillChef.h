#ifndef GRILL_CHEF_H
#define GRILL_CHEF_H

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "Kitchen.h"
#include "StationChef.h"

class GrillChef : public StationChef{
    public:
        GrillChef(std::shared_ptr<Engine> engine, std::shared_ptr<Kitchen> kitchen);
        ~GrillChef();
        void prepareOrder(std::shared_ptr<Order> order) override;
        void setNextChef() override;
};

#endif