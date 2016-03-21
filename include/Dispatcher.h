//
// Created by Pedro Vanzella on 3/18/16.
//

#pragma once

#include <memory>

class Building;
class Elevator;

/* This is an interface for all dispatchers */

class Dispatcher : public std::enable_shared_from_this<Dispatcher> {
public:
    Dispatcher(Building building);

    virtual ~Dispatcher() {}

    virtual std::shared_ptr<Elevator> pick_next_elevator() = 0;

protected:
    std::shared_ptr<Building> _building;
};