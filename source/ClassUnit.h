#ifndef CLASSUNIT_H
#define CLASSUNIT_H

#include "Modifiers.h"
#include "Unit.h"

#include <memory>
#include <string>
#include <vector>

class ClassUnit : public Unit {
public:
    static const std::vector<std::string> ACCESS_MODIFIERS;

public:
    explicit ClassUnit(const std::string& name);

    void add(const std::shared_ptr<Unit>& unit, Flags flags) override;

    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name;

    using Fields = std::vector<std::shared_ptr<Unit>>;
    std::vector<Fields> m_fields;
};

#endif 