#include <stdio.h>
#include <stdlib.h>

#include <qdmi_internal.h>


/*----------------------------------------*/
/* Stub routines for control API */

int QDMI_control_pack_qasm2(QDMI_device dev, char *qasmstr, QDMI_fragment *frag)
{
    return dev->library.QDMI_control_pack_qasm2(dev, qasmstr, frag);
}

int QDMI_control_pack_qir(QDMI_device dev, Module *qirmod, QDMI_fragment *frag)
{
    return dev->library.QDMI_control_pack_qir(dev, qirmod, frag);
}

int QDMI_control_submit(QDMI_device dev, QDMI_fragment *frag, int numshots, QInfo info, QDMI_job *job)
{
    return dev->library.QDMI_control_submit(dev, frag, numshots, info, job);
}

int QDMI_control_cancel(QDMI_device dev, QDMI_job *job, QInfo info)
{
    return dev->library.QDMI_control_cancel(dev, job, info);
}

int QDMI_control_pause(QDMI_device dev, QDMI_job *job, QInfo info)
{
    return dev->library.QDMI_control_pause(dev, job, info);
}

int QDMI_control_test(QDMI_device dev, QDMI_job *job, int *flag, QDMI_status *status)
{
    return dev->library.QDMI_control_test(dev, job, flag, status);
}

int QDMI_control_wait(QDMI_device dev, QDMI_job *job, QDMI_status *status)
{
    return dev->library.QDMI_control_wait(dev, job, status);
}

int QDMI_control_extract_state(QDMI_device dev, QDMI_status status, int *state)
{
    return dev->library.QDMI_control_extract_state(dev, status, state);
}

int QDMI_control_readout_size(QDMI_device dev, QDMI_status *status, int *numbits)
{
    return dev->library.QDMI_control_readout_size(dev, status, numbits);
}

int QDMI_control_readout_hist_size(QDMI_device dev, QDMI_status *status, int *size)
{
    return dev->library.QDMI_control_readout_hist_size(dev, status, size);
}

int QDMI_control_readout_hist_top(QDMI_device dev, QDMI_status *status, int numhist, QInfo info, long *hist)
{
    return dev->library.QDMI_control_readout_hist_top(dev, status, numhist, info, hist);
}

int QDMI_control_readout_raw_num(QDMI_device dev, QDMI_status *status, int *num)
{
    return dev->library.QDMI_control_readout_raw_num(dev, status, num);
}

int QDMI_control_readout_raw_sample(QDMI_device dev, QDMI_status *status, int numraw, QInfo info, long *hist)
{
    return dev->library.QDMI_control_readout_raw_sample(dev, status, numraw, info, hist);
}


/*----------------------------------------*/
/* Stub routines for query API */

int QDMI_query_device_property_exists(QDMI_device dev, QDMI_device_property prop, int* scope)
{
    return dev->library.QDMI_query_device_property_exists(dev, prop, scope);
}

int QDMI_query_device_property_i(QDMI_device dev, QDMI_device_property prop, int *value)
{
    return dev->library.QDMI_query_device_property_i(dev, prop, value);
}

int QDMI_query_device_property_f(QDMI_device dev, QDMI_device_property prop, float *value)
{
    return dev->library.QDMI_query_device_property_f(dev, prop, value);
}

int QDMI_query_device_property_d(QDMI_device dev, QDMI_device_property prop, double *value)
{
    return dev->library.QDMI_query_device_property_d(dev, prop, value);
}

int QDMI_query_gateset_num(QDMI_device dev, int *num_gates)
{
    return dev->library.QDMI_query_gateset_num(dev, num_gates);
}

int QDMI_query_one_gate(QDMI_device dev, QDMI_gate *gate)
{
    return dev->library.QDMI_query_one_gate(dev, gate);
}

int QDMI_query_all_gates(QDMI_device dev, QDMI_gate *gates)
{
    return dev->library.QDMI_query_all_gates(dev, gates);
}

int QDMI_query_byname(QDMI_device dev, char *name, QDMI_gate *gate)
{
    return dev->library.QDMI_query_byname(dev, name, gate);
}

int QDMI_query_gate_name(QDMI_device dev, QDMI_gate gate, char* name, int* len)
{
    return dev->library.QDMI_query_gate_name(dev, gate, name, len);
}

int QDMI_query_gate_size(QDMI_device dev, QDMI_gate gate, int* gatesize)
{
    return dev->library.QDMI_query_gate_size(dev, gate, gatesize);
}

int QDMI_query_gate_unitary(QDMI_device dev, QDMI_gate gate, QDMI_unitary *unitary)
{
    return dev->library.QDMI_query_gate_unitary(dev, gate, unitary);
}

int QDMI_query_gate_property_exists(QDMI_device dev, QDMI_gate gate, QDMI_gate_property prop, int* scope)
{
    return dev->library.QDMI_query_gate_property_exists(dev, gate, prop, scope);
}

int QDMI_query_gate_property_i(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, int* value)
{
    return dev->library.QDMI_query_gate_property_i(dev, prop, gate, coor, value);
}

int QDMI_query_gate_property_f(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, float* value)
{
    return dev->library.QDMI_query_gate_property_f(dev, prop, gate, coor, value);
}

int QDMI_query_gate_property_d(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, double* value)
{
    return dev->library.QDMI_query_gate_property_d(dev, prop, gate, coor, value);
}


/*----------------------------------------*/
/* Stub routines for device API */

int QDMI_device_status(QDMI_device dev, QInfo info, int *status)
{
    return dev->library.QDMI_device_status(dev, info, status);
}

int QDMI_device_quality_check(QDMI_device dev, double *result)
{
    return dev->library.QDMI_device_quality_check(dev, result);
}

int QDMI_device_quality_limit(QDMI_device dev, double *result)
{
    return dev->library.QDMI_device_quality_limit(dev, result);
}

int QDMI_device_quality_calibrate(QDMI_device dev)
{
    return dev->library.QDMI_device_quality_calibrate(dev);
}


/*----------------------------------------*/
/* The End. */
