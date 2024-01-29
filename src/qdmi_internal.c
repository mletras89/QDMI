#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qdmi_internal.h"
    
QDMI_Session       qdmi_session_list = NULL;
QDMI_Library       qdmi_library_list = NULL;
QDMI_Devicelist_t *qdmi_device_list  = NULL; 

/*----------------------------------------*/
/* QDMI core implementation support functions */

/*.....................................*/
/* Translate QInfo Error into QDMI Error */
/*  IN:  QInfo error code
    RET: QDMI error code
*/

int qdmi_internal_translate_qinfo_error(int err)
{
    switch (err) {
        case QINFO_SUCCESS:
            return QDMI_SUCCESS;
            break;
        case QINFO_ERROR_OUTOFMEM:
            return QDMI_ERROR_OUTOFMEM;
    }
    
    if (err<QDMI_SUCCESS)
        return QDMI_ERROR_FATAL;
    else
        return QDMI_WARN_GENERAL;
}


/*.....................................*/
/* Trim a line by white space and ensure only one word is there */
/*  IN:  pointer to input string
    RET: pointer to trimmed string
 
 Note: returned pointer will always point to within line string
*/

char *trim_line(char *line)
{
    int pos=0;
    char *starter,*poschar;
    
    while ((line[pos]==' ') || (line[pos]=='\t'))
        {
            pos++;
        }
    starter=&(line[pos]);
   
    /* now: leading chars are removed */
    
    do
    {
        poschar=strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",line[pos]);
        if (poschar==NULL) 
        {
            /* kill trailing white space */
            
            while ((line[pos]==' ') || (line[pos]=='\t'))
                {
                    pos++;
                }
            
            /* are we really at the end? */

            if (line[pos]=='\0') return starter;
            
            /* something went wrong, return that we didn't find a proper string */
            
            return NULL;
        }
        pos++;
    }
    while (1);
}

/*.....................................*/
/* Finds the right library in qdmi_library_list */
/*  IN:  pointer to input string
    RET: pointer to QDMI_Library
*/

QDMI_Library find_library_by_name(const char *libname)
{
    QDMI_Library lib = qdmi_library_list;

    while (lib != NULL)
    {
        printf("\nlib->libname: %s =? libname: %s", lib->libname, libname);

        if (strcmp(lib->libname, libname) == 0)
            return lib;

        lib = lib->next;
    }

    return NULL;
}

/*----------------------------------------*/
/* The End. */
