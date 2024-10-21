/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a driver implementation in C.
 * @details This file can be used as a template for implementing a driver in C.
 */

#include "qdmi/driver/session.h"
#include "qdmi/enums.h"

#include <dlfcn.h>
#include <stdlib.h>

/**
 * @brief Handle for a job.
 */
typedef struct QDMI_Job_impl_d *QDMI_Job;

typedef int (*QDMI_query_device_property_string_dev_t)(
    QDMI_Device_Property prop, char **value);

typedef int (*QDMI_query_device_property_double_dev_t)(
    QDMI_Device_Property prop, double *value);

typedef int (*QDMI_query_device_property_int_dev_t)(QDMI_Device_Property prop,
                                                    int *value);

typedef int (*QDMI_query_device_property_string_list_dev_t)(
    QDMI_Device_Property prop, char ***value, int *size);

typedef int (*QDMI_query_device_property_double_list_dev_t)(
    QDMI_Device_Property prop, double **value, int *size);

typedef int (*QDMI_query_device_property_int_list_dev_t)(
    QDMI_Device_Property prop, int **value, int *size);

typedef int (*QDMI_query_site_property_string_dev_t)(int site,
                                                     QDMI_Site_Property prop,
                                                     char **value);

typedef int (*QDMI_query_site_property_double_dev_t)(int site,
                                                     QDMI_Site_Property prop,
                                                     double *value);

typedef int (*QDMI_query_site_property_int_dev_t)(int site,
                                                  QDMI_Site_Property prop,
                                                  int *value);

typedef int (*QDMI_query_site_property_string_list_dev_t)(
    int site, QDMI_Site_Property prop, char ***value, int *size);

typedef int (*QDMI_query_site_property_double_list_dev_t)(
    int site, QDMI_Site_Property prop, double **value, int *size);

typedef int (*QDMI_query_site_property_int_list_dev_t)(int site,
                                                       QDMI_Site_Property prop,
                                                       int **value, int *size);

typedef int (*QDMI_query_operation_property_string_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Operation_Property prop, char **value);

typedef int (*QDMI_query_operation_property_double_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Operation_Property prop, double *value);

typedef int (*QDMI_query_operation_property_int_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Operation_Property prop, int *value);

typedef int (*QDMI_query_operation_property_string_list_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Operation_Property prop, char ***value, int *size);

typedef int (*QDMI_query_operation_property_double_list_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Operation_Property prop, double **value, int *size);

typedef int (*QDMI_query_operation_property_int_list_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Operation_Property prop, int **value, int *size);

typedef int (*QDMI_control_submit_qasm_dev_t)(const char *qasm_string,
                                              int num_shots, QDMI_Job *job);

typedef int (*QDMI_control_submit_qir_string_dev_t)(const char *qir_string,
                                                    int num_shots,
                                                    QDMI_Job *job);

typedef int (*QDMI_control_submit_qir_module_dev_t)(const void *qir_module,
                                                    int num_shots,
                                                    QDMI_Job *job);

typedef int (*QDMI_control_cancel_dev_t)(QDMI_Job job);

typedef int (*QDMI_control_check_dev_t)(QDMI_Job job, QDMI_Job_Status *status);

typedef int (*QDMI_control_wait_dev_t)(QDMI_Job job);

typedef int (*QDMI_control_get_hist_dev_t)(QDMI_Job job, char ***data,
                                           int **counts, int *size);

typedef int (*QDMI_control_get_raw_dev_t)(QDMI_Job job, char ***data,
                                          int *size);

typedef void (*QDMI_control_free_job_dev_t)(QDMI_Job job);

typedef int (*QDMI_control_initialize_dev_t)(void);

typedef int (*QDMI_control_finalize_dev_t)(void);

/**
 * @brief Definition of the QDMI Device.
 */
