#ifndef TENSOR_HAO_REF_H
#define TENSOR_HAO_REF_H

#include <iomanip>
#include "tensor_core.h"

namespace tensor_hao
{

 template<class T = double, int D = 1> class Tensor_hao_ref : public Tensor_core<T, D>
 {
  public:
     //============
     //CONSTRUCTORS
     //============

     Tensor_hao_ref(void): Tensor_core<T,D>() 
     {
         for(int i=0; i<D; i++)
         {
            this->n[i]=0;
            this->n_step[i]=0;
         } 
         //std::cout<<"In Tensor_hao_ref void constructor "<<std::endl;
     }

     //Variadic template 
     template<typename... Values>
     explicit Tensor_hao_ref(int input, Values... inputs)
     {
         int  len = sizeof...(Values);
         int vals[] = {input, inputs...};

         if( (len+1) != D) {std::cout<<"Length of inputs number is not consistent with template class!!! "<<len+1<<" "<<D<<std::endl; exit(1);}

         std::copy(vals, vals+D, this->n);

         this->n_step[0]=1; for(int i=1; i<D; i++) {this->n_step[i] = (this->n_step[i-1]) * (this->n[i-1]);}

         this->L = this->n_step[D-1] * ( this->n[D-1] );

         this->p = nullptr;
     }

     Tensor_hao_ref(const int* n_ptr)
     {
         std::copy(n_ptr, n_ptr+D, this->n);

         this->n_step[0]=1; for(int i=1; i<D; i++) {this->n_step[i] = (this->n_step[i-1]) * (this->n[i-1]);}

         this->L = this->n_step[D-1] * ( this->n[D-1] );

         this->p = nullptr;

         //std::cout<<"In Tensor_hao_ref pointer constructor "<<std::endl;
     }

     Tensor_hao_ref(const Tensor_hao_ref<T, D>& x)
     {
         copy_ref(x);
         //std::cout<<"In Tensor_hao_ref constructor "<<std::endl;
     }

     Tensor_hao_ref(const Tensor_core<T, D>& x)
     {
         copy_ref(x);
         //std::cout<<"In Tensor_core constructor "<<std::endl;
     }

     ~Tensor_hao_ref() {}

     Tensor_hao_ref<T, D>& operator  = (const Tensor_hao_ref<T, D>& x) 
     {
         if(&x!=this) copy_ref(x);
         //std::cout<<"In Tensor_hao_ref assginment "<<std::endl;
         return *this;
     }

     Tensor_hao_ref<T, D> & operator  = (const Tensor_core<T, D>& x)
     {
         if(&x!=this) copy_ref(x);
         //std::cout<<"In Tensor_core assginment "<<std::endl;
         return *this;
     }

     Tensor_hao_ref<T, D> & operator  = (const std::initializer_list <T> &args)
     {
         if( !(this->p) ) {std::cout<<"Tensor_hao_ref has not point to any memory space yet, can not copy from list!"<<std::endl; exit(1);}
         this->copy_list(args);
         return *this;
     }

     Tensor_hao_ref<T, D> & operator  =  (T x)
     {
         for(int i=0; i<this->L; i++) this->p[i] = x;
         return *this;
     }


     //=========
     //FUNCTIONS
     //=========

     void point(T* p_in) { this->p=p_in; }

     void point(std::vector<T>& vec)
     {
         int vec_size = vec.size();
         if( this->L != vec_size )
         {
             std::cout<<"Size is not consistent between ref matrix and vector."<<std::endl;
             std::cout<<this->L<<" "<<vec.size()<<std::endl;
             exit(1);
         }
         this->p=vec.data();
     }

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
     void copy_ref(const Tensor_core<T, D>& x)
     {
         std::copy(x.n,      x.n+D,      this->n     );
         std::copy(x.n_step, x.n_step+D, this->n_step);
         this->L = x.L;
         this->p = x.p;
     }

 }; //end class Tensor_hao_ref

} //end namespace tensor_hao

#endif

