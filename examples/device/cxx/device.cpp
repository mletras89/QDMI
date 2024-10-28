/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a device implementation in C++.
 * @details This file can be used as a template for implementing a device in
 * C++. For more implemented functions, see also the \ref device5.c file.
 */

#include "qdmi/device.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <functional>
#include <limits>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct QDMI_Job_impl_d {
  int id = 0;
  QDMI_Job_Status status = QDMI_JOB_STATUS_SUBMITTED;
  int num_shots = 0;
  std::vector<std::string> results;
  std::bernoulli_distribution binary_dist{0.5};
};

struct QDMI_Site_impl_d {
  int id;
};

struct QDMI_Operation_impl_d {
  std::string name;
};

struct QDMI_Device_State {
  QDMI_Device_Status status = QDMI_DEVICE_STATUS_OFFLINE;
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dis;
};

QDMI_Device_State device_state;

constexpr static std::array<QDMI_Site, 7> device_sites = {
    new QDMI_Site_impl_d{0}, new QDMI_Site_impl_d{1}, new QDMI_Site_impl_d{2},
    new QDMI_Site_impl_d{3}, new QDMI_Site_impl_d{4}};

constexpr static std::array<QDMI_Operation, 4> device_operations = {
    new QDMI_Operation_impl_d{"rx"}, new QDMI_Operation_impl_d{"ry"},
    new QDMI_Operation_impl_d{"rz"}, new QDMI_Operation_impl_d{"cx"}};

#define ADD_SINGLE_VALUE_PROPERTY(prop_name, prop_type, prop_value, prop,      \
                                  size, value, size_ret)                       \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((size) < sizeof(prop_type)) {                                        \
        return QDMI_ERROR_INVALIDARGUMENT;                                     \
      }                                                                        \
      if ((value) != nullptr) {                                                \
        *static_cast<prop_type *>(value) = prop_value;                         \
      }                                                                        \
      if ((size_ret) != nullptr) {                                             \
        *(size_ret) = sizeof(prop_type);                                       \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  }

#define ADD_STRING_PROPERTY(prop_name, prop_value, prop, size, value,          \
                            size_ret)                                          \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((size) < (prop_value).length() + 1) {                                \
        return QDMI_ERROR_INVALIDARGUMENT;                                     \
      }                                                                        \
      if ((value) != nullptr) {                                                \
        strcpy(static_cast<char *>(value), (prop_value).c_str());              \
      }                                                                        \
      if ((size_ret) != nullptr) {                                             \
        *(size_ret) = static_cast<int>((prop_value).length()) + 1;             \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  }

#define ADD_LIST_PROPERTY(prop_name, prop_type, prop_values, prop, size,       \
                          value, size_ret)                                     \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((size) < (prop_values).size() * sizeof(prop_type)) {                 \
        return QDMI_ERROR_INVALIDARGUMENT;                                     \
      }                                                                        \
      if ((value) != nullptr) {                                                \
        memcpy(static_cast<void *>(value),                                     \
               static_cast<const void *>((prop_values).data()),                \
               (prop_values).size() * sizeof(prop_type));                      \
      }                                                                        \
      if ((size_ret) != nullptr) {                                             \
        *(size_ret) = (int)((prop_values).size() * sizeof(prop_type));         \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  }

