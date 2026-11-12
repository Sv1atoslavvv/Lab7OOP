#include "voucher_record.h"

#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <utility>

VoucherRecord::VoucherRecord(std::string code, int student_id,
                             std::string student_name, std::string city,
                             double price, int priority)
    : code_(std::move(code)),
      student_id_(student_id),
      student_name_(std::move(student_name)),
      city_(std::move(city)),
      price_(price),
      priority_(priority) {
  if (code_.empty() || student_id_ <= 0 || price_ < 0.0 || priority_ < 0) {
    throw std::invalid_argument("Некоректні дані запису путівки.");
  }
}

const std::string& VoucherRecord::code() const { return code_; }

int VoucherRecord::student_id() const { return student_id_; }

const std::string& VoucherRecord::student_name() const {
  return student_name_;
}

const std::string& VoucherRecord::city() const { return city_; }

double VoucherRecord::price() const { return price_; }

int VoucherRecord::priority() const { return priority_; }

bool VoucherRecord::operator<(const VoucherRecord& other) const {
  return code_ < other.code_;
}

std::ostream& operator<<(std::ostream& output,
                         const VoucherRecord& voucher) {
  output << voucher.code() << " | студент: " << voucher.student_name()
         << " | місто: " << voucher.city() << " | " << std::fixed
         << std::setprecision(2) << voucher.price() << " грн | пріоритет: "
         << voucher.priority();
  return output;
}

bool VoucherPriceLess::operator()(const VoucherRecord& left,
                                  const VoucherRecord& right) const {
  if (left.price() == right.price()) {
    return left.code() < right.code();
  }
  return left.price() < right.price();
}

bool VoucherPriorityLess::operator()(const VoucherRecord& left,
                                     const VoucherRecord& right) const {
  if (left.priority() == right.priority()) {
    return left.code() > right.code();
  }
  return left.priority() < right.priority();
}
