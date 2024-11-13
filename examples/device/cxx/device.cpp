/*------------------------------------------------------------------------------
Copyright 2024 Munich Quantum Software Stack Project

Licensed under the Apache License, Version 2.0 with LLVM Exceptions (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at

https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
License for the specific language governing permissions and limitations under
the License.

SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a device implementation in C++.
 * @details This file can be used as a template for implementing a device in
 * C++. For more implemented functions, see also the \ref device5.c file.
 */

#include "cxx_qdmi/device.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct CXX_QDMI_Job_impl_d {
  int id = 0;
  QDMI_Job_Status status = QDMI_JOB_STATUS_SUBMITTED;
  size_t num_shots = 0;
  std::vector<std::string> results;
  std::vector<std::complex<double>> state_vec;
};

struct CXX_QDMI_Site_impl_d {
  size_t id;
};

struct CXX_QDMI_Operation_impl_d {
  const char *name;
};

struct CXX_QDMI_Device_State {
  QDMI_Device_Status status = QDMI_DEVICE_STATUS_OFFLINE;
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dis =
      std::uniform_int_distribution<>(0, std::numeric_limits<int>::max());
  std::bernoulli_distribution dis_bin{0.5};
  std::uniform_real_distribution<> dis_real =
      std::uniform_real_distribution<>(-1.0, 1.0);
};

