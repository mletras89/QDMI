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
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct QDMI_Job_impl_d {
  int id = 0;
  QDMI_Job_Status status = QDMI_JOB_STATUS_SUBMITTED;
  int num_shots = 0;
  std::vector<std::string> data;
  std::bernoulli_distribution binary_dist{0.5};
};

struct QDMI_Device_State {
  QDMI_Device_Status status = QDMI_DEVICE_OFFLINE;
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dis;
};

struct QDMI_Site_impl_d {
  int id;
};

struct QDMI_Operation_impl_d {
  std::string name;
};

QDMI_Device_State device_state;

constexpr static std::array<QDMI_Site, 7> device_sites = {
    new QDMI_Site_impl_d{0}, new QDMI_Site_impl_d{1}, new QDMI_Site_impl_d{2},
    new QDMI_Site_impl_d{3}, new QDMI_Site_impl_d{4}, new QDMI_Site_impl_d{5},
    new QDMI_Site_impl_d{6}};

constexpr static std::array<QDMI_Operation, 4> device_operations = {
    new QDMI_Operation_impl_d{"cz"}, new QDMI_Operation_impl_d{"rx"},
    new QDMI_Operation_impl_d{"ry"}, new QDMI_Operation_impl_d{"rz"}};

#define ADD_SINGLE_VALUE_PROPERTY(prop_name, prop_type, prop_value, prop,      \
                                  size, value, size_ret)                       \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((size) < sizeof(prop_type)) {                                        \
        return QDMI_ERROR_INVALID_ARGUMENT;                                    \
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
        return QDMI_ERROR_INVALID_ARGUMENT;                                    \
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
        return QDMI_ERROR_INVALID_ARGUMENT;                                    \
      }                                                                        \
      if ((value) != nullptr) {                                                \
        memcpy((value), (prop_values).data(),                                  \
               (prop_values).size() * sizeof(prop_type));                      \
      }                                                                        \
      if ((size_ret) != nullptr) {                                             \
        *(size_ret) = (prop_values).size() * (int)sizeof(prop_type);           \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  }

