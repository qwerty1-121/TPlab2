#include "CSharpMethodUnit.h"

CSharpMethodUnit::CSharpMethodUnit(
    const std::string& name,
    const std::string& returnType,
    Flags flags
)
    : m_name(name),
      m_returnType(returnType),
      m_flags(flags) {
}

void CSharpMethodUnit::add(const std::shared_ptr<Unit>& unit, Flags) {
    m_body.push_back(unit);
}

std::string CSharpMethodUnit::compile(unsigned int level) const {
    std::string result = generateShift(level);

    if (m_flags & MethodModifier::STATIC) {
        result += "static ";
    } else if (m_flags & MethodModifier::VIRTUAL) {
        result += "virtual ";
    }

    result += m_returnType + " ";
    result += m_name + "()";

    result += " {\n";

    for (const auto& bodyUnit : m_body) {
        result += bodyUnit->compile(level + 1);
    }

    result += generateShift(level) + "}\n";

    return result;
}