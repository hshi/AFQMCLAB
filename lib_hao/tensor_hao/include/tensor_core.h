#ifndef TENSOR_CORE_H
#define TENSOR_CORE_H

#include <iostream>
#include <cstdarg>
#include <vector>

namespace tensor_hao
{

 template<class T, int D> class Tensor_hao_ref;
 template<class T, int D> class Tensor_hao;

 template<class T = double, int D =1 > class Tensor_core
 {
  private:
     int n[D];
     int n_step[D];
     int L;
     T* p;

     Tensor_core(void): L(0), p(nullptr) {}
     ~Tensor_core() {}

  public:
     inline const int* n_ptr() const {return n;}

     inline int rank(int i) const 
     {
         #ifndef NDEBUG
         if( i >= D || i<0 ) { std::cout<<"Input i for rank() should be [0, D)!!! "<<i<<" "<<D<<std::endl; exit(1); }
         #endif

         return n[i];
     }

     inline int rank_step(int i) const 
     {
         #ifndef NDEBUG
         if( i >= D || i<0 ) { std::cout<<"Input i for rank_step() should be [0, D)!!! "<<i<<" "<<D<<std::endl; exit(1); }
         #endif

         return n_step[i];
     }


     inline int size() const {return L;}

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
     inline T operator () (int i0) const 
     {
         #ifndef NDEBUG
         if( D != 1    )         { std::cout<<"Tensor_core::operator(int) only works for D=1 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         #endif 
         return p[ i0 ];
     }

     inline T& operator () (int i0)
     {
         #ifndef NDEBUG
         if( D != 1    )         { std::cout<<"Tensor_core::operator(int) only works for D=1 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         #endif
         return p[ i0 ];
     }


     //Read elements: for D=2
     inline T operator () (int i0, int i1) const 
     {
         #ifndef NDEBUG
         if(D != 2) { std::cout<<"Tensor_core::operator(int, int) only works for D=2 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); } 
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*n_step[1] ]; 
     }

     inline T& operator () (int i0, int i1)
     {
         #ifndef NDEBUG
         if(D != 2) { std::cout<<"Tensor_core::operator(int, int) only works for D=2 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*n_step[1] ];
     }


     //Read elements: for D=3
     inline T operator () (int i0, int i1, int i2) const 
     {
         #ifndef NDEBUG
         if(D != 3) { std::cout<<"Tensor_core::operator(int, int, int) only works for D=3 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }   
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         if(i2 >= n[2] || i2<0 ) { std::cout<<"i2 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*n_step[1]+i2*n_step[2] ]; 
     }

     inline T& operator () (int i0, int i1, int i2)
     {
         #ifndef NDEBUG
         if(D != 3) { std::cout<<"Tensor_core::operator(int, int, int) only works for D=3 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         if(i2 >= n[2] || i2<0 ) { std::cout<<"i2 is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*n_step[1]+i2*n_step[2] ];
     }


     //Read elements: for D>3
     template<typename... Values>
     T operator () (int i0, int i1, int i2, int i3, Values... inputs) const 
     {
         int vals[] = {i0, i1, i2, i3, inputs...};

         #ifndef NDEBUG
         int  len = sizeof...(Values);
         if(D != (len+4) ) { std::cout<<"Tensor_core::operator(int...) not consisten with D !!!"<<std::endl; exit(1); }
         for(int i=0; i<D; i++)
         {
             if( vals[i] >= n[i] || vals[i]<0  ) { std::cout<<"i... is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         }
         #endif

         int index=0; for(int i=0; i<D; i++) index += vals[i]*n_step[i];
         return p[index];
     }

     template<typename... Values>
     T& operator () (int i0, int i1, int i2, int i3, Values... inputs)
     {
         int vals[] = {i0, i1, i2, i3, inputs...};

         #ifndef NDEBUG
         int  len = sizeof...(Values);
         if(D != (len+4) ) { std::cout<<"Tensor_core::operator(int...) not consisten with D !!!"<<std::endl; exit(1); }
         for(int i=0; i<D; i++)
         {
             if( vals[i] >= n[i] || vals[i]<0  ) { std::cout<<"i... is out of range in Tensor_core::operator() !!!"<<std::endl; exit(1); }
         }
         #endif

         int index=0; for(int i=0; i<D; i++) index += vals[i]*n_step[i];
         return p[index];
     }
     //=====================================================================
     //END READ ELEMENTS FOR D=1,2,3,4,5 ....; WRITE OUT 1,2,3 for efficency
     //=====================================================================


     inline void operator += (const Tensor_core<T,D>& x) 
     {
         if( L != x.L ) { std::cout<<"Size not consistent in operator += "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(int i=0; i<L; i++) p[i]+=x.p[i];
     }


     inline void operator -= (const Tensor_core<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"Size not consistent in operator -= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(int i=0; i<L; i++) p[i]-=x.p[i];
     }

     inline void min_add_equal(const Tensor_core<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"Size not consistent in operator min_add_equal "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(int i=0; i<L; i++) p[i]=x.p[i]-p[i];
     }

     inline void operator *= (const Tensor_core<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"Size not consistent in operator *= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(int i=0; i<L; i++) p[i]*=x.p[i];
     }

     inline void operator /= (const Tensor_core<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"Size not consistent in operator /= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(int i=0; i<L; i++) p[i]/=x.p[i];
     }

     inline void inv_div_equal(const Tensor_core<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"Size not consistent in operator inv_div_equal "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(int i=0; i<L; i++) p[i] = x.p[i]/p[i];
     }


     inline void operator +=   (T x) { for(int i=0; i<L; i++) p[i] += x;      }
     inline void operator -=   (T x) { for(int i=0; i<L; i++) p[i] -= x;      }
     inline void min_add_equal (T x) { for(int i=0; i<L; i++) p[i] =  x-p[i]; }
     inline void operator *=   (T x) { for(int i=0; i<L; i++) p[i] *= x;      }
     inline void operator /=   (T x) { for(int i=0; i<L; i++) p[i] /= x;      }
     inline void inv_div_equal (T x) { for(int i=0; i<L; i++) p[i] =  x/p[i]; }

     T sum(int begin = -1, int end = -1, int step = 1) const 
     {
         if( begin < 0 ) begin = 0;
         if( end   < 0 ) end   = L;
         T sum_all = 0;
         for(int i=begin; i<end; i+=step) sum_all += p[i];
         return sum_all;
     }

     T mean(int begin = -1, int end = -1, int step = 1) const
     {
         if( begin < 0 ) begin = 0;
         if( end   < 0 ) end   = L;

         int number_of_points;
         if( ( (end-begin)%step )==0  ) number_of_points = (end-begin)/step;
         else   number_of_points = (end-begin)/step+1;

         T mean_all = 0;
         for(int i=begin; i<end; i+=step) mean_all += p[i];
         return mean_all / ( number_of_points * 1.0 );
     }


  protected:
     void copy_list(const std::initializer_list <T> &args)
     {
         int args_size = args.size();
         if(L != args_size)
         {
             std::cout<<"Something is wrong with input args_size, not consisten with L!"<<std::endl;
             std::cout<<L<<" "<<args_size<<std::endl;
             exit(1);
         }
         std::copy( args.begin(), args.begin()+args_size, p );
     }


  private:
     //Avoid program to generater constructor and assigment for Tensor_core. (Suppose to be an abstract class.)
     Tensor_core(const Tensor_core<T,D>& x)  { }
     Tensor_core<T,D> & operator  = (const Tensor_core<T,D>& x) { return *this; }

  friend class Tensor_hao_ref<T,D>;
  friend class Tensor_hao<T,D>;
  friend class Tensor_hao_ref<T,D+1>;
  friend class Tensor_hao<T,D+1>;

 };  //end class Tensor_core

} //end namespace tensor_hao

#endif
