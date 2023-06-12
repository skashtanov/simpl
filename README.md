# Stack pIMPL (SIMPL)

Simpl is a fast PIMPL idiom realization that uses stack preallocated array instead of heap allocated one.  

## Motivation

The basic approach is using `std::unique_ptr<Impl>` / `Impl*` into a header file.  
But this cause several undesirable problems, such as:

* heap allocation on construction (syscall)
* pointer indirection for each call of `impl`

That's all can be solved by replacing heap allocated memory by stack preallocated one.  

### Warning

This realization ignores ABI compatibility, because with PIMPL, you always have a member with `sizeof(T*)`, with SIMPL you'll have `sizeof(T)` bytes. So after changing of `sizeof(T)`, you'll lose ABI compatibility. If that's not critical, use SIMPL.

## Usage

### Declaring a class

```cpp
class Data
{
public:
  // Data ctor, etc
private:
  struct Impl;
  simpl<Impl, /* random size */, /* random alignment */> impl_;
};
```

### Implementing it

When you're defining an `Impl` into the `.cpp` file, the compiler knows `sizeof(Impl)` and `alignof(Impl)`.  
So if your `/* random size */` and `/* random alignment */` was incorrect, it will say about that via `static_assert`.  
After that you just need to replace `/* random size */` and `/* random alignment */` with the numbers that compiler evaluates for you.

For example your `.hpp` file is:

```cpp
class Data
{
public:
  Data();

  // Data ctor, etc
  void Do();

  // must be user-declared as non-default
  // to prevent compiler-generated destrcutor 
  // for an incomplete type in .hpp
  ~Data(); 
private:
  struct Impl;
  simpl<Impl, 1, 2> impl_;
};
```

And `.cpp` file is:

```cpp
#include "data.hpp"
#include <utility>
#include <iostream>

// sizeof(Impl) == 40
// alignof(Impl) == 8
// NOTE: for x64
struct Data::Impl
{
    std::string name;
    int id; 

    Impl(std::string n, int i) :
      name(std::move(n)),
      id(i) 
    {
    }  

    void Do() {
      std::cout << "Hello from " << name << " with id " << id;
    }
};

Data::Data() :
  impl_{"SIMPL", 1}
{
}

// we prevented compiler-generated destructor in header,
// so we should define in in .cpp
// as a default, in most cases
Data::~Data() = default;

void Data::Do() {
  impl_->Do();
}
```

If `1` and `2` in the `.hpp` were incorrect, the compiler warns you about that with `static_assert`.  
You'll get an error like  

```text
assertion failed (1 != 40): Provided Size doesn't equal to sizeof(T)
assertion failed (2 != 8):  Provided Alignment doesn't equal to alignof(T)
```

After that you just need to replace `1` and `2` with `40` and `8` into `.hpp` file and recomplile. That's all!

**Note**: see an example into `example` folder

## Building

```cmake
cmake -S . -B build
cmake --build build --config Release
cmake --install build --prefix build --config Release
```

## Building an example

```cmake
cmake -S example -B example/build -DCMAKE_BUILD_TYPE=Release
cmake --build example/build --config Release
```
