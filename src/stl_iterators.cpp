#include "stl_iterators.h"

#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>

void demonstrate_iterators(const std::vector<VoucherRecord>& records,
                           std::ostream& output) {
  output << "\n=== Категорії ітераторів ===\n";

  // Task 2.1: istream_iterator is an input iterator with single-pass access.
  std::istringstream input("101 102 103");
  std::istream_iterator<int> input_iterator(input);
  const std::istream_iterator<int> input_end;
  int input_sum = 0;
  for (; input_iterator != input_end; ++input_iterator) {
    input_sum += *input_iterator;
  }
  output << "input iterator: прочитана сума ID -> " << input_sum << '\n';

  // Task 2.2: ostream_iterator writes values to an output stream.
  std::ostringstream serialized;
  std::ostream_iterator<std::string> output_iterator(serialized, ", ");
  *output_iterator++ = records[0].code();
  *output_iterator++ = records[1].code();
  *output_iterator = records[2].code();
  output << "output iterator: " << serialized.str() << '\n';

  // Task 2.3: forward_list exposes a forward iterator.
  std::forward_list<VoucherRecord> forward_records(records.begin(),
                                                   records.end());
  auto forward_iterator = forward_records.begin();
  ++forward_iterator;
  output << "forward iterator: другий запис -> " << forward_iterator->code()
         << '\n';

  // Task 2.4: list supports movement in both directions.
  std::list<VoucherRecord> bidirectional_records(records.begin(),
                                                records.end());
  output << "bidirectional iterator, reverse: ";
  for (auto iterator = bidirectional_records.rbegin();
       iterator != bidirectional_records.rend(); ++iterator) {
    output << iterator->code() << ' ';
  }
  output << '\n';

  // Task 2.5: vector iterators allow arithmetic and indexed access.
  auto random_iterator = records.begin() + 1;
  output << "random-access iterator: begin()+1 -> " << random_iterator->code()
         << ", наступний через [1] -> " << random_iterator[1].code() << '\n';
}
