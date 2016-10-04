#ifndef TENSOR_CORE_H
#define TENSOR_CORE_H

#include <iostream>
#include <cstdarg>
#include <vector>
#include "../../utilities/Hao_types.h"

namespace tensor_hao
{

 template<class T, HAO_INT D> class TensorHaoRef;
 template<class T, HAO_INT D> class TensorHao;

 template<class T = double, HAO_INT D =1 > class TensorCore
 {
  private:
     HAO_INT n[D];
     HAO_INT nStep[D];
     HAO_INT L;
     T* p;

     TensorCore(void): L(0), p(nullptr) {}
     ~TensorCore() {}

  public:
     inline const HAO_INT* getRank() const {return n;}

     inline HAO_INT rank(HAO_INT i) const
     {
         #ifndef NDEBUG
         if( i >= D || i<0 ) { std::cout<<"Input i for rank() should be [0, D)!!! "<<i<<" "<<D<<std::endl; exit(1); }
         #endif

         return n[i];
     }

     inline HAO_INT rankStep(HAO_INT i) const
     {
         #ifndef NDEBUG
         if( i >= D || i<0 ) { std::cout<<"Input i for rankStep() should be [0, D)!!! "<<i<<" "<<D<<std::endl; exit(1); }
         #endif

         return nStep[i];
     }


     inline HAO_INT size() const {return L;}

     inline const T * data() const {return p;}
     inline       T * data()       {return p;}

     //COMMET THIS LINE, IT IS NOT A SAFE FUNCTION
     //Return reference to pointer: it can be used as T *& A_p = A.data_ref();
     //inline const T *& data_ref() const {return p;}
     //inline       T *& data_ref()       {return p;}


     //=======================================================================
     //START READ ELEMENTS FOR D=1,2,3,4,5 ....; WRITE OUT 1,2,3 for efficency
     //=======================================================================

     //Read elements: for D=1
     inline T operator () (HAO_INT i0) const
     {
         #ifndef NDEBUG
         if( D != 1    )         { std::cout<<"TensorCore::operator(HAO_INT) only works for D=1 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif 
         return p[ i0 ];
     }

     inline T& operator () (HAO_INT i0)
     {
         #ifndef NDEBUG
         if( D != 1    )         { std::cout<<"TensorCore::operator(HAO_INT) only works for D=1 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif
         return p[ i0 ];
     }


     //Read elements: for D=2
     inline T operator () (HAO_INT i0, HAO_INT i1) const
     {
         #ifndef NDEBUG
         if(D != 2) { std::cout<<"TensorCore::operator(HAO_INT, HAO_INT) only works for D=2 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*nStep[1] ];
     }

     inline T& operator () (HAO_INT i0, HAO_INT i1)
     {
         #ifndef NDEBUG
         if(D != 2) { std::cout<<"TensorCore::operator(HAO_INT, HAO_INT) only works for D=2 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*nStep[1] ];
     }


     //Read elements: for D=3
     inline T operator () (HAO_INT i0, HAO_INT i1, HAO_INT i2) const
     {
         #ifndef NDEBUG
         if(D != 3) { std::cout<<"TensorCore::operator(HAO_INT, HAO_INT, HAO_INT) only works for D=3 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i2 >= n[2] || i2<0 ) { std::cout<<"i2 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*nStep[1]+i2*nStep[2] ];
     }

     inline T& operator () (HAO_INT i0, HAO_INT i1, HAO_INT i2)
     {
         #ifndef NDEBUG
         if(D != 3) { std::cout<<"TensorCore::operator(HAO_INT, HAO_INT, HAO_INT) only works for D=3 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i2 >= n[2] || i2<0 ) { std::cout<<"i2 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*nStep[1]+i2*nStep[2] ];
     }


     //Read elements: for D>3
     template<typename... Values>
     T operator () (HAO_INT i0, HAO_INT i1, HAO_INT i2, HAO_INT i3, Values... inputs) const
     {
         HAO_INT vals[] = {i0, i1, i2, i3, inputs...};

         #ifndef NDEBUG
         HAO_INT  len = sizeof...(Values);
         if(D != (len+4) ) { std::cout<<"TensorCore::operator(HAO_INT...) not consisten with D !!!"<<std::endl; exit(1); }
         for(HAO_INT i=0; i<D; i++)
         {
             if( vals[i] >= n[i] || vals[i]<0  ) { std::cout<<"i... is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         }
         #endif

         HAO_INT index=0; for(HAO_INT i=0; i<D; i++) index += vals[i]*nStep[i];
         return p[index];
     }

     template<typename... Values>
     T& operator () (HAO_INT i0, HAO_INT i1, HAO_INT i2, HAO_INT i3, Values... inputs)
     {
         HAO_INT vals[] = {i0, i1, i2, i3, inputs...};

         #ifndef NDEBUG
         HAO_INT  len = sizeof...(Values);
         if(D != (len+4) ) { std::cout<<"TensorCore::operator(HAO_INT...) not consisten with D !!!"<<std::endl; exit(1); }
         for(HAO_INT i=0; i<D; i++)
         {
             if( vals[i] >= n[i] || vals[i]<0  ) { std::cout<<"i... is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         }
         #endif

         HAO_INT index=0; for(HAO_INT i=0; i<D; i++) index += vals[i]*nStep[i];
         return p[index];
     }
     //=====================================================================
     //END READ ELEMENTS FOR D=1,2,3,4,5 ....; WRITE OUT 1,2,3 for efficency
     //=====================================================================


     inline void operator += (const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator += "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(HAO_INT i=0; i<L; i++) p[i]+=x.p[i];
     }


     inline void operator -= (const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator -= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(HAO_INT i=0; i<L; i++) p[i]-=x.p[i];
     }

     inline void min_add_equal(const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator min_add_equal "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(HAO_INT i=0; i<L; i++) p[i]=x.p[i]-p[i];
     }

     inline void operator *= (const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator *= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(HAO_INT i=0; i<L; i++) p[i]*=x.p[i];
     }

     inline void operator /= (const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator /= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(HAO_INT i=0; i<L; i++) p[i]/=x.p[i];
     }

     inline void inv_div_equal(const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator inv_div_equal "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(HAO_INT i=0; i<L; i++) p[i] = x.p[i]/p[i];
     }


     inline void operator +=   (T x) { for(HAO_INT i=0; i<L; i++) p[i] += x;      }
     inline void operator -=   (T x) { for(HAO_INT i=0; i<L; i++) p[i] -= x;      }
     inline void min_add_equal (T x) { for(HAO_INT i=0; i<L; i++) p[i] =  x-p[i]; }
     inline void operator *=   (T x) { for(HAO_INT i=0; i<L; i++) p[i] *= x;      }
     inline void operator /=   (T x) { for(HAO_INT i=0; i<L; i++) p[i] /= x;      }
     inline void inv_div_equal (T x) { for(HAO_INT i=0; i<L; i++) p[i] =  x/p[i]; }

     T sum(HAO_INT begin = -1, HAO_INT end = -1, HAO_INT step = 1) const
     {
         if( begin < 0 ) begin = 0;
         if( end   < 0 ) end   = L;
         T sum_all = 0;
         for(HAO_INT i=begin; i<end; i+=step) sum_all += p[i];
         return sum_all;
     }

     T mean(HAO_INT begin = -1, HAO_INT end = -1, HAO_INT step = 1) const
     {
         if( begin < 0 ) begin = 0;
         if( end   < 0 ) end   = L;

         HAO_INT number_of_points;
         if( ( (end-begin)%step )==0  ) number_of_points = (end-begin)/step;
         else   number_of_points = (end-begin)/step+1;

         T mean_all = 0;
         for(HAO_INT i=begin; i<end; i+=step) mean_all += p[i];
         return mean_all / ( number_of_points * 1.0 );
     }


  protected:
     void copy_list(const std::initializer_list <T> &args)
     {
         HAO_INT args_size = args.size();
         if(L != args_size)
         {
             std::cout<<"Something is wrong with input args_size, not consisten with L!"<<std::endl;
             std::cout<<L<<" "<<args_size<<std::endl;
             exit(1);
         }
         std::copy( args.begin(), args.begin()+args_size, p );
     }


  private:
     //Avoid program to generater constructor and assigment for TensorCore. (Suppose to be an abstract class.)
     TensorCore(const TensorCore<T,D>& x)  { }
     TensorCore<T,D> & operator  = (const TensorCore<T,D>& x) { return *this; }

  friend class TensorHaoRef<T,D>;
  friend class TensorHao<T,D>;
  friend class TensorHaoRef<T,D+1>;
  friend class TensorHao<T,D+1>;

 };  //end class TensorCore

} //end namespace tensor_hao

#endif
