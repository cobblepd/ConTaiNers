#include "s21_list.h"

namespace s21 {

template <typename T>
list<T>::list() noexcept
    : topHead(nullptr), topTail(nullptr), topEnd(nullptr), size_(0){};

template <typename T>
list<T>::list(size_type n) : list() {
  if (n < max_size()) {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (auto i : items) {
    push_back(i);
  }
}

template <typename T>
list<T>::list(const list &l) : list() {
  *this = l;
}

template <typename T>
list<T>::list(list &&l) noexcept : list() {
  *this = std::move(l);
}

template <typename T>
list<T>::~list() noexcept {
  clear();
}

template <typename T>
list<T> &list<T>::operator=(const list &l) {
  if (this != &l) {
    clear();
    CopyList(l);
  }
  return *this;
}

template <typename T>
list<T> list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    MoveList(std::move(l));
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const noexcept {
  const_reference zero = value_type();
  return empty() ? zero : topHead->value;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const noexcept {
  const_reference zero = value_type();
  return empty() ? zero : topTail->value;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  if (topEnd == nullptr) {
    CreateEnd();
  }
  return iterator(topHead, topEnd);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  if (topEnd == nullptr) {
    CreateEnd();
  }
  return iterator(topEnd, topEnd);
}

template <typename T>
bool list<T>::empty() const noexcept {
  return topHead == nullptr;
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_t>::max() / sizeof(typename list<T>::Node) /
         2;
}

template <typename T>
void list<T>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
  delete topEnd;
  topEnd = nullptr;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == topHead) {
    push_front(value);
    pos.itr_ = topHead;
  } else if (pos == end()) {
    push_back(value);
    pos.itr_ = topTail;
  } else {
    Node *temp = nullptr;
    try {
      temp = new Node(value);
    } catch (const std::bad_alloc &e) {
      clear();
      throw e;
    }
    Node *itr = pos.itr_;
    if (pos.itr_ == nullptr) {
      Node *tmp = topTail->next;
      temp->prev = topTail;
      topTail->next = temp;
      topTail = temp;
      topTail->next = tmp;
      itr = topTail;
    } else {
      temp->next = itr;
      temp->prev = itr->prev;
      if (temp->prev != nullptr) temp->prev->next = temp;
      itr->prev = temp;
    }
    ++size_;
    topEnd->value++;
    pos = iterator(temp);
  }
  return pos;
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
  } else if (pos == topTail) {
    pop_back();
  } else if (!empty() && pos != end()) {
    iterator prevPos = pos - 1;
    iterator nextPos = pos + 1;
    Node *temp = pos.itr_;
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    delete temp;
    size_--;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node *temp = nullptr;
  try {
    temp = new Node(value);
  } catch (const std::bad_alloc &e) {
    clear();
    throw e;
  }
  if (topHead == nullptr) topHead = temp;
  if (topTail == nullptr)
    topTail = temp;
  else {
    if (topTail->next == nullptr) {
      topTail->next = temp;
      temp->next = nullptr;
      temp->prev = topTail;
      topTail = temp;
    }
  }
  ++size_;
}

template <typename T>
void list<T>::pop_back() noexcept {
  if (topTail != nullptr) {
    Node *temp = topTail;
    if (temp == topHead) {
      delete temp;
      topHead = nullptr;
      topTail = nullptr;
    } else {
      topTail = temp->prev;
      topTail->next = nullptr;
      delete temp;
    }
    --size_;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node *temp = nullptr;
  try {
    temp = new Node(value);
  } catch (const std::bad_alloc &e) {
    clear();
    throw e;
  }
  if (topTail == nullptr) {
    topTail = temp;
  }
  if (topHead == nullptr)
    topHead = temp;
  else {
    topHead->prev = temp;
    temp->prev = nullptr;
    temp->next = topHead;
    topHead = temp;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_front() noexcept {
  if (topTail != nullptr) {
    Node *temp = topHead;
    if (temp == topTail) {
      delete temp;
      topHead = nullptr;
      topTail = nullptr;
    } else {
      topHead = temp->next;
      topHead->prev = nullptr;
      delete temp;
    }
    --size_;
  }
}

template <typename T>
void list<T>::swap(list &other) noexcept {
  std::swap(topHead, other.topHead);
  std::swap(topTail, other.topTail);
  std::swap(topEnd, other.topEnd);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list &other) {
  if (empty() && !other.empty()) {
    CopyList(other);
  } else if (!empty() && !other.empty()) {
    iterator it = begin();
    iterator it_other = other.begin();
    while (it != end() && it_other != other.end()) {
      if (it.itr_->value >= it_other.itr_->value) {
        insert(it, it_other.itr_->value);
        ++it_other;
      } else {
        ++it;
      }
    }
    while (it_other != other.end()) {
      insert(it, it_other.itr_->value);
      ++it_other;
    }
  }
  other.clear();
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (!other.empty()) {
    iterator our_it;
    our_it.itr_ = pos.itr_;
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(our_it, *it);
    }
    other.clear();
  }
}

template <typename T>
void list<T>::reverse() noexcept {
  Node *itr = topHead;
  for (size_type i = 0; i < size_; ++i) {
    std::swap(itr->next, itr->prev);
    itr = itr->prev;
  }
  std::swap(topTail, topHead);
}

template <typename T>
void list<T>::unique() {
  if (topHead != nullptr) {
    Node *currentNode = topHead;
    Node *nextNode = topHead->next;
    list<T> tmp;
    for (size_type i = 0; i < size_ - 1; ++i) {
      if (currentNode->value != nextNode->value) {
        tmp.push_back(currentNode->value);
      }
      currentNode = currentNode->next;
      nextNode = nextNode->next;
    }
    tmp.push_back(currentNode->value);
    *this = std::move(tmp);
  }
};

template <typename T>
void list<T>::sort() noexcept {
  for (size_type i = 0; i < size_ - 1; ++i) {
    Node *node = topHead;
    for (size_type j = 0; j < size_ - i - 1; ++j) {
      if (node->value >= node->next->value) {
        T temp = node->value;
        node->value = node->next->value;
        node->next->value = temp;
      }
      node = node->next;
    }
  }
}

template <typename T>
void list<T>::MoveList(list &&l) {
  std::swap(topHead, l.topHead);
  std::swap(topTail, l.topTail);
  std::swap(topEnd, l.topEnd);
  std::swap(size_, l.size_);
}

template <typename T>
void list<T>::CopyList(const list &l) {
  Node *temp = l.topHead;
  if (l.topTail) {
    while (temp != l.topTail->next) {
      push_back(temp->value);
      temp = temp->next;
    }
  }
}

template <typename T>
void list<T>::CreateEnd() {
  try {
    topEnd = new Node(value_type());
    topEnd->prev = topTail;
    topEnd->value = size_;
    topEnd->next = topHead;
  } catch (const std::bad_alloc &e) {
    clear();
    throw e;
  }
}

template <typename T>
list<T>::const_iterator::ConstListIterator() noexcept {
  itr_ = nullptr;
}

template <typename T>
list<T>::const_iterator::ConstListIterator(Node *n) noexcept {
  itr_ = n;
}

template <typename T>
list<T>::const_iterator::ConstListIterator(Node *n, Node *end) noexcept {
  itr_ = n;
  itr_end_ = end;
}

template <typename T>
list<T>::const_iterator::ConstListIterator(
    const ConstListIterator &other) noexcept {
  *this = other;
}
template <typename T>
list<T>::const_iterator::ConstListIterator(ConstListIterator &&other) noexcept {
  *this = std::move(other);
}

template <typename T>
typename list<T>::const_iterator &list<T>::const_iterator::operator=(
    const ConstListIterator &other) noexcept {
  itr_ = other.itr_;
  itr_end_ = other.itr_end_;
  return *this;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator=(
    ConstListIterator &&other) noexcept {
  itr_ = other.itr_;
  itr_end_ = other.itr_end_;
  other.itr_ = nullptr;
  other.itr_end_ = nullptr;
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::const_iterator::operator*()
    const noexcept {
  value_type zero = value_type();
  return itr_ == nullptr ? zero : itr_->value;
}

template <typename T>
typename list<T>::const_iterator
list<T>::const_iterator::operator++() noexcept {
  if (itr_->next)
    itr_ = itr_->next;
  else
    itr_ = itr_end_;
  return itr_;
}

template <typename T>
typename list<T>::const_iterator
list<T>::const_iterator::operator--() noexcept {
  if (itr_->prev)
    itr_ = itr_->prev;
  else
    itr_ = itr_end_;
  return itr_;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator+(
    const size_type step) noexcept {
  for (size_type i = 0; i < step; ++i) {
    ++*this;
  }
  return *this;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_iterator::operator-(
    const size_type step) noexcept {
  for (size_type i = 0; i < step; ++i) {
    --*this;
  }
  return *this;
}

template <typename T>
bool list<T>::const_iterator::operator==(
    const ConstListIterator &other) const noexcept {
  return itr_ == other.itr_;
}

template <typename T>
bool list<T>::const_iterator::operator!=(
    const ConstListIterator &other) const noexcept {
  return itr_ != other.itr_;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator=(
    const ConstListIterator &other) noexcept {
  *this = other;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator=(
    ConstListIterator &&other) noexcept {
  *this = std::move(other);
  return *this;
}

template <typename T>
typename list<T>::reference list<T>::iterator::operator*() const noexcept {
  value_type zero = value_type();
  return this->itr_ == nullptr ? zero : this->itr_->value;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++() noexcept {
  if (this->itr_) {
    if (this->itr_->next)
      this->itr_ = this->itr_->next;
    else
      this->itr_ = this->itr_end_;
  } else
    this->itr_ = this->itr_end_;
  return this->itr_;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator--() noexcept {
  if (this->itr_) {
    if (this->itr_->prev)
      this->itr_ = this->itr_->prev;
    else
      this->itr_ = this->itr_end_;
  } else
    this->itr_ = this->itr_end_;
  return this->itr_;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator+(
    const size_type step) noexcept {
  iterator res = this->itr_;
  for (size_type i = 0; i < step; ++i) {
    ++res;
  }
  return res;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator-(
    const size_type step) noexcept {
  iterator res = this->itr_;
  for (size_type i = 0; i < step; ++i) {
    --res;
  }
  return res;
}

template <class T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator it;
  it.itr_ = pos.itr_;
  for (auto &i : {args...}) {
    insert(it, i);
  }
  return it;
}

template <class T>
template <class... Args>
void list<T>::insert_many_back(Args &&...args) {
  for (auto &i : {args...}) {
    push_back(i);
  }
}

template <class T>
template <class... Args>
void list<T>::insert_many_front(Args &&...args) {
  for (auto &i : {args...}) {
    push_front(i);
  }
}

}  // namespace s21