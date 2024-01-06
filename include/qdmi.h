/* Headerfile to be included by all QDMI clients */

#ifndef QDMI_H
#define QDMI_H

#include <qinfo.h>


/*----------------------------------------*/
/* QDMI Constants for API usage*/

/* Timing Units */
#define QDMI_TIME_S  0
#define QDMI_TIME_MS 1
#define QDMI_TIME_US 2
#define QDMI_TIME_NS 3
#define QDMI_TIME_PS 4

/* Behavior of QDMI properties */
#define QDMI_PROPERTY_NOTEXIST 0
#define QDMI_PROPERTY_STATIC   1
#define QDMI_PROPERTY_DYNAMIC  2

/* Status values to be used per job */
#define QDMI_COMPLETE  0
#define QDMI_EXECUTING 1
#define QDMI_WAITING   2
#define QDMI_HALTED    3

/* Error classes, i.e., status returned by API */
#define QDMI_WARN_NOBACKEND    2
#define QDMI_WARN_GENERAL      1
#define QDMI_SUCCESS           0
#define QDMI_ERROR_FATAL      -1
#define QDMI_ERROR_OUTOFMEM   -2
#define QDMI_ERROR_NOSESSION  -3
#define QDMI_ERROR_NOCFGFILE  -4
#define QDMI_ERROR_CONFIG     -5
#define QDMI_ERROR_BACKEND    -6

#define QDMI_IS_SUCCESS(err) (err==QDMI_SUCCESS)
#define QDMI_IS_WARNING(err) (err>QDMI_SUCCESS)
#define QDMI_IS_ERROR(err)   (err!=QDMI_SUCCESS)
#define QDMI_IS_FATAL(err)   (err<QDMI_SUCCESS)



/*----------------------------------------*/
/* QDMI Constants to represent platform items*/

/* Query interface: Global device properties */
#define QDMI_QUBIT_COUNT       0
#define QDMI_NATIVE_GATE_COUNT 1

/* Query Interface: Gate and Qubit properties*/
#define QDMI_FIDELITY     0
#define QDMI_T1_TIME      1
#define QDMI_T2_TIME      2
#define QDMI_T2_ECHO_TIME 3

/* Well known gate nams */
/*
        QDMI_QUBIT
        QDMI_CNOT
        QDMI_H
 
    (reserved names for well defined gate types)
 */


/*----------------------------------------*/
/* QDMI Type defintions */

typedef void* QDMI_session;
typedef void* QDMI_device;

typedef void* QDMI_job;
typedef void* QDMI_fragment;
typedef int QDMI_status;

typedef int QDMI_qubit_index;
typedef int QDMI_device_property;
typedef int QDMI_gate_property;

typedef void* QDMI_gate;
typedef void* QDMI_unitary;



/*----------------------------------------*/
/* Function defintions */

