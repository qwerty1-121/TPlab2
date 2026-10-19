#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


class Unit {
public:
    using Flags = unsigned int;

public:
    virtual ~Unit() = default;

    virtual void add(const std::shared_ptr<Unit>&, Flags) {
        throw std::runtime_error("Not supported");
    }

    virtual std::string compile(unsigned int level = 0) const = 0;

protected:
    virtual std::string generateShift(unsigned int level) const {
        static const auto DEFAULT_SHIFT = "    ";
        std::string result;

        for (unsigned int i = 0; i < level; ++i) {
            result += DEFAULT_SHIFT;
        }

        return result;
    }
};


class ClassUnit : public Unit {
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };

    static const std::vector<std::string> ACCESS_MODIFIERS;

    using Fields = std::vector<std::shared_ptr<Unit>>;

public:
    explicit ClassUnit(const std::string& name)
        : m_name(name)
    {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }

    void add(const std::shared_ptr<Unit>& unit, Flags flags) override {
        int accessModifier = PRIVATE;

        if (flags < ACCESS_MODIFIERS.size()) {
            accessModifier = flags;
        }

        m_fields[accessModifier].push_back(unit);
    }

protected:
    const std::string& getName() const {
        return m_name;
    }

    const Fields& getFields(unsigned int accessGroup) const {
        if (ACCESS_MODIFIERS.size() <= accessGroup) {
            throw std::out_of_range("Invalid access group index");
        }

        return m_fields[accessGroup];
    }

private:
    std::string m_name;
    std::vector<Fields> m_fields;
};


const std::vector<std::string> ClassUnit::ACCESS_MODIFIERS = {
    "public",
    "protected",
    "private"
};


class MethodUnit : public Unit {
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2
    };

public:
    MethodUnit(const std::string& name,
               const std::string& returnType,
               Flags flags)
        : m_name(name),
        m_returnType(returnType),
        m_flags(flags)
    {
    }

    void add(const std::shared_ptr<Unit>& unit,
             Flags /* flags */ = 0) override
    {
        m_body.push_back(unit);
    }

protected:
    const std::string& getName() const {
        return m_name;
    }

    const std::string& getReturnType() const {
        return m_returnType;
    }

    Flags getFlags() const {
        return m_flags;
    }

    const std::vector<std::shared_ptr<Unit>>& getBody() const {
        return m_body;
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
        : m_text(text)
    {
    }

protected:
    const std::string& getText() const {
        return m_text;
    }

private:
    std::string m_text;
};


class LangFactory {
public:
    virtual ~LangFactory() = default;

    virtual std::shared_ptr<ClassUnit> createClass(
        const std::string& name
        ) = 0;

    virtual std::shared_ptr<MethodUnit> createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
        ) = 0;

    virtual std::shared_ptr<PrintOperatorUnit> createPrintOperator(
        const std::string& text
        ) = 0;
};


class CppClass : public ClassUnit {
public:
    explicit CppClass(const std::string& name)
        : ClassUnit(name)
    {
    }

    std::string compile(unsigned int level = 0) const override {
        std::string result =
            generateShift(level) + "class " + getName() + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (getFields(i).empty()) {
                continue;
            }

            result += ACCESS_MODIFIERS[i] + ":\n";

            for (const auto& f : getFields(i)) {
                result += f->compile(level + 1);
            }

            result += "\n";
        }

        result += generateShift(level) + "};\n";

        return result;
    }
};


class CppMethod : public MethodUnit {
public:
    CppMethod(const std::string& name,
              const std::string& returnType,
              Flags flags)
        : MethodUnit(name, returnType, flags)
    {
    }

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level);

        if (getFlags() & STATIC) {
            result += "static ";
        } else if (getFlags() & VIRTUAL) {
            result += "virtual ";
        }

        result += getReturnType() + " ";
        result += getName() + "()";

        if (getFlags() & CONST) {
            result += " const";
        }

        result += " {\n";

        for (const auto& b : getBody()) {
            result += b->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }
};


class CppPrintOperator : public PrintOperatorUnit {
public:
    explicit CppPrintOperator(const std::string& text)
        : PrintOperatorUnit(text)
    {
    }

