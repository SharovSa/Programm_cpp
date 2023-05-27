template<class Iterator>
class IndexedIterator {
 private:
  size_t index_;
  Iterator it_;

 public:
  using iterator_category = std::iterator_traits<Iterator>::iterator_category;
  using value_type = std::iterator_traits<Iterator>::value_type;
  using difference_type = std::iterator_traits<Iterator>::difference_type;
  using pointer = std::iterator_traits<Iterator>::pointer;
  using reference = std::iterator_traits<Iterator>::reference;
  IndexedIterator(Iterator it, size_t index) : it_(it), index_(index) {}
  IndexedIterator<Iterator>&  operator++();
  IndexedIterator<Iterator>  operator++(int);
  IndexedIterator<Iterator>&  operator--();
  reference operator*() const;
  IndexedIterator<Iterator> operator+(size_t);
  difference_type operator-(const IndexedIterator<Iterator>& indexed_iterator);
  bool operator!=(const IndexedIterator<Iterator>&);
  bool operator!=(const Iterator&);
  size_t index() const {
    return index_;
  }
};

template<class It>
IndexedIterator<It> CreateIndexedIterator(It iterator, size_t index = 0) {
  return IndexedIterator<It>(iterator, index);
}

template<class Iterator>
IndexedIterator<Iterator>& IndexedIterator<Iterator>::operator++() {
  ++index_;
  ++it_;
  return *this;
}

template<class Iterator>
IndexedIterator<Iterator>::reference IndexedIterator<Iterator>::operator*() const{
  return *it_;
}

template<class Iterator>
bool IndexedIterator<Iterator>::operator!=(const IndexedIterator<Iterator> &indexed_iterator) {
  return this->it_ != indexed_iterator.it_;
}

template<class Iterator>
bool IndexedIterator<Iterator>::operator!=(const Iterator &iterator) {
  return this->it_ != iterator;
}

template<class Iterator>
IndexedIterator<Iterator> IndexedIterator<Iterator>::operator+(size_t num) {
  return CreateIndexedIterator(it_ + num, index_ + num);
}

template<class Iterator>
IndexedIterator<Iterator> IndexedIterator<Iterator>::operator++(int) {
  IndexedIterator<Iterator> tmp{*this};
  ++(*this);
  return tmp;
}

template<class Iterator>
IndexedIterator<Iterator>& IndexedIterator<Iterator>::operator--() {
  --index_;
  --it_;
  return *this;
}

template<class Iterator>
IndexedIterator<Iterator>::difference_type IndexedIterator<Iterator>::operator-(const IndexedIterator<Iterator> &indexed_iterator) {
  return it_ - indexed_iterator.it_;
}