//
// Created by Pedro Vanzella on 3/21/16.
//
#include "Dispatcher.h"
#include "Building.h"
#include <memory>

Dispatcher::Dispatcher(std::shared_ptr<Building> building)
{
    _building = building;
}
