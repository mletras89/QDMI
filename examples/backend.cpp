/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a backend implementation in C++.
 * @details This file can be used as a template for implementing a backend in
 * C++. For more implemented functions, see also the \ref backend5.c file.
 */

#include "qdmi/backend.h"

#include <cassert>
#include <cstring>
#include <limits>
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

QDMI_Device_State device_state;

int QDMI_query_device_property_string_dev(const QDMI_Device_Property prop,
                                          char **value) {
  if (prop == QDMI_NAME) {
    const std::string name("Backend with 7 qubits");
    *value = new char[name.length() + 1];
    strcpy(*value, name.c_str());
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_DEVICE_VERSION) {
    const std::string version("0.1.0");
    *value = new char[version.length() + 1];
    strcpy(*value, version.c_str());
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_LIBRARY_VERSION) {
    const std::string version("0.2.0");
    *value = new char[version.length() + 1];
    strcpy(*value, version.c_str());
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double_dev(const QDMI_Device_Property prop,
                                          double *value) {
  if (prop == QDMI_AVG_T1_TIME) {
    *value = 1000.0;
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_AVG_T2_TIME) {
    *value = 100000.0;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int_dev(const QDMI_Device_Property prop,
                                       int *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 7;
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_DEVICE_STATUS) {
    *value = device_state.status;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_string_list_dev(const QDMI_Device_Property prop,
                                               char ***value, int *size) {
  if (prop == QDMI_GATE_SET) {
    std::vector<std::string> gates = {"cz", "rx", "ry", "rz"};
    *size = gates.size();
    *value = new char *[*size];
    for (int i = 0; i < *size; ++i) {
      (*value)[i] = new char[gates[i].length() + 1];
      strcpy((*value)[i], gates[i].c_str());
    }
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double_list_dev(const QDMI_Device_Property prop,
                                               double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int_list_dev(const QDMI_Device_Property prop,
                                            int **value, int *size) {
  if (prop == QDMI_COUPLING_MAP) {
    std::vector<std::pair<int, int>> coupling_map_pairs = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 0}};
    *size = static_cast<int>(coupling_map_pairs.size() * 2);
    *value = new int[*size];
    for (int i = 0; i < coupling_map_pairs.size(); ++i) {
      (*value)[2 * i] = coupling_map_pairs[i].first;
      (*value)[2 * i + 1] = coupling_map_pairs[i].second;
    }
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_string_dev(const int site,
                                        const QDMI_Site_Property prop,
                                        char **value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_double_dev(const int site,
                                        const QDMI_Site_Property prop,
                                        double *value) {
  int num_qubits = 0;
  QDMI_query_device_property_int_dev(QDMI_NUM_QUBITS, &num_qubits);

  if (site < 0 || site >= num_qubits) {
    return QDMI_ERROR_OUT_OF_RANGE;
  }

  if (prop == QDMI_T1_TIME) {
    *value = 1000.0;
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_T2_TIME) {
    *value = 100000.0;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_int_dev(const int site,
                                     const QDMI_Site_Property prop,
                                     int *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_string_list_dev(const int site,
                                             const QDMI_Site_Property prop,
                                             char ***value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_double_list_dev(const int site,
                                             const QDMI_Site_Property prop,
                                             double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_int_list_dev(const int site,
                                          const QDMI_Site_Property prop,
                                          int **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_string_dev(const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Operation_Property prop,
                                             char **value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);
    return hash1 ^ hash2;
  }
};

int QDMI_query_operation_property_double_dev(const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Operation_Property prop,
                                             double *value) {
  static const std::unordered_map<std::string, double> operation_durations = {
      {"cz", 0.1}, {"rx", 0.01}, {"ry", 0.01}, {"rz", 0.01},
      // Add other operations if needed
  };

  static const std::unordered_map<
      std::string, std::unordered_map<std::pair<int, int>, double, pair_hash>>
      operation_fidelities = {
          {"cz",
           {{{0, 1}, 0.99},
            {{1, 0}, 0.99},
            {{1, 2}, 0.98},
            {{2, 1}, 0.98},
            {{2, 3}, 0.97},
            {{3, 2}, 0.97},
            {{3, 4}, 0.96},
            {{4, 3}, 0.96},
            {{4, 5}, 0.95},
            {{5, 4}, 0.95},
            {{5, 6}, 0.94},
            {{6, 5}, 0.94},
            {{6, 0}, 0.93},
            {{0, 6}, 0.93}}},
          // No need to specify single-qubit fidelities here
      };

  static const double single_qubit_fidelity = 0.999;

  if (operation == nullptr) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  const std::string op(operation);
  if (prop == QDMI_OPERATION_DURATION) {
    auto it = operation_durations.find(op);
    if (it != operation_durations.end()) {
      *value = it->second;
      return QDMI_SUCCESS;
    }
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  if (prop == QDMI_OPERATION_FIDELITY) {
    if (num_sites == 2) {
      const std::pair<int, int> site_pair = {sites[0], sites[1]};
      auto it = operation_fidelities.find(op);
      if (it != operation_fidelities.end()) {
        auto fit = it->second.find(site_pair);
        if (fit != it->second.end()) {
          *value = fit->second;
          return QDMI_SUCCESS;
        }
      }
    } else if (num_sites == 1) {
      if (op == "rx" || op == "ry" || op == "rz") {
        *value = single_qubit_fidelity;
        return QDMI_SUCCESS;
      }
    }
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
} /// [DOXYGEN END OF QDMI_query_operation_property_double_dev]

int QDMI_query_operation_property_int_dev(const char *operation,
                                          const int *sites, const int num_sites,
                                          const QDMI_Operation_Property prop,
                                          int *value) {
  if (prop == QDMI_OPERATION_NUM_QUBITS) {
    if (operation == nullptr) {
      return QDMI_ERROR_INVALID_ARGUMENT;
    }

    assert(num_sites == 0);
    assert(sites == nullptr);

    const std::string op(operation);
    if (op == "cz") {
      *value = 2;
      return QDMI_SUCCESS;
    }
    if (op == "rx" || op == "ry" || op == "rz") {
      *value = 1;
      return QDMI_SUCCESS;
    }
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_string_list_dev(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, char ***value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_double_list_dev(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_int_list_dev(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, int **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

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
}

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
}

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
}

int QDMI_control_cancel_dev(QDMI_Job job) {
  if (job->status == QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  job->status = QDMI_JOB_STATUS_CANCELLED;
  device_state.status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
}

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  // randomly decide whether job is done or not
  if (job->status == QDMI_JOB_STATUS_SUBMITTED) {
    job->status = job->binary_dist(device_state.gen)
                      ? QDMI_JOB_STATUS_DONE
                      : QDMI_JOB_STATUS_SUBMITTED;
  }
  *status = job->status;
  return QDMI_SUCCESS;
}

int QDMI_control_wait_dev(QDMI_Job job) {
  job->status = QDMI_JOB_STATUS_DONE;
  device_state.status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
}

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
}

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
}

void QDMI_control_free_job_dev(QDMI_Job job) { delete job; }

int QDMI_control_initialize_dev() {
  device_state.status = QDMI_DEVICE_IDLE;
  device_state.gen = std::mt19937(device_state.rd());
  device_state.dis =
      std::uniform_int_distribution<>(0, std::numeric_limits<int>::max());
  return QDMI_SUCCESS;
}

int QDMI_control_finalize_dev() {
  device_state.status = QDMI_DEVICE_OFFLINE;
  return QDMI_SUCCESS;
}
