#include "CppCodeFactory.h"

#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

std::shared_ptr<Unit> CppCodeFactory::createClass(
    const std::string& name
) const {
    return std::make_shared<ClassUnit>(name);
}

std::shared_ptr<Unit> CppCodeFactory::createMethod(
    const std::string& name,
    const std::string& returnType,
    Unit::Flags flags
) const {
    return std::make_shared<MethodUnit>(name, returnType, flags);
}

std::shared_ptr<Unit> CppCodeFactory::createPrintOperator(
    const std::string& text
) const {
    return std::make_shared<PrintOperatorUnit>(text);
}