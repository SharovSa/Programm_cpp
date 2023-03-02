#include <vector>

template<class T>
void TransformIf(T *begin, T *end, bool (*p)(const T &), void (*f)(T &)) {
  std::vector<T> tmp;
  for (T *ptr = begin; ptr < end; ++ptr) {
    try {
      tmp.push_back(*ptr);
    } catch(...) {
      tmp.push_back(*ptr);
    }
  }
  for (T *ptr = begin; ptr < end; ++ptr) {
    try {
      if (p(*ptr))
        f(*ptr);
    } catch (...) {
      T *s_ptr = begin;
      for (int i = 0; i < tmp.size(); ++i, ++s_ptr) {
        *s_ptr = tmp[i];
        if (s_ptr == (end - 1)) {
          break;
        }
      }
      throw;
    }
  }
}
