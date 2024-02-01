#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dlfcn.h>
#include <string.h>

#include <qdmi_backend.h>
#include "qdmi_internal.h"

#define CHECK_ERR(a,b) { if (a!=QDMI_SUCCESS) { printf("\n[Error]: %i at %s",a,b); return 1; }}

int QDMI_device_status(QDMI_Device dev, QInfo info, int *status)
{
    printf("\n[DEBUG]: Q5 Backend - QDMI_device_status");
    return 0;
}

int QDMI_backend_init(QInfo info)
{
    printf("\n[DEBUG]: Q5 Backend - QDMI_backend_init");

    char *uri = NULL;
    void *regpointer = NULL;
    int err;

    err = QDMI_core_register_belib(uri, regpointer);
    //CHECK_ERR(err, "QDMI_core_register_belib");

    return 0;
}

int QDMI_control_submit(QDMI_Device dev, QDMI_Fragment *frag, int numshots, QInfo info, QDMI_Job *job)
{
    printf("\n[DEBUG]: Q5 Backend - QDMI_control_submit");
    printf("\n[DEBUG]: Q5 Backend - (*frag)->QIR_bitcode: ");
    printf("%s", (*frag)->QIR_bitcode);
    return 0;
}
