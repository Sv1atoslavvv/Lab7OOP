#ifndef PROFSPILKA_LAB7_VOUCHER_RECORD_H_
#define PROFSPILKA_LAB7_VOUCHER_RECORD_H_

#include <iosfwd>
#include <string>

// A compact value object used by the STL catalog demonstrations.
class VoucherRecord {
 public:
  VoucherRecord(std::string code, int student_id, std::string student_name,
                std::string city, double price, int priority);

  const std::string& code() const;
  int student_id() const;
  const std::string& student_name() const;
  const std::string& city() const;
  double price() const;
  int priority() const;

  // The default ordering lets std::set keep voucher codes unique.
  bool operator<(const VoucherRecord& other) const;

 private:
  std::string code_;
  int student_id_;
  std::string student_name_;
  std::string city_;
  double price_;
  int priority_;
};

std::ostream& operator<<(std::ostream& output, const VoucherRecord& voucher);

struct VoucherPriceLess {
  bool operator()(const VoucherRecord& left,
                  const VoucherRecord& right) const;
};

struct VoucherPriorityLess {
  bool operator()(const VoucherRecord& left,
                  const VoucherRecord& right) const;
};

#endif  // PROFSPILKA_LAB7_VOUCHER_RECORD_H_
