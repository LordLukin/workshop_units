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

  template<typename Rep>
  using meters = quantity<Rep>;

  // class invariants

//  constexpr quantity<meters<int>> error(meters<int>(0));  // should trigger a static_assert

  // member types

  static_assert(std::is_same_v<meters<int>::rep, int>);
  static_assert(std::is_same_v<meters<float>::rep, float>);

  // constructors

  static_assert(meters<int>().count() == 0);
  constexpr meters<int> kilometer{1000};
  static_assert(kilometer.count() == 1000);
  static_assert(meters<int>(kilometer).count() == kilometer.count());

  static_assert(meters<int>(1).count() == 1);
//  static_assert(meters<int>(1.0).count() == 1);   // should not compile
  static_assert(meters<float>(1.0).count() == 1.0);
  static_assert(meters<float>(1).count() == 1.0);
  static_assert(meters<float>(3.14f).count() == 3.14f);

  static_assert(meters<int>(kilometer).count() == 1000);
//  static_assert(meters<int>(meters<float>(1000.0)).count() == 1000);   // should not compile
  static_assert(meters<float>(meters<float>(1000.0)).count() == 1000.0);
  static_assert(meters<float>(kilometer).count() == 1000.0);

  // assignment operator

  static_assert([](){ meters<int> l1(1), l2(2); return l2 = l1; }().count() == 1);

  // static member functions

  static_assert(meters<int>::zero().count() == 0);
  static_assert(meters<int>::min().count() == std::numeric_limits<int>::lowest());
  static_assert(meters<int>::max().count() == std::numeric_limits<int>::max());
  static_assert(meters<float>::zero().count() == 0.0);
  static_assert(meters<float>::min().count() == std::numeric_limits<float>::lowest());
  static_assert(meters<float>::max().count() == std::numeric_limits<float>::max());

  // unary member operators

  static_assert((+kilometer).count() == 1000);
  static_assert((-kilometer).count() == -1000);
  static_assert((+(-kilometer)).count() == -1000);
  static_assert((-(-kilometer)).count() == 1000);

  // binary member operators

  static_assert([](auto v) { auto vv = v++; return std::make_pair(v, vv); }(kilometer) == std::make_pair(meters<int>(1001), meters<int>(1000)));
  static_assert([](auto v) { auto vv = ++v; return std::make_pair(v, vv); }(kilometer) == std::make_pair(meters<int>(1001), meters<int>(1001)));
  static_assert([](auto v) { auto vv = v--; return std::make_pair(v, vv); }(kilometer) == std::make_pair(meters<int>(999), meters<int>(1000)));
  static_assert([](auto v) { auto vv = --v; return std::make_pair(v, vv); }(kilometer) == std::make_pair(meters<int>(999), meters<int>(999)));

  // compound assignment

  static_assert((meters<int>(1) += meters<int>(1)).count() == 2);
  static_assert((meters<int>(2) -= meters<int>(1)).count() == 1);
  static_assert((meters<int>(1) *= 2).count() == 2);
  static_assert((meters<int>(2) /= 2).count() == 1);
  static_assert((meters<int>(7) %= 2).count() == 1);
  static_assert((meters<int>(7) %= meters<int>(2)).count() == 1);

  // non-member arithmetic operators

  static_assert(std::is_same_v<decltype(meters<int>() + meters<float>()), meters<float>>);
  static_assert(std::is_same_v<decltype(meters<float>() - meters<int>()), meters<float>>);
  static_assert(std::is_same_v<decltype(meters<int>() * 1.0f), meters<float>>);
  static_assert(std::is_same_v<decltype(1.0f * meters<int>()), meters<float>>);
  static_assert(std::is_same_v<decltype(meters<int>() / 1.0f), meters<float>>);
  static_assert(std::is_same_v<decltype(meters<int>() / meters<float>()), float>);
  static_assert(std::is_same_v<decltype(meters<int>() % short(1)), meters<int>>);
  static_assert(std::is_same_v<decltype(meters<int>() % meters<short>(1)), meters<int>>);

  static_assert((meters<int>(1) + kilometer).count() == 1001);
  static_assert((kilometer - meters<int>(1)).count() == 999);
  static_assert((meters<int>(2) * 2).count() == 4);
  static_assert((3 * meters<int>(3)).count() == 9);
  static_assert((meters<int>(4) / 2).count() == 2);
  static_assert(meters<int>(4) / meters<int>(2) == 2);
  static_assert((meters<int>(7) % 2).count() == 1);
  static_assert((meters<int>(7) % meters<int>(2)).count() == 1);

  // comparators

  static_assert(meters<int>(2) + meters<int>(1) == meters<int>(3));
  static_assert(!(meters<int>(2) + meters<int>(2) == meters<int>(3)));
  static_assert(meters<int>(2) + meters<int>(2) != meters<int>(3));
  static_assert(!(meters<int>(2) + meters<int>(2) != meters<int>(4)));
  static_assert(meters<int>(2) > meters<int>(1));
  static_assert(!(meters<int>(1) > meters<int>(1)));
  static_assert(meters<int>(1) < meters<int>(2));
  static_assert(!(meters<int>(2) < meters<int>(2)));
  static_assert(meters<int>(2) >= meters<int>(1));
  static_assert(meters<int>(2) >= meters<int>(2));
  static_assert(!(meters<int>(2) >= meters<int>(3)));
  static_assert(meters<int>(1) <= meters<int>(2));
  static_assert(meters<int>(2) <= meters<int>(2));
  static_assert(!(meters<int>(3) <= meters<int>(2)));

  static_assert(meters<int>(3) == meters<float>(3.0));
  static_assert(meters<int>(3) != meters<float>(3.14));
  static_assert(meters<int>(2) > meters<float>(1.0));
  static_assert(meters<float>(1.0) < meters<int>(2));
  static_assert(meters<float>(2.0) >= meters<int>(1));
  static_assert(meters<int>(1) <= meters<float>(2.0));

}  // namespace
