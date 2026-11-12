#ifndef PROFSPILKA_LAB6_VOUCHER_COST_H_
#define PROFSPILKA_LAB6_VOUCHER_COST_H_

#include <array>
#include <cstddef>
#include <iosfwd>
#include <string>

enum class CostPart : std::size_t {
  kTrip = 0,
  kAccommodation,
  kTransport,
  kInsurance,
  kService,
  kCount
};

// Tasks 1-3: a value object representing a five-part voucher quotation.
// Arithmetic combines or scales budgets, while ++/-- adjust the service fee.
class VoucherCost {
 public:
  static constexpr std::size_t kPartCount =
      static_cast<std::size_t>(CostPart::kCount);
  static constexpr double kServiceStep = 100.0;

  VoucherCost();
  VoucherCost(double trip, double accommodation, double transport,
              double insurance, double service,
              std::string currency = "грн");
  VoucherCost(const VoucherCost& other);
  VoucherCost& operator=(const VoucherCost& other);

  double total() const;
  const std::string& currency() const;
  void print(std::ostream& output) const;

  double& operator[](std::size_t index);
  const double& operator[](std::size_t index) const;
  double& operator[](CostPart part);
  const double& operator[](CostPart part) const;

  VoucherCost& operator++();
  VoucherCost operator++(int);
  VoucherCost& operator--();
  VoucherCost operator--(int);

  VoucherCost operator+(const VoucherCost& other) const;
  VoucherCost operator-(const VoucherCost& other) const;
  VoucherCost operator*(double factor) const;
  VoucherCost& operator+=(const VoucherCost& other);
  VoucherCost& operator-=(const VoucherCost& other);
  VoucherCost& operator*=(double factor);

 private:
  static void validate_amount(double amount);
  void validate_currency(const VoucherCost& other) const;

  std::array<double, kPartCount> parts_;
  std::string currency_;
};

#endif  // PROFSPILKA_LAB6_VOUCHER_COST_H_
