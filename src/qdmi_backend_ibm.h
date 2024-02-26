#ifndef QDMIBACKENDIBM_H
#define QDMIBACKENDIBM_H
#include <jansson.h>
#include <qdmi_backend.h>
#include "qdmi_internal.h"

extern json_t *root;
extern char **gate_set;

const char *backend_properties[] = 
{
    "backend_name", "backend_version",
    "n_qubits", "basis_gates", "gates", "coupling_map"
};

int fetch_configuration();
#endif // QDMIBACKENDIBM_H