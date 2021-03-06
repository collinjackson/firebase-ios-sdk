/*
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FIRESTORE_CORE_TEST_FIREBASE_FIRESTORE_IMMUTABLE_TESTING_H_
#define FIRESTORE_CORE_TEST_FIREBASE_FIRESTORE_IMMUTABLE_TESTING_H_

#include <algorithm>
#include <utility>
#include <vector>

#include "Firestore/core/src/firebase/firestore/util/secure_random.h"
#include "gtest/gtest.h"

namespace firebase {
namespace firestore {
namespace immutable {

template <typename Container, typename K>
testing::AssertionResult NotFound(const Container& map, const K& key) {
  auto found = map.find(key);
  if (found == map.end()) {
    return testing::AssertionSuccess();
  } else {
    return testing::AssertionFailure()
           << "Should not have found (" << found->first << ", " << found->second
           << ")";
  }
}

template <typename Container, typename K, typename V>
testing::AssertionResult Found(const Container& map,
                               const K& key,
                               const V& expected) {
  auto found = map.find(key);
  if (found == map.end()) {
    return testing::AssertionFailure() << "Did not find key " << key;
  }
  if (found->second == expected) {
    return testing::AssertionSuccess();
  } else {
    return testing::AssertionFailure() << "Found entry was (" << found->first
                                       << ", " << found->second << ")";
  }
}

/** Creates an empty vector (for readability). */
inline std::vector<int> Empty() {
  return {};
}

/**
 * Creates a vector containing a sequence of integers from the given starting
 * element up to, but not including, the given end element, with values
 * incremented by the given step.
 *
 * If step is negative the sequence is in descending order (but still starting
 * at start and ending before end).
 */
inline std::vector<int> Sequence(int start, int end, int step = 1) {
  std::vector<int> result;
  if (step > 0) {
    for (int i = start; i < end; i += step) {
      result.push_back(i);
    }
  } else {
    for (int i = start; i > end; i += step) {
      result.push_back(i);
    }
  }
  return result;
}

/**
 * Creates a vector containing a sequence of integers with the given number of
 * elements, from zero up to, but not including the given value.
 */
inline std::vector<int> Sequence(int num_elements) {
  return Sequence(0, num_elements);
}

/**
 * Creates a copy of the given vector with contents shuffled randomly.
 */
inline std::vector<int> Shuffled(const std::vector<int>& values) {
  std::vector<int> result{values};
  util::SecureRandom rng;
  std::shuffle(result.begin(), result.end(), rng);
  return result;
}

/**
 * Creates a copy of the given vector with contents sorted.
 */
inline std::vector<int> Sorted(const std::vector<int>& values) {
  std::vector<int> result{values};
  std::sort(result.begin(), result.end());
  return result;
}

/**
 * Creates a copy of the given vector with contents reversed.
 */
inline std::vector<int> Reversed(const std::vector<int>& values) {
  std::vector<int> result{values};
  std::reverse(result.begin(), result.end());
  return result;
}

/**
 * Creates a vector of pairs where each pair has the same first and second
 * corresponding to an element in the given vector.
 */
inline std::vector<std::pair<int, int>> Pairs(const std::vector<int>& values) {
  std::vector<std::pair<int, int>> result;
  for (auto&& value : values) {
    result.emplace_back(value, value);
  }
  return result;
}

/**
 * Creates a SortedMap by inserting a pair for each value in the vector.
 * Each pair will have the same key and value.
 */
template <typename Container>
Container ToMap(const std::vector<int>& values) {
  Container result;
  for (auto&& value : values) {
    result = result.insert(value, value);
  }
  return result;
}

/**
 * Appends the contents of the given container to a new vector.
 */
template <typename Container>
std::vector<typename Container::value_type> Append(const Container& container) {
  return {container.begin(), container.end()};
}

#define ASSERT_SEQ_EQ(x, y) ASSERT_EQ((x), Append(y));
#define EXPECT_SEQ_EQ(x, y) EXPECT_EQ((x), Append(y));

}  // namespace immutable
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_TEST_FIREBASE_FIRESTORE_IMMUTABLE_TESTING_H_
