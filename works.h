#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "test_runner.h"

using namespace std;

namespace Works {
struct WorkInfo {
  double length;
  double weight;
};

double ComputeWorksDuration(const vector<WorkInfo> &works) {
  double total_length = 0;
  double total_weight = 0;
  for (const auto &work : works) {
    total_length += work.length;
    total_weight += work.weight * total_length;
  }
  return total_weight;
}

double GreedyDiff(vector<WorkInfo> works) {
  sort(works.begin(), works.end(),
       [](const WorkInfo &lhs, const WorkInfo &rhs) {
         double lhs_diff = (lhs.weight - lhs.length);
         double rhs_diff = (rhs.weight - rhs.length);
         return lhs_diff == rhs_diff ? lhs.weight > rhs.weight : lhs_diff > rhs_diff;
       });
  return ComputeWorksDuration(works);
}

double GreedyRatio(vector<WorkInfo> works) {
  sort(works.begin(), works.end(),
       [](const WorkInfo &lhs, const WorkInfo &rhs) {
         return lhs.weight / lhs.length > rhs.weight / rhs.length;
       });
  return ComputeWorksDuration(works);
}

void Run(istream &is, ostream &os) {
  int works_count;
  is >> works_count;

  vector<WorkInfo> works;
  works.reserve(works_count);

  for (int i = 0; i < works_count; ++i) {
    double weight, length;
    is >> weight >> length;
    works.push_back({.length = length, .weight = weight});
  }

  os << GreedyDiff(works) << " " << GreedyRatio(works) << endl;
}

void SimpleTest() {
  istringstream input(R"(12
8 50
74 59
31 73
45 79
24 10
41 66
93 43
88 4
28 30
41 13
4 70
10 58
)");

  ostringstream output;
  output << setprecision(25);
  Run(input, output);
  ASSERT_EQUAL(output.str(), "68615 67247\n")
}

void RunTests() {
  TestRunner tr;
  RUN_TEST(tr, SimpleTest);
}
} // namespace Works