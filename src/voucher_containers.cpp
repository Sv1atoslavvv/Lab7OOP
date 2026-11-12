#include "voucher_containers.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

namespace {

template <typename Container>
void print_size(std::ostream& output, const std::string& label,
                const Container& container) {
  output << label << ": " << container.size() << " запис(и)\n";
}

}  // namespace

VoucherContainers::VoucherContainers(const Sample& sample) : sample_(sample) {}

std::vector<VoucherRecord> VoucherContainers::records() const {
  return std::vector<VoucherRecord>(sample_.begin(), sample_.end());
}

void VoucherContainers::demonstrate(std::ostream& output) const {
  output << "\n=== Контейнери STL ===\n";

  // Task 1.1: vector demonstrates indexed access, insertion, and removal.
  std::vector<VoucherRecord> vector_records;
  vector_records.push_back(sample_[0]);
  vector_records.push_back(sample_[1]);
  vector_records.insert(vector_records.begin() + 1, sample_[2]);
  vector_records.erase(vector_records.begin());
  output << "vector: at(0) -> " << vector_records.at(0) << '\n';
  print_size(output, "vector після push_back/insert/erase", vector_records);

  // Task 1.2: list demonstrates operations at the beginning and in the middle.
  std::list<VoucherRecord> list_records;
  list_records.push_back(sample_[0]);
  list_records.push_front(sample_[1]);
  list_records.insert(std::next(list_records.begin()), sample_[2]);
  list_records.remove_if([](const VoucherRecord& item) {
    return item.price() < 3000.0;
  });
  print_size(output, "list після push_front/push_back/insert/remove_if",
             list_records);

  // Task 1.3: deque supports efficient insertion at both ends.
  std::deque<VoucherRecord> deque_records;
  deque_records.push_back(sample_[0]);
  deque_records.push_front(sample_[1]);
  deque_records.push_back(sample_[2]);
  deque_records.pop_back();
  output << "deque: front -> " << deque_records.front() << '\n';

  // Task 1.4: set stores unique records, ordered by the voucher code.
  std::set<VoucherRecord> set_records;
  set_records.insert(sample_[0]);
  set_records.insert(sample_[1]);
  set_records.insert(sample_[0]);
  const auto set_match = set_records.find(sample_[0]);
  output << "set: код V-101 знайдено -> "
         << (set_match != set_records.end() ? "так" : "ні")
         << ", дублікат не доданий; " << set_records.size() << " унікальні\n";
  set_records.erase(sample_[1]);

  // Task 1.5: multiset permits repeated records and counts their occurrences.
  std::multiset<VoucherRecord, VoucherPriceLess> multiset_records;
  multiset_records.insert(sample_[0]);
  multiset_records.insert(sample_[0]);
  multiset_records.insert(sample_[1]);
  output << "multiset: повторів V-101 -> " << multiset_records.count(sample_[0])
         << '\n';
  multiset_records.erase(multiset_records.begin());

  // Task 1.6: map accesses a voucher object by a unique student ID.
  std::map<int, VoucherRecord> map_records;
  map_records.insert_or_assign(sample_[0].student_id(), sample_[0]);
  map_records.insert_or_assign(sample_[1].student_id(), sample_[1]);
  map_records.insert_or_assign(sample_[2].student_id(), sample_[2]);
  const auto map_match = map_records.find(sample_[0].student_id());
  output << "map: студент " << sample_[0].student_id() << " -> "
         << map_match->second.code() << "; at() -> "
         << map_records.at(sample_[1].student_id()).code() << '\n';
  map_records.erase(sample_[2].student_id());

  // Task 1.7: multimap keeps multiple voucher objects under the same city key.
  std::multimap<std::string, VoucherRecord> multimap_records;
  multimap_records.emplace(sample_[0].city(), sample_[0]);
  multimap_records.emplace(sample_[1].city(), sample_[1]);
  multimap_records.emplace(sample_[2].city(), sample_[2]);
  const auto city_range = multimap_records.equal_range("Львів");
  output << "multimap: путівок до Львова -> "
         << std::distance(city_range.first, city_range.second) << '\n';
  multimap_records.erase("Одеса");

  // Task 1.8: stack follows last-in, first-out order.
  std::stack<VoucherRecord> stack_records;
  stack_records.push(sample_[0]);
  stack_records.push(sample_[1]);
  stack_records.push(sample_[2]);
  output << "stack: top -> " << stack_records.top().code() << '\n';
  stack_records.pop();
  output << "stack після pop(): " << stack_records.size() << " елементи\n";

  // Task 1.9: queue follows first-in, first-out order.
  std::queue<VoucherRecord> queue_records;
  queue_records.push(sample_[0]);
  queue_records.push(sample_[1]);
  queue_records.push(sample_[2]);
  output << "queue: front -> " << queue_records.front().code() << '\n';
  queue_records.pop();
  output << "queue після pop(): " << queue_records.size() << " елементи\n";

  // Task 1.10: priority_queue returns the record with the highest priority.
  std::priority_queue<VoucherRecord, std::vector<VoucherRecord>,
                      VoucherPriorityLess>
      priority_records;
  for (const VoucherRecord& record : sample_) {
    priority_records.push(record);
  }
  output << "priority_queue: top -> " << priority_records.top().code()
         << " (пріоритет " << priority_records.top().priority() << ")\n";
  priority_records.pop();
  output << "priority_queue після pop(): " << priority_records.size()
         << " елементи\n";
}
