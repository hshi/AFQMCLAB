#ifndef TENSOR_HAO_H
#define TENSOR_HAO_H

#include <iomanip>
#include "tensor_core.h"
#include "tensor_hao_ref.h"

namespace tensor_hao
{

 template<class T = double, size_t D = 1> class TensorHao : public TensorCore<T, D>
 {
  public:
     TensorHao(void): TensorCore<T,D>()
     {
         for(size_t i=0; i<D; i++) 
         {
            this->n[i]=0;
            this->nStep[i]=0;
         }
         this->L = 0;
         //std::cout<<"In TensorHao void constructor "<<std::endl;
     }
    
     template<typename... Values>
     explicit TensorHao(size_t input, Values... inputs)
     {
         size_t len = sizeof...(Values) + 1;
         size_t vals[] = {input, static_cast<std::size_t>(inputs)...};

         if( len != D) {std::cout<<"Length of inputs number is not consistent with template class!!! "
                                 <<len <<" "<<D<<std::endl; exit(1);}

         this->setNNstepL(vals);

         this->p = new T[this->L];

         //std::cout<<"In TensorHao Variadic constructor "<<std::endl;
     }

     TensorHao(const size_t* n_ptr)
     {
         this->setNNstepL(n_ptr);

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
         for(size_t i=0; i<this->L; i++) this->p[i] = x;
         return *this;
     }

     template<typename... Values>
     void resize(size_t input, Values... inputs)
     {
         size_t LBackup = this->L;

         size_t len = sizeof...(Values) + 1;
         size_t vals[] = {input, static_cast<std::size_t>(inputs)...};

         if( len != D) {std::cout<<"Length of inputs number is not consistent with template class!!! "
                                 <<len <<" "<<D<<std::endl; exit(1);}

         this->setNNstepL(vals);

         if(this->L != LBackup) safelyAllocatePointer();
     }

     virtual void resize(const size_t* n_ptr)
     {
         size_t LBackup = this->L;

         this->setNNstepL(n_ptr);

         if(this->L != LBackup) safelyAllocatePointer();
     }

     double getMemory() const
     {
         double mem(0.0);
         mem += 8.0*D+8.0*D+8.0+8.0+this->L*sizeof(T);
         return mem;
     }

  private:
     void safelyAllocatePointer()
     {
         if(this->p) delete[] this->p;
         this->p = new T[this->L];
     }

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
         std::copy(x.n,      x.n+D,    this->n  );
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

         T* p_temp = this->p;
         this->p = x.p;
         x.p = p_temp;
     }

 }; //end class TensorHao

} //end namespace tensor_hao

#endif

