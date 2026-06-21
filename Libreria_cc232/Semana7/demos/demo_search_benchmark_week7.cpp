#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Capitulo7.h"

namespace {

using Clock = std::chrono::steady_clock;

template <typename Tree>
long long benchmarkContains(Tree& tree, const std::vector<int>& queries, std::size_t& hits) {
  const auto start = Clock::now();
  hits = 0;

  for (int query : queries) {
    if (tree.contains(query)) {
      ++hits;
    }
  }

  const auto finish = Clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

template <typename Tree>
void fillTree(Tree& tree, const std::vector<int>& values) {
  for (int value : values) {
    tree.insert(value);
  }
}

void fillTree(ods::RedBlackTree1<int>& tree, const std::vector<int>& values) {
  for (int value : values) {
    tree.add(value);
  }
}

std::vector<int> makeRange(int n) {
  std::vector<int> values;
  values.reserve(n);
  for (int i = 1; i <= n; ++i) values.push_back(i);
  return values;
}

std::vector<int> makeQueries(const std::vector<int>& values, int missOffset) {
  std::vector<int> queries = values;
  queries.insert(queries.end(), values.begin(), values.end());
  for (int value : values) queries.push_back(value + missOffset);
  return queries;
}

template <typename Tree>
void runCase(const std::string& title, const std::vector<int>& insertOrder,
             const std::vector<int>& queries) {
  Tree tree;
  fillTree(tree, insertOrder);

  std::size_t hits = 0;
  const long long elapsed = benchmarkContains(tree, queries, hits);

  std::cout << title << " -> time(us)=" << elapsed
            << ", hits=" << hits << '/' << queries.size() << '\n';
}

template <>
void runCase<ods::RedBlackTree1<int>>(const std::string& title,
                                      const std::vector<int>& insertOrder,
                                      const std::vector<int>& queries) {
  ods::RedBlackTree1<int> tree;
  fillTree(tree, insertOrder);

  std::size_t hits = 0;
  const long long elapsed = benchmarkContains(tree, queries, hits);

  std::cout << title << " -> time(us)=" << elapsed
            << ", hits=" << hits << '/' << queries.size() << '\n';
}

void runScenario(int n, std::mt19937& rng) {
  std::vector<int> ordered = makeRange(n);
  std::vector<int> shuffled = ordered;
  std::shuffle(shuffled.begin(), shuffled.end(), rng);
  std::vector<int> queries = makeQueries(ordered, n * 10);
  std::shuffle(queries.begin(), queries.end(), rng);

  std::cout << "n = " << n << '\n';

  std::cout << "Caso ordenado" << '\n';
  runCase<ods::BST<int>>("BST", ordered, queries);
  runCase<ods::AVL<int>>("AVL", ordered, queries);
  runCase<ods::RedBlackTree1<int>>("RedBlack", ordered, queries);

  std::cout << "Caso aleatorio" << '\n';
  runCase<ods::BST<int>>("BST", shuffled, queries);
  runCase<ods::AVL<int>>("AVL", shuffled, queries);
  runCase<ods::RedBlackTree1<int>>("RedBlack", shuffled, queries);

  std::cout << '\n';
}

}  // namespace

int main() {
  std::mt19937 rng(20260621);

  for (int n : {1000, 5000, 10000}) {
    runScenario(n, rng);
  }
}