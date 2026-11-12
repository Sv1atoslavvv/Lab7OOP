#include "stl_demo.h"

#include <array>

#include "stl_algorithms.h"
#include "stl_iterators.h"
#include "voucher_containers.h"

void run_stl_demonstration(std::ostream& output) {
  const VoucherContainers::Sample sample = {
      VoucherRecord("V-101", 2, "Олена Коваль", "Львів", 5850.0, 3),
      VoucherRecord("V-102", 4, "Андрій Мельник", "Львів", 4250.0, 2),
      VoucherRecord("V-103", 5, "Марія Бондар", "Одеса", 6100.0, 5),
      VoucherRecord("V-104", 6, "Іван Петренко", "Київ", 2800.0, 1),
  };

  const VoucherContainers containers(sample);
  containers.demonstrate(output);
  const std::vector<VoucherRecord> records = containers.records();
  demonstrate_iterators(records, output);
  demonstrate_algorithms(records, output);
  demonstrate_function_objects(output);
}
