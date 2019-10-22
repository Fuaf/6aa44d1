#pragma once

#include <Arduino.h>
#include <Settings/NamespaceSettings.hpp>

BEGIN_CS_NAMESPACE
#ifdef min
#undef min
#endif
template <class T, class U>
constexpr auto min(const T &a, const U &b) -> decltype(b < a ? b : a) {
    return b < a ? b : a;
}

#ifdef max
#undef max
#endif
template <class T, class U>
constexpr auto max(const T &a, const U &b) -> decltype(b < a ? b : a) {
    return a < b ? b : a;
}
END_CS_NAMESPACE