#ifdef __cplusplus
extern "C" {
#endif


/* Core Session, basic start/close routines */

int QDMI_session_init(QInfo info, QDMI_session *session);
int QDMI_session_finalize(QDMI_session session);


/* Core Interface */

int QDMI_core_version(QDMI_session *session, int* major, int* minor);
int QDMI_core_device_count(QDMI_session *session, int *count);
int QDMI_core_open_device(QDMI_session *session, int idx, QInfo *info, QDMI_device* handle);
int QMPI_core_query_device(QDMI_session *session, int idx, QInfo *info);
int QDMI_core_close_device(QDMI_session *session, QDMI_device handle);

// support linear queue with reordering without QPU splitting
// consider packing


/* Control Interface */

/* Pack routines */

int QDMI_control_pack_qasm2(QDMI_device dev, char *qasmstr, QDMI_fragment *frag);
typedef int (*QDMI_control_pack_qasm2_t)(QDMI_device dev, char *qasmstr, QDMI_fragment *frag);

int QDMI_control_pack_qir(QDMI_device dev, Module *qirmod, QDMI_fragment *frag);
typedef int (*QDMI_control_pack_qir_t)(QDMI_device dev, Module *qirmod, QDMI_fragment *frag);

/* QC job control routines */

int QDMI_control_submit(QDMI_device dev, QDMI_fragment *frag, int numshots, QInfo info, QDMI_job *job);
typedef int (*QDMI_control_submit_t)(QDMI_device dev, QDMI_fragment *frag, int numshots, QInfo info, QDMI_job *job);

int QDMI_control_cancel(QDMI_device dev, QDMI_job *job, QInfo info);
typedef int (*int QDMI_control_cancel_t)(QDMI_device dev, QDMI_job *job, QInfo info);

int QDMI_control_pause(QDMI_device dev, QDMI_job *job, QInfo info);
typedef int (*QDMI_control_pause_t)(QDMI_device dev, QDMI_job *job, QInfo info);

int QDMI_control_test(QDMI_device dev, QDMI_job *job, int *flag, QDMI_status *status);
typedef int (*QDMI_control_test_t)(QDMI_device dev, QDMI_job *job, int *flag, QDMI_status *status);

int QDMI_control_wait(QDMI_device dev, QDMI_job *job, QDMI_status *status);
typedef int (*QDMI_control_wait_t)(QDMI_device dev, QDMI_job *job, QDMI_status *status);

int QDMI_control_extract_state(QDMI_device dev, QDMI_status status, int *state);
typedef int (*QDMI_control_extract_state_t)(QDMI_device dev, QDMI_status status, int *state);

/* read out routines */

int QDMI_control_readout_size(QDMI_device dev, QDMI_status *status, int *numbits);
typedef int (*QDMI_control_readout_size_t)(QDMI_device dev, QDMI_status *status, int *numbits);

/* Histogram */
int QDMI_control_readout_hist_size(QDMI_device dev, QDMI_status *status, int *size);
typedef int (*QDMI_control_readout_hist_size_t)(QDMI_device dev, QDMI_status *status, int *size);
int QDMI_control_readout_hist_top(QDMI_device dev, QDMI_status *status, int numhist, QInfo info, long *hist);
typedef int (*QDMI_control_readout_hist_top_t)(QDMI_device dev, QDMI_status *status, int numhist, QInfo info, long *hist);

/* Full data */
int QDMI_control_readout_raw_num(QDMI_device dev, QDMI_status *status, int *num);
typedef int (*QDMI_control_readout_raw_num_t)(QDMI_device dev, QDMI_status *status, int *num);
int QDMI_control_readout_raw_sample(QDMI_device dev, QDMI_status *status, int numraw, QInfo info, long *hist);
typedef int (*QDMI_control_readout_raw_sample_t)(QDMI_device dev, QDMI_status *status, int numraw, QInfo info, long *hist);


/* Query Interface */

// check if a specific device property exists
int QDMI_query_device_property_exists(QDMI_device dev, QDMI_device_property prop, int* scope);
typedef int (*QDMI_query_device_property_exists_t)(QDMI_device dev, QDMI_device_property prop, int* scope);

// query device property as int or float
int QDMI_query_device_property_i(QDMI_device dev, QDMI_device_property prop, int *value);
typedef int (*QDMI_query_device_property_i_t)(QDMI_device dev, QDMI_device_property prop, int *value);
int QDMI_query_device_property_f(QDMI_device dev, QDMI_device_property prop, float *value);
typedef int (*QDMI_query_device_property_f_t)(QDMI_device dev, QDMI_device_property prop, float *value);
int QDMI_query_device_property_d(QDMI_device dev, QDMI_device_property prop, double *value);
typedef int (*QDMI_query_device_property_d_t)(QDMI_device dev, QDMI_device_property prop, double *value);

// routines to query gate set
int QDMI_query_gateset_num(QDMI_device dev, int *num_gates);
typedef int (*QDMI_query_gateset_num_t)(QDMI_device dev, int *num_gates);
int QDMI_query_one_gate(QDMI_device dev, QDMI_gate *gate);
typedef int (*QDMI_query_one_gate_t)(QDMI_device dev, QDMI_gate *gate);
int QDMI_query_all_gates(QDMI_device dev, QDMI_gate *gates);
typedef int (*QDMI_query_all_gates_t)(QDMI_device dev, QDMI_gate *gates);
int QDMI_query_byname(QDMI_device dev, char *name, QDMI_gate *gate);
typedef int (*QDMI_query_byname_t)(QDMI_device dev, char *name, QDMI_gate *gate);

int QDMI_query_gate_name(QDMI_device dev, QDMI_gate gate, char* name, int* len);
typedef int (*QDMI_query_gate_name_t)(QDMI_device dev, QDMI_gate gate, char* name, int* len);
int QDMI_query_gate_size(QDMI_device dev, QDMI_gate gate, int* gatesize);
typedef int (*QDMI_query_gate_size_t)(QDMI_device dev, QDMI_gate gate, int* gatesize);
int QDMI_query_gate_unitary(QDMI_device dev, QDMI_gate gate, QDMI_unitary *unitary);
typedef int (*QDMI_query_gate_unitary_t)(QDMI_device dev, QDMI_gate gate, QDMI_unitary *unitary);

  
// routines to query gate properties
int QDMI_query_gate_property_exists(QDMI_device dev, QDMI_gate gate, QDMI_gate_property prop, int* scope);
typedef int (*QDMI_query_gate_property_exists_t)(QDMI_device dev, QDMI_gate gate, QDMI_gate_property prop, int* scope);
int QDMI_query_gate_property_i(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, int* value);
typedef int (*QDMI_query_gate_property_i_t)(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, int* value);
int QDMI_query_gate_property_f(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, float* value);
typedef int (*QDMI_query_gate_property_f_t)(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, float* value);
int QDMI_query_gate_property_d(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, double* value);
typedef int (*QDMI_query_gate_property_d_t)(QDMI_device dev, QDMI_gate_property prop, QDMI_gate gate, int *coor, double* value);


/* Device Interface */

/* general query */

int QDMI_device_status(QDMI_device dev, QInfo info, int *status);
typedef int (*QDMI_device_status_t)(QDMI_device dev, QInfo info, int *status);

/* calibration management */
int QDMI_device_quality_check(QDMI_device dev, double *result);
typedef int (*QDMI_device_quality_check_t)(QDMI_device dev, double *result);
int QDMI_device_quality_limit(QDMI_device dev, double *result);
typedef int (*QDMI_device_quality_limit_t)(QDMI_device dev, double *result);
int QDMI_device_quality_calibrate(QDMI_device dev);
typedef int (*QDMI_device_quality_calibrate_t)(QDMI_device dev);


#ifdef __cplusplus
} // extern "C"
#endif

#endif

