#ifndef QDMIBACKENDQ20_H
#define QDMIBACKENDQ20_H

#include <qdmi_backend.h>
#include "qdmi_internal.h"

const char *gate_set[] = 
{
    "__quantum__qis__barrier__body", "__quantum__qis__ccx__body",
    "__quantum__qis__cx__body",      "__quantum__qis__cnot__body",
    "__quantum__qis__cz__body",      "__quantum__qis__h__body",
    "__quantum__qis__mz__body",      "__quantum__qis__reset__body",
    "__quantum__qis__rx__body",      "__quantum__qis__ry__body",
    "__quantum__qis__rz__body",      "__quantum__qis__s__body",
    "__quantum__qis__s_adj__body",   "__quantum__qis__swap__body",
    "__quantum__qis__t__body",       "__quantum__qis__t_adj__body",
    "__quantum__qis__x__body",       "__quantum__qis__y__body",
    "__quantum__qis__z__body",       "__quantum__qis__if_result__body",
};

#endif // QDMIBACKENDQ20_H
