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
template<typename Rep>
using meters = quantity<Rep>;

constexpr meters d1(1), d2(2);
constexpr meters d3 = d1 + d2;
static_assert(d3.count() == 3);

constexpr meters<float> d4(3.0);
constexpr meters<float> d5 = d4 + d1;
static_assert(d5.count() == 4.0);
```

1. Convert `quantity` to the following class template
    ```cpp
    template<typename Rep>
    class quantity;
    ```
2. Update the `quantity` class to
    - provide `rep` member type in its interface
    - use `Rep` instead of `int` in its interface and implementation.
3. Make sure that `quantity` type is not used as class template `Rep` argument.
4. Add converting constructor
    ```cpp
    template<class Rep2>
    constexpr quantity(const quantity<Rep2>& q);
    ```
5. Both converting constructors should only participate in the overload resolution if:
    - destination `Rep` is convertible from source `Rep`
    - either destination `Rep` is of floating point type or source `Rep` is not of floating
      point type.
6. The result of binary operations using 2 different `Rep` types should return a new type
   that contains a `Rep` type that is common to the `Rep` of both operands.
7. Please note that `Rep` type can be a large class in some use cases so the `quantity` and
   `rep` function arguments should be passed by a reference rather than a value.
