/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum QDMI_Device_Property_t {
  QDMI_NUM_QUBITS = 0, /**< The number of qubits in the device. */
};
typedef enum QDMI_Device_Property_t QDMI_Device_Property;

#ifdef __cplusplus
} // extern "C"
#endif
