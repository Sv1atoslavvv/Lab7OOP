#include "stl_algorithms.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <ostream>
#include <vector>

namespace {

struct VoucherPriceAtMost {
  explicit VoucherPriceAtMost(double maximum_price)
      : maximum_price_(maximum_price) {}

  bool operator()(const VoucherRecord& voucher) const {
    return voucher.price() <= maximum_price_;
  }

 private:
  double maximum_price_;
};

}  // namespace

void demonstrate_algorithms(const std::vector<VoucherRecord>& records,
                            std::ostream& output) {
  output << "\n=== Алгоритми STL ===\n";
  std::vector<VoucherRecord> sorted_records(records);

  // Task 3: five standard algorithms operate on the same domain collection.
  std::sort(sorted_records.begin(), sorted_records.end(), VoucherPriceLess());
  output << "1) sort: найдешевша путівка -> "
         << sorted_records.front().code() << " (" << sorted_records.front().price()
         << " грн)\n";

  const auto expensive = std::find_if(
      sorted_records.begin(), sorted_records.end(),
      [](const VoucherRecord& voucher) { return voucher.price() > 5000.0; });
  output << "2) find_if: перша путівка дорожче 5000 грн -> "
         << (expensive != sorted_records.end() ? expensive->code() : "не знайдена")
         << '\n';

  const auto affordable_count = std::count_if(
      sorted_records.begin(), sorted_records.end(), VoucherPriceAtMost(5000.0));
  output << "3) count_if з власним functor: до 5000 грн -> "
         << affordable_count << '\n';

  std::vector<double> discounted_prices;
  discounted_prices.reserve(sorted_records.size());
  std::transform(sorted_records.begin(), sorted_records.end(),
                 std::back_inserter(discounted_prices),
                 [](const VoucherRecord& voucher) {
                   return voucher.price() * 0.90;
                 });
  output << "4) transform: ціна V-101 зі знижкою 10% -> ";
  const auto student_voucher = std::find_if(
      sorted_records.begin(), sorted_records.end(),
      [](const VoucherRecord& voucher) { return voucher.code() == "V-101"; });
  if (student_voucher != sorted_records.end()) {
    const auto index = static_cast<std::size_t>(
        std::distance(sorted_records.begin(), student_voucher));
    output << discounted_prices[index] << " грн\n";
  }

  const double total = std::accumulate(
      sorted_records.begin(), sorted_records.end(), 0.0,
      [](double sum, const VoucherRecord& voucher) {
        return sum + voucher.price();
      });
  output << "5) accumulate: сума вартостей -> " << total << " грн\n";
}

void demonstrate_function_objects(std::ostream& output) {
  output << "\n=== Функціональні об'єкти STL ===\n";

  // Task 4.1: arithmetic function objects.
  output << "арифметика plus/minus/multiplies/divides/modulus/negate: "
         << std::plus<double>()(12.0, 3.0) << ", "
         << std::minus<double>()(12.0, 3.0) << ", "
         << std::multiplies<double>()(12.0, 3.0) << ", "
         << std::divides<double>()(12.0, 3.0) << ", "
         << std::modulus<int>()(12, 5) << ", "
         << std::negate<double>()(12.0) << '\n';

  // Task 4.2: relational function objects.
  output << "порівняння equal/not_equal/greater/less/greater_equal/less_equal: "
         << std::equal_to<int>()(5, 5) << '/' << std::not_equal_to<int>()(5, 3)
         << '/' << std::greater<int>()(5, 3) << '/' << std::less<int>()(3, 5)
         << '/' << std::greater_equal<int>()(5, 5) << '/'
         << std::less_equal<int>()(3, 5) << '\n';

  // Task 4.3: logical function objects.
  output << "логічні logical_and/logical_or/logical_not: "
         << std::logical_and<bool>()(true, true) << '/'
         << std::logical_or<bool>()(false, true) << '/'
         << std::logical_not<bool>()(false) << '\n';
}
