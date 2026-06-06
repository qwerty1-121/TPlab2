#include "ClassUnit.h"
#include "Unit.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class MethodUnit : public Unit {
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2
    };

public:
    MethodUnit(
        const std::string& name,
        const std::string& returnType,
        Flags flags
    )
        : m_name(name),
          m_returnType(returnType),
          m_flags(flags) {
    }

    void add(const std::shared_ptr<Unit>& unit, Flags = 0) override {
        m_body.push_back(unit);
    }

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level);

        if (m_flags & STATIC) {
            result += "static ";
        } else if (m_flags & VIRTUAL) {
            result += "virtual ";
        }

        result += m_returnType + " ";
        result += m_name + "()";

        if (m_flags & CONST) {
            result += " const";
        }

        result += " {\n";

        for (const auto& bodyUnit : m_body) {
            result += bodyUnit->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }

private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};

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