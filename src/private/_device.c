/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "_device.h"

#include "_types.h"
#include "qdmi/return_codes.h"

#include <dlfcn.h>
#include <stdlib.h>

#define LOAD_SYMBOL(device, symbol)                                            \
  {                                                                            \
    (device)->symbol = NULL;                                                   \
    *(void **)(&((device)->symbol)) = dlsym((device)->lib_handle, #symbol);    \
    if ((device)->symbol == NULL) {                                            \
      QDMI_device_close(device);                                               \
      return QDMI_ERROR_NOT_FOUND;                                             \
    }                                                                          \
  }

int QDMI_device_open(const char *lib_name, QDMI_Device *device) {
  // allocate memory for the device
  *device = (QDMI_Device)malloc(sizeof(QDMI_Device_impl_t));
  if (*device == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }
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
