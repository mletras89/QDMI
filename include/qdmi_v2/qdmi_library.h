/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct QDMI_Library_impl_d *QDMI_Library;

int QDMI_library_load(char *lib_name, QDMI_Library *library);
void QDMI_library_free(QDMI_Library library);

int QDMI_library_add_parameter_i64(QDMI_Library library, const char *name,
                                   int64_t val);
int QDMI_library_add_parameter_d(QDMI_Library library, const char *name,
                                 double val);
int QDMI_library_add_parameter_c(QDMI_Library library, const char *name,
                                 const char *val);

#ifdef __cplusplus
} // extern "C"
#endif