int QDMI_query_get_sites_dev(int num_entries, QDMI_Site *sites,
                             int *num_sites) {
  if ((sites != nullptr && num_entries <= 0) ||
      (sites == nullptr && num_sites == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (sites != nullptr) {
    memcpy(static_cast<void *>(sites),
           static_cast<const void *>(device_sites.data()),
           std::min(num_entries, static_cast<int>(device_sites.size())) *
               sizeof(QDMI_Site));
  }
  if (num_sites != nullptr) {
    *num_sites = static_cast<int>(device_sites.size());
  }
  return QDMI_SUCCESS;
}

int QDMI_query_get_operations_dev(int num_entries, QDMI_Operation *operations,
                                  int *num_operations) {
  if ((operations != nullptr && num_entries <= 0) ||
      (operations == nullptr && num_operations == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (operations != nullptr) {
    memcpy(static_cast<void *>(operations),
           static_cast<const void *>(device_operations.data()),
           std::min(static_cast<std::size_t>(num_entries),
                    device_operations.size()) *
               sizeof(QDMI_Operation));
  }
  if (num_operations != nullptr) {
    *num_operations = static_cast<int>(device_operations.size());
  }
  return QDMI_SUCCESS;
}

int QDMI_query_device_property_dev(QDMI_Device_Property prop, int size,
                                   void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX ||
      (value == nullptr && size_ret == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_NAME,
                      std::string("Device with 5 qubits"), prop, size, value,
                      size_ret);
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_VERSION, std::string("0.1.0"), prop,
                      size, value, size_ret);
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_LIBRARYVERSION,
                      std::string("1.0.0b1"), prop, size, value, size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_DEVICE_PROPERTY_QUBITSNUM, int, 5, prop, size,
                            value, size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_DEVICE_PROPERTY_STATUS, QDMI_Device_Status,
                            device_state.status, prop, size, value, size_ret);
  const std::vector<std::pair<QDMI_Site, QDMI_Site>> edges = {
      {device_sites[0], device_sites[1]},
      {device_sites[1], device_sites[2]},
      {device_sites[2], device_sites[3]},
      {device_sites[3], device_sites[4]},
      {device_sites[4], device_sites[0]}};
  ADD_LIST_PROPERTY(
      QDMI_DEVICE_PROPERTY_COUPLINGMAP, int,
      (std::accumulate(edges.cbegin(), edges.cend(), std::vector<int>(),
                       [](auto &acc, const auto e) {
                         acc.emplace_back(e.first);
                         acc.emplace_back(e.second);
                         return acc;
                       })),
      prop, size, value, size_ret);
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_query_site_property_dev(QDMI_Site site, QDMI_Site_Property prop,
                                 int size, void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX ||
      (value == nullptr && size_ret == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  ADD_SINGLE_VALUE_PROPERTY(QDMI_SITE_PROPERTY_TIME_T1, double, 1000.0, prop,
                            size, value, size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_SITE_PROPERTY_TIME_T2, double, 100000.0, prop,
                            size, value, size_ret);
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);
    return hash1 ^ hash2;
  }
}; /// [DOXYGEN FUNCTION END]

int QDMI_query_operation_property_dev(QDMI_Operation operation, int num_sites,
                                      const QDMI_Site *sites,
                                      QDMI_Operation_Property prop, int size,
                                      void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX || operation == nullptr ||
      (sites != nullptr && num_sites <= 0) ||
      (value == nullptr && size_ret == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  // General properties
  ADD_STRING_PROPERTY(QDMI_OPERATION_PROPERTY_NAME, operation->name, prop, size,
                      value, size_ret);
  constexpr static std::unordered_map<QDMI_Operation, double>
      operation_durations = {
          {device_operations[0], 0.1},
          {device_operations[1], 0.01},
          {device_operations[2], 0.01},
          {device_operations[3], 0.01},
      };
  constexpr static std::unordered_map<
      QDMI_Operation,
      std::unordered_map<std::pair<QDMI_Site, QDMI_Site>, double, pair_hash>>
      operation_fidelities = {
          {device_operations[0],
           {{{device_sites[0], device_sites[1]}, 0.99},
            {{device_sites[1], device_sites[0]}, 0.99},
            {{device_sites[1], device_sites[2]}, 0.98},
            {{device_sites[2], device_sites[1]}, 0.98},
            {{device_sites[2], device_sites[3]}, 0.97},
            {{device_sites[3], device_sites[2]}, 0.97},
            {{device_sites[3], device_sites[4]}, 0.96},
            {{device_sites[4], device_sites[3]}, 0.96},
            {{device_sites[4], device_sites[0]}, 0.95},
            {{device_sites[0], device_sites[4]}, 0.95}}},
          // No need to specify single-qubit fidelities here
      };
  if (operation->name == "cx") {
    if (sites != nullptr && num_sites != 2) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_DURATION, double,
                              operation_durations.at(operation), prop, size,
                              value, size_ret);
    if (sites == nullptr) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_QUBITSNUM, int, 2, prop,
                                size, value, size_ret);
      return QDMI_ERROR_NOTSUPPORTED;
    }
    const std::pair site_pair = {sites[0], sites[1]};
    if (site_pair.first == site_pair.second) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    const auto it = operation_fidelities.find(operation);
    if (it == operation_fidelities.end()) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    const auto fit = it->second.find(site_pair);
    if (fit == it->second.end()) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double,
                              fit->second, prop, size, value, size_ret);
  } else if (operation->name == "rx" || operation->name == "ry" ||
             operation->name == "rz") {
    if (sites != nullptr && num_sites != 1) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_DURATION, double, 0.01,
                              prop, size, value, size_ret);
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_QUBITSNUM, int, 1, prop,
                              size, value, size_ret);
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double, 0.999,
                              prop, size, value, size_ret);
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_create_job_dev(const QDMI_Program_Format format,
                                const int size, const void *prog,
                                QDMI_Job *job) {
  if (device_state.status != QDMI_DEVICE_STATUS_IDLE) {
    return QDMI_ERROR_FATAL;
  }
  if (format == QDMI_PROGRAM_FORMAT_QASM2) {
    device_state.status = QDMI_DEVICE_STATUS_BUSY;
    *job = new QDMI_Job_impl_d;
    // set job id to current time for demonstration purposes
    (*job)->id = device_state.dis(device_state.gen);
    (*job)->status = QDMI_JOB_STATUS_CREATED;
    return QDMI_SUCCESS;
  }
  if (format == QDMI_PROGRAM_FORMAT_QIRSTRING) {
    device_state.status = QDMI_DEVICE_STATUS_BUSY;
    *job = new QDMI_Job_impl_d;
    // set job id to current time for demonstration purposes
    (*job)->id = device_state.dis(device_state.gen);
    (*job)->status = QDMI_JOB_STATUS_CREATED;
    return QDMI_SUCCESS;
  }
  if (format == QDMI_PROGRAM_FORMAT_QIRMODULE) {
    device_state.status = QDMI_DEVICE_STATUS_BUSY;
    *job = new QDMI_Job_impl_d;
    // set job id to current time for demonstration purposes
    (*job)->id = device_state.dis(device_state.gen);
    (*job)->status = QDMI_JOB_STATUS_CREATED;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_set_parameter_dev(QDMI_Job job, const QDMI_Job_Parameter param,
                                   const int size, const void *value) {
  if (job == nullptr || param >= QDMI_JOB_PARAMETER_MAX || size <= 0) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (param == QDMI_JOB_PARAMETER_SHOTS_NUM) {
    job->num_shots = *static_cast<const int *>(value);
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
}

int QDMI_control_submit_job_dev(QDMI_Job job) {
  device_state.status = QDMI_DEVICE_STATUS_BUSY;
  job->status = QDMI_JOB_STATUS_SUBMITTED;
  // here, the actual submission of the problem to the device would happen
  // ...
  // set job status to running for demonstration purposes
  job->status = QDMI_JOB_STATUS_RUNNING;
  // generate random result data
  int num_qubits = 0;
  QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                 &num_qubits, nullptr);
  job->results.clear();
  job->results.reserve(job->num_shots);
  for (int i = 0; i < job->num_shots; i++) {
    // generate random 5-bit string
    std::string result(num_qubits, '0');
    std::generate(result.begin(), result.end(), [&]() {
      return device_state.dis(device_state.gen) % 2 ? '1' : '0';
    });
    job->results.emplace_back(std::move(result));
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_cancel_dev(QDMI_Job job) {
  if (job->status == QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }

  job->status = QDMI_JOB_STATUS_CANCELLED;
  device_state.status = QDMI_DEVICE_STATUS_IDLE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  // randomly decide whether job is done or not
  if (job->status == QDMI_JOB_STATUS_RUNNING &&
      job->binary_dist(device_state.gen)) {
    device_state.status = QDMI_DEVICE_STATUS_IDLE;
    job->status = QDMI_JOB_STATUS_DONE;
  }
  *status = job->status;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_wait_dev(QDMI_Job job) {
  job->status = QDMI_JOB_STATUS_DONE;
  device_state.status = QDMI_DEVICE_STATUS_IDLE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_get_data_dev(QDMI_Job job, const QDMI_Job_Result result,
                              const int size, void *data, int *size_ret) {
  if (job->status != QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (result == QDMI_JOB_RESULT_SHOTS) {
    // generate random measurement results
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, nullptr);
    if (data != nullptr) {
      if (size < job->num_shots * (num_qubits + 1)) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      for (int i = 0; i < job->num_shots; i++) {
        strcpy(static_cast<char *>(data) +
                   static_cast<std::size_t>(i * (num_qubits + 1)),
               job->results[i].c_str());
      }
    }
    if ((size_ret) != nullptr) {
      *(size_ret) = job->num_shots * (num_qubits + 1);
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_HIST_KEYS) {
    int raw_size = 0;
    QDMI_control_get_data_dev(job, QDMI_JOB_RESULT_SHOTS, 0, nullptr,
                              &raw_size);
    std::string raw_data(raw_size, '\0');
    QDMI_control_get_data_dev(job, QDMI_JOB_RESULT_SHOTS, raw_size,
                              raw_data.data(), nullptr);
    // Count unique elements
    std::unordered_map<std::string, int> hist;
    std::stringstream ss(raw_data);
    std::string token;
    while (std::getline(ss, token, ',')) {
      hist[token]++;
    }
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, nullptr);
    if (data != nullptr) {
      if (size < hist.size() * (num_qubits + 1)) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      for (const auto &[k, v] : hist) {
        strcpy(static_cast<char *>(data), k.c_str());
        data += k.length() + 1;
      }
    }
    if ((size_ret) != nullptr) {
      *(size_ret) = static_cast<int>(hist.size()) * (num_qubits + 1);
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_HIST_VALUES) {
    int raw_size = 0;
    QDMI_control_get_data_dev(job, QDMI_JOB_RESULT_SHOTS, 0, nullptr,
                              &raw_size);
    std::string raw_data(raw_size, '\0');
    QDMI_control_get_data_dev(job, QDMI_JOB_RESULT_SHOTS, raw_size,
                              raw_data.data(), nullptr);
    // Count unique elements
    std::unordered_map<std::string, int> hist;
    std::stringstream ss(raw_data);
    std::string token;
    while (std::getline(ss, token, ',')) {
      hist[token]++;
    }
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, nullptr);
    if (data != nullptr) {
      if (size < hist.size() * sizeof(int)) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      for (const auto &[k, v] : hist) {
        *static_cast<int *>(data) = v;
        data += sizeof(int);
      }
    }
    if ((size_ret) != nullptr) {
      *(size_ret) = static_cast<int>(hist.size()) * sizeof(int);
    }
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

void QDMI_control_free_job_dev(QDMI_Job job) { delete job; }

int QDMI_control_initialize_dev() {
  device_state.status = QDMI_DEVICE_STATUS_IDLE;
  device_state.gen = std::mt19937(device_state.rd());
  device_state.dis =
      std::uniform_int_distribution<>(0, std::numeric_limits<int>::max());
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_finalize_dev() {
  device_state.status = QDMI_DEVICE_STATUS_OFFLINE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]
