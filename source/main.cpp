#include "ClassUnit.h"
#include "MethodUnit.h"
#include "Modifiers.h"
#include "PrintOperatorUnit.h"

#include <iostream>
#include <memory>
#include <string>

std::string generateProgram() {
    ClassUnit myClass("MyClass");

    myClass.add(
        std::make_shared<MethodUnit>("testFunc1", "void", 0),
        AccessModifier::PUBLIC
    );

    myClass.add(
        std::make_shared<MethodUnit>(
            "testFunc2",
            "void",
            MethodModifier::STATIC
        ),
        AccessModifier::PRIVATE
    );

    myClass.add(
        std::make_shared<MethodUnit>(
            "testFunc3",
            "void",
            MethodModifier::VIRTUAL | MethodModifier::CONST
        ),
        AccessModifier::PUBLIC
    );

    auto method = std::make_shared<MethodUnit>(
        "testFunc4",
        "void",
        MethodModifier::STATIC
    );

    method->add(std::make_shared<PrintOperatorUnit>("Hello, world!\\n"));

    myClass.add(method, AccessModifier::PROTECTED);

    return myClass.compile();
}

int main() {
    std::cout << generateProgram() << std::endl;

    return 0;
}