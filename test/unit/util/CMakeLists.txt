###############################################################################
# Copyright (c) 2016-21, Lawrence Livermore National Security, LLC
# and RAJA project contributors. See the RAJA/COPYRIGHT file for details.
#
# SPDX-License-Identifier: (BSD-3-Clause)
###############################################################################

raja_add_test(
  NAME test-float-limits
  SOURCES test-float-limits.cpp)

raja_add_test(
  NAME test-integral-limits
  SOURCES test-integral-limits.cpp)

raja_add_test(
  NAME test-operators
  SOURCES test-operators.cpp)

raja_add_test(
  NAME test-timer
  SOURCES test-timer.cpp)

raja_add_test(
  NAME test-span
  SOURCES test-span.cpp)
