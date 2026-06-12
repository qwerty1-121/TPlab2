#include "CodeFactory.h"
#include "CppCodeFactory.h"
#include "Modifiers.h"

#include <iostream>
#include <memory>
#include <string>

std::string generateProgram(const CodeFactory& factory) {
    auto myClass = factory.createClass("MyClass");

    myClass->add(
        factory.createMethod("testFunc1", "void", 0),
        AccessModifier::PUBLIC
    );

    myClass->add(
        factory.createMethod(
            "testFunc2",
            "void",
            MethodModifier::STATIC
        ),
        AccessModifier::PRIVATE
    );

    myClass->add(
        factory.createMethod(
            "testFunc3",
            "void",
            MethodModifier::VIRTUAL | MethodModifier::CONST
        ),
        AccessModifier::PUBLIC
    );

    auto method = factory.createMethod(
        "testFunc4",
        "void",
        MethodModifier::STATIC
    );

    method->add(
        factory.createPrintOperator("Hello, world!\\n"),
        0
    );

    myClass->add(method, AccessModifier::PROTECTED);

    return myClass->compile();
}

int main() {
    CppCodeFactory factory;

    std::cout << generateProgram(factory) << std::endl;

    return 0;
}