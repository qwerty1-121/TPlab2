#ifndef MODIFIERS_H
#define MODIFIERS_H

namespace AccessModifier {
    enum Value {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };
}

namespace MethodModifier {
    enum Value {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2
    };
}

#endif 