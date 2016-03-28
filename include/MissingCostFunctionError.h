//
// Created by Pedro Vanzella on 3/28/16.
//

#ifndef INTELEVATOR_MISSINGCOSTFUNCTIONERROR_H
#define INTELEVATOR_MISSINGCOSTFUNCTIONERROR_H

#include <stdexcept>

class MissingCostFunctionError : public std::runtime_error
{
public:
    explicit MissingCostFunctionError(const std::string& what) : std::runtime_error("Cost Function not found: " + what) {}

    virtual ~MissingCostFunctionError() {}
};

#endif //INTELEVATOR_MISSINGCOSTFUNCTIONERROR_H
