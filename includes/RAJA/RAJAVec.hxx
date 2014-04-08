/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   RAJA header file for simple vector template class that enables 
 *          RAJA to be used with or without STL vectors.
 *     
 * \author  Rich Hornung, Center for Applied Scientific Computing, LLNL
 * \author  Jeff Keasler, Applications, Simulations And Quality, LLNL
 *
 ******************************************************************************
 */

#ifndef RAJA_RAJAVec_HXX
#define RAJA_RAJAVec_HXX

#if defined(RAJA_USE_STL)
#include <vector>
#include <algorithm>
#endif


namespace RAJA {

/*!
 ******************************************************************************
 *
 * \brief  Class template that provides a simple vector implementation 
 *         sufficient to insulate RAJA entities from the STL.
 *
 *         Note: This class has limited functionality sufficient to 
 *               support its usage for RAJA HybridISet operations.
 *  
 *               Template type should support standard semantics for
 *               copy, swap, etc. 
 *
 ******************************************************************************
 */
template< typename T>
class RAJAVec
{
public:
   //
   // Construct empty vector with given capacity.
   //
   explicit RAJAVec(unsigned init_cap = 0)
#if !defined(RAJA_USE_STL)
   : m_capacity(0), m_size(0), m_data(0)
#endif
   {
#if defined(RAJA_USE_STL)
      m_data.reserve(init_cap);
#else
      resize(init_cap);
#endif
   }

   //
   // Copy ctor for vector.
   //
   RAJAVec(const RAJAVec<T>& other) 
#if !defined(RAJA_USE_STL)
   : m_capacity(0), m_size(0), m_data(0)
#endif
   {
      copy(other); 
   }

   //
   // Copy-assignment operator for vector.
   //
   RAJAVec<T>& operator=(const RAJAVec<T>& rhs) 
   {
      if ( &rhs != this ) {
         RAJAVec<T> copy(rhs);
         this->swap(copy);
      }
      return *this;
   }

   //
   // Destroy vector and its data.
   //
   ~RAJAVec()
   {
#if !defined(RAJA_USE_STL)
      if (m_capacity > 0) delete m_data;  
#endif
   }

   ///
   /// Swap function for copy-and-swap idiom.
   /// 
   void swap(RAJAVec<T>& other)
   {
#if defined(RAJA_USE_STL)
      using std::swap;
      swap(m_data, other.m_data);
#else
      m_capacity = other.m_capacity;
      m_size = other.m_size;
      m_data = other.m_data;
#endif
   }


   unsigned size() const { 
#if defined(RAJA_USE_STL)
      return m_data.size();
#else
      return m_size;
#endif
   }

   const T& operator [] (unsigned i) const
   {
      return m_data[i];
   }

   void push_back(const T& item) 
   {
#if defined(RAJA_USE_STL)
      m_data.push_back(item); 
#else
      appendItem(item);
#endif
   }


private:
   //
   // Copy function for copy-and-swap idiom (deep copy).
   //
   void copy(const RAJAVec<T>& other)
   {
#if defined(RAJA_USE_STL)
      m_data = other.m_data;
#else
      resize(other.m_capacity);
      for (unsigned i = 0; i < other.m_size; ++i) {
         m_data[i] = other[i];
      }
      m_capacity = other.m_capacity;
      m_size = other.m_size;
#endif
   }


   //
   // The following private members and methods provide a quick and dirty 
   // memory allocation scheme to mimick std::vector behavior without 
   // relying on STL directly.
   //
   const unsigned s_init_cap = 4;
   const double   s_grow_fac = 1.5;

   unsigned nextCap(unsigned current_cap) 
   {
      if (current_cap == 0) { return s_init_cap; }
      return static_cast<unsigned>( current_cap * s_grow_fac ); 
   }

#if 0
   unsigned chooseCap(unsigned size) 
   {
      unsigned current_cap = 0;
      while (current_cap < size) { current_cap = nextCap(current_cap); }
      return current_cap;
   }
#endif

   void resize(unsigned target_size)
   {
#if 0
      unsigned current_cap = chooseCap(m_size);
#endif

      unsigned target_cap = m_capacity;
      while ( target_cap < target_size ) { target_cap = nextCap(target_cap); } 

      if ( m_capacity < target_cap ) {
         T* tdata = new T[target_cap];

         if ( m_data ) {
            for (unsigned i = 0; (i < m_size)&&(i < target_cap); ++i) {
               tdata[i] = m_data[i];
            } 
            delete[] m_data;
         }

         m_data = tdata;
         m_capacity = target_cap;
      }
   }

   void appendItem(const T& item)
   {
      resize(m_size+1);
      m_data[m_size] = item;
      m_size++;
   }
   

#if defined(RAJA_USE_STL)
   std::vector<T> m_data;
#else
   unsigned m_capacity;
   unsigned m_size;
   T* m_data;
#endif
};



}  // closing brace for RAJA namespace

#endif  // closing endif for header file include guard
