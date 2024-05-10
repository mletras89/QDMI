#ifndef QDMIBACKENDQLM_H
#define QDMIBACKENDQLM_H

#include <qdmi_backend.h>
#include <qdmi_internal.h>

#include "rabbitmq-c/amqp.h"
#include "rabbitmq-c/tcp_socket.h"

#define INSTRUCTIONSIZE 100
#define N_GATE 19
#define N_R_GATE 3

#define HOST_NAME "10.195.1.175"
#define PORT 5672

amqp_connection_state_t SendConnection, ListenConnection;
amqp_socket_t *SendSocket = NULL, *Listensocket = NULL;

const char *gate_set[] = {
    "__quantum__qis__h__body",         "__quantum__qis__x__body",
    "__quantum__qis__y__body",         "__quantum__qis__z__body",
    "__quantum__qis__t__body",         "__quantum__qis__s__body",

    "__quantum__qis__s_adj__body",     "__quantum__qis__t_adj__body",
    "__quantum__qis__rx__body",        "__quantum__qis__ry__body",
    "__quantum__qis__rz__body",        "__quantum__qis__mz__body",
    "__quantum__qis__cx__body",        "__quantum__qis__cz__body",
    "__quantum__qis__swap__body",      "__quantum__qis__ccx__body",
    "__quantum__qis__cnot__body",

    "__quantum__qis__barrier__body",   "__quantum__qis__reset__body",

    "__quantum__qis__if_result__body",
};

const char *qasm_gate_set[] = {

    "h q[%d];\n",
    "x q[%d];\n",
    "y q[%d];\n",
    "z q[%d];\n",
    "t q[%d];\n",
    "s q[%d];\n",
    "sdg q[%d];\n",
    "tdg q[%d];\n",
    "rx(%s) q[%d];\n",
    "ry(%s) q[%d];\n",
    "rz(%s) q[%d];\n",
    "measure q[%d] -> c[%d];\n",
    "cx q[%d], q[%d];\n",
    "cz q[%d], q[%d];\n",
    "swap q[%d], q[%d];\n",
    "ccx q[%d], q[%d] q[%d];\n",
    "cx q[%d], q[%d];\n",
    "barrier q[%d]",
    "reset q[%d]",
    "if(c%d==%d)\n",

};

const char *rotation_gate_set[] = {
    "__quantum__qis__rx__body",        "__quantum__qis__ry__body",
    "__quantum__qis__rz__body",       
};

#endif // QDMIBACKENDQLM_H
