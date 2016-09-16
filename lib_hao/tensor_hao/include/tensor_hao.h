#ifndef TENSOR_HAO_H
#define TENSOR_HAO_H

#include <iomanip>
#include "tensor_core.h"
#include "tensor_hao_ref.h"

namespace tensor_hao
{

 template<class T = double, int D = 1> class TensorHao : public TensorCore<T, D>
 {
  public:
     //============
     //CONSTRUCTORS
     //============

     TensorHao(void): TensorCore<T,D>()
     {
         for(int i=0; i<D; i++) 
         {
            this->n[i]=0;
            this->nStep[i]=0;
         }
         //std::cout<<"In TensorHao void constructor "<<std::endl;
     }
    
     //Variadic template 
     template<typename... Values>
     explicit TensorHao(int input, Values... inputs)
     {
         int  len = sizeof...(Values);
         int vals[] = {input, inputs...};

         if( (len+1) != D) {std::cout<<"Length of inputs number is not consistent with template class!!! "<<len+1<<" "<<D<<std::endl; exit(1);}

         std::copy(vals, vals+D, this->n);

         this->nStep[0]=1; for(int i=1; i<D; i++) {this->nStep[i] = (this->nStep[i-1]) * (this->n[i-1]);}

         this->L = this->nStep[D-1] * ( this->n[D-1] );

         this->p = new T[this->L];

         //std::cout<<"In TensorHao Variadic constructor "<<std::endl;
     }

     TensorHao(const int* n_ptr)
     {
         std::copy(n_ptr, n_ptr+D, this->n);

         this->nStep[0]=1; for(int i=1; i<D; i++) {this->nStep[i] = (this->nStep[i-1]) * (this->n[i-1]);}

         this->L = this->nStep[D-1] * ( this->n[D-1] );

         this->p = new T[this->L];

         //std::cout<<"In TensorHao pointer constructor "<<std::endl;
     }

     TensorHao(const TensorHao<T, D>& x)
     {
         copy_deep_constructor(x);
         //std::cout<<"In TensorHao copy constructor."<<std::endl;
     }

     TensorHao(TensorHao<T, D>&& x)
     {
         move_deep_constructor(x);
         //std::cout<<"In TensorHao move constructor."<<std::endl;
     }

     TensorHao(const TensorCore<T, D>& x)
     {
         copy_deep_constructor(x);
         //std::cout<<"In TensorCore copy constructor."<<std::endl;
     }

     //No TensorCore move constructor
     //We do not want to move pointer to TensorHaoRef
     //Since TensorHaoRef do not own the memory space

     ~TensorHao()
     {
         if(this->p) delete[] this->p;
     }

     TensorHao<T, D> & operator  = (const TensorHao<T, D>& x)
     {
         if(&x!=this) copy_deep_assignment(x);
         //std::cout<<"In TensorHao copy assginment "<<std::endl;
         return *this;
     }

     TensorHao<T, D> & operator  = (TensorHao<T, D>&& x)
     {
         if(&x!=this) move_deep_assignment(x);
         //std::cout<<"In TensorHao move assginment "<<std::endl;
         return *this;
     }

     TensorHao<T, D> & operator  = (const TensorCore<T, D>& x)
     {
         if(&x!=this) copy_deep_assignment(x);
         //std::cout<<"In TensorCore copy assginment "<<std::endl;
         return *this;
     }

     TensorHao<T, D> & operator  = (const std::initializer_list <T> &args)
     {
         this->copy_list(args);
         return *this;
     }

     TensorHao<T, D> & operator  =  (T x)
     { 
         for(int i=0; i<this->L; i++) this->p[i] = x;
         return *this;
     }

     //=========
     //FUNCTIONS
     //=========
     TensorHaoRef<T, D-1> operator[] (int i)
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
     void copy_deep_constructor(const TensorCore<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.nStep, x.nStep+D, this->nStep);
         this->L = x.L;

         this->p = new T[this->L];
         std::copy(x.p, x.p+(this->L), this->p);
     }

     void move_deep_constructor(TensorCore<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.nStep, x.nStep+D, this->nStep);
         this->L = x.L;

         this->p = x.p;
         x.p = nullptr;
     }

     void copy_deep_assignment(const TensorCore<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.nStep, x.nStep+D, this->nStep);

         if( this->L != x.L )
         {
             this->L = x.L;
             if(this->p) delete[] this->p;
             this->p = new T[this->L]; 
         }

         std::copy(x.p, x.p+(this->L), this->p);
     }

     void move_deep_assignment(TensorCore<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.nStep, x.nStep+D, this->nStep);
         this->L = x.L;

         //SWAP
         T* p_temp = this->p; 
         this->p = x.p;
         x.p = p_temp;
     }

 }; //end class TensorHao

} //end namespace tensor_hao

#endif

