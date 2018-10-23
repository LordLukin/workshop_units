// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <limits>
#include <type_traits>

// Requires

template<bool B>
using Requires = std::enable_if_t<B, bool>;

namespace units {

  // is_quantity

  template<typename Rep>
  class quantity;

  template<typename T>
  struct is_quantity : std::false_type {
  };

  template<typename Rep>
  struct is_quantity<quantity<Rep>> : std::true_type {
  };

  // treat_as_floating_point

  template<class Rep>
  struct treat_as_floating_point : std::is_floating_point<Rep> {
  };

  template<class Rep>
  inline constexpr bool treat_as_floating_point_v = treat_as_floating_point<Rep>::value;

  // quantity_values

  template<typename Rep>
  struct quantity_values {
    static constexpr Rep zero() { return Rep(0); }
    static constexpr Rep max() { return std::numeric_limits<Rep>::max(); }
    static constexpr Rep min() { return std::numeric_limits<Rep>::lowest(); }
  };

  // quantity

  template<typename Rep>
  class quantity {
    Rep value_;

  public:
    using rep = Rep;
    static_assert(!is_quantity<Rep>::value, "rep cannot be a quantity");

    quantity() = default;
    quantity(const quantity&) = default;

    template<class Rep2, Requires<std::is_convertible_v<Rep2, rep> &&
                                  (treat_as_floating_point_v<rep> || !treat_as_floating_point_v<Rep2>)> = true>
    constexpr explicit quantity(const Rep2& r) : value_{static_cast<rep>(r)}
    {
    }

    template<class Rep2, Requires<std::is_convertible_v<Rep2, rep> &&
                                  (treat_as_floating_point_v<rep> || !treat_as_floating_point_v<Rep2>)> = true>
    constexpr quantity(const quantity<Rep2>& q) : value_{static_cast<rep>(q.count())}
    {
    }

    quantity& operator=(const quantity& other) = default;

    constexpr rep count() const noexcept { return value_; }

    static constexpr quantity zero() { return quantity(quantity_values<Rep>::zero()); }
    static constexpr quantity min() { return quantity(quantity_values<Rep>::min()); }
    static constexpr quantity max() { return quantity(quantity_values<Rep>::max()); }

    constexpr quantity operator+() const { return quantity(*this); }
    constexpr quantity operator-() const { return quantity(-count()); }

    constexpr quantity& operator++()
    {
      ++value_;
      return *this;
    }
    constexpr quantity operator++(int) { return quantity(value_++); }

    constexpr quantity& operator--()
    {
      --value_;
      return *this;
    }
    constexpr quantity operator--(int) { return quantity(value_--); }

    constexpr quantity& operator+=(const quantity& q)
    {
      value_ += q.count();
      return *this;
    }

    constexpr quantity& operator-=(const quantity& q)
    {
      value_ -= q.count();
      return *this;
    }

    constexpr quantity& operator*=(const rep& rhs)
    {
      value_ *= rhs;
      return *this;
    }

    constexpr quantity& operator/=(const rep& rhs)
    {
      value_ /= rhs;
      return *this;
    }

    constexpr quantity& operator%=(const rep& rhs)
    {
      value_ %= rhs;
      return *this;
    }

    constexpr quantity& operator%=(const quantity& q)
    {
      value_ %= q.count();
      return *this;
    }
  };

  template<typename Rep1, typename Rep2>
  constexpr quantity<std::common_type_t<Rep1, Rep2>> operator+(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    using ret = quantity<std::common_type_t<Rep1, Rep2>>;
    return ret(lhs.count() + rhs.count());
  }

  template<typename Rep1, typename Rep2>
  constexpr quantity<std::common_type_t<Rep1, Rep2>> operator-(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    using ret = quantity<std::common_type_t<Rep1, Rep2>>;
    return ret(lhs.count() - rhs.count());
  }

  template<typename Rep1, typename Rep2>
  constexpr quantity<std::common_type_t<Rep1, Rep2>> operator*(const quantity<Rep1>& q, const Rep2& v)
  {
    using ret = quantity<std::common_type_t<Rep1, Rep2>>;
    return ret(q.count() * v);
  }

  template<typename Rep1, typename Rep2>
  constexpr quantity<std::common_type_t<Rep1, Rep2>> operator*(const Rep1& v, const quantity<Rep2>& q)
  {
    return q * v;
  }

  template<typename Rep1, typename Rep2>
  constexpr quantity<std::common_type_t<Rep1, Rep2>> operator/(const quantity<Rep1>& q, const Rep2& v)
  {
    using ret = quantity<std::common_type_t<Rep1, Rep2>>;
    return ret(q.count() / v);
  }

  template<typename Rep1, typename Rep2>
  constexpr std::common_type_t<Rep1, Rep2> operator/(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    return lhs.count() / rhs.count();
  }

  template<typename Rep1, typename Rep2>
  constexpr quantity<std::common_type_t<Rep1, Rep2>> operator%(const quantity<Rep1>& q, const Rep2& v)
  {
    using ret = quantity<std::common_type_t<Rep1, Rep2>>;
    return ret(q.count() % v);
  }

  template<typename Rep1, typename Rep2>
  constexpr quantity<std::common_type_t<Rep1, Rep2>> operator%(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    using ret = quantity<std::common_type_t<Rep1, Rep2>>;
    return ret(lhs.count() % rhs.count());
  }

  template<typename Rep1, typename Rep2>
  constexpr bool operator==(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    return lhs.count() == rhs.count();
  }

  template<typename Rep1, typename Rep2>
  constexpr bool operator!=(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename Rep1, typename Rep2>
  constexpr bool operator<(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    return lhs.count() < rhs.count();
  }

  template<typename Rep1, typename Rep2>
  constexpr bool operator<=(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    return !(rhs < lhs);
  }

  template<typename Rep1, typename Rep2>
  constexpr bool operator>(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    return rhs < lhs;
  }

  template<typename Rep1, typename Rep2>
  constexpr bool operator>=(const quantity<Rep1>& lhs, const quantity<Rep2>& rhs)
  {
    return !(lhs < rhs);
  }

}  // namespace units
