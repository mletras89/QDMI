#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dlfcn.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#include "qdmi_backend_wmi.h"

#define BUZZ_SIZE 65
#define CHECK_ERR(a,b) { if (a!=QDMI_SUCCESS) { printf("\n[Error]: %i at %s",a,b); return 1; }}

struct ResponseStruct {
    cJSON *json;
    size_t size;
};

// directly parsing response to json
size_t parse_json(void *contents, size_t size, size_t nmemb, struct ResponseStruct *response){
    
    size_t realsize = size * nmemb;
    
    struct ResponseStruct *mem = (struct ResponseStruct *)response;
    
    cJSON *ptr = cJSON_ParseWithLength(contents, realsize);
  
    if(!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
  
    mem->json = ptr;
    mem->size += realsize;
  
    return realsize;
}

// import api token from folder
char *get_token(){ 
    char token[BUZZ_SIZE];
    FILE *f = fopen("token.txt", "r");
    fgets(token, BUZZ_SIZE, f);
    fclose(f);

    char *token_header = NULL;
    asprintf(&token_header,"access-token: %s", token);

    return(token_header);
}


// how many gates, what is dev? assume 1 backend for now
int QDMI_query_gateset_num(QDMI_Device dev, int *num_gates)
{
    if (sizeof(gate_set) > 0)
        *num_gates = sizeof(gate_set) / sizeof(gate_set[0]);
    else
        *num_gates = 0;

    return QDMI_SUCCESS;
}

// These properties are dummy values, why query each individually and not all at once like qiskit properties?
void QDMI_get_gate_info(QDMI_Device dev, int gate_index, QDMI_Gate gate)
{
    gate->name     = gate_set[gate_index];
    gate->unitary  = "Unitary_Matrix";
    gate->fidelity = 1.0;
}

// get complete list of gate objects with supposedly real properties
int QDMI_query_all_gates(QDMI_Device dev, QDMI_Gate *gates)
{
    int i, num_gates = 0;
    QDMI_query_gateset_num(dev, &num_gates);

    *gates = (QDMI_Gate)malloc(num_gates * sizeof(QDMI_Gate_impl_t));

    for (i = 0; i < num_gates; i++)
        QDMI_get_gate_info(dev, i, (*gates) + i);

    return QDMI_SUCCESS;
}

// get status of device. 
int QDMI_device_status(QDMI_Device dev, QInfo info, int *status)
{   
    CURL *curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Init failed\n");
        return EXIT_FAILURE;
    }
    char *token_header = get_token();

    struct ResponseStruct response;
    response.json = NULL;
    response.size = 0;

    // set options
    curl_easy_setopt(curl, CURLOPT_URL, "https://wmiqc-api.wmi.badw.de/1/wmiqc/qobj");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parse_json);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, token_header);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // payload
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"qobj\": {\"config\": {\"chip\": \"dedicated\"}}}");
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    // send request
    CURLcode result = curl_easy_perform(curl);
    if (result  != CURLE_OK){
        fprintf(stderr, "Request problem: %s\n", curl_easy_strerror(result));
    } 
    
    // obtain result 
    char *backend_status = response.json->child->valuestring;

    // I set status = 0 for offline, status = 1 for online
    if (strcmp(backend_status, "online") == 0){
        *status = 1;
    } 
    else if (strcmp(backend_status, "offline") == 0){
        *status = 0;
    } 
    
    free(response.json);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return QDMI_SUCCESS;
}

// init not needed for wmi backend
int QDMI_backend_init(QInfo info)
{
    printf("   [Backend].............WMI doesn't need initialization via QDMI\n");

    char *uri = NULL;
    void *regpointer = NULL;
    int err;

    err = QDMI_core_register_belib(uri, regpointer);
    //CHECK_ERR(err, "QDMI_core_register_belib");

    return QDMI_SUCCESS;
}

// num classical bits in measurement, same as qubits. Why status needed?
int QDMI_control_readout_size(QDMI_Device dev, QDMI_Status *status, int *numbits)
{
    printf("   [Backend].............Returning size\n");
    
    *numbits = 3;
    return QDMI_SUCCESS;
}

// looks like this returns the number of measured bitstrings for each outcome
int QDMI_control_readout_raw_num(QDMI_Device dev, QDMI_Status *status, int *num)
{
    printf("   [Backend].............Returning raw numbers\n");

    int err = 0, numbits = 0;
    long i;

    err = QDMI_control_readout_size(dev, status, &numbits);
    CHECK_ERR(err, "QDMI_control_readout_raw_num");

    for (i = 0; i < ((long)1 << numbits); i++)
        num[i] = rand();

    return QDMI_SUCCESS;
}

// hardcoded coupling map as for each qubit, what are the two neighbours. Are QDMI qubits 1 indexed? Assuming yes and full connectivity for chip.
void QDMI_set_coupling_mapping(QDMI_Device dev, int qubit_index, QDMI_Qubit qubit)
{
    qubit->index = qubit_index;

    switch (qubit_index) {
        case 1:
            qubit->coupling_mapping = (QDMI_qubit_index*)malloc(2 * sizeof(QDMI_qubit_index));
            qubit->coupling_mapping[0] = 2;
            qubit->coupling_mapping[1] = 3;
            break;
        case 2:
            qubit->coupling_mapping = (QDMI_qubit_index*)malloc(2 * sizeof(QDMI_qubit_index));
            qubit->coupling_mapping[0] = 1;
            qubit->coupling_mapping[1] = 3;
            break;
        case 3:
            qubit->coupling_mapping = (QDMI_qubit_index*)malloc(3 * sizeof(QDMI_qubit_index));
            qubit->coupling_mapping[0] = 1;
            qubit->coupling_mapping[1] = 2;
            break;
        // don't know what default does
        default:
            qubit->coupling_mapping = NULL;
            break; 
    }
}

// Looks like this is initializing qubits and setting the coupling map for each qubit
int QDMI_query_all_qubits(QDMI_Device dev, QDMI_Qubit *qubits)
{
    int err, num_qubits;

    // TODO Handle err
    err = QDMI_query_qubits_num(dev, &num_qubits);

    *qubits = (QDMI_Qubit)malloc(num_qubits * sizeof(QDMI_Qubit_impl_t));

    if (*qubits == NULL)
    {
        printf("   [Backend].............Couldn't allocate memory for the qubit array\n");
        return QDMI_WARN_GENERAL;
    }

    int i;
    for (i = 0; i < num_qubits; i++)
    {
        QDMI_set_coupling_mapping(dev, i, (*qubits) + i);
    }

    printf("   [Backend].............Returning available qubits\n");
    return QDMI_SUCCESS;
}

// number of qubits 
int QDMI_query_qubits_num(QDMI_Device dev, int *num_qubits)
{
    *num_qubits = 3;
    printf("   [Backend].............QDMI_query_qubits_num\n");
    return QDMI_SUCCESS;
}

// submit function. Need to know what the different structs are for
int QDMI_control_submit(QDMI_Device dev, QDMI_Fragment *frag, int numshots, QInfo info, QDMI_Job *job)
{
    printf("   [Backend].............QDMI_control_submit\n");
    //printf("   [Backend].............(*frag)->QIR_bitcode: %s\n", (*frag)->QIR_bitcode);

    return QDMI_SUCCESS;
}
