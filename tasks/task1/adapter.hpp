#include "some_library.hpp"

typedef int SomeLibrary::ValueHolder::* mem_ptr_t;

mem_ptr_t global_mem_ptr;

template<mem_ptr_t P>
class Transform {
  static bool tmp;
};

template<mem_ptr_t P>
bool Transform<P>::tmp = (global_mem_ptr = P, false);

template
class Transform<&SomeLibrary::ValueHolder::value_>;

inline void SetValue(SomeLibrary::ValueHolder& valueHolder, int value) {
  int &val = valueHolder.*global_mem_ptr;
  val = value;
}
