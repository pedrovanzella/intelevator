//
// Created by Pedro Vanzella on 3/18/16.
//

#include "DummyDispatcher.h"

DummyDispatcher::DummyDispatcher(Building* building)
{
    _building = std::make_shared<Building>(*building);
}

std::shared_ptr<Elevator> DummyDispatcher::pick_next_elevator()
{
    return nullptr;
}
