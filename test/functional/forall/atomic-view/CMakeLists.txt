###############################################################################
# Copyright (c) 2016-21, Lawrence Livermore National Security, LLC
# and RAJA project contributors. See the RAJA/COPYRIGHT file for details.
#
# SPDX-License-Identifier: (BSD-3-Clause)
###############################################################################

#
# List of atomic test types for generating test files.
#
set(TESTTYPES AtomicView AtomicMultiView)

#
# Generate tests for each enabled RAJA back-end.
#
# Note: FORALL_ATOMIC_BACKENDS is defined in ../CMakeLists.txt
#
foreach( ATOMIC_BACKEND ${FORALL_ATOMIC_BACKENDS} )
  foreach( TEST ${TESTTYPES} )
    configure_file( test-forall-atomic-view.cpp.in
                    test-forall-${TEST}-${ATOMIC_BACKEND}.cpp )
    raja_add_test( NAME test-forall-${TEST}-${ATOMIC_BACKEND}
                   SOURCES ${CMAKE_CURRENT_BINARY_DIR}/test-forall-${TEST}-${ATOMIC_BACKEND}.cpp )

    target_include_directories(test-forall-${TEST}-${ATOMIC_BACKEND}.exe
                                 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  endforeach()
endforeach()

unset( TESTTYPES )
