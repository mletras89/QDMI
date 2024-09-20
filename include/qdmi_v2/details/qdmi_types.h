/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include <qinfo.h>

typedef struct QDMI_Device_impl_d {
  char *name;     /**< The name of the device. */
  int num_qubits; /**< The number of qubits of the device. */
  QInfo info;     /**< Additional information about the device. */
} QDMI_Device_impl_t;
typedef struct QDMI_Device_impl_d *QDMI_Device;

typedef int (*QDMI_device_name_t)(QDMI_Device device);
typedef int (*QDMI_device_num_qubits_t)(QDMI_Device device);
typedef int (*QDMI_device_info_t)(QDMI_Device device);

typedef struct QDMI_Library_impl_d {
  char *lib_name;   /**< The name of the library to open. */
  void *lib_handle; /**< The dlopen handle to the library. */

  QDMI_device_name_t QDMI_device_name;
  QDMI_device_num_qubits_t QDMI_device_num_qubits;
  QDMI_device_info_t QDMI_device_info;

  struct QDMI_Library_impl_d *next; /**< Pointer to the next library. */

  QInfo info; /**< Info object for storing additional information. */
} QDMI_Library_impl_t;
typedef struct QDMI_Library_impl_d *QDMI_Library;

typedef struct QDMI_Session_impl_d {
  QDMI_Library library_list; /**< Library list associated with this session. */
  int num_libraries;         /**< Number of libraries in the list. */
  struct QDMI_Session_impl_d *next; /**< Pointer to the next session. */
  QInfo info; /**< Info object for storing additional information. */
} QDMI_Session_impl_t;
typedef struct QDMI_Session_impl_d *QDMI_Session;
