#ifndef CSHARPMETHODUNIT_H
#define CSHARPMETHODUNIT_H

#include "Modifiers.h"
#include "Unit.h"

#include <memory>
#include <string>
#include <vector>

class CSharpMethodUnit : public Unit {
public:
    CSharpMethodUnit(
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

#endif // CSHARPMETHODUNIT_H