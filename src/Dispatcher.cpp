//
// Created by Pedro Vanzella on 3/21/16.
//
#include "Dispatcher.h"
#include "Building.h"

Dispatcher::Dispatcher(Building building)
{
    _building = std::make_shared<Building>(building);
}