typedef struct QDMI_Device_impl_d {
  void *lib_handle; /**< The dlopen handle to the dynamic library. */

  QDMI_Device_Mode mode; /**< The mode in which the device was opened. */

  /// Function pointer to @ref QDMI_query_device_property_string_dev.
  QDMI_query_device_property_string_dev_t QDMI_query_device_property_string_dev;
  /// Function pointer to @ref QDMI_query_device_property_double_dev.
  QDMI_query_device_property_double_dev_t QDMI_query_device_property_double_dev;
  /// Function pointer to @ref QDMI_query_device_property_int_dev.
  QDMI_query_device_property_int_dev_t QDMI_query_device_property_int_dev;
  /// Function pointer to @ref QDMI_query_device_property_string_list_dev.
  QDMI_query_device_property_string_list_dev_t
      QDMI_query_device_property_string_list_dev;
  /// Function pointer to @ref QDMI_query_device_property_double_list_dev.
  QDMI_query_device_property_double_list_dev_t
      QDMI_query_device_property_double_list_dev;
  /// Function pointer to @ref QDMI_query_device_property_int_list_dev.
  QDMI_query_device_property_int_list_dev_t
      QDMI_query_device_property_int_list_dev;

  /// Function pointer to @ref QDMI_query_site_property_string_dev.
  QDMI_query_site_property_string_dev_t QDMI_query_site_property_string_dev;
  /// Function pointer to @ref QDMI_query_site_property_double_dev.
  QDMI_query_site_property_double_dev_t QDMI_query_site_property_double_dev;
  /// Function pointer to @ref QDMI_query_site_property_int_dev.
  QDMI_query_site_property_int_dev_t QDMI_query_site_property_int_dev;

  /// Function pointer to @ref QDMI_query_site_property_string_list_dev.
  QDMI_query_site_property_string_list_dev_t
      QDMI_query_site_property_string_list_dev;
  /// Function pointer to @ref QDMI_query_site_property_double_list_dev.
  QDMI_query_site_property_double_list_dev_t
      QDMI_query_site_property_double_list_dev;
  /// Function pointer to @ref QDMI_query_site_property_int_list_dev.
  QDMI_query_site_property_int_list_dev_t QDMI_query_site_property_int_list_dev;

  /// Function pointer to @ref QDMI_query_operation_property_string_dev.
  QDMI_query_operation_property_string_dev_t
      QDMI_query_operation_property_string_dev;
  /// Function pointer to @ref QDMI_query_operation_property_double_dev.
  QDMI_query_operation_property_double_dev_t
      QDMI_query_operation_property_double_dev;
  /// Function pointer to @ref QDMI_query_operation_property_int_dev.
  QDMI_query_operation_property_int_dev_t QDMI_query_operation_property_int_dev;
  /// Function pointer to @ref QDMI_query_operation_property_string_list_dev.
  QDMI_query_operation_property_string_list_dev_t
      QDMI_query_operation_property_string_list_dev;
  /// Function pointer to @ref QDMI_query_operation_property_double_list_dev.
  QDMI_query_operation_property_double_list_dev_t
      QDMI_query_operation_property_double_list_dev;
  /// Function pointer to @ref QDMI_query_operation_property_int_list_dev.
  QDMI_query_operation_property_int_list_dev_t
      QDMI_query_operation_property_int_list_dev;

  /// Function pointer to @ref QDMI_control_submit_qasm_dev.
  QDMI_control_submit_qasm_dev_t QDMI_control_submit_qasm_dev;
  /// Function pointer to @ref QDMI_control_submit_qir_string_dev.
  QDMI_control_submit_qir_string_dev_t QDMI_control_submit_qir_string_dev;
  /// Function pointer to @ref QDMI_control_submit_qir_module_dev.
  QDMI_control_submit_qir_module_dev_t QDMI_control_submit_qir_module_dev;
  /// Function pointer to @ref QDMI_control_cancel_dev.
  QDMI_control_cancel_dev_t QDMI_control_cancel_dev;
  /// Function pointer to @ref QDMI_control_check_dev.
  QDMI_control_check_dev_t QDMI_control_check_dev;
  /// Function pointer to @ref QDMI_control_wait_dev.
  QDMI_control_wait_dev_t QDMI_control_wait_dev;
  /// Function pointer to @ref QDMI_control_get_hist_dev.
  QDMI_control_get_hist_dev_t QDMI_control_get_hist_dev;
  /// Function pointer to @ref QDMI_control_get_raw_dev.
  QDMI_control_get_raw_dev_t QDMI_control_get_raw_dev;
  /// Function pointer to @ref QDMI_control_free_job_dev.
  QDMI_control_free_job_dev_t QDMI_control_free_job_dev;
  /// Function pointer to @ref QDMI_control_initialize_dev.
  QDMI_control_initialize_dev_t QDMI_control_initialize_dev;
  /// Function pointer to @ref QDMI_control_finalize_dev.
  QDMI_control_finalize_dev_t QDMI_control_finalize_dev;

  struct QDMI_Device_impl_d *next; /**< Pointer to the next device. */
} QDMI_Device_impl_t;

