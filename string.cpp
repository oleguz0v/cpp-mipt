#include <cstring>
#include <iostream>

class String {
 public:
  String(const char* str = "") {
    size_ = std::strlen(str);
    capacity_ = size_;
    data_ = new char[capacity_ + 1];
    std::memcpy(data_, str, size_ + 1);
  }

  String(size_t n, char c) {
    size_ = n;
    capacity_ = n;
    data_ = new char[capacity_ + 1];
    std::fill(data_, data_ + size_, c);
    data_[size_] = '\0';
  }

  String(const String& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new char[other.capacity_ + 1];
    std::memcpy(data_, other.data_, size_ + 1);
  }

  ~String() { delete[] data_; }

  String& operator=(const String& other) {
    if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = new char[capacity_ + 1];
      std::memcpy(data_, other.data_, size_ + 1);
    }
    return *this;
  }

  char& operator[](size_t ind) { return data_[ind]; }

  const char& operator[](size_t ind) const { return data_[ind]; }

  String& operator+=(char c) {
    if (capacity_ == size_) {
      res_capacity(2 * capacity_ + 1);
    }
    data_[size_] = c;
    ++size_;
    data_[size_] = '\0';
    return *this;
  }

  String& operator+=(const String& other) {
    res_capacity(size_ + other.size_);
    std::memcpy(data_ + size_, other.data_, other.size_);
    size_ += other.size_;
    data_[size_] = '\0';
    return *this;
  }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  size_t length() const { return size_; }

  void push_back(char c) { *this += c; }

  void pop_back() {
    if (size_ > 0) {
      data_[--size_] = '\0';
    }
  }

  char& front() { return data_[0]; }
  const char& front() const { return data_[0]; }

  char& back() { return data_[size_ - 1]; }
  const char& back() const { return data_[size_ - 1]; }

  size_t find(const String& substring) const { return find(substring, 0); }

  size_t rfind(const String& substring) const {
    size_t res = size_;
    for (size_t i = find(substring, 0); i < size_; i = find(substring, i + 1)) {
      res = i;
    }
    return res;
  }

  String substr(size_t start, size_t count) const {
    String res(count, '\0');
    std::memcpy(res.data_, data_ + start, count);
    return res;
  }

  bool empty() const { return size_ == 0; }

  void clear() {
    size_ = 0;
    data_[0] = '\0';
  }

  void shrink_to_fit() {
    if (capacity_ > size_) {
      capacity_ = size_;
      char* new_data = new char[capacity_ + 1];
      std::memcpy(new_data, data_, size_ + 1);
      delete[] data_;
      data_ = new_data;
    }
  }

  const char* data() const { return data_; }
  char* data() { return data_; }

 private:
  char* data_;
  size_t size_;
  size_t capacity_;

  void res_capacity(size_t new_capacity) {
    if (new_capacity > capacity_) {
      capacity_ = new_capacity;
      char* new_data = new char[capacity_ + 1];
      std::memcpy(new_data, data_, size_);
      delete[] data_;
      data_ = new_data;
      data_[size_] = '\0';
    }
  }

  size_t find(const String& substring, size_t start) const {
    if (substring.size_ == 0 || substring.size_ > size_) {
      return size_;
    }
    for (size_t i = start; i < size_ - substring.size_ + 1; ++i) {
      if (std::memcmp(data_ + i, substring.data_, substring.size_) == 0) {
        return i;
      }
    }
    return size_;
  }
};

bool operator==(const String& first, const String& second) {
  if (first.size() != second.size()) {
    return false;
  }
  return std::memcmp(first.data(), second.data(), first.size()) == 0;
}

bool operator!=(const String& first, const String& second) {
  return !(first == second);
}

bool operator<(const String& first, const String& second) {
  int res = std::memcmp(first.data(), second.data(),
                        std::min(first.size(), second.size()));
  if (res == 0) {
    return first.size() < second.size();
  }
  return res < 0;
}

bool operator>(const String& first, const String& second) {
  return second < first;
}

bool operator<=(const String& first, const String& second) {
  return !(first > second);
}

bool operator>=(const String& first, const String& second) {
  return !(first < second);
}

String operator+(const String& first, const String& second) {
  String res(first.size() + second.size(), '\0');
  res.clear();
  res += first;
  res += second;
  return res;
}

String operator+(char first, const String& second) {
  String res(1 + second.size(), '\0');
  res.clear();
  res += first;
  res += second;
  return res;
}

String operator+(const String& first, char second) {
  String res(first.size() + 1, '\0');
  res.clear();
  res += first;
  res += second;
  return res;
}

std::ostream& operator<<(std::ostream& output, const String& string) {
  for (size_t i = 0; i < string.size(); ++i) {
    output << string[i];
  }
  return output;
}

std::istream& operator>>(std::istream& input, String& string) {
  char symbol = input.get();
  while (symbol == ' ') {
    symbol = input.get();
  }
  string.clear();
  do {
    string.push_back(symbol);
    symbol = input.get();
  } while (symbol != ' ' && symbol != '\n' && symbol != EOF && symbol != '\0');
  return input;
}
