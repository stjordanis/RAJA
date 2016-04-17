/*
 * Copyright (c) 2016, Lawrence Livermore National Security, LLC.
 *
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * For release details and restrictions, please see raja/README-license.txt
 */


/**
 *
 * This is the non-code-generated for Lambda-Free (lf) forallN implementation.
 *
 * We bent over backwards to avoid using lambdas anywhere in this code,
 * instead using functors and other struct objects, in order to avoid the
 * CUDA host/device labmda issue.
 *
 */


#ifndef RAJA_forallN_generic_lf_HXX__
#define RAJA_forallN_generic_lf_HXX__

#include"config.hxx"
#include"int_datatypes.hxx"
#include<tuple>

namespace RAJA {



/******************************************************************
 *  ForallN generic policies
 ******************************************************************/

template<typename P, typename I>
struct ForallN_PolicyPair : public I {
  
  typedef P POLICY;
  typedef I ISET;

  RAJA_INLINE
  constexpr ForallN_PolicyPair(ISET const &i) : ISET(i) {}
};


template<typename ... PLIST>
struct ExecList{
  constexpr const static size_t num_loops = sizeof...(PLIST);
  typedef std::tuple<PLIST...> tuple;
};



// Execute (Termination default)
struct ForallN_Execute_Tag {};


struct Execute {
  typedef ForallN_Execute_Tag PolicyTag;
};

template<typename EXEC, typename NEXT=Execute>
struct NestedPolicy {
  typedef NEXT NextPolicy;
  typedef EXEC ExecPolicies;
};



/******************************************************************
 *  ForallN_Executor(): Default Executor for loops
 ******************************************************************/


template<typename BODY, typename INDEX_TYPE=Index_type>
struct ForallN_BindFirstArg {

  BODY const body;
  INDEX_TYPE const i;

  RAJA_INLINE
  RAJA_HOST_DEVICE
  constexpr
  ForallN_BindFirstArg(BODY const &b, INDEX_TYPE i0) : body(b), i(i0) {}

  template<typename ... ARGS>
  RAJA_INLINE
  RAJA_HOST_DEVICE
  void  operator()(ARGS ... args) const {
    body(i, args...);
  }
};

template<typename NextExec, typename BODY>
struct ForallN_PeelOuter {

  NextExec const next_exec;
  BODY const body;

  RAJA_INLINE
  constexpr
  ForallN_PeelOuter(NextExec const &ne, BODY const &b) : next_exec(ne), body(b) {}

  RAJA_INLINE
  void operator()(Index_type i) const {
    ForallN_BindFirstArg<BODY> inner(body, i);
    next_exec(inner);
  }
  
  RAJA_INLINE
  void operator()(Index_type i, Index_type j) const {
    ForallN_BindFirstArg<BODY> inner_i(body, i);
    ForallN_BindFirstArg<decltype(inner_i)> inner_j(inner_i, j);
    next_exec(inner_j);
  }
};

template<typename ... PREST>
struct ForallN_Executor {};

template<typename PI, typename ... PREST>
struct ForallN_Executor<PI, PREST...> {
  typedef typename PI::ISET TI;
  typedef typename PI::POLICY POLICY_I;

  typedef ForallN_Executor<PREST...> NextExec;

  PI const is_i;
  NextExec next_exec;

  template<typename ... TREST>
  constexpr
  ForallN_Executor(PI const &is_i0, TREST ... is_rest) : is_i(is_i0), next_exec(is_rest...) {}

  template<typename BODY>
  RAJA_INLINE
  void operator()(BODY body) const {
    ForallN_PeelOuter<NextExec, BODY> outer(next_exec, body);
    RAJA::forall<POLICY_I>(is_i, outer);
  }
};

template<>
struct ForallN_Executor<> {
  constexpr
  ForallN_Executor()  {}

  template<typename BODY>
  RAJA_INLINE void operator()(BODY body) const {
    body();
  }
};


/******************************************************************
 *  forallN_policy(), base execution policies
 ******************************************************************/


/*!
 * \brief Execute inner loops policy function.
 *
 * This is the default termination case.
 */
 
template<typename POLICY, typename BODY, typename ... ARGS>
RAJA_INLINE
void forallN_policy(ForallN_Execute_Tag, BODY body, ARGS ... args){

  // Create executor object to launch loops
  ForallN_Executor<ARGS...> exec(args...);

  // Launch loop body
  exec(body);
}



/******************************************************************
 *  Index type conversion, wraps lambda given by user with an outer
 *  callable object where all variables are Index_type
 ******************************************************************/



template<typename BODY, typename IdxI, typename ... IdxRest>
struct ForallN_IndexTypeConverter {

  RAJA_INLINE
  RAJA_HOST_DEVICE
  constexpr
  explicit ForallN_IndexTypeConverter(BODY const &b) : body(b) {}

  // call 'policy' layer with next policy
  template<typename ... ARGS>
  RAJA_INLINE
  RAJA_HOST_DEVICE
  void operator()(Index_type i, ARGS ... args) const {
    // Bind the first argument
    ForallN_BindFirstArg<BODY, IdxI> bound(body, IdxI(i));

    // Peel a wrapper
    ForallN_IndexTypeConverter<ForallN_BindFirstArg<BODY, IdxI>, IdxRest...> inner(bound);
    inner(args...);
  }

  // Copy of loop body
  BODY const body;
};

template<typename BODY, typename IdxI>
struct ForallN_IndexTypeConverter<BODY, IdxI> {

  RAJA_INLINE
  RAJA_HOST_DEVICE
  constexpr
  explicit ForallN_IndexTypeConverter(BODY const &b) : body(b) {}

  // call 'policy' layer with next policy
  RAJA_INLINE
  RAJA_HOST_DEVICE
  void operator()(Index_type i) const {
    body(IdxI(i));
  }

  // Copy of loop body
  BODY const body;
};




} // namespace RAJA
  
#endif

