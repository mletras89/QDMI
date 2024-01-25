#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <qdmi.h>
#include "../src/qdmi_internal.h"

int QDMI_session_init(QInfo info, QDMI_Session *session);
int QDMI_session_finalize(QDMI_Session session);
QDMI_Library find_library_by_name(const char *libname);

#define CHECK_ERR(a,b) { if (a!=QDMI_SUCCESS) { printf("\n[Error]: %i at %s",a,b); return 1; }}

int main(int argc, char** argv)
{
    QInfo info;
    QDMI_Session session = NULL;
    QDMI_Library lib;
    QDMI_Fragment *frag;
    QDMI_Device device;
    QDMI_Job *job;
    int err, count = 0;

    device = malloc(sizeof(struct QDMI_Device_impl_d));
    if (device == NULL)
        exit(EXIT_FAILURE);

    err = QInfo_create(&info);
    CHECK_ERR(err, "QInfo_create");

    // QDMI_session_init(info, &session) -> QDMI_internal_startup(info) -> QDMI_load_libraries(info) -> QInfo_create(&(newlib->info))
    err = QDMI_session_init(info, &session);
    CHECK_ERR(err, "QDMI_session_init");

    lib = find_library_by_name("libbackend_q5.so");
    if(!lib)
    {
	printf("\n[ERROR]: Library cannot be found");
	return 1;
    }
    device->library = *lib;
    err = QDMI_control_submit(device, frag, 10000, device->library.info, job);
    CHECK_ERR(err, "QDMI_control_submit");

    // QDMI_session_finalize(session) -> QDMI_internal_shutdown()
    err = QDMI_session_finalize(session);
    CHECK_ERR(err, "QDMI_session_finalize");

    err = QInfo_free(info);
    CHECK_ERR(err, "QInfo_free");
    
    printf("\n[DEBUG]: Test Finished\n\n");

    return 0;
}


