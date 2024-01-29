#include "qdmi_internal.h"
#include <qdmi.h>

QDMI_Device QDMI_allocate_device()
{
    return malloc(sizeof(struct QDMI_Device_impl_d));
}

QDMI_Job QDMI_allocate_job()
{
    return malloc(sizeof(struct QDMI_Job_impl_d));
}
