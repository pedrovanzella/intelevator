//
// Created by Pedro Vanzella on 3/18/16.
//

#pragma once

#include <memory>

class Building;
class Elevator;
#include "ClientArrival.h"

/* This is an interface for all dispatchers */

class Dispatcher : public std::enable_shared_from_this<Dispatcher> {
public:
    Dispatcher(Building building);

    virtual ~Dispatcher() {}

    virtual std::shared_ptr<Elevator> pick_next_elevator(const std::shared_ptr<const ClientArrival>) = 0;

protected:
    std::shared_ptr<Building> _building;
};