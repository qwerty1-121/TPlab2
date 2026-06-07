#include "ClassUnit.h"
#include "MethodUnit.h"
#include "Unit.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class PrintOperatorUnit : public Unit {
public:
    explicit PrintOperatorUnit(const std::string& text)
        : m_text(text) {
    }

    std::string compile(unsigned int level = 0) const override {
        return generateShift(level) + "printf(\"" + m_text + "\");\n";
    }

private:
    std::string m_text;
};

std::string generateProgram() {
    ClassUnit myClass("MyClass");

    myClass.add(
        std::make_shared<MethodUnit>("testFunc1", "void", 0),
        ClassUnit::PUBLIC
    );

    myClass.add(
        std::make_shared<MethodUnit>("testFunc2", "void", MethodUnit::STATIC),
        ClassUnit::PRIVATE
    );

    myClass.add(
        std::make_shared<MethodUnit>(
            "testFunc3",
            "void",
            MethodUnit::VIRTUAL | MethodUnit::CONST
        ),
        ClassUnit::PUBLIC
    );

    auto method = std::make_shared<MethodUnit>(
        "testFunc4",
        "void",
        MethodUnit::STATIC
    );

    method->add(std::make_shared<PrintOperatorUnit>("Hello, world!\\n"));

    myClass.add(method, ClassUnit::PROTECTED);

    return myClass.compile();
}

int main() {
    std::cout << generateProgram() << std::endl;

    return 0;
}