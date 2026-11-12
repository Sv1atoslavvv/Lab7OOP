#include "voucher_cost.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

VoucherCost::VoucherCost() : parts_{0.0, 0.0, 0.0, 0.0, 0.0}, currency_("грн") {}

VoucherCost::VoucherCost(double trip, double accommodation, double transport,
                         double insurance, double service, std::string currency)
    : parts_{trip, accommodation, transport, insurance, service},
      currency_(std::move(currency)) {
  for (double part : parts_) validate_amount(part);
  if (currency_.empty()) {
    throw std::invalid_argument("Валюта кошторису не може бути порожньою");
  }
}

VoucherCost::VoucherCost(const VoucherCost& other)
    : parts_(other.parts_), currency_(other.currency_) {}

VoucherCost& VoucherCost::operator=(const VoucherCost& other) {
  // Task 3: member assignment copies all parts and the currency label.
  if (this != &other) {
    parts_ = other.parts_;
    currency_ = other.currency_;
  }
  return *this;
}

double VoucherCost::total() const {
  double result = 0.0;
  for (double part : parts_) result += part;
  return result;
}

const std::string& VoucherCost::currency() const { return currency_; }

void VoucherCost::print(std::ostream& output) const {
  output << std::fixed << std::setprecision(2)
         << "Поїздка: " << (*this)[CostPart::kTrip]
         << ", проживання: " << (*this)[CostPart::kAccommodation]
         << ", транспорт: " << (*this)[CostPart::kTransport]
         << ", страховка: " << (*this)[CostPart::kInsurance]
         << ", сервіс: " << (*this)[CostPart::kService]
         << ", разом: " << total() << ' ' << currency_ << '\n';
}

double& VoucherCost::operator[](std::size_t index) {
  // Task 3: indexed access checks bounds instead of exposing raw storage.
  if (index >= parts_.size()) {
    throw std::out_of_range("Індекс компонента кошторису поза межами");
  }
  return parts_[index];
}

const double& VoucherCost::operator[](std::size_t index) const {
  if (index >= parts_.size()) {
    throw std::out_of_range("Індекс компонента кошторису поза межами");
  }
  return parts_[index];
}

double& VoucherCost::operator[](CostPart part) {
  return (*this)[static_cast<std::size_t>(part)];
}

const double& VoucherCost::operator[](CostPart part) const {
  return (*this)[static_cast<std::size_t>(part)];
}

VoucherCost& VoucherCost::operator++() {
  // Task 1: prefix ++ increases the service fee in place.
  (*this)[CostPart::kService] += kServiceStep;
  return *this;
}

VoucherCost VoucherCost::operator++(int) {
  // Task 1: postfix ++ returns the old value, then increases the service fee.
  VoucherCost previous(*this);
  ++(*this);
  return previous;
}

VoucherCost& VoucherCost::operator--() {
  // Task 1: prefix -- reduces the service fee without making it negative.
  double& service = (*this)[CostPart::kService];
  service = service >= kServiceStep ? service - kServiceStep : 0.0;
  return *this;
}

VoucherCost VoucherCost::operator--(int) {
  VoucherCost previous(*this);
  --(*this);
  return previous;
}

VoucherCost VoucherCost::operator+(const VoucherCost& other) const {
  // Task 2: + combines two compatible itemized budgets component by component.
  validate_currency(other);
  VoucherCost result(*this);
  for (std::size_t i = 0; i < kPartCount; ++i) result.parts_[i] += other.parts_[i];
  return result;
}

VoucherCost VoucherCost::operator-(const VoucherCost& other) const {
  // Task 2: - subtracts corresponding costs and floors each part at zero.
  validate_currency(other);
  VoucherCost result(*this);
  for (std::size_t i = 0; i < kPartCount; ++i) {
    result.parts_[i] = parts_[i] >= other.parts_[i]
                           ? parts_[i] - other.parts_[i]
                           : 0.0;
  }
  return result;
}

VoucherCost VoucherCost::operator*(double factor) const {
  if (!std::isfinite(factor) || factor < 0.0) {
    throw std::invalid_argument("Множник вартості має бути скінченним і невід'ємним");
  }
  VoucherCost result(*this);
  for (double& part : result.parts_) part *= factor;
  return result;
}

VoucherCost& VoucherCost::operator+=(const VoucherCost& other) {
  *this = *this + other;
  return *this;
}

VoucherCost& VoucherCost::operator-=(const VoucherCost& other) {
  *this = *this - other;
  return *this;
}

VoucherCost& VoucherCost::operator*=(double factor) {
  *this = *this * factor;
  return *this;
}

void VoucherCost::validate_amount(double amount) {
  if (!std::isfinite(amount) || amount < 0.0) {
    throw std::invalid_argument("Складова кошторису має бути скінченною і невід'ємною");
  }
}

void VoucherCost::validate_currency(const VoucherCost& other) const {
  if (currency_ != other.currency_) {
    throw std::invalid_argument("Не можна об'єднувати кошториси в різних валютах");
  }
}
