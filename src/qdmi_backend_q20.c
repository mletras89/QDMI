#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dlfcn.h>
#include <string.h>

#include "qdmi_backend_q20.h"

#define CHECK_ERR(a,b) { if (a!=QDMI_SUCCESS) { printf("\n[Error]: %i at %s",a,b); return 1; }}

int QDMI_query_gateset_num(QDMI_Device dev, int *num_gates)
{
    if (sizeof(gate_set) > 0)
        *num_gates = sizeof(gate_set) / sizeof(gate_set[0]);
    else
        *num_gates = 0;

    return 0;
}

void QDMI_get_gate_info(QDMI_Device dev, int gate_index, QDMI_Gate gate)
{
    gate->name     = gate_set[gate_index];
    gate->unitary  = "Unitary_Matrix";
    gate->fidelity = 1.0;
}

int QDMI_query_all_gates(QDMI_Device dev, QDMI_Gate *gates)
{
    int i, num_gates = 0;
    QDMI_query_gateset_num(dev, &num_gates);

    *gates = (QDMI_Gate)malloc(num_gates * sizeof(QDMI_Gate_impl_t));

    for (i = 0; i < num_gates; i++)
        QDMI_get_gate_info(dev, i, (*gates) + i);

    return 0;
}

int QDMI_device_status(QDMI_Device dev, QInfo info, int *status)
{
    *status = 0;
    return 0;
}

int QDMI_backend_init(QInfo info)
{
    printf("   [Backend].............Initializing Q20 via QDMI\n");

    char *uri = NULL;
    void *regpointer = NULL;
    int err;

    err = QDMI_core_register_belib(uri, regpointer);
    //CHECK_ERR(err, "QDMI_core_register_belib");

    return 0;
}

int QDMI_control_submit(QDMI_Device dev, QDMI_Fragment *frag, int numshots, QInfo info, QDMI_Job *job)
{
    printf("   [Backend].............QDMI_control_submit\n");
    //printf("   [Backend].............(*frag)->QIR_bitcode: %s\n", (*frag)->QIR_bitcode);
    return 0;
}