typedef struct QDMI_Device_impl_d *QDMI_Device;

/**
 * @brief Definition of the QDMI Session.
 */
typedef struct QDMI_Session_impl_d {
  QDMI_Device device_list; /**< Device list associated with this session. */
} QDMI_Session_impl_t;

typedef struct QDMI_Session_impl_d *QDMI_Session;

int QDMI_session_alloc(QDMI_Session *session) {
  // allocate session
  *session = (QDMI_Session)malloc(sizeof(QDMI_Session_impl_t));
  if (*session == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }
  // initialize session
  (*session)->device_list = NULL;
  // return success
  return QDMI_SUCCESS;
}

void QDMI_session_free(QDMI_Session session) {
  // close and free all devices
  while (session->device_list != NULL) {
    QDMI_Device next = session->device_list->next;
    QDMI_device_close(session->device_list);
    session->device_list = next;
  }
  // free session
  free(session);
}

int QDMI_session_open_device(QDMI_Session session, const char *lib_name,
                             QDMI_Device_Mode mode, QDMI_Device *device) {
  // open device
  const int err = QDMI_device_open(lib_name, mode, device);
  if (err != QDMI_SUCCESS) {
    return err;
  }
  // add device to session
  (*device)->next = session->device_list;
  session->device_list = *device;
  // return success
  return QDMI_SUCCESS;
}

int QDMI_session_close_device(QDMI_Session session, QDMI_Device device) {
  // find device in session
  QDMI_Device prev = NULL;
  QDMI_Device curr = session->device_list;
  while (curr != NULL && curr != device) {
    prev = curr;
    curr = curr->next;
  }
  // check if device was found
  if (curr == NULL) {
    return QDMI_ERROR_NOT_FOUND;
  }
  // remove device from session
  if (prev == NULL) {
    session->device_list = device->next;
  } else {
    prev->next = device->next;
  }
  // close and free device
  QDMI_device_close(device);
  // return success
  return QDMI_SUCCESS;
}

int QDMI_session_get_device(QDMI_Session session, int index,
                            QDMI_Device *device) {
  // find device in session
  QDMI_Device curr = session->device_list;
  for (int i = 0; i < index; i++) {
    if (curr == NULL) {
      return QDMI_ERROR_OUT_OF_RANGE;
    }
    curr = curr->next;
  }
  // return device
  *device = curr;
  // return success
  return QDMI_SUCCESS;
}

int QDMI_session_get_num_devices(QDMI_Session session, int *num_devices) {
  // count devices in session
  int count = 0;
  QDMI_Device curr = session->device_list;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  // return number of devices
  *num_devices = count;
  // return success
  return QDMI_SUCCESS;
}

typedef struct QDMI_Session_impl_d *QDMI_Session;

int QDMI_query_device_property_string(QDMI_Device device,
                                      const QDMI_Device_Property prop,
                                      char **value) {
  return device->QDMI_query_device_property_string_dev(prop, value);
}

int QDMI_query_device_property_double(QDMI_Device device,
                                      const QDMI_Device_Property prop,
                                      double *value) {
  return device->QDMI_query_device_property_double_dev(prop, value);
}

int QDMI_query_device_property_int(QDMI_Device device,
                                   const QDMI_Device_Property prop,
                                   int *value) {
  return device->QDMI_query_device_property_int_dev(prop, value);
}

int QDMI_query_device_property_string_list(QDMI_Device device,
                                           const QDMI_Device_Property prop,
                                           char ***value, int *size) {
  return device->QDMI_query_device_property_string_list_dev(prop, value, size);
}

int QDMI_query_device_property_double_list(QDMI_Device device,
                                           const QDMI_Device_Property prop,
                                           double **value, int *size) {
  return device->QDMI_query_device_property_double_list_dev(prop, value, size);
}

