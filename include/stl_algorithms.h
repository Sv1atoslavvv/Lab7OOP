#ifndef PROFSPILKA_LAB7_STL_ALGORITHMS_H_
#define PROFSPILKA_LAB7_STL_ALGORITHMS_H_

#include <iosfwd>
#include <vector>

#include "voucher_record.h"

void demonstrate_algorithms(const std::vector<VoucherRecord>& records,
                            std::ostream& output);
void demonstrate_function_objects(std::ostream& output);

#endif  // PROFSPILKA_LAB7_STL_ALGORITHMS_H_
