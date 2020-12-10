/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   RAJA header file defining SIMD/SIMT register operations.
 *
 ******************************************************************************
 */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2016-19, Lawrence Livermore National Security, LLC
// and RAJA project contributors. See the RAJA/COPYRIGHT file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#ifndef RAJA_pattern_vector_matrixproductref_HPP
#define RAJA_pattern_vector_matrixproductref_HPP

#include "RAJA/config.hpp"

#include "RAJA/util/macros.hpp"

#include <array>

namespace RAJA
{
namespace internal
{

  template<typename MATRIX_TYPE, typename INDEX_TYPE,
           typename POINTER_TYPE, bool ROW_STRIDE_ONE, bool COL_STRIDE_ONE>
  class MatrixRef;

/*!
 * \file
 * Vector operation functions in the namespace RAJA

 *
 */

  template<typename A_MATRIX_TYPE, typename B_MATRIX_TYPE>
  class MatrixProductRef {
    public:
      using self_type =
          MatrixProductRef<A_MATRIX_TYPE, B_MATRIX_TYPE>;

      using element_type = typename A_MATRIX_TYPE::element_type;

      using helper_t = MatrixMatrixProductHelper<A_MATRIX_TYPE, B_MATRIX_TYPE>;

      using result_type = typename helper_t::result_type;

      using register_policy = typename A_MATRIX_TYPE::register_policy;

    private:
      A_MATRIX_TYPE const &m_matrix_a;
      B_MATRIX_TYPE const &m_matrix_b;

    public:



      /*!
       * @brief Constructor
       */
      RAJA_HOST_DEVICE
      RAJA_INLINE
      constexpr
      MatrixProductRef(A_MATRIX_TYPE const &a, B_MATRIX_TYPE const &b) :
      m_matrix_a(a),
      m_matrix_b(b)
          {}


      /*!
       * @brief Copy constructor
       */
      RAJA_HOST_DEVICE
      RAJA_INLINE
      constexpr
      MatrixProductRef(self_type const &c) :
      m_matrix_a(c.m_matrix_a),
      m_matrix_b(c.m_matrix_b)
          {}


      RAJA_HOST_DEVICE
      RAJA_INLINE
      static
      constexpr
      bool is_root() {
        return result_type::is_root();
      }

      RAJA_HOST_DEVICE
      RAJA_INLINE
      result_type get_result() const
      {
        return helper_t::multiply(m_matrix_a, m_matrix_b);
      }

      RAJA_HOST_DEVICE
      RAJA_INLINE
      constexpr
      A_MATRIX_TYPE const &get_left() const
      {
        return m_matrix_a;
      }

      RAJA_HOST_DEVICE
      RAJA_INLINE
      constexpr
      B_MATRIX_TYPE const &get_right() const
      {
        return m_matrix_b;
      }


      /*!
       * @brief Automatic conversion to the underlying vector_type.
       *
       * This will evaluate the underlying operation on the two vectors
       */
      RAJA_HOST_DEVICE
      RAJA_INLINE
      operator result_type() const {
        return get_result();
      }







      /*!
       * @brief Add this product to another vector with an FMA.
       * @param x Vector to add to this product
       * @return Value of (*this)+x
       */
      RAJA_HOST_DEVICE
      RAJA_INLINE
      result_type operator+(result_type const &x) const
      {
        return helper_t::multiply_accumulate(m_matrix_a, m_matrix_b, x);
      }



      /*!
       * @brief Subtract two vector registers
       * @param x Vector to subctract from this register
       * @return Value of (*this)+x
       */
      RAJA_HOST_DEVICE
      RAJA_INLINE
      result_type operator-(result_type const &x) const
      {
        return helper_t::multiply_accumulate(m_matrix_a, m_matrix_b, -x);
      }



      /*!
       * @brief Multiply two vector registers, element wise
       * @param x Vector to subctract from this register
       * @return Value of (*this)+x
       */
      template<typename MAT>
      RAJA_HOST_DEVICE
      RAJA_INLINE
      MatrixProductRef<result_type, MAT> operator*(MAT const &x) const
      {
        return MatrixProductRef<result_type, MAT>(get_result(), x);
      }


      /*!
       * @brief Multiply two vector registers, element wise
       * @param x Vector to subctract from this register
       * @return Value of (*this)+x
       */
      RAJA_HOST_DEVICE
      RAJA_INLINE
      MatrixProductRef<result_type, RegisterMatrix<element_type, typename A_MATRIX_TYPE::layout_type, register_policy> >
      operator*(RegisterMatrix<element_type, typename A_MATRIX_TYPE::layout_type, register_policy> const &x) const
      {
        return MatrixProductRef<result_type, RegisterMatrix<element_type, typename A_MATRIX_TYPE::layout_type, register_policy> >(get_result(), x);
      }

      /*!
       * @brief Multiply two MatrixRefs
       */
      template<typename MT, typename ID,
                typename PT, bool RSO, bool CSO>
      RAJA_HOST_DEVICE
      RAJA_INLINE
      MatrixProductRef<result_type, MT >
      operator*(MatrixRef<MT, ID, PT, RSO, CSO> const &x) const
      {
        return MatrixProductRef<result_type, MT>(get_result(), x.load());
      }


  };




}  // namespace internal
}  // namespace RAJA


#endif