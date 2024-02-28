#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <qdmi.h>
#include "qdmi_internal.h"

int QDMI_session_init(QInfo info, QDMI_Session *session);
int QDMI_session_finalize(QDMI_Session session);
QDMI_Library find_library_by_name(const char *libname);

#define CHECK_ERR(a,b) { if (a!=QDMI_SUCCESS) { printf("\n[Error]: %i at %s",a,b); return 1; }}

int main(int argc, char** argv)
{
    QInfo info;
    QDMI_Session session = NULL;
    QDMI_Library lib;
    QDMI_Fragment frag;
    QDMI_Device device;
    QDMI_Job job;
    int err, count = 0;

    device = malloc(sizeof(struct QDMI_Device_impl_d));
    if (device == NULL)
    {
	printf("\n[ERROR]: Device could not be created");
        exit(EXIT_FAILURE);
    }

    err = QInfo_create(&info);
    CHECK_ERR(err, "QInfo_create");

    // QDMI_session_init(info, &session) -> QDMI_internal_startup(info) -> QDMI_load_libraries(info) -> QInfo_create(&(newlib->info))
    err = QDMI_session_init(info, &session);
    CHECK_ERR(err, "QDMI_session_init");

    frag = (QDMI_Fragment)malloc(sizeof(struct QDMI_Fragment_d));
    if (frag == NULL)
    {
        QDMI_session_finalize(session);

        printf("\n[ERROR]: The fragment could not be created");
        exit(EXIT_FAILURE);
    }
    
    char * buffer = 0;
    long length;
    FILE * f = fopen ("../inputs/basic_circuit.ll", "rb");
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    frag->qirmod = malloc (length);
    fread (frag->qirmod, 1, length, f);
    fclose (f);

    //frag->qirmod = buffer;
    
    lib = find_library_by_name("/home/martin/bin/lib/libbackend_wmi.so");
    if(!lib)
    {
	    printf("\n[ERROR]: Library could not be found");
        exit(EXIT_FAILURE);
    }
    device->library = *lib;

    err = QDMI_control_submit(device, &frag, 10000, device->library.info, &job);
    CHECK_ERR(err, "QDMI_control_submit");

    // QDMI_session_finalize(session) -> QDMI_internal_shutdown()
    err = QDMI_session_finalize(session);
    CHECK_ERR(err, "QDMI_session_finalize");

    err = QInfo_free(info);
    CHECK_ERR(err, "QInfo_free");
    
    free(frag->qirmod);
    free(frag);
    free(device);

    printf("\n[DEBUG]: Test Finished\n\n");

    return 0;
}

