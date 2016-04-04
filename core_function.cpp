/*
 * core_function.cpp
 *
 *  Created on: 04.04.2016
 *      Author: user
 */

#include "core_function.h"
#include <random>
#include "fks.h"

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

