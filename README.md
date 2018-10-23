# Physical Units Library Workshop

## Overview

The purpose of that workshop is to create a simple physical units library for C++.

It will support:
- several physical dimensions,
- automatic conversions between different units,
- compile time expressions verification,
- literals to easily work with different dimensions and their various units.

Above features will be provided without any runtime performance overhead.

Example:

```cpp
static_assert(1000 / 1_s == 1_kHz);
static_assert(1_h == 3600_s);
static_assert(1_km + 1_m == 1001_m);
static_assert(10_km / 5_km == 2);
static_assert(10_km / 2 == 5_km);
static_assert(1_km / 1_s == 1000_mps);
static_assert(2_kmph * 2_h == 4_km);
static_assert(2_km / 2_kmph == 1_h);
```


## How to proceed?

1. While solving workshop tasks please do not modify the code in the `ref` directory to not hit
   merge conflicts when moving to the next task.
2. The initial state of the task is always provided in the `ref/include` directory. If you want to
   use the reference implementation for the next tasks (instead using the one you wrote) than
   copy headers from `ref/include` to `include` before starting the assignment.
3. Reference unit tests and examples are always in `ref/src` directory. The target of each task is
   to make that code compile and pass without any issues. 
4. If you want to add additional unit tests than please do so in `src/tests.cpp` file.


## Task

```cpp
template<typename Rep> using meters = quantity<Rep>;
template<typename Rep> using kilometers = quantity<Rep, std::kilo>;
template<typename Rep> using millimeters = quantity<Rep, std::milli>;

constexpr meters<int> d1{1};
constexpr kilometers<int> d2{1};
// constexpr meters<int> d3 = d1 + d2; // should not compile
constexpr meters<int> d3(d1.count() + d2.count() * 1000);
```

1. Convert `quantity` to the following class template
    ```cpp
    template<typename Rep, class Ratio = std::ratio<1>>
    class quantity;
    ```
2. Update the `quantity` class to provide `ratio` member type in its interface.
3. Make sure that `Ratio` argument of `quantity` class template is a specialization of `std::ratio`.
4. Make sure that value provided to `Ratio` is positive (non-negative).
5. All binary functions using `quantity` for both arguments should use the same `Ratio` for both of them.
