#ifndef TENSOR_CORE_H
#define TENSOR_CORE_H

#include <iostream>
#include <cstdarg>
#include <vector>
#include <limits>
#include "readWriteTemplateForTensor.h"

namespace tensor_hao
{

 template<class T, size_t D> class TensorHaoRef;
 template<class T, size_t D> class TensorHao;

 template<class T = double, size_t D =1 > class TensorCore
 {
  private:
     size_t n[D];
     size_t nStep[D];
     size_t L;
     T* p;

     TensorCore(void): L(0), p(nullptr) {}
     ~TensorCore() {}

  public:
     inline const size_t* getRank() const {return n;}

     inline size_t rank(size_t i) const
     {
         #ifndef NDEBUG
         if( i >= D || i<0 ) { std::cout<<"Input i for rank() should be [0, D)!!! "<<i<<" "<<D<<std::endl; exit(1); }
         #endif

         return n[i];
     }

     inline size_t rankStep(size_t i) const
     {
         #ifndef NDEBUG
         if( i >= D || i<0 ) { std::cout<<"Input i for rankStep() should be [0, D)!!! "<<i<<" "<<D<<std::endl; exit(1); }
         #endif

         return nStep[i];
     }


     inline size_t size() const {return L;}

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
     inline T operator () (size_t i0) const
     {
         #ifndef NDEBUG
         if( D != 1    )         { std::cout<<"TensorCore::operator(size_t) only works for D=1 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif 
         return p[ i0 ];
     }

     inline T& operator () (size_t i0)
     {
         #ifndef NDEBUG
         if( D != 1    )         { std::cout<<"TensorCore::operator(size_t) only works for D=1 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif
         return p[ i0 ];
     }


     //Read elements: for D=2
     inline T operator () (size_t i0, size_t i1) const
     {
         #ifndef NDEBUG
         if(D != 2) { std::cout<<"TensorCore::operator(size_t, size_t) only works for D=2 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*nStep[1] ];
     }

     inline T& operator () (size_t i0, size_t i1)
     {
         #ifndef NDEBUG
         if(D != 2) { std::cout<<"TensorCore::operator(size_t, size_t) only works for D=2 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*nStep[1] ];
     }


     //Read elements: for D=3
     inline T operator () (size_t i0, size_t i1, size_t i2) const
     {
         #ifndef NDEBUG
         if(D != 3) { std::cout<<"TensorCore::operator(size_t, size_t, size_t) only works for D=3 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i2 >= n[2] || i2<0 ) { std::cout<<"i2 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*nStep[1]+i2*nStep[2] ];
     }

     inline T& operator () (size_t i0, size_t i1, size_t i2)
     {
         #ifndef NDEBUG
         if(D != 3) { std::cout<<"TensorCore::operator(size_t, size_t, size_t) only works for D=3 !!!"<<std::endl; exit(1); }
         if(i0 >= n[0] || i0<0 ) { std::cout<<"i0 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i1 >= n[1] || i1<0 ) { std::cout<<"i1 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         if(i2 >= n[2] || i2<0 ) { std::cout<<"i2 is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         #endif

         return p[ i0+i1*nStep[1]+i2*nStep[2] ];
     }


     //Read elements: for D>3
     template<typename... Values>
     T operator () (size_t i0, size_t i1, size_t i2, size_t i3, Values... inputs) const
     {
         size_t vals[] = {i0, i1, i2, i3, inputs...};

         #ifndef NDEBUG
         size_t  len = sizeof...(Values);
         if(D != (len+4) ) { std::cout<<"TensorCore::operator(size_t...) not consisten with D !!!"<<std::endl; exit(1); }
         for(size_t i=0; i<D; i++)
         {
             if( vals[i] >= n[i] || vals[i]<0  ) { std::cout<<"i... is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         }
         #endif

         size_t index=0; for(size_t i=0; i<D; i++) index += vals[i]*nStep[i];
         return p[index];
     }

     template<typename... Values>
     T& operator () (size_t i0, size_t i1, size_t i2, size_t i3, Values... inputs)
     {
         size_t vals[] = {i0, i1, i2, i3, inputs...};

         #ifndef NDEBUG
         size_t  len = sizeof...(Values);
         if(D != (len+4) ) { std::cout<<"TensorCore::operator(size_t...) not consisten with D !!!"<<std::endl; exit(1); }
         for(size_t i=0; i<D; i++)
         {
             if( vals[i] >= n[i] || vals[i]<0  ) { std::cout<<"i... is out of range in TensorCore::operator() !!!"<<std::endl; exit(1); }
         }
         #endif

         size_t index=0; for(size_t i=0; i<D; i++) index += vals[i]*nStep[i];
         return p[index];
     }
     //=====================================================================
     //END READ ELEMENTS FOR D=1,2,3,4,5 ....; WRITE OUT 1,2,3 for efficency
     //=====================================================================

     TensorHaoRef<T, D-1> operator[] (size_t i)
     {
         if( i > ( this->n[D-1] ) || i<0 )
         {
             std::cout<<"Slice i not consistent with n[D-1] !!"<<std::endl;
             std::cout<<i<<" "<<this->n[D-1]<<std::endl;
             exit(1);
         }
         TensorHaoRef<T, D-1> A (this->n);
         A.p = this->p + i * this->nStep[D-1];
         return A;
     }

     TensorHaoRef<T, 2> reshape(size_t L0, size_t L1)
     {
         TensorHaoRef<T, 2> A (L0, L1);
         if(L0*L1 != L) { std::cout<<"Error! Size not consistent in reshape!"<<std::endl; exit(1); }
         A.point(p);
         return A;
     }

     inline void operator += (const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator += "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(size_t i=0; i<L; i++) p[i]+=x.p[i];
     }


     inline void operator -= (const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator -= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(size_t i=0; i<L; i++) p[i]-=x.p[i];
     }

     inline void min_add_equal(const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator min_add_equal "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(size_t i=0; i<L; i++) p[i]=x.p[i]-p[i];
     }

     inline void operator *= (const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator *= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(size_t i=0; i<L; i++) p[i]*=x.p[i];
     }

     inline void operator /= (const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator /= "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(size_t i=0; i<L; i++) p[i]/=x.p[i];
     }

     inline void inv_div_equal(const TensorCore<T,D>& x)
     {
         if( L != x.L ) { std::cout<<"size not consistent in operator inv_div_equal "<<L<<" "<<x.L<<std::endl; exit(1); }
         for(size_t i=0; i<L; i++) p[i] = x.p[i]/p[i];
     }


     inline void operator +=   (T x) { for(size_t i=0; i<L; i++) p[i] += x;      }
     inline void operator -=   (T x) { for(size_t i=0; i<L; i++) p[i] -= x;      }
     inline void min_add_equal (T x) { for(size_t i=0; i<L; i++) p[i] =  x-p[i]; }
     inline void operator *=   (T x) { for(size_t i=0; i<L; i++) p[i] *= x;      }
     inline void operator /=   (T x) { for(size_t i=0; i<L; i++) p[i] /= x;      }
     inline void inv_div_equal (T x) { for(size_t i=0; i<L; i++) p[i] =  x/p[i]; }

     T sum(size_t begin = 0, size_t end = std::numeric_limits<std::size_t>::max(), size_t step = 1) const
     {
         if(end > L) end = L;
         T sum_all = 0;
         for(size_t i=begin; i<end; i+=step) sum_all += p[i];
         return sum_all;
     }

     T mean(size_t begin = 0, size_t end = std::numeric_limits<std::size_t>::max(), size_t step = 1) const
     {
         if(end > L) end = L;
         size_t number_of_points;
         if( ( (end-begin)%step )==0  ) number_of_points = (end-begin)/step;
         else   number_of_points = (end-begin)/step+1;

         T mean_all = 0;
         for(size_t i=begin; i<end; i+=step) mean_all += p[i];
         return mean_all / ( number_of_points * 1.0 );
     }

     T max(size_t begin = 0, size_t end = std::numeric_limits<std::size_t>::max(), size_t step = 1) const
     {
         if(end > L) end = L;
         T maxValue = p[begin];
         for(size_t i=begin; i<end; i+=step) { if( maxValue < p[i] ) maxValue = p[i]; }
         return maxValue;
     }

     T min(size_t begin = 0, size_t end = std::numeric_limits<std::size_t>::max(), size_t step = 1) const
     {
         if(end > L) end = L;
         T minValue = p[begin];
         for(size_t i=begin; i<end; i+=step) { if( minValue > p[i] ) minValue = p[i]; }
         return minValue;
     }

     virtual void resize(const size_t* n_ptr) {}

     void read(std::ifstream &file)
     {
         size_t D_in; file>> D_in;
         if( D_in != D ) { std::cout << "Error!!! Dimen is not consistent! "<<D<<" "<<D_in<<std::endl; exit(1); }
         size_t n_ptr[D]; for(size_t i=0; i<D; i++) file>>n_ptr[i];
         resize( n_ptr );
         readFileForTensor(this->L, this->p, file );
     }

     void read(const std::string& filename)
     {
         std::ifstream file;
         file.open(filename, std::ios::in);
         if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
         read(file);
         file.close();
     }

     void write(std::ofstream &file) const
     {
         file<<D<<"\n";
         for(size_t i=0; i<D; i++) file<<n[i]<<" "; file<<"\n";
         writeFileForTensor(L, p, file);
     }

     void write(const std::string& filename) const
     {
         std::ofstream file;
         file.open(filename, std::ios::out|std::ios::trunc);
         if( !file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
         write(file);
         file.close();
     }

  protected:
     void setNNstepL(const size_t* n_ptr)
     {
         std::copy(n_ptr, n_ptr+D, this->n);

         this->nStep[0]=1; for(size_t i=1; i<D; i++) {this->nStep[i] = (this->nStep[i-1]) * (this->n[i-1]);}

         this->L = this->nStep[D-1] * ( this->n[D-1] );
     }

     void copy_list(const std::initializer_list <T> &args)
     {
         size_t args_size = args.size();
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
  friend class TensorCore<T,D+1>;

 };  //end class TensorCore

} //end namespace tensor_hao

#endif
