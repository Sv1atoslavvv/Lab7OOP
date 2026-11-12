#ifndef PROFSPILKA_LAB7_VOUCHER_CONTAINERS_H_
#define PROFSPILKA_LAB7_VOUCHER_CONTAINERS_H_

#include <array>
#include <deque>
#include <forward_list>
#include <iosfwd>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "voucher_record.h"

class VoucherContainers {
 public:
  using Sample = std::array<VoucherRecord, 4>;

  explicit VoucherContainers(const Sample& sample);
  void demonstrate(std::ostream& output) const;
  std::vector<VoucherRecord> records() const;

 private:
  Sample sample_;
};

#endif  // PROFSPILKA_LAB7_VOUCHER_CONTAINERS_H_