int QDMI_query_device_property_int_list(QDMI_Device device,
                                        const QDMI_Device_Property prop,
                                        int **value, int *size) {
  return device->QDMI_query_device_property_int_list_dev(prop, value, size);
}

int QDMI_query_site_property_string(QDMI_Device device, const int site,
                                    const QDMI_Site_Property prop,
                                    char **value) {
  return device->QDMI_query_site_property_string_dev(site, prop, value);
}

int QDMI_query_site_property_double(QDMI_Device device, const int site,
                                    const QDMI_Site_Property prop,
                                    double *value) {
  return device->QDMI_query_site_property_double_dev(site, prop, value);
}

int QDMI_query_site_property_int(QDMI_Device device, const int site,
                                 const QDMI_Site_Property prop, int *value) {
  return device->QDMI_query_site_property_int_dev(site, prop, value);
}

int QDMI_query_site_property_string_list(QDMI_Device device, const int site,
                                         const QDMI_Site_Property prop,
                                         char ***value, int *size) {
  return device->QDMI_query_site_property_string_list_dev(site, prop, value,
                                                          size);
}

int QDMI_query_site_property_double_list(QDMI_Device device, const int site,
                                         const QDMI_Site_Property prop,
                                         double **value, int *size) {
  return device->QDMI_query_site_property_double_list_dev(site, prop, value,
                                                          size);
}

int QDMI_query_site_property_int_list(QDMI_Device device, const int site,
                                      const QDMI_Site_Property prop,
                                      int **value, int *size) {
  return device->QDMI_query_site_property_int_list_dev(site, prop, value, size);
}

int QDMI_query_operation_property_string(QDMI_Device device,
                                         const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Operation_Property prop,
                                         char **value) {
  return device->QDMI_query_operation_property_string_dev(
      operation, sites, num_sites, prop, value);
}

int QDMI_query_operation_property_double(QDMI_Device device,
                                         const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Operation_Property prop,
                                         double *value) {
  return device->QDMI_query_operation_property_double_dev(
      operation, sites, num_sites, prop, value);
}

int QDMI_query_operation_property_int(QDMI_Device device, const char *operation,
                                      const int *sites, const int num_sites,
                                      const QDMI_Operation_Property prop,
                                      int *value) {
  return device->QDMI_query_operation_property_int_dev(operation, sites,
                                                       num_sites, prop, value);
}

