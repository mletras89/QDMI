#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dlfcn.h>
#include <string.h>

#include <qdmi_backend.h>

int QDMI_core_register_belib(char *uri, void *regpointer)
{
    printf("\n[DEBUG]: Q5 Backend - QDMI_core_register_belib");
    return 0;
}

int QDMI_core_unregister_belib(char *uri)
{
    printf("\n[DEBUG]: Q5 Backend - QDMI_core_unregister_belib");
    return 0;
}

int QDMI_device_status(QDMI_Device dev, QInfo info, int *status)
{
    printf("\n[DEBUG]: Q5 Backend - QDMI_device_status");
    return 0;
}

int QDMI_backend_init(QInfo info)
{
    printf("\n[DEBUG]: Q5 Backend - QDMI_backend_init");
    return 0;
}
