#pragma once

#include <stdexcept>

template<typename Exception>
inline void throwIf(bool shouldThrow, const Exception& e) {
    if (shouldThrow)
        throw e;
}

template<typename Value, typename Exception>
inline void throwIfNull(const Value* value, const Exception& e) {
    throwIf(value == nullptr, e);
}