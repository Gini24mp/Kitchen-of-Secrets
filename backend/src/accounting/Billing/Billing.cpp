#include "Billing.h"

Billing::Billing(std::shared_ptr<Engine> engine, std::shared_ptr<BillStrategy> billStrategy) : GameComponent(engine)
{
    this->billStrategy = billStrategy;
}

double Billing::getAmount() {
    return amount;
}

void Billing::setAmount(double amount){
    this->amount = amount;
}

json Billing::pay(double amount)
{
    return billStrategy->pay(amount);
}

void Billing::sendEvent() {}

void Billing::receiveEvent(std::string event)
{
    if (event == "Pay Bill") {
        pay(getAmount());
    }
}
