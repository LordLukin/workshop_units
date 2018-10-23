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

namespace units {

  class quantity {
    int value_;

  public:
    quantity() = default;
    constexpr quantity(const quantity&) = default;
    constexpr explicit quantity(int r) : value_{r} {}

    quantity& operator=(const quantity& other) = default;

    constexpr int count() const noexcept { return value_; }

    static constexpr quantity zero() { return quantity(0); }
    static constexpr quantity min() { return quantity(std::numeric_limits<int>::lowest()); }
    static constexpr quantity max() { return quantity(std::numeric_limits<int>::max()); }

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

    constexpr quantity& operator+=(quantity q)
    {
      value_ += q.count();
      return *this;
    }

    constexpr quantity& operator-=(quantity q)
    {
      value_ -= q.count();
      return *this;
    }

    constexpr quantity& operator*=(int rhs)
    {
      value_ *= rhs;
      return *this;
    }

    constexpr quantity& operator/=(int rhs)
    {
      value_ /= rhs;
      return *this;
    }

    constexpr quantity& operator%=(int rhs)
    {
      value_ %= rhs;
      return *this;
    }

    constexpr quantity& operator%=(quantity q)
    {
      value_ %= q.count();
      return *this;
    }
  };

  constexpr quantity operator+(quantity lhs, quantity rhs) { return quantity(lhs.count() + rhs.count()); }
  constexpr quantity operator-(quantity lhs, quantity rhs) { return quantity(lhs.count() - rhs.count()); }
  constexpr quantity operator*(quantity q, int v) { return quantity(q.count() * v); }
  constexpr quantity operator*(int v, quantity q) { return q * v; }
  constexpr quantity operator/(quantity q, int v) { return quantity(q.count() / v); }
  constexpr int operator/(quantity lhs, quantity rhs) { return lhs.count() / rhs.count(); }
  constexpr quantity operator%(quantity q, int v) { return quantity(q.count() % v); }
  constexpr quantity operator%(quantity lhs, quantity rhs) { return quantity(lhs.count() % rhs.count()); }

  constexpr bool operator==(quantity lhs, quantity rhs) { return lhs.count() == rhs.count(); }
  constexpr bool operator!=(quantity lhs, quantity rhs) { return !(lhs == rhs); }
  constexpr bool operator<(quantity lhs, quantity rhs) { return lhs.count() < rhs.count(); }
  constexpr bool operator<=(quantity lhs, quantity rhs) { return !(rhs < lhs); }
  constexpr bool operator>(quantity lhs, quantity rhs) { return rhs < lhs; }
  constexpr bool operator>=(quantity lhs, quantity rhs) { return !(lhs < rhs); }

}  // namespace units
