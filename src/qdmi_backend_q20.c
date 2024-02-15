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

    return QDMI_SUCCESS;
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

    return QDMI_SUCCESS;
}

int QDMI_device_status(QDMI_Device dev, QInfo info, int *status)
{
    *status = 1;
    return QDMI_SUCCESS;
}

int QDMI_backend_init(QInfo info)
{
    printf("   [Backend].............Initializing Q20 via QDMI\n");

    char *uri = NULL;
    void *regpointer = NULL;
    int err;

    err = QDMI_core_register_belib(uri, regpointer);
    //CHECK_ERR(err, "QDMI_core_register_belib");

    return QDMI_SUCCESS;
}

int QDMI_control_readout_size(QDMI_Device dev, QDMI_Status *status, int *numbits)
{
    printf("   [Backend].............Returning size\n");
    
    *numbits = 20;
    return QDMI_SUCCESS;
}

int QDMI_control_readout_raw_num(QDMI_Device dev, QDMI_Status *status, int *num)
{
    printf("   [Backend].............Returning raw numbers\n");

    int err = 0, numbits = 0;
    long i;

    err = QDMI_control_readout_size(dev, status, &numbits);
    CHECK_ERR(err, "QDMI_control_readout_raw_num");

    for (i = 0; i < ((long)1 << numbits); i++)
        num[i] = rand();

    return QDMI_SUCCESS;
}

void QDMI_set_coupling_mapping(QDMI_Device dev, int qubit_index, QDMI_Qubit qubit)
{
    qubit->index = qubit_index;

    qubit->coupling_mapping = (QDMI_qubit_index*)malloc(2 * sizeof(QDMI_qubit_index));

    if (qubit_index == 0)
    {
        qubit->coupling_mapping[0] = 1;
        qubit->coupling_mapping[1] = 2;
    }
    else
    {
        if (qubit_index == 19)
        {
            qubit->coupling_mapping[0] = 17;
            qubit->coupling_mapping[1] = 18;
        }
        else
        {
            qubit->coupling_mapping[0] = qubit_index - 1;
            qubit->coupling_mapping[1] = qubit_index + 1;
        }
    }
}

int QDMI_query_all_qubits(QDMI_Device dev, QDMI_Qubit *qubits)
{
    int err, num_qubits;

    // TODO Handle err
    err = QDMI_query_qubits_num(dev, &num_qubits);

    printf("   [QDMI]................before malloc\n");
    *qubits = (QDMI_Qubit)malloc(num_qubits * sizeof(QDMI_Qubit_impl_t));
    printf("   [QDMI]................after malloc\n");

    if (*qubits == NULL)
    {
        printf("   [QDMI]................Couldn't allocate memory for the qubit array\n");
        return QDMI_WARN_GENERAL;
    }

    int i;
    for (i = 0; i < num_qubits; i++)
        QDMI_set_coupling_mapping(dev, i, (*qubits) + i);

    printf("   [QDMI]................Returning available qubits\n");
    return QDMI_SUCCESS;
}

int QDMI_query_qubits_num(QDMI_Device dev, int *num_qubits)
{
    *num_qubits = 7;
    printf("   [Backend].............QDMI_query_qubits_num\n");
    return QDMI_SUCCESS;
}

int QDMI_control_submit(QDMI_Device dev, QDMI_Fragment *frag, int numshots, QInfo info, QDMI_Job *job)
{
    printf("   [Backend].............QDMI_control_submit\n");
    //printf("   [Backend].............(*frag)->QIR_bitcode: %s\n", (*frag)->QIR_bitcode);

    return QDMI_SUCCESS;
}
