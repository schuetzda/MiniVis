#ifndef TYPEIDGENERATOR_H
#define TYPEIDGENERATOR_H

#include <QtGlobal>
namespace mini {
class TypeIDGenerator {
    static quint32 identifier() noexcept
    {
        static quint32 value = 0;
        return value++;
    }

public:
    template <typename>
    static quint32 type() noexcept
    {
        static const quint32 value = identifier();
        return value;
    }
};
} // namespace mini
#endif
