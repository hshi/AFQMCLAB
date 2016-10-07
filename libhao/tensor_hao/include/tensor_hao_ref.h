#ifndef TENSOR_HAO_REF_H
#define TENSOR_HAO_REF_H

#include <iomanip>
#include "tensor_core.h"

namespace tensor_hao
{

 template<class T = double, size_t D = 1> class TensorHaoRef : public TensorCore<T, D>
 {
  public:

     TensorHaoRef(void): TensorCore<T,D>()
     {
         for(size_t i=0; i<D; i++)
         {
            this->n[i]=0;
            this->nStep[i]=0;
         } 
         //std::cout<<"In TensorHaoRef void constructor "<<std::endl;
     }

     template<typename... Values>
     explicit TensorHaoRef(size_t input, Values... inputs)
     {
         size_t len = sizeof...(Values);
         size_t vals[] = {input, static_cast<std::size_t>(inputs)...};

         if( (len+1) != D) {std::cout<<"Length of inputs number is not consistent with template class!!! "<<len+1<<" "<<D<<std::endl; exit(1);}

         std::copy(vals, vals+D, this->n);

         this->nStep[0]=1; for(size_t i=1; i<D; i++) {this->nStep[i] = (this->nStep[i-1]) * (this->n[i-1]);}

         this->L = this->nStep[D-1] * ( this->n[D-1] );

         this->p = nullptr;
     }

     TensorHaoRef(const size_t* n_ptr)
     {
         std::copy(n_ptr, n_ptr+D, this->n);

         this->nStep[0]=1; for(size_t i=1; i<D; i++) {this->nStep[i] = (this->nStep[i-1]) * (this->n[i-1]);}

         this->L = this->nStep[D-1] * ( this->n[D-1] );

         this->p = nullptr;

         //std::cout<<"In TensorHaoRef pointer constructor "<<std::endl;
     }

     TensorHaoRef(const TensorHaoRef<T, D>& x)
     {
         copy_ref(x);
         //std::cout<<"In TensorHaoRef constructor "<<std::endl;
     }

     TensorHaoRef(const TensorCore<T, D>& x)
     {
         copy_ref(x);
         //std::cout<<"In TensorCore constructor "<<std::endl;
     }

     ~TensorHaoRef() {}

     TensorHaoRef<T, D>& operator  = (const TensorHaoRef<T, D>& x)
     {
         if(&x!=this) copy_ref(x);
         //std::cout<<"In TensorHaoRef assginment "<<std::endl;
         return *this;
     }

     TensorHaoRef<T, D> & operator  = (const TensorCore<T, D>& x)
     {
         if(&x!=this) copy_ref(x);
         //std::cout<<"In TensorCore assginment "<<std::endl;
         return *this;
     }

     TensorHaoRef<T, D> & operator  = (const std::initializer_list <T> &args)
     {
         if( !(this->p) ) {std::cout<<"TensorHaoRef has not point to any memory space yet, can not copy from list!"<<std::endl; exit(1);}
         this->copy_list(args);
         return *this;
     }

     TensorHaoRef<T, D> & operator  =  (T x)
     {
         for(size_t i=0; i<this->L; i++) this->p[i] = x;
         return *this;
     }


     void point(T* p_in) { this->p=p_in; }

     void point(std::vector<T>& vec)
     {
         size_t vec_size = vec.size();
         if( this->L != vec_size )
         {
             std::cout<<"size is not consistent between ref matrix and vector."<<std::endl;
             std::cout<<this->L<<" "<<vec.size()<<std::endl;
             exit(1);
         }
         this->p=vec.data();
     }

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

  private:
     void copy_ref(const TensorCore<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.nStep, x.nStep+D, this->nStep);
         this->L = x.L;
         this->p = x.p;
     }

 }; //end class TensorHaoRef

} //end namespace tensor_hao

#endif

