/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi_library.h"

#include "details/qdmi_types.h"
#include "qdmi_device.h"
#include "qdmi_return_codes.h"

#include <dlfcn.h>
#include <qinfo.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_SYMBOL(library, symbol)                                           \
  {                                                                            \
    (library)->symbol = (symbol##_t)dlsym((library)->lib_handle, #symbol);     \
    if ((library)->symbol == NULL) {                                           \
      QDMI_library_free(library);                                              \
      return QDMI_ERROR_SYMBOL_NOT_FOUND;                                      \
    }                                                                          \
  }

int QDMI_library_load(char *lib_name, QDMI_Library *library) {
  *library = (QDMI_Library_impl_t *)malloc(sizeof(QDMI_Library_impl_t));
  if (*library == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }
  (*library)->lib_name = strdup(lib_name);

  int err = QInfo_create(&(*library)->info);
  if (!QDMI_is_Success(err)) {
    QDMI_library_free(*library);
    return QDMI_translate_qinfo_error(err);
  }

  (*library)->lib_handle = dlopen(lib_name, RTLD_LAZY);
  if ((*library)->lib_handle == NULL) {
    QDMI_library_free(*library);
    return QDMI_ERROR_LIBRARY_NOT_FOUND;
  }

  LOAD_SYMBOL(*library, QDMI_device_name);
  LOAD_SYMBOL(*library, QDMI_device_num_qubits);
  LOAD_SYMBOL(*library, QDMI_device_info);

  (*library)->next = NULL;

  return QDMI_SUCCESS;
}

void QDMI_library_free(QDMI_Library library) {
  free(library->lib_name);
  dlclose(library->lib_handle);
  QInfo_free(library->info);
  if (library->next != NULL) {
    QDMI_library_free(library->next);
  }
  free(library);
}

int QDMI_library_add_parameter_i64(QDMI_Library library, const char *name,
                                   const int64_t val) {
  QInfo_index index = 0;
  int err = QInfo_add(library->info, name, QINFO_TYPE_INT64, &index);
  if (!QInfo_is_Success(err)) {
    return QDMI_translate_qinfo_error(err);
  }
  err = QInfo_set_i64(library->info, index, val);
  return QDMI_translate_qinfo_error(err);
}

int QDMI_library_add_parameter_d(QDMI_Library library, const char *name,
                                 const double val) {
  QInfo_index index = 0;
  int err = QInfo_add(library->info, name, QINFO_TYPE_DOUBLE, &index);
  if (!QInfo_is_Success(err)) {
    return QDMI_translate_qinfo_error(err);
  }
  err = QInfo_set_d(library->info, index, val);
  return QDMI_translate_qinfo_error(err);
}

int QDMI_library_add_parameter_c(QDMI_Library library, const char *name,
                                 const char *val) {
  QInfo_index index = 0;
  int err = QInfo_add(library->info, name, QINFO_TYPE_STRING, &index);
  if (!QInfo_is_Success(err)) {
    return QDMI_translate_qinfo_error(err);
  }
  err = QInfo_set_c(library->info, index, val);
  return QDMI_translate_qinfo_error(err);
}
