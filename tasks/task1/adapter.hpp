#include "some_library.hpp"

struct ValueHolder_struct {
  std::string name_;
  int value_;
};

inline void SetValue(SomeLibrary::ValueHolder &valueHolder, int value) {
  ValueHolder_struct *structured_valueHolder;
  structured_valueHolder = reinterpret_cast<ValueHolder_struct *>(&valueHolder);
  structured_valueHolder->value_ = value;
}