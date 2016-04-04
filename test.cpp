/*
 * test.cpp
 *
 *  Created on: 28.10.2015
 *      Author: user
 */

#include "test.h"
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <ctime>
#include <memory>
#include "fks.h"
#include "core_function.h"

template <typename T>
void OutputSequence(const std::string &name, const std::vector<T> &sequence) {
  std::cerr << name;
  for (const T& element : sequence) {
    std::cout << ' ' << element;
  }
  std::cerr << std::endl;
}

std::vector<bool> SimpleSlowSolution(std::vector<int> numbers_set,
                                     const std::vector<int>& numbers_to_check) {
  std::vector<bool> check_results;
  check_results.reserve(numbers_to_check.size());
  std::sort(numbers_set.begin(), numbers_set.end());
  for(const int number : numbers_to_check) {
    if(numbers_set.back() < number) {
      check_results.push_back(false);
    }
    else {
      for(int i = 0; i < numbers_set.size(); ++i) {
        if(numbers_set[i] == number) {
          check_results.push_back(true);
          break;
        }
        else if (numbers_set[i] > number) {
          check_results.push_back(false);
          break;
        }
      }
    }
  }

  return check_results;
}

bool GotPrime(int64_t potential_prime) {
  if (potential_prime == 1) {
    return false;
  }
  if (potential_prime == 2) {
    return true;
  }
  if (potential_prime % 2 == 0) {
    return false;
  }
  int64_t divider = 3;
  int64_t UpperLimit = sqrt(potential_prime) + 1;
  while (divider < UpperLimit) {
    if (potential_prime % divider == 0) {
      return false;
    }
    divider += 2;
  }

  return true;
}

void TestAll() {
  int64_t p = 5000000 + 1;
  while (true) {
    if (GotPrime(p)) {
      std::cout << p << std::endl;
      return;
    }
    p += 2;
    std::cout << "next" << std::endl;
  }
  getchar();
  TestFuncAll();
}

void TestFuncAll() {
  std::mt19937 generator;
  generator.seed(838);
  int set_size = 1000;
  int queries_quantity = 1000;
  std::uniform_int_distribution<int> obj(-1000000000, 1000000000);
  for (int test_counter = 0; test_counter < 10; ++test_counter) {
    std::vector<int> numbers_set;
    numbers_set.reserve(set_size);
    std::vector<int> queries;
    std::cout << "mln" << std::endl;
    queries.reserve(queries_quantity);
    std::cout << "mln" << std::endl;
    std::map<int, bool> map;
    for (int j = 0; j < set_size; ++j) {
      int number = 0;
      while (true) {
        number = obj(generator);
        if (map[number] == false) {
          map[number] = true;
          break;
        }
      }
      numbers_set .push_back(number);
    }
    for (int j = 0; j < queries_quantity; ++j) {
      queries.push_back(obj(generator));
    }

    TestFunc(numbers_set, queries);
  }
}

void TestFunc(const std::vector<int>& numbers, const std::vector<int>& queries) {
  int start = clock();
  std::vector<bool> my_answer = CheckIfElementsBelongToSet(numbers, queries);
  std::cout << "time: " << clock() - start << std::endl;
  std::vector<bool> correct_answer = SimpleSlowSolution(numbers, queries);
  if (my_answer != correct_answer) {
    std::cout << "Test failed" << std::endl;
    OutputSequence("my_answer: ", my_answer);
    OutputSequence("correct_answer: ", correct_answer);
    OutputSequence("numbers_set: ", numbers);
    OutputSequence("queries: ", queries);
    getchar();
  } else {
    std::cout << "Test passed" << std::endl;
  }
}
