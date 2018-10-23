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

#include "quantity.h"
#include <utility>

namespace {

  using namespace units;

  using meters = quantity;

  // constructors

  static_assert(meters().count() == 0);
  constexpr meters kilometer{1000};
  static_assert(kilometer.count() == 1000);
  static_assert(meters(kilometer).count() == kilometer.count());

  // assignment operator

  static_assert([](){ meters l1(1), l2(2); return l2 = l1; }().count() == 1);

  // static member functions

  static_assert(meters::zero().count() == 0);
  static_assert(meters::min().count() == std::numeric_limits<int>::lowest());
  static_assert(meters::max().count() == std::numeric_limits<int>::max());

  // unary member operators

  static_assert((+kilometer).count() == 1000);
  static_assert((-kilometer).count() == -1000);
  static_assert((+(-kilometer)).count() == -1000);
  static_assert((-(-kilometer)).count() == 1000);

  // binary member operators

  static_assert([](auto v) { auto vv = v++; return std::make_pair(v, vv); }(kilometer) == std::make_pair(meters(1001), meters(1000)));
  static_assert([](auto v) { auto vv = ++v; return std::make_pair(v, vv); }(kilometer) == std::make_pair(meters(1001), meters(1001)));
  static_assert([](auto v) { auto vv = v--; return std::make_pair(v, vv); }(kilometer) == std::make_pair(meters(999), meters(1000)));
  static_assert([](auto v) { auto vv = --v; return std::make_pair(v, vv); }(kilometer) == std::make_pair(meters(999), meters(999)));

  // compound assignment

  static_assert((meters(1) += meters(1)).count() == 2);
  static_assert((meters(2) -= meters(1)).count() == 1);
  static_assert((meters(1) *= 2).count() == 2);
  static_assert((meters(2) /= 2).count() == 1);
  static_assert((meters(7) %= 2).count() == 1);
  static_assert((meters(7) %= meters(2)).count() == 1);

  // non-member arithmetic operators

  static_assert((meters(1) + kilometer).count() == 1001);
  static_assert((kilometer - meters(1)).count() == 999);
  static_assert((meters(2) * 2).count() == 4);
  static_assert((3 * meters(3)).count() == 9);
  static_assert((meters(4) / 2).count() == 2);
  static_assert(meters(4) / meters(2) == 2);
  static_assert((meters(7) % 2).count() == 1);
  static_assert((meters(7) % meters(2)).count() == 1);

  // comparators

  static_assert(meters(2) + meters(1) == meters(3));
  static_assert(!(meters(2) + meters(2) == meters(3)));
  static_assert(meters(2) + meters(2) != meters(3));
  static_assert(!(meters(2) + meters(2) != meters(4)));
  static_assert(meters(2) > meters(1));
  static_assert(!(meters(1) > meters(1)));
  static_assert(meters(1) < meters(2));
  static_assert(!(meters(2) < meters(2)));
  static_assert(meters(2) >= meters(1));
  static_assert(meters(2) >= meters(2));
  static_assert(!(meters(2) >= meters(3)));
  static_assert(meters(1) <= meters(2));
  static_assert(meters(2) <= meters(2));
  static_assert(!(meters(3) <= meters(2)));

}  // namespace
