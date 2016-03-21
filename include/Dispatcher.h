//
// Created by Pedro Vanzella on 3/18/16.
//

#pragma once

class Elevator;
#include <memory>

/* This is an interface for all dispatchers */

class Dispatcher {
public:
    Dispatcher();

    virtual std::shared_ptr<Elevator> pick_next_elevator() = 0;
};