namespace {
/**
 * @brief Static function to maintain the device state.
 * @return a pointer to the device state.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
CXX_QDMI_Device_State *CXX_QDMI_get_device_state() {
  static CXX_QDMI_Device_State device_state;
  return &device_state;
}

/**
 * @brief Local function to read the device status.
 * @return the current device status.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
QDMI_Device_Status CXX_QDMI_get_device_status() {
  return CXX_QDMI_get_device_state()->status;
}

/**
 * @brief Local function to set the device status.
 * @param status the new device status.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
void CXX_QDMI_set_device_status(QDMI_Device_Status status) {
  CXX_QDMI_get_device_state()->status = status;
}

/**
 * @brief Generate a random job id.
 * @return a random job id.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
int CXX_QDMI_generate_job_id() {
  auto *state = CXX_QDMI_get_device_state();
  return state->dis(state->gen);
}

/**
 * @brief Generate a random bit.
 * @return a random bit.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
bool CXX_QDMI_generate_bit() {
  auto *state = CXX_QDMI_get_device_state();
  return state->dis_bin(state->gen);
}

/**
 * @brief Generate a random real number.
 * @return a random real number.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
double CXX_QDMI_generate_real() {
  auto *state = CXX_QDMI_get_device_state();
  return state->dis_real(state->gen);
}

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
std::array<CXX_QDMI_Operation_impl_d, 4> device_operations = {
    CXX_QDMI_Operation_impl_d{"rx"}, CXX_QDMI_Operation_impl_d{"ry"},
    CXX_QDMI_Operation_impl_d{"rz"}, CXX_QDMI_Operation_impl_d{"cx"}};

std::array<CXX_QDMI_Site_impl_d, 7> device_sites = {
    CXX_QDMI_Site_impl_d{0}, CXX_QDMI_Site_impl_d{1}, CXX_QDMI_Site_impl_d{2},
    CXX_QDMI_Site_impl_d{3}, CXX_QDMI_Site_impl_d{4}};
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
} // namespace

constexpr static std::array<const CXX_QDMI_Site_impl_d *const, 20>
    // clang-format off
    DEVICE_COUPLING_MAP = {
      device_sites.data(), &device_sites[1],
      &device_sites[1], device_sites.data(),
      &device_sites[1], &device_sites[2],
      &device_sites[2], &device_sites[1],
      &device_sites[2], &device_sites[3],
      &device_sites[3], &device_sites[2],
      &device_sites[3], &device_sites[4],
      &device_sites[4], &device_sites[3],
      &device_sites[4], device_sites.data(),
      device_sites.data(), &device_sites[4]};
// clang-format on

const static std::unordered_map<const CXX_QDMI_Operation_impl_d *, double>
    OPERATION_DURATIONS = {
        {device_operations.data(), 0.01},
        {&device_operations[1], 0.01},
        {&device_operations[2], 0.01},
        {&device_operations[3], 0.1},
};

struct CXX_QDMI_Pair_hash {
  template <class T1, class T2>
  size_t operator()(const std::pair<T1, T2> &p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);
    return hash1 ^ hash2;
  }
};

const static std::unordered_map<
    const CXX_QDMI_Operation_impl_d *,
    std::unordered_map<
        std::pair<const CXX_QDMI_Site_impl_d *, const CXX_QDMI_Site_impl_d *>,
        double, CXX_QDMI_Pair_hash>>
    OPERATION_FIDELITIES = {
        {&device_operations[3],
         {{{device_sites.data(), &device_sites[1]}, 0.99},
          {{&device_sites[1], device_sites.data()}, 0.99},
          {{&device_sites[1], &device_sites[2]}, 0.98},
          {{&device_sites[2], &device_sites[1]}, 0.98},
          {{&device_sites[2], &device_sites[3]}, 0.97},
          {{&device_sites[3], &device_sites[2]}, 0.97},
          {{&device_sites[3], &device_sites[4]}, 0.96},
          {{&device_sites[4], &device_sites[3]}, 0.96},
          {{&device_sites[4], device_sites.data()}, 0.95},
          {{device_sites.data(), &device_sites[4]}, 0.95}}},
        // No need to specify single-qubit fidelities here
};

// NOLINTBEGIN(bugprone-macro-parentheses)
#define ADD_SINGLE_VALUE_PROPERTY(prop_name, prop_type, prop_value, prop,      \
                                  size, value, size_ret)                       \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((value) != nullptr) {                                                \
        if ((size) < sizeof(prop_type)) {                                      \
          return QDMI_ERROR_INVALIDARGUMENT;                                   \
        }                                                                      \
        *static_cast<prop_type *>(value) = prop_value;                         \
      }                                                                        \
      if (size_ret != nullptr) {                                               \
        *size_ret = sizeof(prop_type);                                         \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  } /// [DOXYGEN MACRO END]

#define ADD_STRING_PROPERTY(prop_name, prop_value, prop, size, value,          \
                            size_ret)                                          \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((value) != nullptr) {                                                \
        if ((size) < strlen(prop_value) + 1) {                                 \
          return QDMI_ERROR_INVALIDARGUMENT;                                   \
        }                                                                      \
        strncpy(static_cast<char *>(value), prop_value, size);                 \
        static_cast<char *>(value)[size - 1] = '\0';                           \
      }                                                                        \
      if (size_ret != nullptr) {                                               \
        *size_ret = strlen(prop_value) + 1;                                    \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  } /// [DOXYGEN MACRO END]

#define ADD_LIST_PROPERTY(prop_name, prop_type, prop_values, prop, size,       \
                          value, size_ret)                                     \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((value) != nullptr) {                                                \
        if ((size) < (prop_values).size() * sizeof(prop_type)) {               \
          return QDMI_ERROR_INVALIDARGUMENT;                                   \
        }                                                                      \
        memcpy(static_cast<void *>(value),                                     \
               static_cast<const void *>((prop_values).data()),                \
               (prop_values).size() * sizeof(prop_type));                      \
      }                                                                        \
      if (size_ret != nullptr) {                                               \
        *size_ret = (prop_values).size() * sizeof(prop_type);                  \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  } /// [DOXYGEN MACRO END]
// NOLINTEND(bugprone-macro-parentheses)

int CXX_QDMI_query_get_sites_dev(const size_t num_entries, CXX_QDMI_Site *sites,
                                 size_t *num_sites) {
  if ((sites != nullptr && num_entries == 0) ||
      (sites == nullptr && num_sites == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (sites != nullptr) {
    for (size_t i = 0; i < std::min(num_entries, device_sites.size()); ++i) {
      sites[i] = &device_sites[i];
    }
  }
  if (num_sites != nullptr) {
    *num_sites = device_sites.size();
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_query_get_operations_dev(const size_t num_entries,
                                      CXX_QDMI_Operation *operations,
                                      size_t *num_operations) {
  if ((operations != nullptr && num_entries == 0) ||
      (operations == nullptr && num_operations == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (operations != nullptr) {
    for (size_t i = 0; i < std::min(num_entries, device_operations.size());
         ++i) {
      operations[i] = &device_operations[i];
    }
  }
  if (num_operations != nullptr) {
    *num_operations = device_operations.size();
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_query_device_property_dev(const QDMI_Device_Property prop,
                                       const size_t size, void *value,
                                       size_t *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX ||
      (value == nullptr && size_ret == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_NAME, "C++ Device with 5 qubits",
                      prop, size, value, size_ret)
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_VERSION, "0.1.0", prop, size, value,
                      size_ret)
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_LIBRARYVERSION, "1.0.0b2", prop,
                      size, value, size_ret)
  ADD_SINGLE_VALUE_PROPERTY(QDMI_DEVICE_PROPERTY_QUBITSNUM, size_t, 5, prop,
                            size, value, size_ret)
  ADD_SINGLE_VALUE_PROPERTY(QDMI_DEVICE_PROPERTY_STATUS, QDMI_Device_Status,
                            CXX_QDMI_get_device_status(), prop, size, value,
                            size_ret)
  ADD_LIST_PROPERTY(QDMI_DEVICE_PROPERTY_COUPLINGMAP, CXX_QDMI_Site,
                    DEVICE_COUPLING_MAP, prop, size, value, size_ret)
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_query_site_property_dev(CXX_QDMI_Site site,
                                     const QDMI_Site_Property prop,
                                     const size_t size, void *value,
                                     size_t *size_ret) {
  if (site == nullptr || prop >= QDMI_SITE_PROPERTY_MAX ||
      (value == nullptr && size_ret == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  ADD_SINGLE_VALUE_PROPERTY(QDMI_SITE_PROPERTY_TIME_T1, double, 1000.0, prop,
                            size, value, size_ret)
  ADD_SINGLE_VALUE_PROPERTY(QDMI_SITE_PROPERTY_TIME_T2, double, 100000.0, prop,
                            size, value, size_ret)
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_query_operation_property_dev(
    CXX_QDMI_Operation operation, size_t num_sites, const CXX_QDMI_Site *sites,
    QDMI_Operation_Property prop, size_t size, void *value, size_t *size_ret) {
  if (prop >= QDMI_OPERATION_PROPERTY_MAX || operation == nullptr ||
      (sites != nullptr && num_sites == 0) ||
      (value == nullptr && size_ret == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  // General properties
  ADD_STRING_PROPERTY(QDMI_OPERATION_PROPERTY_NAME, operation->name, prop, size,
                      value, size_ret)
  if (strcmp(operation->name, "cx") == 0) {
    if (sites != nullptr && num_sites != 2) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_DURATION, double,
                              OPERATION_DURATIONS.at(operation), prop, size,
                              value, size_ret)
    if (sites == nullptr) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_QUBITSNUM, size_t, 2,
                                prop, size, value, size_ret)
      return QDMI_ERROR_NOTSUPPORTED;
    }
    const std::pair site_pair = {sites[0], sites[1]};
    if (site_pair.first == site_pair.second) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    const auto it = OPERATION_FIDELITIES.find(operation);
    if (it == OPERATION_FIDELITIES.end()) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    const auto fit = it->second.find(site_pair);
    if (fit == it->second.end()) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double,
                              fit->second, prop, size, value, size_ret)
  } else if (strcmp(operation->name, "rx") == 0 ||
             strcmp(operation->name, "ry") == 0 ||
             strcmp(operation->name, "rz") == 0) {
    if (sites != nullptr && num_sites != 1) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_DURATION, double, 0.01,
                              prop, size, value, size_ret)
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_QUBITSNUM, size_t, 1,
                              prop, size, value, size_ret)
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double, 0.999,
                              prop, size, value, size_ret)
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_control_create_job_dev(const QDMI_Program_Format format,
                                    const size_t size, const void *prog,
                                    CXX_QDMI_Job *job) {
  if (CXX_QDMI_get_device_status() != QDMI_DEVICE_STATUS_IDLE) {
    return QDMI_ERROR_FATAL;
  }
  if (size == 0 || prog == nullptr || job == nullptr) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (format != QDMI_PROGRAM_FORMAT_QASM2 &&
      format != QDMI_PROGRAM_FORMAT_QIRSTRING &&
      format != QDMI_PROGRAM_FORMAT_QIRMODULE) {
    return QDMI_ERROR_NOTSUPPORTED;
  }

  *job = new CXX_QDMI_Job_impl_d;
  // set job id to random number for demonstration purposes
  (*job)->id = CXX_QDMI_generate_job_id();
  (*job)->status = QDMI_JOB_STATUS_CREATED;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_control_set_parameter_dev(CXX_QDMI_Job job,
                                       const QDMI_Job_Parameter param,
                                       const size_t size, const void *value) {
  if (job == nullptr || param >= QDMI_JOB_PARAMETER_MAX || size == 0 ||
      job->status != QDMI_JOB_STATUS_CREATED) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (param == QDMI_JOB_PARAMETER_SHOTS_NUM) {
    job->num_shots = *static_cast<const size_t *>(value);
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_control_submit_job_dev(CXX_QDMI_Job job) {
  if (job == nullptr || job->status != QDMI_JOB_STATUS_CREATED) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  CXX_QDMI_set_device_status(QDMI_DEVICE_STATUS_BUSY);
  job->status = QDMI_JOB_STATUS_SUBMITTED;
  // here, the actual submission of the problem to the device would happen
  // ...
  // set job status to running for demonstration purposes
  job->status = QDMI_JOB_STATUS_RUNNING;
  // generate random result data
  size_t num_qubits = 0;
  CXX_QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM,
                                     sizeof(size_t), &num_qubits, nullptr);
  job->results.clear();
  job->results.reserve(job->num_shots);
  for (size_t i = 0; i < job->num_shots; ++i) {
    // generate random bitstring
    std::string result(num_qubits, '0');
    std::generate(result.begin(), result.end(),
                  [&]() { return CXX_QDMI_generate_bit() ? '1' : '0'; });
    job->results.emplace_back(std::move(result));
  }
  // Generate random complex numbers and calculate the norm
  job->state_vec.clear();
  job->state_vec.reserve(1U << num_qubits);
  double norm = 0.0;
  for (size_t i = 0; i < 1U << num_qubits; ++i) {
    const auto &c = job->state_vec.emplace_back(CXX_QDMI_generate_real(),
                                                CXX_QDMI_generate_real());
    norm += std::norm(c);
  }
  // Normalize the vector
  norm = std::sqrt(norm);
  for (auto &c : job->state_vec) {
    c /= norm;
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_control_cancel_dev(CXX_QDMI_Job job) {
  if (job->status == QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }

  job->status = QDMI_JOB_STATUS_CANCELLED;
  CXX_QDMI_set_device_status(QDMI_DEVICE_STATUS_IDLE);
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_control_check_dev(CXX_QDMI_Job job, QDMI_Job_Status *status) {
  // randomly decide whether job is done or not
  if (job->status == QDMI_JOB_STATUS_RUNNING && CXX_QDMI_generate_bit()) {
    CXX_QDMI_set_device_status(QDMI_DEVICE_STATUS_IDLE);
    job->status = QDMI_JOB_STATUS_DONE;
  }
  *status = job->status;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_control_wait_dev(CXX_QDMI_Job job) {
  job->status = QDMI_JOB_STATUS_DONE;
  CXX_QDMI_set_device_status(QDMI_DEVICE_STATUS_IDLE);
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_control_get_data_dev(CXX_QDMI_Job job,
                                  const QDMI_Job_Result result,
                                  const size_t size, void *data,
                                  size_t *size_ret) {
  if (job->status != QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (result == QDMI_JOB_RESULT_SHOTS) {
    const size_t bitstring_size =
        job->results.empty() ? 0 : job->results.front().length();
    const size_t req_size = job->results.size() * (bitstring_size + 1);
    if (data != nullptr) {
      if (size < req_size) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      auto *data_ptr = static_cast<char *>(data);
      for (auto it = job->results.begin(); it != job->results.end(); ++it) {
        data_ptr = std::copy(it->begin(), it->end(), data_ptr);
        if (std::next(it) != job->results.end()) {
          *data_ptr++ = ','; // Add comma separator
        } else {
          *data_ptr++ = '\0'; // Add null terminator at the end
        }
      }
    }
    if (size_ret != nullptr) {
      *size_ret = req_size;
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_HIST_KEYS ||
      result == QDMI_JOB_RESULT_HIST_VALUES) {
    // Count unique elements
    std::map<std::string, size_t> hist;
    for (const auto &shot : job->results) {
      hist[shot]++;
    }
    if (result == QDMI_JOB_RESULT_HIST_KEYS) {
      const size_t bitstring_size =
          job->results.empty() ? 0 : job->results.front().length();
      const size_t req_size = hist.size() * (bitstring_size + 1);
      if (size_ret != nullptr) {
        *size_ret = req_size;
      }
      if (data != nullptr) {
        if (size < req_size) {
          return QDMI_ERROR_INVALIDARGUMENT;
        }
        char *data_ptr = static_cast<char *>(data);
        for (const auto &[bitstring, count] : hist) {
          std::copy(bitstring.begin(), bitstring.end(), data_ptr);
          data_ptr += bitstring.length();
          *data_ptr++ = ',';
        }
        *(data_ptr - 1) = '\0'; // Replace last comma with null terminator
      }
    } else {
      const size_t req_size = hist.size() * sizeof(size_t);
      if (size_ret != nullptr) {
        *size_ret = req_size;
      }
      if (data != nullptr) {
        if (size < req_size) {
          return QDMI_ERROR_INVALIDARGUMENT;
        }
        auto *data_ptr = static_cast<size_t *>(data);
        for (const auto &[_, count] : hist) {
          *data_ptr++ = count;
        }
      }
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_STATEVECTOR_DENSE) {
    const size_t req_size = job->state_vec.size() * 2 * sizeof(double);
    if (data != nullptr) {
      if (size < req_size) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      std::memcpy(data, job->state_vec.data(), req_size);
    }
    if (size_ret != nullptr) {
      *size_ret = req_size;
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_STATEVECTOR_SPARSE_KEYS ||
      result == QDMI_JOB_RESULT_STATEVECTOR_SPARSE_VALUES ||
      result == QDMI_JOB_RESULT_PROBABILITIES_SPARSE_KEYS ||
      result == QDMI_JOB_RESULT_PROBABILITIES_SPARSE_VALUES) {
    // count non-zero elements
    size_t count = 0;
    for (const auto &c : job->state_vec) {
      if (c != 0.) {
        ++count;
      }
    }
    const auto num_qubits =
        static_cast<size_t>(std::log2(job->state_vec.size()));

    if (result == QDMI_JOB_RESULT_STATEVECTOR_SPARSE_KEYS ||
        result == QDMI_JOB_RESULT_PROBABILITIES_SPARSE_KEYS) {
      const size_t req_size = count * (num_qubits + 1);
      if (data != nullptr) {
        if (size < req_size) {
          return QDMI_ERROR_INVALIDARGUMENT;
        }
        auto *data_ptr = static_cast<char *>(data);
        for (size_t i = 0; i < job->state_vec.size(); ++i) {
          if (job->state_vec[i] != 0.0) {
            for (size_t j = 0; j < num_qubits; ++j) {
              *data_ptr++ =
                  ((i & (1 << (num_qubits - j - 1))) != 0U) ? '1' : '0';
            }
            *data_ptr++ = ',';
          }
        }
        *(data_ptr - 1) = '\0'; // Replace last comma with null terminator
      }
      if (size_ret != nullptr) {
        *size_ret = req_size;
      }
      return QDMI_SUCCESS;
    }

    if (result == QDMI_JOB_RESULT_STATEVECTOR_SPARSE_VALUES) {
      const size_t req_size = count * 2 * sizeof(double);
      if (data != nullptr) {
        if (size < req_size) {
          return QDMI_ERROR_INVALIDARGUMENT;
        }
        auto *data_ptr = static_cast<double *>(data);
        for (auto c : job->state_vec) {
          if (c != 0.) {
            *data_ptr++ = c.real();
            *data_ptr++ = c.imag();
          }
        }
      }
      if (size_ret != nullptr) {
        *size_ret = req_size;
      }
    } else {
      const size_t req_size = count * sizeof(double);
      if (data != nullptr) {
        if (size < req_size) {
          return QDMI_ERROR_INVALIDARGUMENT;
        }
        auto *data_ptr = static_cast<double *>(data);
        for (const auto &c : job->state_vec) {
          *data_ptr++ = std::norm(c);
        }
      }
      if (size_ret != nullptr) {
        *size_ret = req_size;
      }
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_PROBABILITIES_DENSE) {
    const size_t req_size = job->state_vec.size() * sizeof(double);
    if (data != nullptr) {
      if (size < req_size) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      auto *data_ptr = static_cast<double *>(data);
      for (const auto &c : job->state_vec) {
        *data_ptr++ = std::norm(c);
      }
    }
    if (size_ret != nullptr) {
      *size_ret = req_size;
    }
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

void CXX_QDMI_control_free_job_dev(CXX_QDMI_Job job) { delete job; }

int CXX_QDMI_control_initialize_dev() {
  CXX_QDMI_set_device_status(QDMI_DEVICE_STATUS_IDLE);
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int CXX_QDMI_control_finalize_dev() {
  CXX_QDMI_set_device_status(QDMI_DEVICE_STATUS_OFFLINE);
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]
