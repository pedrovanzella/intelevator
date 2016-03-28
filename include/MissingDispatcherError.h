//
// Created by Pedro Vanzella on 3/28/16.
//

#ifndef INTELEVATOR_MISSINGDISPATCHERERROR_H
#define INTELEVATOR_MISSINGDISPATCHERERROR_H

#include <stdexcept>

class MissingDispatcherError : public std::runtime_error
{
public:
    explicit MissingDispatcherError(const std::string& what) : std::runtime_error("Dispatcher not found: " + what) {}

    virtual ~MissingDispatcherError() {}
};

#endif //INTELEVATOR_MISSINGDISPATCHERERROR_H