int QDMI_query_operation_property_string_list(
    QDMI_Device device, const char *operation, const int *sites,
    const int num_sites, const QDMI_Operation_Property prop, char ***value,
    int *size) {
  return device->QDMI_query_operation_property_string_list_dev(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_query_operation_property_double_list(
    QDMI_Device device, const char *operation, const int *sites,
    const int num_sites, const QDMI_Operation_Property prop, double **value,
    int *size) {
  return device->QDMI_query_operation_property_double_list_dev(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_query_operation_property_int_list(QDMI_Device device,
                                           const char *operation,
                                           const int *sites,
                                           const int num_sites,
                                           const QDMI_Operation_Property prop,
                                           int **value, int *size) {
  return device->QDMI_query_operation_property_int_list_dev(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_control_submit_qasm(QDMI_Device dev, const char *qasm_string,
                             int num_shots, QDMI_Job *job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_submit_qasm_dev(qasm_string, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_submit_qir_string(QDMI_Device dev, const char *qir_string,
                                   int num_shots, QDMI_Job *job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_submit_qir_string_dev(qir_string, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_submit_qir_module(QDMI_Device dev, const void *qir_module,
                                   int num_shots, QDMI_Job *job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_submit_qir_module_dev(qir_module, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_cancel(QDMI_Device dev, QDMI_Job job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_cancel_dev(job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_check(QDMI_Device dev, QDMI_Job job, QDMI_Job_Status *status) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_check_dev(job, status);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_wait(QDMI_Device dev, QDMI_Job job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_wait_dev(job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_get_hist(QDMI_Device dev, QDMI_Job job, char ***data,
                          int **counts, int *size) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_get_hist_dev(job, data, counts, size);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_get_raw(QDMI_Device dev, QDMI_Job job, char ***data,
                         int *size) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_get_raw_dev(job, data, size);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

void QDMI_control_free_job(QDMI_Device dev, QDMI_Job job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    dev->QDMI_control_free_job_dev(job);
  }
}

#define LOAD_SYMBOL(device, symbol)                                            \
  {                                                                            \
    (device)->symbol = NULL;                                                   \
    *(void **)(&((device)->symbol)) = dlsym((device)->lib_handle, #symbol);    \
    if ((device)->symbol == NULL) {                                            \
      QDMI_device_close(device);                                               \
      return QDMI_ERROR_NOT_FOUND;                                             \
    }                                                                          \
  }

int QDMI_device_open(const char *lib_name, QDMI_Device_Mode mode,
                     QDMI_Device *device) {
  // allocate memory for the device
  *device = (QDMI_Device)malloc(sizeof(QDMI_Device_impl_t));
  if (*device == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }
  (*device)->mode = mode;
  // open the dynamic library at the location passed in `lib_name`
  (*device)->lib_handle = dlopen(lib_name, RTLD_NOW | RTLD_LOCAL);
  if ((*device)->lib_handle == NULL) {
    free(*device);
    return QDMI_ERROR_LIB_NOT_FOUND;
  }
  // load the function symbols from the dynamic library

  // this has to be the first symbol to be loaded because this method is used
  // to close the device in case of any error.
  LOAD_SYMBOL(*device, QDMI_control_finalize_dev);

  LOAD_SYMBOL(*device, QDMI_query_device_property_string_dev);
  LOAD_SYMBOL(*device, QDMI_query_device_property_double_dev);
  LOAD_SYMBOL(*device, QDMI_query_device_property_int_dev);
  LOAD_SYMBOL(*device, QDMI_query_device_property_string_list_dev);
  LOAD_SYMBOL(*device, QDMI_query_device_property_double_list_dev);
  LOAD_SYMBOL(*device, QDMI_query_device_property_int_list_dev);

  LOAD_SYMBOL(*device, QDMI_query_site_property_string_dev);
  LOAD_SYMBOL(*device, QDMI_query_site_property_double_dev);
  LOAD_SYMBOL(*device, QDMI_query_site_property_int_dev);
  LOAD_SYMBOL(*device, QDMI_query_site_property_string_list_dev);
  LOAD_SYMBOL(*device, QDMI_query_site_property_double_list_dev);
  LOAD_SYMBOL(*device, QDMI_query_site_property_int_list_dev);

  LOAD_SYMBOL(*device, QDMI_query_operation_property_string_dev);
  LOAD_SYMBOL(*device, QDMI_query_operation_property_double_dev);
  LOAD_SYMBOL(*device, QDMI_query_operation_property_int_dev);
  LOAD_SYMBOL(*device, QDMI_query_operation_property_string_list_dev);
  LOAD_SYMBOL(*device, QDMI_query_operation_property_double_list_dev);
  LOAD_SYMBOL(*device, QDMI_query_operation_property_int_list_dev);

  LOAD_SYMBOL(*device, QDMI_control_submit_qasm_dev);
  LOAD_SYMBOL(*device, QDMI_control_submit_qir_string_dev);
  LOAD_SYMBOL(*device, QDMI_control_submit_qir_module_dev);
  LOAD_SYMBOL(*device, QDMI_control_cancel_dev);
  LOAD_SYMBOL(*device, QDMI_control_check_dev);
  LOAD_SYMBOL(*device, QDMI_control_wait_dev);
  LOAD_SYMBOL(*device, QDMI_control_get_hist_dev);
  LOAD_SYMBOL(*device, QDMI_control_get_raw_dev);
  LOAD_SYMBOL(*device, QDMI_control_free_job_dev);
  LOAD_SYMBOL(*device, QDMI_control_initialize_dev);

  // initialize the device
  (*device)->QDMI_control_initialize_dev();

  // initialize the next pointer to NULL
  (*device)->next = NULL;
  // return success
  return QDMI_SUCCESS;
}

void QDMI_device_close(QDMI_Device device) {
  // Check if QDMI_control_finalize is not NULL before calling it
  if (device->QDMI_control_finalize_dev != NULL) {
    device->QDMI_control_finalize_dev();
  }
  // close the dynamic library
  dlclose(device->lib_handle);
  // free the memory allocated for the device
  free(device);
}
