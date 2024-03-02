#include <iostream>

#include "vec.h"

int main() {
  nsl::vec<int> v(4);

  v.push(10);
  v.push(20);
  v.push(30);
  v.push(40);

  for (auto& i : v) {
    std::cout << i << "\n";
  }

  v.pop();
  v.pop();

  for (auto& i : v) {
    std::cout << i << "\n";
  }

  nsl::vec<char> str(8);
  str = "testing";

  std::cout << str.ptr() << "\n";

  str = "testing reallocation";
  std::cout << str.ptr() << "\n";

  nsl::vec<double> dbl_vec;

  nsl::str string;
  string = "the string container is just a wrapper on vec<char>";

  std::cout << string << "\n";

  string = "realloc";
  std::cout << string << "\n";

  struct Data {
    nsl::str name;
    int id;
    double balance;
  };

  nsl::vec<Data> data_vec(4);

  data_vec.push(Data{.name = "kai", .id = 1, .balance = 13.23});

  nsl::str str_value = "testing string iterators";

  std::cout << str_value << "\n";

  for (auto& s : str_value) {
    std::cout << s << "\n";
  }
}
