#ifndef CPPCODEFACTORY_H
#define CPPCODEFACTORY_H

#include "CodeFactory.h"

#include <memory>
#include <string>

class CppCodeFactory : public CodeFactory {
public:
    std::shared_ptr<Unit> createClass(
        const std::string& name
    ) const override;

    std::shared_ptr<Unit> createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
    ) const override;

    std::shared_ptr<Unit> createPrintOperator(
        const std::string& text
    ) const override;
};

#endif // CPPCODEFACTORY_H