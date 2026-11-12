#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <variant>

#include "domain.h"
#include "fixed_voucher_catalog.h"
#include "inheritance_demo.h"
#include "services.h"
#include "stl_demo.h"
#include "voucher.h"

int main(int argc, char* argv[]) {
  std::cout << "=== Лабораторна робота №7: контейнери STL ===\n";

  // Lab5 baseline: students, trip, group, and registration interact in a
  // realistic scenario. The group aggregates students; Trip composes details.
  Student olena(2, "Олена Коваль", "Інформаційних технологій", 1,
                "olena@example.edu.ua", "+380000000001", "ІСТ-25-1",
                "REG-2026-001");
  Student andrii(4, "Андрій Мельник", "Інформаційних технологій", 1,
                 "andrii@example.edu.ua", "+380000000002", "ІСТ-25-1",
                 "REG-2026-002");
  Student maria(5, "Марія Бондар", "Економіки", 2, "maria@example.edu.ua",
                "+380000000003", "ЕК-24-2", "REG-2026-003");
  StudentGroup group("Весняна екскурсія");
  group.add_student(olena);
  group.add_student(andrii);
  group.add_student(maria);
  group.print();
  Trip trip("Львів", 2500.0, 3,
            TripDetails("Історичний центр і музей", "08:00, головний корпус",
                        "Університет — центр Львова — музей",
                        "Координатор: +380 00 000 00 00",
                        "Студентський квиток, зручне взуття та вода"));
  trip.print();

  // Lab5 baseline: inspect shared class data through a static method.
  Voucher::print_live_count();

  // Lab5 baseline: five static objects stored in a static array of variants.
  StaticVoucherSlots static_vouchers;
  static_vouchers[0].emplace(std::in_place_type<StudentVoucher>);
  static_vouchers[1].emplace(std::in_place_type<GroupVoucher>);
  static_vouchers[2].emplace(std::in_place_type<SponsoredVoucher>);
  static_vouchers[3].emplace(std::in_place_type<StudentGroupVoucher>);
  static_vouchers[4].emplace(std::in_place_type<StudentVoucher>);
  std::cout << "\n=== П'ять статичних об'єктів ===\n";
  show_static(static_vouchers);
  service_static(static_vouchers, 3700.0);
  std::cout << "Після Service_Static:\n";
  show_static(static_vouchers);

  // Lab5 baseline: five dynamic objects use unique_ptr in a fixed registry.
  DynamicVoucherSlots dynamic_vouchers;
  dynamic_vouchers[0] = std::make_unique<StudentVoucher>(
      "V-101", "Львів", 2500, 3, "готель", "поїзд", true, "", 2,
      "Олена Коваль", "ІТ", 1, "olena@example.edu.ua", "+380000000001",
      "ІСТ-25-1", "сплачено");
  dynamic_vouchers[1] = std::make_unique<GroupVoucher>(
      "V-102", "Львів", 2500, 3, "гуртожиток", "автобус", false, "",
      "Весняна", 3, "Олена Коваль", "+380000000001", group.discount_rate(),
      "автобус", "гуртожиток", "Спільний маршрут");
  dynamic_vouchers[2] = std::make_unique<SponsoredVoucher>(
      "V-103", "Київ", 1800, 2, "гуртожиток", "поїзд", false, "",
      "Профспілка ХНУ", 500, "студент", "підтверджено", "Ірина", "GR-103",
      "Фонд підтримки", "2026-10-28");
  dynamic_vouchers[3] = std::make_unique<StudentGroupVoucher>(
      "V-104", "Львів", 2500, 3, "готель", "поїзд", true, "", 2,
      "Олена Коваль", "ІТ", 1, "olena@example.edu.ua", "+380000000001",
      "ІСТ-25-1", "сплачено", "Весняна", 3, "Олена Коваль",
      "+380000000001", group.discount_rate(), "поїзд", "готель",
      "Спільний маршрут");
  dynamic_vouchers[4] = std::make_unique<StudentVoucher>(
      "V-105", "Одеса", 3100, 4, "готель", "літак", false, "", 5,
      "Марія Бондар", "Економіки", 2, "maria@example.edu.ua",
      "+380000000003", "ЕК-24-2", "очікує оплати");
  std::cout << "\n=== П'ять динамічних об'єктів ===\n";
  show_dynamic(dynamic_vouchers);
  service_dynamic(dynamic_vouchers, 5000.0);
  std::cout << "Після Service_Dinamic:\n";
  show_dynamic(dynamic_vouchers);

  // Lab5 baseline: file path comes from argv; the service writes/reads an object.
  StudentVoucher file_voucher(
      "FILE-001", trip.city(), trip.base_price(), 3, "готель", "поїзд", true,
      "Реєстрація профспілки", olena.id(), olena.name(), "ІТ", 1,
      "olena@example.edu.ua", "+380000000001", "ІСТ-25-1", "сплачено");
  const std::string file_name = argc > 1 ? argv[1] : "voucher_data.txt";
  try {
    service(file_voucher, file_name);
  } catch (const std::exception& error) {
    std::cerr << "Файловий сервіс завершився з помилкою: " << error.what() << '\n';
  }
  Registration registration(olena, trip, file_voucher);
  registration.print();

  // Tasks 1-3: demonstrate prefix/postfix ++/--, +, -, *, =, +=, -=, *=, [].
  std::cout << "\n=== Перевантаження операторів ===\n";
  VoucherCost olena_cost(2500.0, 2200.0, 800.0, 350.0, 0.0);
  VoucherCost maria_cost(3100.0, 2200.0, 3000.0, 0.0, 0.0);
  std::cout << "Початковий кошторис Олени: ";
  olena_cost.print(std::cout);
  VoucherCost previous_cost = olena_cost++;
  std::cout << "Постфіксний ++ повернув: ";
  previous_cost.print(std::cout);
  std::cout << "Після постфіксного ++: ";
  olena_cost.print(std::cout);
  ++olena_cost;
  --olena_cost;
  olena_cost--;
  std::cout << "Після ++, -- та постфіксного --: ";
  olena_cost.print(std::cout);
  VoucherCost combined_cost = olena_cost + maria_cost;
  std::cout << "Сума двох кошторисів: ";
  combined_cost.print(std::cout);
  VoucherCost difference_cost = combined_cost - maria_cost;
  std::cout << "Різниця кошторисів: ";
  difference_cost.print(std::cout);
  VoucherCost scaled_cost = maria_cost * 0.9;
  std::cout << "Кошторис після множення на 0.9: ";
  scaled_cost.print(std::cout);
  difference_cost += maria_cost;
  difference_cost -= maria_cost;
  difference_cost *= 1.0;
  VoucherCost assigned_cost;
  assigned_cost = difference_cost;
  std::cout << "Компонент проживання через []: "
            << assigned_cost[CostPart::kAccommodation] << " грн\n";

  // Tasks 4-6: the member-function template filters a catalog instantiated
  // with the user-defined VoucherCost type and four additional parameters.
  std::cout << "\n=== Шаблон каталогу кошторисів ===\n";
  FixedVoucherCatalog<VoucherCost, int, std::string, double, 5> catalog(
      6, "Осінні путівки", 0.95);
  catalog.add(olena_cost);
  catalog.add(VoucherCost(2500.0, 700.0, 600.0, 0.0, 0.0));
  catalog.add(maria_cost);
  std::cout << "Каталог: " << catalog.label() << ", записів: "
            << catalog.size() << "/" << catalog.capacity() << '\n';
  std::cout << "Кошторисів дорожче 5000 грн: "
            << catalog.count_if([](const VoucherCost& cost) {
                 return cost.total() > 5000.0;
               })
            << '\n';
  std::cout << "Перший запис каталогу: ";
  catalog[0].print(std::cout);
  catalog.apply_multiplier();
  std::cout << "Після застосування коефіцієнта " << catalog.multiplier()
            << ": ";
  catalog[0].print(std::cout);
  std::cout << "Сума кошторисів каталогу: ";
  catalog.aggregate().print(std::cout);

  demonstrate_file_exceptions(file_name);
  demonstrate_memory_exceptions();
  demonstrate_polymorphism();
  demonstrate_destructor_rules();

  // Lab7 tasks 1-4: containers, iterator categories, algorithms, and functors.
  run_stl_demonstration(std::cout);

  // Lab5 baseline: menu allows the user to create and destroy a dynamic voucher.
  run_menu(dynamic_vouchers);
  Voucher::print_live_count();
  std::cout << "=== Завершення демонстрації ===\n";
  // Lab6 baseline remains above; Lab7 task groups 1-4 are in the STL module.
  // Code style follows Google C++ conventions; the student uploads to GitHub.
  return 0;
}
