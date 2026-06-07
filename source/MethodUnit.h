#ifndef METHODUNIT_H
#define METHODUNIT_H

#include "Unit.h"

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
    );

    void add(const std::shared_ptr<Unit>& unit, Flags flags = 0) override;

    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};

#endif 