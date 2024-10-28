/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/device.h"
#include "test_impl_direct.hpp"

#include <gtest/gtest.h>

TEST_F(QDMIImplementationTest, QubitNum) {
  int num_qubits = 0;
  EXPECT_EQ(QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM,
                                           sizeof(int), &num_qubits, nullptr),
            QDMI_SUCCESS);
}
