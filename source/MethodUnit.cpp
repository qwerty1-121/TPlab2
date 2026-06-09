#include "MethodUnit.h"

MethodUnit::MethodUnit(
    const std::string& name,
    const std::string& returnType,
    Flags flags
)
    : m_name(name),
      m_returnType(returnType),
      m_flags(flags) {
}

void MethodUnit::add(const std::shared_ptr<Unit>& unit, Flags) {
    m_body.push_back(unit);
}

std::string MethodUnit::compile(unsigned int level) const {
    std::string result = generateShift(level);

    if (m_flags & MethodModifier::STATIC) {
        result += "static ";
    } else if (m_flags & MethodModifier::VIRTUAL) {
        result += "virtual ";
    }

    result += m_returnType + " ";
    result += m_name + "()";

    if (m_flags & MethodModifier::CONST) {
        result += " const";
    }

    result += " {\n";

    for (const auto& bodyUnit : m_body) {
        result += bodyUnit->compile(level + 1);
    }

    result += generateShift(level) + "}\n";

    return result;
}