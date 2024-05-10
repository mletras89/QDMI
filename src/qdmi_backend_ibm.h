#ifndef QDMIBACKENDIBM_H
#define QDMIBACKENDIBM_H
#include <qdmi_backend.h>
#include "qdmi_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dlfcn.h>
#include <string.h>
#include <stdbool.h>
#include <jansson.h>
#include <stdlib.h>
#include <unistd.h>

extern json_error_t error;
extern json_t *root;
extern char **gate_set;

const char *backend_properties[] = 
{
    "backend_name", "backend_version",
    "n_qubits", "basis_gates", "gates", "coupling_map"
};

int fetch_configuration();
#endif // QDMIBACKENDIBM_H
