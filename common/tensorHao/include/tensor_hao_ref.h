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
         this->L = 0;
         //std::cout<<"In TensorHaoRef void constructor "<<std::endl;
     }

     template<typename... Values>
     explicit TensorHaoRef(size_t input, Values... inputs)
     {
         size_t len = sizeof...(Values) + 1;
         size_t vals[] = {input, static_cast<std::size_t>(inputs)...};

         if( len != D) {std::cout<<"Length of inputs number is not consistent with template class!!! "
                                 <<len <<" "<<D<<std::endl; exit(1);}

         this->setNNstepL(vals);

         this->p = nullptr;
     }

     TensorHaoRef(const size_t* n_ptr)
     {
         this->setNNstepL(n_ptr);

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

     template<typename... Values>
     void resize(size_t input, Values... inputs)
     {
         size_t LBackup = this->L;

         size_t len = sizeof...(Values) + 1;
         size_t vals[] = {input, static_cast<std::size_t>(inputs)...};

         if( len != D)
         {
             std::cout<<"Length of inputs number is not consistent with template class!!! " <<len <<" "<<D<<std::endl;
             exit(1);
         }

         this->setNNstepL(vals);

         if(this->L != LBackup)
         {
             std::cout<<"Error! Resize L can not be different with original size in TensorHaoRef!"<<std::endl;
             exit(1);
         }

     }

     virtual void resize(const size_t* n_ptr)
     {
         size_t LBackup = this->L;

         this->setNNstepL(n_ptr);

         if(this->L != LBackup)
         {
             std::cout<<"Error! Resize L can not be different with original size in TensorHaoRef!"<<std::endl;
             exit(1);
         }
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

