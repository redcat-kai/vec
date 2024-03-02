# A Simple, Modern C++ Vector Implementation

This is a simple and safe reimplementation of std::vector and 
std::string, including iterators and operator overloading in under 200 
lines.

Array access is bounds checked by default, and memory leaks have been
checked using valgrind. Do not this vector with std::string (and likely
other stl types) as it will leak memory, instead use nsl::str.

Currently there are 5 includes in ``vec.h``, all of these could be
removed if you got rid of the classes operator overloading

## Usage
```
#include "vec.h"

int main() {
    ksl::vec<int> int_vec;
    int_vec.push(1);

    int_vec[0] 
}
```

see ``example.cxx`` for further examples

