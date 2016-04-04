# FKS-two-levels-hashing-
Classes implementing FKS hashing. And solving a problem using FKS.

The following problem has been solved:
Реализуйте cледующий класс для хранения множества целых чисел:
class FixedSet { public: FixedSet(); void Initialize(const vector<int>& numbers); bool Contains(int number) const; };
FixedSet получает при вызове Initialize набор целых чисел, который впоследствии и будет хранить. Набор чисел не будет изменяться с течением времени (до следующего вызова Initialize). Операция Contains возвращает true, если число number содержится в наборе. Мат. ожидание времени работы Initialize должно составлять O(n), где n — количество чисел в numbers. Затраты памяти должны быть порядка O(n) в худшем случае. Операция Contains должна выполняться за O(1) в худшем случае.
С помощью этого класса решите модельную задачу: во входе будет дано множество различных чисел, а затем множество запросов — целых чисел. Необходимо для каждого запроса определить, лежит ли число из запроса в множестве.
