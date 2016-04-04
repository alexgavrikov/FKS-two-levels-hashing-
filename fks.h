/*
 * fks.h
 *
 *  Created on: 04.04.2016
 *      Author: user
 */

#ifndef FKS_H_
#define FKS_H_

#include <cstdint>
#include <random>
#include <vector>

struct HashFunction {
  int64_t factor;
  int64_t shift;
  int64_t prime_modulo;
  int64_t image_size;

  HashFunction();
  HashFunction(const int64_t factor,
               const int64_t shift,
               const int64_t prime_modulo,
               const int64_t image_size);
  int operator()(const int argument) const;
};

static constexpr int kPrimeModulo = 2000000011;

HashFunction GenerateRandomHashFunction(
    std::mt19937& generator,
    const int hash_function_image_size,
    const int prime_modulo = kPrimeModulo);

class AbstractHashSet {
 public:
  virtual ~AbstractHashSet() {
  }
  virtual void Initialize(const std::vector<int>& numbers,
                          std::mt19937& generator) = 0;
  virtual bool Contains(int number) const = 0;

 protected:
  AbstractHashSet() {
  }
  HashFunction hash_function_;
};

class PerfectHashSet : AbstractHashSet {
 public:
  PerfectHashSet() {
  }
  void Initialize(const std::vector<int>& numbers,
                  std::mt19937& generator) override;
  bool Contains(const int number) const override;
  bool IsEmpty() const;

 private:
  static bool IsHashFunctionSuitable(const HashFunction& hash_function,
                                     const std::vector<int>& numbers);

  void FillHashTable(const std::vector<int>& numbers);

  std::vector<int> hash_table_;
};

class FixedSet : AbstractHashSet {
 public:
  FixedSet() {
  }
  void Initialize(const std::vector<int>& numbers,
                  std::mt19937& generator) override;
  bool Contains(int number) const override;

 private:
  static constexpr int kShiftSize = 1000000000;

  static bool IsHashFunctionSuitable(
      const HashFunction& hash_function,
      const std::vector<int>& numbers);

  using BucketData = std::vector<int>;
  std::vector<BucketData> DistributeNumbersOnBuckets(
      const std::vector<int>& numbers);

  std::vector<PerfectHashSet> buckets_;
};

static constexpr int kEmptyNumber = -1;

std::vector<int> ShiftNumbers(std::vector<int> numbers, const int shift_size);

// The function finds hash-function satisfying hash_function_condition.
// Precisely, it will generate hash-functions till it finds hash_function for
// which hash_function_condition(hash_function, numbers) == true.
template <typename HashFunctionCondition, typename HashFunctionGenerator>
HashFunction FindHashFunction(HashFunctionCondition hash_function_condition,
                              HashFunctionGenerator hash_function_generator);

int ComputeIntegerSquare(const int integer_number);


#endif /* FKS_H_ */
