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
    constexpr quantity();
    constexpr quantity(const quantity& q);
    constexpr explicit quantity(int r);

    constexpr quantity& operator=(const quantity& other);

    constexpr int count() const noexcept;

    static constexpr quantity zero();
    static constexpr quantity min();
    static constexpr quantity max();

    constexpr quantity operator+() const;
    constexpr quantity operator-() const;

    constexpr quantity& operator++();
    constexpr quantity operator++(int);
    constexpr quantity& operator--();
    constexpr quantity operator--(int);

    constexpr quantity& operator+=(quantity q);
    constexpr quantity& operator-=(quantity q);
    constexpr quantity& operator*=(int rhs);
    constexpr quantity& operator/=(int rhs);
    constexpr quantity& operator%=(int rhs);
    constexpr quantity& operator%=(quantity q);
  };

  constexpr quantity operator+(quantity lhs, quantity rhs);
  constexpr quantity operator-(quantity lhs, quantity rhs);
  constexpr quantity operator*(quantity q, int v);
  constexpr quantity operator*(int v, quantity q);
  constexpr quantity operator/(quantity q, int v);
  constexpr int operator/(quantity lhs, quantity rhs);
  constexpr quantity operator%(quantity q, int v);
  constexpr quantity operator%(quantity lhs, quantity rhs);

  constexpr bool operator==(quantity lhs, quantity rhs);
  constexpr bool operator!=(quantity lhs, quantity rhs);
  constexpr bool operator<(quantity lhs, quantity rhs);
  constexpr bool operator<=(quantity lhs, quantity rhs);
  constexpr bool operator>(quantity lhs, quantity rhs);
  constexpr bool operator>=(quantity lhs, quantity rhs);

}  // namespace units