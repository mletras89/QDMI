/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief This file is for testing whether a device implements all the required
 * functions.
 * @details It calls all the functions in the device interface to ensure that
 * they are implemented. During linking, when a function is not implemented this
 * will raise an error.
 * @note This file is not meant to be ever executed, only linked.
 */

#include "qdmi/device.h"

int main() {
  QDMI_Job job = nullptr;
  QDMI_Site site = nullptr;
  QDMI_Operation operation = nullptr;
  // query interface
  QDMI_query_get_sites_dev(1, &site, nullptr);
  QDMI_query_get_operations_dev(1, &operation, nullptr);
  QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_MAX, 0, nullptr, nullptr);
  QDMI_query_site_property_dev(site, QDMI_SITE_PROPERTY_MAX, 0, nullptr,
                               nullptr);
  QDMI_query_operation_property_dev(
      operation, 0, nullptr, QDMI_OPERATION_PROPERTY_MAX, 0, nullptr, nullptr);
  // control interface
  QDMI_control_create_job_dev(QDMI_PROGRAM_FORMAT_MAX, 0, nullptr, &job);
  QDMI_control_set_parameter_dev(job, QDMI_JOB_PARAMETER_MAX, 0, nullptr);
  QDMI_control_submit_job_dev(job);
  QDMI_control_cancel_dev(job);
  QDMI_control_check_dev(job, nullptr);
  QDMI_control_wait_dev(job);
  QDMI_control_get_data_dev(job, QDMI_JOB_RESULT_MAX, 0, nullptr, nullptr);
  QDMI_control_free_job_dev(job);
  QDMI_control_initialize_dev();
  QDMI_control_finalize_dev();
}
