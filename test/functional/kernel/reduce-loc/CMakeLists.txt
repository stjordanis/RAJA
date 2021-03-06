###############################################################################
# Copyright (c) 2016-21, Lawrence Livermore National Security, LLC
# and RAJA project contributors. See the RAJA/COPYRIGHT file for details.
#
# SPDX-License-Identifier: (BSD-3-Clause)
###############################################################################

set(LOCTYPES Min2D Max2D Min2DView Max2DView Min2DViewTuple Max2DViewTuple)

#
# Generate kernel region basic tests for each enabled RAJA back-end.
#
foreach( LOC_BACKEND ${KERNEL_BACKENDS} )
  foreach( LOC_TYPE ${LOCTYPES} )
    configure_file( test-kernel-reduceloc.cpp.in
                    test-kernel-reduceloc-${LOC_TYPE}-${LOC_BACKEND}.cpp )
    raja_add_test( NAME test-kernel-reduceloc-${LOC_TYPE}-${LOC_BACKEND}
                   SOURCES ${CMAKE_CURRENT_BINARY_DIR}/test-kernel-reduceloc-${LOC_TYPE}-${LOC_BACKEND}.cpp )

    target_include_directories(test-kernel-reduceloc-${LOC_TYPE}-${LOC_BACKEND}.exe
                               PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  endforeach()
endforeach()

unset( LOCTYPES )
