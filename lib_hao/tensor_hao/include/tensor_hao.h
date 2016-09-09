#ifndef TENSOR_HAO_H
#define TENSOR_HAO_H

#include <iomanip>
#include "tensor_core.h"
#include "tensor_hao_ref.h"

namespace tensor_hao
{

 template<class T = double, int D = 1> class Tensor_hao : public Tensor_core<T, D>
 {
  public:
     //============
     //CONSTRUCTORS
     //============

     Tensor_hao(void): Tensor_core<T,D>() 
     {
         for(int i=0; i<D; i++) 
         {
            this->n[i]=0;
            this->n_step[i]=0;
         }
         //std::cout<<"In Tensor_hao void constructor "<<std::endl;
     }
    
     //Variadic template 
     template<typename... Values>
     explicit Tensor_hao(int input, Values... inputs)
     {
         int  len = sizeof...(Values);
         int vals[] = {input, inputs...};

         if( (len+1) != D) {std::cout<<"Length of inputs number is not consistent with template class!!! "<<len+1<<" "<<D<<std::endl; exit(1);}

         std::copy(vals, vals+D, this->n);

         this->n_step[0]=1; for(int i=1; i<D; i++) {this->n_step[i] = (this->n_step[i-1]) * (this->n[i-1]);}

         this->L = this->n_step[D-1] * ( this->n[D-1] );

         this->p = new T[this->L];

         //std::cout<<"In Tensor_hao Variadic constructor "<<std::endl;
     }

     Tensor_hao(const int* n_ptr)
     {
         std::copy(n_ptr, n_ptr+D, this->n);

         this->n_step[0]=1; for(int i=1; i<D; i++) {this->n_step[i] = (this->n_step[i-1]) * (this->n[i-1]);}

         this->L = this->n_step[D-1] * ( this->n[D-1] );

         this->p = new T[this->L];

         //std::cout<<"In Tensor_hao pointer constructor "<<std::endl;
     }

     Tensor_hao(const Tensor_hao<T, D>& x)
     {
         copy_deep_constructor(x);
         //std::cout<<"In Tensor_hao copy constructor."<<std::endl;
     }

     Tensor_hao(Tensor_hao<T, D>&& x)
     {
         move_deep_constructor(x);
         //std::cout<<"In Tensor_hao move constructor."<<std::endl;
     }

     Tensor_hao(const Tensor_core<T, D>& x)
     {
         copy_deep_constructor(x);
         //std::cout<<"In Tensor_core copy constructor."<<std::endl;
     }

     //No Tensor_core move constructor
     //We do not want to move pointer to Tensor_hao_ref
     //Since Tensor_hao_ref do not own the memory space

     ~Tensor_hao() 
     {
         if(this->p) delete[] this->p;
     }

     Tensor_hao<T, D> & operator  = (const Tensor_hao<T, D>& x)
     {
         if(&x!=this) copy_deep_assignment(x);
         //std::cout<<"In Tensor_hao copy assginment "<<std::endl;
         return *this;
     }

     Tensor_hao<T, D> & operator  = (Tensor_hao<T, D>&& x)
     {
         if(&x!=this) move_deep_assignment(x);
         //std::cout<<"In Tensor_hao move assginment "<<std::endl;
         return *this;
     }

     Tensor_hao<T, D> & operator  = (const Tensor_core<T, D>& x)
     {
         if(&x!=this) copy_deep_assignment(x);
         //std::cout<<"In Tensor_core copy assginment "<<std::endl;
         return *this;
     }

     Tensor_hao<T, D> & operator  = (const std::initializer_list <T> &args)
     {
         this->copy_list(args);
         return *this;
     }

     Tensor_hao<T, D> & operator  =  (T x) 
     { 
         for(int i=0; i<this->L; i++) this->p[i] = x;
         return *this;
     }

     //=========
     //FUNCTIONS
     //=========
     Tensor_hao_ref<T, D-1> operator[] (int i)
     {
         if( i > ( this->n[D-1] ) || i<0 )
         {
             std::cout<<"Slice i not consistent with n[D-1] !!"<<std::endl;
             std::cout<<i<<" "<<this->n[D-1]<<std::endl;
             exit(1);
         }
         Tensor_hao_ref<T, D-1> A (this->n);
         A.p = this->p + i * this->n_step[D-1];
         return A;
     }

  private:
     void copy_deep_constructor(const Tensor_core<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.n_step, x.n_step+D, this->n_step);
         this->L = x.L;

         this->p = new T[this->L];
         std::copy(x.p, x.p+(this->L), this->p);
     }

     void move_deep_constructor(Tensor_core<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.n_step, x.n_step+D, this->n_step);
         this->L = x.L;

         this->p = x.p;
         x.p = nullptr;
     }

     void copy_deep_assignment(const Tensor_core<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.n_step, x.n_step+D, this->n_step);

         if( this->L != x.L )
         {
             this->L = x.L;
             if(this->p) delete[] this->p;
             this->p = new T[this->L]; 
         }

         std::copy(x.p, x.p+(this->L), this->p);
     }

     void move_deep_assignment(Tensor_core<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.n_step, x.n_step+D, this->n_step);
         this->L = x.L;

         //SWAP
         T* p_temp = this->p; 
         this->p = x.p;
         x.p = p_temp;
     }

 }; //end class Tensor_hao

} //end namespace tensor_hao

#endif

