#ifndef CODEFACTORY_H
#define CODEFACTORY_H

#include "Unit.h"

#include <memory>
#include <string>

class CodeFactory {
public:
    virtual ~CodeFactory() = default;

    virtual std::shared_ptr<Unit> createClass(
        const std::string& name
    ) const = 0;

    virtual std::shared_ptr<Unit> createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
    ) const = 0;

    virtual std::shared_ptr<Unit> createPrintOperator(
        const std::string& text
    ) const = 0;
};

#endif // CODEFACTORY_H