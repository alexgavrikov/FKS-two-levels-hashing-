/*
 * main.cpp
 *
 *  Created on: 28.10.2015
 *      Author: user
 */

#include <iostream>
#include <string>
#include <vector>
#include "fks.h"

#include "test.h"


std::vector<int> ReadElements(std::istream& istream = std::cin);

std::vector<bool> CheckIfElementsBelongToSet(
    const std::vector<int>& set_elements,
    const std::vector<int>& elements_to_check);

void PrintCheckResults(const std::vector<bool>& check_results,
                       std::ostream& ostream = std::cout);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
//  TestAll();

  const std::vector<int> set_elements = ReadElements();
  const std::vector<int> elements_to_check = ReadElements();

  const std::vector<bool> check_results =
      CheckIfElementsBelongToSet(set_elements, elements_to_check);

  PrintCheckResults(check_results);

  return 0;
}


std::vector<int> ReadElements(std::istream& istream) {
  int vector_size;
  istream >> vector_size;
  std::vector<int> numbers;
  numbers.reserve(vector_size);
  for (int i = 0; i < vector_size; ++i) {
    int number;
    istream >> number;
    numbers.push_back(number);
  }
  return numbers;
}

std::vector<bool> CheckIfElementsBelongToSet(
    const std::vector<int>& set_elements,
    const std::vector<int>& elements_to_check) {
  FixedSet fixed_set;
  std::mt19937 generator;
  generator.seed(838);
  fixed_set.Initialize(set_elements, generator);
  std::vector<bool> check_results;
  check_results.reserve(elements_to_check.size());
  for (const int number : elements_to_check) {
    check_results.push_back(fixed_set.Contains(number));
  }
  return check_results;
}

void PrintCheckResults(const std::vector<bool>& check_results,
                       std::ostream& ostream) {
  static const std::string kPositiveResponse = "Yes";
  static const std::string kNegativeResponse = "No";
  for (const bool check_result : check_results) {
    ostream << (check_result ? kPositiveResponse : kNegativeResponse) << "\n";
  }
}
