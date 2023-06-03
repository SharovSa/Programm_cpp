#include <vector>

template <class T>
void TransformIf(T* begin, T* end, bool (*p)(const T&), void (*f)(T&)) {
  std::vector<T> transformed;
  std::vector<T*> transformed_ptrs;
  // Если не сделать отдельный массив для указателей, то при создании pair<T, T*> int.counter_ будет обновляться 2 раза
  bool copy_fail = false;
  for (T *ptr = begin; ptr < end; ++ptr) {
    try {
      if (p(*ptr)) {
        transformed_ptrs.push_back(ptr);
        try {
          transformed.push_back(*ptr);
        } catch (...) {
          copy_fail = true;
        }
        f(*ptr);
      }
    } catch (...) {
      if (copy_fail) {
        throw;
      }
      for (size_t i = 0; i < transformed.size(); ++i) {
        *transformed_ptrs[i] = transformed[i];
      }
      throw;
    }
  }
}
