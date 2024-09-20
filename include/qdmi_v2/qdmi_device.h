/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include <qinfo.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct QDMI_Device_impl_d *QDMI_Device;

int QDMI_device_create(QDMI_Device *device);
void QDMI_device_free(QDMI_Device device);

int QDMI_device_get_name(QDMI_Device device, char **name);
int QDMI_device_get_num_qubits(QDMI_Device device, int *num_qubits);
int QDMI_device_get_info(QDMI_Device device, QInfo *info);

int QDMI_device_set_name(QDMI_Device device, char *name);
int QDMI_device_set_num_qubits(QDMI_Device device, int num_qubits);
int QDMI_device_set_info(QDMI_Device device, QInfo info);

// ---- Methods that need to be implemented by a backend ----

int QDMI_device_name(QDMI_Device device);
typedef int (*QDMI_device_name_t)(QDMI_Device device);

int QDMI_device_num_qubits(QDMI_Device device);
typedef int (*QDMI_device_num_qubits_t)(QDMI_Device device);

int QDMI_device_info(QDMI_Device device);
typedef int (*QDMI_device_info_t)(QDMI_Device device);

#ifdef __cplusplus
} // extern "C"
#endif