int QDMI_query_get_sites_dev(int num_entries, const QDMI_Site *sites,
                             int *num_sites) {
  if ((sites != nullptr && num_entries <= 0) ||
      (sites == nullptr && num_sites == nullptr)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  if (sites != nullptr) {
    memcpy(*sites, static_cast<const void *>(device_sites.data()),
           std::min(num_entries, static_cast<int>(device_sites.size())) *
               sizeof(QDMI_Site));
  }
  if (num_sites != nullptr) {
    *num_sites = 7;
  }
  return QDMI_SUCCESS;
}

int QDMI_query_get_operations_dev(int num_entries, QDMI_Operation *operations,
                                  int *num_operations) {
  if ((operations != nullptr && num_entries <= 0) ||
      (operations == nullptr && num_operations == nullptr)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  if (operations != nullptr) {
    memcpy(*operations, static_cast<const void *>(device_operations.data()),
           std::min(num_entries, 4) * sizeof(QDMI_Operation));
  }
  if (num_operations != nullptr) {
    *num_operations = 4;
  }
  return QDMI_SUCCESS;
}

int QDMI_query_device_property_dev(QDMI_Device_Property prop, int size,
                                   void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX ||
      (value == nullptr && size_ret == nullptr)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  ADD_STRING_PROPERTY(QDMI_NAME, std::string("Device with 5 qubits"), prop,
                      size, value, size_ret);
  ADD_STRING_PROPERTY(QDMI_DEVICE_VERSION, std::string("0.1.0"), prop, size,
                      value, size_ret);
  ADD_STRING_PROPERTY(QDMI_LIBRARY_VERSION, std::string("0.2.0"), prop, size,
                      value, size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_NUM_QUBITS, int, 7, prop, size, value,
                            size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_DEVICE_STATUS, QDMI_Device_Status,
                            device_state.status, prop, size, value, size_ret);
  ADD_STRING_PROPERTY(QDMI_GATE_SET, std::string("rx,ry,rz,cx"), prop, size,
                      value, size_ret);
  ADD_STRING_PROPERTY(QDMI_GATE_SET, std::string("rx,ry,rz,cx"), prop, size,
                      value, size_ret);
  const std::vector<std::pair<int, int>> edges = {
      {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 0}};
  ADD_LIST_PROPERTY(
      QDMI_COUPLING_MAP, int,
      (std::accumulate(edges.cbegin(), edges.cend(), std::vector<int>(),
                       [](auto &acc, const auto e) {
                         acc.emplace_back(e.first);
                         acc.emplace_back(e.second);
                         return acc;
                       })),
      prop, size, value, size_ret);
  return QDMI_ERROR_NOT_SUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_query_site_property_dev(QDMI_Site site, QDMI_Site_Property prop,
                                 int size, void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX ||
      (value == nullptr && size_ret == nullptr)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  ADD_SINGLE_VALUE_PROPERTY(QDMI_T1_TIME, double, 1000.0, prop, size, value,
                            size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_T2_TIME, double, 100000.0, prop, size, value,
                            size_ret);
  return QDMI_ERROR_NOT_SUPPORTED;
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
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  static const std::unordered_map<QDMI_Operation, double> operation_durations =
      {
          {device_operations[0], 0.1},
          {device_operations[1], 0.01},
          {device_operations[2], 0.01},
          {device_operations[3], 0.01},
      };

  static const std::unordered_map<
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
            {{device_sites[4], device_sites[5]}, 0.95},
            {{device_sites[5], device_sites[4]}, 0.95},
            {{device_sites[5], device_sites[6]}, 0.94},
            {{device_sites[6], device_sites[5]}, 0.94},
            {{device_sites[6], device_sites[0]}, 0.93},
            {{device_sites[0], device_sites[6]}, 0.93}}},
          // No need to specify single-qubit fidelities here
      };

  ADD_STRING_PROPERTY(QDMI_OPERATION_NAME, operation->name, prop, size, value,
                      size_ret);
  if (prop == QDMI_OPERATION_DURATION &&
      operation_durations.find(operation) == operation_durations.end()) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_DURATION, double,
                            operation_durations.at(operation), prop, size,
                            value, size_ret);
  if (prop == QDMI_OPERATION_FIDELITY) {
    if (num_sites == 2) {
      const std::pair site_pair = {sites[0], sites[1]};
      auto it = operation_fidelities.find(operation);
      if (it != operation_fidelities.end()) {
        auto fit = it->second.find(site_pair);
        if (fit != it->second.end()) {
          ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_FIDELITY, double,
                                    fit->second, prop, size, value, size_ret);
        }
      }
    } else if (num_sites == 1) {
      if (operation == device_operations[1] ||
          operation == device_operations[2] ||
          operation == device_operations[3]) {
        ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_FIDELITY, double, 0.999, prop,
                                  size, value, size_ret);
      }
    }
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  if (prop == QDMI_OPERATION_NUM_QUBITS) {
    if (sites != nullptr) {
      return QDMI_ERROR_NOT_SUPPORTED;
    }
    if (operation == device_operations[0]) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_NUM_QUBITS, int, 2, prop, size,
                                value, size_ret);
    } else if (operation == device_operations[1] ||
               operation == device_operations[2] ||
               operation == device_operations[3]) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_NUM_QUBITS, int, 1, prop, size,
                                value, size_ret);
    }
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  return QDMI_ERROR_NOT_SUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_submit_qasm_dev(const char *qasm_string, int num_shots,
                                 QDMI_Job *job) {
  if (device_state.status != QDMI_DEVICE_IDLE) {
    return QDMI_ERROR_FATAL;
  }

  device_state.status = QDMI_DEVICE_BUSY;
  *job = new QDMI_Job_impl_d;
  (*job)->id = device_state.dis(device_state.gen);
  (*job)->num_shots = num_shots;
  (*job)->status = QDMI_JOB_STATUS_SUBMITTED;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_submit_qir_string_dev(const char *qir_string, int num_shots,
                                       QDMI_Job *job) {
  if (device_state.status != QDMI_DEVICE_IDLE) {
    return QDMI_ERROR_FATAL;
  }

  device_state.status = QDMI_DEVICE_BUSY;
  *job = new QDMI_Job_impl_d;
  (*job)->id = device_state.dis(device_state.gen);
  (*job)->num_shots = num_shots;
  (*job)->status = QDMI_JOB_STATUS_SUBMITTED;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_submit_qir_module_dev(const void *qir_module, int num_shots,
                                       QDMI_Job *job) {
  if (device_state.status != QDMI_DEVICE_IDLE) {
    return QDMI_ERROR_FATAL;
  }

  device_state.status = QDMI_DEVICE_BUSY;
  *job = new QDMI_Job_impl_d;
  (*job)->id = device_state.dis(device_state.gen);
  (*job)->num_shots = num_shots;
  (*job)->status = QDMI_JOB_STATUS_SUBMITTED;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_cancel_dev(QDMI_Job job) {
  if (job->status == QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  job->status = QDMI_JOB_STATUS_CANCELLED;
  device_state.status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  // randomly decide whether job is done or not
  if (job->status == QDMI_JOB_STATUS_SUBMITTED) {
    job->status = job->binary_dist(device_state.gen)
                      ? QDMI_JOB_STATUS_DONE
                      : QDMI_JOB_STATUS_SUBMITTED;
  }
  *status = job->status;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_wait_dev(QDMI_Job job) {
  job->status = QDMI_JOB_STATUS_DONE;
  device_state.status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_get_hist_dev(QDMI_Job job, char ***data, int **counts,
                              int *size) {
  if (job->status != QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  char **raw_data = nullptr;
  int raw_size = 0;
  QDMI_control_get_raw_dev(job, &raw_data, &raw_size);
  std::vector<std::string> str_vector(raw_size);
  for (int i = 0; i < raw_size; ++i) {
    str_vector[i] = raw_data[i];
  }
  std::unordered_map<std::string, int> hist;
  for (const auto &str : str_vector) {
    hist[str]++;
  }
  *size = hist.size();
  *data = new char *[*size];
  *counts = new int[*size];
  int i = 0;
  for (const auto &pair : hist) {
    (*data)[i] = new char[pair.first.length() + 1];
    strcpy((*data)[i], pair.first.c_str());
    (*counts)[i] = pair.second;
    ++i;
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_get_raw_dev(QDMI_Job job, char ***data, int *size) {
  if (job->status != QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  *size = job->num_shots;
  *data = new char *[job->num_shots];

  int num_qubits = 0;
  QDMI_query_device_property_int_dev(QDMI_NUM_QUBITS, &num_qubits);

  std::bernoulli_distribution binary_dist(0.5); // 50% chance for '0' or '1'

  for (int i = 0; i < job->num_shots; ++i) {
    std::string bitstring;
    for (int j = 0; j < num_qubits; ++j) {
      bitstring += binary_dist(device_state.gen) ? '1' : '0';
    }
    (*data)[i] = new char[bitstring.size() + 1];
    std::strcpy((*data)[i], bitstring.c_str());
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

void QDMI_control_free_job_dev(QDMI_Job job) { delete job; }

int QDMI_control_initialize_dev() {
  device_state.status = QDMI_DEVICE_IDLE;
  device_state.gen = std::mt19937(device_state.rd());
  device_state.dis =
      std::uniform_int_distribution<>(0, std::numeric_limits<int>::max());
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_finalize_dev() {
  device_state.status = QDMI_DEVICE_OFFLINE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]
