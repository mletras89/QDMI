/* Headerfile to be included by all QDMI backend implementations */

#ifndef QDMI_BACKEND_H
#define QDMI_BACKEND_H

#include <stdio.h>
#include <stdlib.h>

#include <qdmi.h>
    
/*----------------------------------------*/
/* Backend-only constants */

#define QINFO_INTERNAL_SPACEGRANULARITY 10


/*----------------------------------------*/
/* Backend-only types */

typedef struct QInfo_value_space_d
{
    QInfo_value value;
    int         occupied;
    char        *name;
} QInfo_value_space_t;


/*----------------------------------------*/
/* Type concretizations for all backends */

typedef struct QDMI_device_impl_d
{
    QInfo           libinfo;
    QInfo           sessioninfo;
    QDMI_library    *library;
    void            *device_state;
} QDMI_device_impl_t;
typedef QDMI_device_impl_t* QDMI_device;

typedef void* QDMI_job;
typedef void* QDMI_fragment;

typedef void* QDMI_gate;
typedef void* QDMI_unitary;

/*----------------------------------------*/
/* Backend-only Function defintions */

#ifdef __cplusplus
extern "C" {
#endif

/* Functions in the QDMI library to be called by the backend libraries */

int QDMI_core_register_belib(char *uri, void *regpointer);
int QDMI_core_unregister_belib(char *uri);

/* Functions that the backend libraries need to provide */

int QDMI_backend_init(Qinfo info);
typedef int (*QDMI_backend_init_t)(Qinfo info);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

