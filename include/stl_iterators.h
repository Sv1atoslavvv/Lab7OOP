#ifndef PROFSPILKA_LAB7_STL_ITERATORS_H_
#define PROFSPILKA_LAB7_STL_ITERATORS_H_

#include <iosfwd>
#include <vector>

#include "voucher_record.h"

void demonstrate_iterators(const std::vector<VoucherRecord>& records,
                           std::ostream& output);

#endif  // PROFSPILKA_LAB7_STL_ITERATORS_H_