    std::string compile(unsigned int level = 0) const override {
        return generateShift(level)
        + "printf( \"" + getText() + "\" );\n";
    }
};


class CppFactory : public LangFactory {
public:
    std::shared_ptr<ClassUnit> createClass(
        const std::string& name
        ) override {
        return std::make_shared<CppClass>(name);
    }

    std::shared_ptr<MethodUnit> createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
        ) override {
        return std::make_shared<CppMethod>(
            name,
            returnType,
            flags
            );
    }

    std::shared_ptr<PrintOperatorUnit> createPrintOperator(
        const std::string& text
        ) override {
        return std::make_shared<CppPrintOperator>(text);
    }
};

class CSharpClass : public ClassUnit {
public:
    explicit CSharpClass(const std::string& name)
        : ClassUnit(name)
    {
    }

    std::string compile(unsigned int level = 0) const override {
        std::string result =
            generateShift(level) + "class " + getName() + "\n";

        result += generateShift(level) + "{\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            for (const auto& field : getFields(i)) {
                std::string fieldCode = field->compile(level + 1);

                const std::string shift = generateShift(level + 1);

                fieldCode.insert(
                    shift.size(),
                    ACCESS_MODIFIERS[i] + " "
                    );

                result += fieldCode;
                result += "\n";
            }
        }

        result += generateShift(level) + "}\n";

        return result;
    }
};


class CSharpMethod : public MethodUnit {
public:
    CSharpMethod(const std::string& name,
                 const std::string& returnType,
                 Flags flags)
        : MethodUnit(name, returnType, flags)
    {
    }

    std::string compile(unsigned int level = 0) const override {
        std::string result = generateShift(level);

        if (getFlags() & STATIC) {
            result += "static ";
        } else if (getFlags() & VIRTUAL) {
            result += "virtual ";
        }

        result += getReturnType() + " ";
        result += getName() + "()";

        result += "\n";
        result += generateShift(level) + "{\n";

        for (const auto& bodyElement : getBody()) {
            result += bodyElement->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }
};


class CSharpPrintOperator : public PrintOperatorUnit {
public:
    explicit CSharpPrintOperator(const std::string& text)
        : PrintOperatorUnit(text)
    {
    }

    std::string compile(unsigned int level = 0) const override {
        return generateShift(level)
        + "System.Console.WriteLine( \"" + getText() + "\" );\n";
    }
};


class CSharpFactory : public LangFactory {
public:
    std::shared_ptr<ClassUnit> createClass(
        const std::string& name
        ) override {
        return std::make_shared<CSharpClass>(name);
    }

    std::shared_ptr<MethodUnit> createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
        ) override {
        return std::make_shared<CSharpMethod>(
            name,
            returnType,
            flags
            );
    }

    std::shared_ptr<PrintOperatorUnit> createPrintOperator(
        const std::string& text
        ) override {
        return std::make_shared<CSharpPrintOperator>(text);
    }
};

std::string generateProgram(
    const std::shared_ptr<LangFactory>& factory
    ) {
    auto myClass = factory->createClass("MyClass");

    myClass->add(
        factory->createMethod(
            "testFunc1",
            "void",
            0
            ),
        ClassUnit::PUBLIC
        );

    myClass->add(
        factory->createMethod(
            "testFunc2",
            "void",
            MethodUnit::STATIC
            ),
        ClassUnit::PRIVATE
        );

    myClass->add(
        factory->createMethod(
            "testFunc3",
            "void",
            MethodUnit::VIRTUAL | MethodUnit::CONST
            ),
        ClassUnit::PUBLIC
        );

    auto method = factory->createMethod(
        "testFunc4",
        "void",
        MethodUnit::STATIC
        );

    method->add(
        factory->createPrintOperator(
            R"(Hello, world!\n)"
            )
        );

    myClass->add(
        method,
        ClassUnit::PROTECTED
        );

    return myClass->compile();
}


int main() {
    std::cout
        << generateProgram(std::make_shared<CSharpFactory>())
        << std::endl;

    return 0;
}
