//
// Created by Pedro Vanzella on 3/18/16.
//

#include "DummyDispatcher.h"

std::shared_ptr<const Elevator> DummyDispatcher::pick_next_elevator(const std::shared_ptr<const ClientArrival> ca) const
{
    return nullptr;
}