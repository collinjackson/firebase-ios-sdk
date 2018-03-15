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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_TYPES_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_TYPES_H_

#include <stdint.h>

namespace firebase {
namespace firestore {
namespace model {

/**
 * BatchId is a locally assigned ID for a batch of mutations that have been
 * applied.
 */
typedef int32_t BatchId;

typedef int32_t TargetId;

}  // namespace model
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_TYPES_H_
