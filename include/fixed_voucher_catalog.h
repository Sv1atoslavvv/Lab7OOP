#ifndef PROFSPILKA_LAB6_FIXED_VOUCHER_CATALOG_H_
#define PROFSPILKA_LAB6_FIXED_VOUCHER_CATALOG_H_

#include <array>
#include <cstddef>
#include <stdexcept>
#include <utility>

// Tasks 5-6: five template parameters, six data fields, and a user-defined T
// are used to build a fixed-capacity generic catalog of voucher cost objects.
template <typename T, typename Key, typename Label, typename Measure,
          std::size_t Capacity>
class FixedVoucherCatalog {
 public:
  static_assert(Capacity > 0, "Catalog capacity must be positive");

  FixedVoucherCatalog(Key key, Label label, Measure multiplier)
      : entries_{},
        size_(0),
        key_(std::move(key)),
        label_(std::move(label)),
        multiplier_(std::move(multiplier)),
        revision_(0) {}

  bool add(const T& item) {
    if (size_ == Capacity) return false;
    entries_[size_++] = item;
    ++revision_;
    return true;
  }

  bool erase(std::size_t index) {
    if (index >= size_) return false;
    for (std::size_t i = index; i + 1 < size_; ++i) {
      entries_[i] = std::move(entries_[i + 1]);
    }
    entries_[--size_] = T{};
    ++revision_;
    return true;
  }

  std::size_t size() const { return size_; }
  constexpr std::size_t capacity() const { return Capacity; }
  const Key& key() const { return key_; }
  const Label& label() const { return label_; }
  const Measure& multiplier() const { return multiplier_; }
  std::size_t revision() const { return revision_; }

  T& operator[](std::size_t index) {
    if (index >= size_) throw std::out_of_range("Індекс каталогу поза межами");
    return entries_[index];
  }

  const T& operator[](std::size_t index) const {
    if (index >= size_) throw std::out_of_range("Індекс каталогу поза межами");
    return entries_[index];
  }

  T aggregate() const {
    T result{};
    for (std::size_t i = 0; i < size_; ++i) result += entries_[i];
    return result;
  }

  void apply_multiplier() {
    for (std::size_t i = 0; i < size_; ++i) {
      entries_[i] *= static_cast<double>(multiplier_);
    }
    ++revision_;
  }

  // Task 4: member function template filters elements by a caller-supplied rule.
  template <typename Predicate>
  std::size_t count_if(Predicate predicate) const {
    std::size_t matches = 0;
    for (std::size_t i = 0; i < size_; ++i) {
      if (predicate(entries_[i])) ++matches;
    }
    return matches;
  }

  template <typename Action>
  void for_each(Action action) const {
    for (std::size_t i = 0; i < size_; ++i) action(entries_[i]);
  }

 private:
  std::array<T, Capacity> entries_;
  std::size_t size_;
  Key key_;
  Label label_;
  Measure multiplier_;
  std::size_t revision_;
};

#endif  // PROFSPILKA_LAB6_FIXED_VOUCHER_CATALOG_H_
