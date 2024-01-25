#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <qdmi.h>

int QDMI_load_libraries(QInfo sesioninfo);
int QDMI_internal_startup(QInfo info);
int QDMI_session_init(QInfo info, QDMI_Session *session);
int QDMI_session_finalize(QDMI_Session session);
int QDMI_internal_shutdown(void);

#define CHECK_ERR(a,b) { if (a!=QDMI_SUCCESS) { printf("\nError: %i at %s\n",a,b); return 1; }}

int main(int argc, char** argv)
{
    QInfo info;
    QDMI_Session session = NULL;
    int err, count = 0;

    err = QInfo_create(&info);
    CHECK_ERR(err, "QInfo_create");

    // QDMI_session_init(info, &session) -> QDMI_internal_startup(info) -> QDMI_load_libraries(info) -> QInfo_create(&(newlib->info))
    err = QDMI_session_init(info, &session);
    CHECK_ERR(err, "QDMI_session_init");

    //err = QDMI_core_device_count(&session, &count);
    //CHECK_ERR(err, "QDMI_core_device_count");
    //printf("\nQDMI_core_device_count: %d", count);

    // QDMI_session_finalize(session) -> QDMI_internal_shutdown()
    err = QDMI_session_finalize(session);
    CHECK_ERR(err, "QDMI_session_finalize");

    err = QInfo_free(info);
    CHECK_ERR(err, "QInfo_free");
    
    printf("\n[DEBUG]: Test Finished\n\n");

    return 0;
}


