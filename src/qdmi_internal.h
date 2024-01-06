/* Internal Headerfile for the QDMI core implementation */

#ifndef QDMI_INTERNAL_H
#define QDMI_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>

#include <qinfo.h>
#include <qdmi_backend.h>
    
/*----------------------------------------*/
/* Internal-use constants */

#define QDMI_CONFIG_FILE "QDMI_CONFIG_FILE"
#define QDMI_CONFIG_FILE_DEFAULT ".qdmi-config"


/*----------------------------------------*/
/* Internal-use types */

typedef struct QDMI_internal_library_d
{
    /* Info object */
    
    QInfo info;
    
    /* Name of the library to open */
    
    char *libname;
    
    /* Library handle */
    
    void *libhandle;
    
    /* All library management functions */
    
    QDMI_backend_init_t                 QDMI_backend_init;

    
    /* All public functions */
    
    QDMI_control_pack_qasm2_t           QDMI_control_pack_qasm2;
    QDMI_control_pack_qir_t             QDMI_control_pack_qir;
    QDMI_control_submit_t               QDMI_control_submit;
    QDMI_control_cancel_t               QDMI_control_cancel;
    QDMI_control_pause_t                QDMI_control_pause;
    QDMI_control_test_t                 QDMI_control_test;
    QDMI_control_wait_t                 QDMI_control_wait;
    QDMI_control_extract_state_t        QDMI_control_extract_state;
    QDMI_control_readout_size_t         QDMI_control_readout_size;
    QDMI_control_readout_hist_size_t    QDMI_control_readout_hist_size;
    QDMI_control_readout_hist_top_t     QDMI_control_readout_hist_top;
    QDMI_control_readout_raw_num_t      QDMI_control_readout_raw_num;
    QDMI_control_readout_raw_sample_t   QDMI_control_readout_raw_sample;
    QDMI_query_device_property_exists_t QDMI_query_device_property_exists;
    QDMI_query_device_property_i_t      QDMI_query_device_property_i;
    QDMI_query_device_property_f_t      QDMI_query_device_property_f;
    QDMI_query_device_property_d_t      QDMI_query_device_property_d;
    QDMI_query_gateset_num_t            QDMI_query_gateset_num;
    QDMI_query_one_gate_t               QDMI_query_one_gate;
    QDMI_query_all_gates_t              QDMI_query_all_gates;
    QDMI_query_byname_t                 QDMI_query_byname;
    QDMI_query_gate_name_t              QDMI_query_gate_name;
    QDMI_query_gate_size_t              QDMI_query_gate_size;
    QDMI_query_gate_unitary_t           QDMI_query_gate_unitary;
    QDMI_query_gate_property_exists_t   QDMI_query_gate_property_exists;
    QDMI_query_gate_property_i_t        QDMI_query_gate_property_i;
    QDMI_query_gate_property_f_t        QDMI_query_gate_property_f;
    QDMI_query_gate_property_d_t        QDMI_query_gate_property_d;
    QDMI_device_status_t                QDMI_device_status;
    QDMI_device_quality_check_t         QDMI_device_quality_check;
    QDMI_device_quality_limit_t         QDMI_device_quality_limit;
    QDMI_device_quality_calibrate_t     QDMI_device_quality_calibrate;
    
    /* Pointer to next library */
    
    QDMI_internal_library_t *next;
} QDMI_internal_library_t;

typedef QDMI_internal_library_t *QDMI_library;

typedef struct QDMI_devicelist_d
{
    QDMI_device_impl_t device;
    QDMI_devicelist_t *next;
} QDMI_devicelist_t;


/*----------------------------------------*/
/* Type concretizations */

typedef struct QDMI_Session_impl_d;
{
    QInfo info;
    QDMI_Session_impl_t *next;
} QDMI_Session_impl_t;

typedef QDMI_Session *QDMI_Session_impl_t;


/*----------------------------------------*/
/* Anchors for global lists */

QDMI_session      *qdmi_session_list = NULL;
QDMI_library      *qdmi_library_list = NULL;
QDMI_devicelist_t *qdmi-device_list  = NULL;


/*----------------------------------------*/
/* Internal-use Function definitions */

#ifdef __cplusplus
extern "C" {
#endif

/* Internal functions */

int qdmi_internal_translate_qinfo_error(int err);
char *trim_line(char *line);
  
#ifdef __cplusplus
} // extern "C"
#endif

#endif

