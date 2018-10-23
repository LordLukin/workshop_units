#pragma once

#include <ratio>
#include <type_traits>

// static_sign

template<std::intmax_t Pn>
struct static_sign;

// static_abs

template<std::intmax_t Pn>
struct static_abs;

// static_gcd

template<std::intmax_t Pn, std::intmax_t Qn>
struct static_gcd;

// common_ratio

template<typename Ratio1, typename Ratio2>
struct common_ratio;

template<typename Ratio1, typename Ratio2>
using common_ratio_t = typename common_ratio<Ratio1, Ratio2>::type;
