#ifndef STRINGVIEWHASH_H
#define STRINGVIEWHASH_H
#include <QtTypes>
#include <string_view>

namespace mini {
/**
 * @brief Wrapper enabling efficient string lookup for std maps.
 * Prevents temporary string allocation and hashes the given string
 * @note In rare cases the hash function can introduce identical hashes for two
 * different string views.
 */
struct StringViewHash {
    using isTransparent = void;
    quint64 operator()(std::string_view sv) const noexcept
    {
        return std::hash<std::string_view> {}(sv);
    }
};
} // namespace mini
#endif // STRINGVIEWHASH_H
