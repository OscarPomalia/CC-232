#pragma once

namespace ods {

template <typename K, typename V>
struct Entry {
  K key{};
  V value{};

  Entry() = default;
  Entry(const K& k, const V& v) : key(k), value(v) {}

  bool operator==(const Entry& other) const { return key == other.key; }
  bool operator!=(const Entry& other) const { return key != other.key; }
  bool operator<(const Entry& other) const { return key < other.key; }
  bool operator>(const Entry& other) const { return key > other.key; }
};

}  // namespace ods
