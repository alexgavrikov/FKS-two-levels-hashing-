/*
 * fks.cpp
 *
 *  Created on: 04.04.2016
 *      Author: user
 */

#include "fks.h"
#include <cmath>
#include <algorithm>

HashFunction::HashFunction()
    : factor(1),
      shift(0),
      prime_modulo(1),
      image_size(1) {
}

HashFunction::HashFunction(const int64_t factor,
                           const int64_t shift,
                           const int64_t prime_modulo,
                           const int64_t image_size)
    : factor(factor),
      shift(shift),
      prime_modulo(prime_modulo),
      image_size(image_size) {
}

int HashFunction::operator()(const int argument) const {
  return ((factor * argument + shift) % prime_modulo) % image_size;
}

HashFunction GenerateRandomHashFunction(
    std::mt19937& generator,
    const int hash_function_image_size,
    const int prime_modulo) {
  static std::uniform_int_distribution<int> factor_distribution(
      1, prime_modulo - 1);
  static std::uniform_int_distribution<int> shift_distribution(
      0, prime_modulo - 1);

  return { factor_distribution(generator), shift_distribution(generator),
           prime_modulo, hash_function_image_size };
}

void PerfectHashSet::Initialize(const std::vector<int>& numbers,
                                std::mt19937& generator) {
  if (numbers.empty()) {
    return;
  }
  const int hash_function_image_size = ComputeIntegerSquare(numbers.size());
  hash_function_
      = FindHashFunction([&numbers](const HashFunction& hash_function){
                           return IsHashFunctionSuitable(hash_function,
                                                         numbers);
                         },
                         [&generator, hash_function_image_size](){
                           return GenerateRandomHashFunction(
                               generator,
                               hash_function_image_size);
                         });
  FillHashTable(numbers);
}

bool PerfectHashSet::Contains(const int number) const {
  const int number_index = hash_function_(number);
  return hash_table_[number_index] == number;
}

bool PerfectHashSet::IsEmpty() const {
  return hash_table_.empty();
}

bool PerfectHashSet::IsHashFunctionSuitable(const HashFunction& hash_function,
                                            const std::vector<int>& numbers) {
  std::vector<int> hash_table(hash_function.image_size, kEmptyNumber);
  for (const int number : numbers) {
    const int element_index = hash_function(number);
    if (hash_table[element_index] == kEmptyNumber) {
      hash_table[element_index] = number;
    } else {
      return false;
    }
  }
  return true;
}

void PerfectHashSet::FillHashTable(const std::vector<int>& numbers) {
  hash_table_.assign(hash_function_.image_size, kEmptyNumber);
  for (const int number : numbers) {
    const int element_index = hash_function_(number);
    hash_table_[element_index] = number;
  }
}

void FixedSet::Initialize(const std::vector<int>& numbers,
                          std::mt19937& generator) {
  const std::vector<int> set_to_hash = ShiftNumbers(numbers, kShiftSize);
  buckets_.resize(set_to_hash.size());
  const int hash_function_image_size = set_to_hash.size();
  hash_function_
      = FindHashFunction([&set_to_hash](const HashFunction& hash_function) {
                           return IsHashFunctionSuitable(hash_function,
                                                         set_to_hash);
                         },
                         [&generator, hash_function_image_size]() {
                           return GenerateRandomHashFunction(
                               generator,
                               hash_function_image_size);
                         });
  const std::vector<BucketData> subsets_to_hash = DistributeNumbersOnBuckets(
      set_to_hash);
  for (int subset_index = 0; subset_index < subsets_to_hash.size();
       ++subset_index) {
    buckets_[subset_index].Initialize(subsets_to_hash[subset_index], generator);
  }
}

bool FixedSet::Contains(int number) const {
  number += kShiftSize;
  const int bucket_index = hash_function_(number);
  return !buckets_[bucket_index].IsEmpty()
      && buckets_[bucket_index].Contains(number);
}

bool FixedSet::IsHashFunctionSuitable(
    const HashFunction& hash_function,
    const std::vector<int>& numbers) {
  static constexpr int kMemoryRatioThreshold = 3;
  std::vector<int> buckets_sizes(hash_function.image_size);
  for (const int number : numbers) {
    ++buckets_sizes[hash_function(number)];
  }

  int64_t squared_sizes_sum = 0;
  for (const int bucket_size : buckets_sizes) {
    squared_sizes_sum += bucket_size * bucket_size;
  }

  return squared_sizes_sum <= kMemoryRatioThreshold * hash_function.image_size;
}

std::vector<FixedSet::BucketData> FixedSet::DistributeNumbersOnBuckets(
    const std::vector<int>& numbers) {
  std::vector<BucketData> subsets(hash_function_.image_size);
  for (const int number : numbers) {
    int subset_index = hash_function_(number);
    subsets[subset_index].emplace_back(number);
  }
  return subsets;
}

std::vector<int> ShiftNumbers(std::vector<int> numbers, const int shift_size) {
  std::for_each(numbers.begin(), numbers.end(), [shift_size](int &number){
                                                  number += shift_size;
                                                });
  return numbers;
}

template <typename HashFunctionCondition, typename HashFunctionGenerator>
HashFunction FindHashFunction(HashFunctionCondition hash_function_condition,
                              HashFunctionGenerator hash_function_generator) {
  HashFunction hash_function = hash_function_generator();
  while (!hash_function_condition(hash_function)) {
    hash_function = hash_function_generator();
  }
  return hash_function;
}

int ComputeIntegerSquare(const int integer_number) {
  return integer_number * integer_number;
}

