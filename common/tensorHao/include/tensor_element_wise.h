#ifndef TENSOR_ELEMENT_WISE_H
#define TENSOR_ELEMENT_WISE_H

#include <complex>
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_myabs.h"

namespace tensor_hao
{

 template <class T, size_t D>
 TensorHao<std::complex<T>, D> conj(const TensorCore<std::complex<T>, D>& A)
 {
     TensorHao<std::complex<T>, D> B (A.getRank() );
     size_t L = A.size();
     const std::complex<T>* A_p = A.data(); 
           std::complex<T>* B_p = B.data();
     for(size_t i=0; i<L; i++) B_p[i] = std::conj( A_p[i] );
     return B;
 }

 template <class T, size_t D>
 TensorHao<T, D> exp(const TensorCore<T, D>& A)
 {
     TensorHao<T, D> B (A.getRank() );
     size_t L = A.size();
     const T * A_p = A.data();
           T * B_p = B.data();
     for(size_t i=0; i<L; i++) B_p[i] = std::exp( A_p[i] );
     return B;
 }

 template <class T, size_t D>
 TensorHao<T, D> log(const TensorCore<T, D>& A)
 {
     TensorHao<T, D> B (A.getRank() );
     size_t L = A.size();
     const T * A_p = A.data();
     T * B_p = B.data();
     for(size_t i=0; i<L; i++) B_p[i] = std::log( A_p[i] );
     return B;
 }

 template <class T, size_t D>
 TensorHao<T, D> norm(const TensorCore<T, D>& A)
 {
     TensorHao<T, D> B (A.getRank() );
     size_t L = A.size();
     const T * A_p = A.data();
           T * B_p = B.data();
     for(size_t i=0; i<L; i++) B_p[i] = std::norm( A_p[i] );
     return B;
 }

 template <class T, size_t D>
 TensorHao<T, D> abs(const TensorCore<T, D>& A)
 {
     TensorHao<T, D> B (A.getRank() );
     size_t L = A.size();
     const T * A_p = A.data();
     T * B_p = B.data();
     for(size_t i=0; i<L; i++) B_p[i] = myabs( A_p[i] );
     return B;
 }

 template <class T, size_t D>
 TensorHao<T, D> sqrt(const TensorCore<T, D>& A)
 {
     TensorHao<T, D> B (A.getRank() );
     size_t L = A.size();
     const T * A_p = A.data();
           T * B_p = B.data();
     for(size_t i=0; i<L; i++) B_p[i] = std::sqrt( A_p[i] );
     return B;
 }


 template <class T, size_t D>
 TensorHao<T, D> operator - (const TensorCore<T, D>& A)
 {
     TensorHao<T, D> B (A.getRank() );
     size_t L = A.size();
     const T * A_p = A.data();
           T * B_p = B.data();
     for(size_t i=0; i<L; i++) B_p[i] = -A_p[i];
     return B;
 }


 //for add tensor + tensor
 template <class T, size_t D>
 TensorHao<T,D> operator + (const TensorHao<T,D>& A,const TensorHao<T,D>& B) {TensorHao<T,D> C=A; C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (const TensorHao<T,D>& A, TensorHao<T,D>&& B)     {TensorHao<T,D> C=std::move(B); C+=A; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (TensorHao<T,D>&& A,const TensorHao<T,D>& B)      {TensorHao<T,D> C=std::move(A); C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (TensorHao<T,D>&& A,TensorHao<T,D>&& B)           {TensorHao<T,D> C=std::move(A); C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (const TensorHao<T,D>& A,const TensorHaoRef<T,D>& B) {TensorHao<T,D> C=A; C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (TensorHao<T,D>&& A,const TensorHaoRef<T,D>& B)      {TensorHao<T,D> C=std::move(A); C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (const TensorHaoRef<T,D>& A,const TensorHao<T,D>& B) {TensorHao<T,D> C=A; C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (const TensorHaoRef<T,D>& A, TensorHao<T,D>&& B)  {TensorHao<T,D> C=std::move(B); C+=A; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (const TensorHaoRef<T,D>& A,const TensorHaoRef<T,D>& B) {TensorHao<T,D> C=A; C+=B; return C;}


 //for minus tensor - tensor
 template <class T, size_t D>
 TensorHao<T,D> operator - (const TensorHao<T,D>& A,const TensorHao<T,D>& B) {TensorHao<T,D> C=A; C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (const TensorHao<T,D>& A, TensorHao<T,D>&& B) {TensorHao<T,D> C=std::move(B); C.min_add_equal(A); return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (TensorHao<T,D>&& A,const TensorHao<T,D>& B)      {TensorHao<T,D> C=std::move(A); C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (TensorHao<T,D>&& A,TensorHao<T,D>&& B)           {TensorHao<T,D> C=std::move(A); C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (const TensorHao<T,D>& A,const TensorHaoRef<T,D>& B) {TensorHao<T,D> C=A; C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (TensorHao<T,D>&& A,const TensorHaoRef<T,D>& B)      {TensorHao<T,D> C=std::move(A); C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (const TensorHaoRef<T,D>& A,const TensorHao<T,D>& B) {TensorHao<T,D> C=A; C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (const TensorHaoRef<T,D>& A, TensorHao<T,D>&& B)  {TensorHao<T,D> C=std::move(B); C.min_add_equal(A); return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (const TensorHaoRef<T,D>& A,const TensorHaoRef<T,D>& B) {TensorHao<T,D> C=A; C-=B; return C;}


 //for time tensor * tensor
 template <class T, size_t D>
 TensorHao<T,D> operator * (const TensorHao<T,D>& A,const TensorHao<T,D>& B) {TensorHao<T,D> C=A; C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (const TensorHao<T,D>& A, TensorHao<T,D>&& B)     {TensorHao<T,D> C=std::move(B); C*=A; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (TensorHao<T,D>&& A,const TensorHao<T,D>& B)      {TensorHao<T,D> C=std::move(A); C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (TensorHao<T,D>&& A,TensorHao<T,D>&& B)           {TensorHao<T,D> C=std::move(A); C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (const TensorHao<T,D>& A,const TensorHaoRef<T,D>& B) {TensorHao<T,D> C=A; C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (TensorHao<T,D>&& A,const TensorHaoRef<T,D>& B)      {TensorHao<T,D> C=std::move(A); C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (const TensorHaoRef<T,D>& A,const TensorHao<T,D>& B) {TensorHao<T,D> C=A; C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (const TensorHaoRef<T,D>& A, TensorHao<T,D>&& B)  {TensorHao<T,D> C=std::move(B); C*=A; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (const TensorHaoRef<T,D>& A,const TensorHaoRef<T,D>& B) {TensorHao<T,D> C=A; C*=B; return C;}

 //for divide tensor / tensor
 template <class T, size_t D>
 TensorHao<T,D> operator / (const TensorHao<T,D>& A,const TensorHao<T,D>& B) {TensorHao<T,D> C=A; C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (const TensorHao<T,D>& A, TensorHao<T,D>&& B) {TensorHao<T,D> C=std::move(B); C.inv_div_equal(A); return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (TensorHao<T,D>&& A,const TensorHao<T,D>& B)      {TensorHao<T,D> C=std::move(A); C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (TensorHao<T,D>&& A,TensorHao<T,D>&& B)           {TensorHao<T,D> C=std::move(A); C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (const TensorHao<T,D>& A,const TensorHaoRef<T,D>& B) {TensorHao<T,D> C=A; C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (TensorHao<T,D>&& A,const TensorHaoRef<T,D>& B)      {TensorHao<T,D> C=std::move(A); C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (const TensorHaoRef<T,D>& A,const TensorHao<T,D>& B) {TensorHao<T,D> C=A; C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (const TensorHaoRef<T,D>& A, TensorHao<T,D>&& B)  {TensorHao<T,D> C=std::move(B); C.inv_div_equal(A); return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (const TensorHaoRef<T,D>& A,const TensorHaoRef<T,D>& B) {TensorHao<T,D> C=A; C/=B; return C;}

 //for add: tensor + scalar
 template <class T, size_t D>
 TensorHao<T,D> operator + (const TensorHao<T,D>& A,T B) {TensorHao<T,D> C=A; C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (TensorHao<T,D>&& A, T B)     {TensorHao<T,D> C=std::move(A); C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (T B,const TensorHao<T,D>& A) {TensorHao<T,D> C=A; C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (T B,TensorHao<T,D>&& A)      {TensorHao<T,D> C=std::move(A); C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (const TensorHaoRef<T,D>& A,T B) {TensorHao<T,D> C=A; C+=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator + (T B,const TensorHaoRef<T,D>& A) {TensorHao<T,D> C=A; C+=B; return C;}

 //for minus: tensor - scalar
 template <class T, size_t D>
 TensorHao<T,D> operator - (const TensorHao<T,D>& A,T B) {TensorHao<T,D> C=A; C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (TensorHao<T,D>&& A, T B)     {TensorHao<T,D> C=std::move(A); C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (T B,const TensorHao<T,D>& A) {TensorHao<T,D> C=A; C.min_add_equal(B);return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (T B,TensorHao<T,D>&& A)      {TensorHao<T,D> C=std::move(A);C.min_add_equal(B);return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (const TensorHaoRef<T,D>& A,T B) {TensorHao<T,D> C=A; C-=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator - (T B,const TensorHaoRef<T,D>& A) {TensorHao<T,D> C=A; C.min_add_equal(B);return C;}

 //for time: tensor * scalar
 template <class T, size_t D>
 TensorHao<T,D> operator * (const TensorHao<T,D>& A,T B) {TensorHao<T,D> C=A; C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (TensorHao<T,D>&& A, T B)     {TensorHao<T,D> C=std::move(A); C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (T B,const TensorHao<T,D>& A) {TensorHao<T,D> C=A; C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (T B,TensorHao<T,D>&& A)      {TensorHao<T,D> C=std::move(A); C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (const TensorHaoRef<T,D>& A,T B) {TensorHao<T,D> C=A; C*=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator * (T B,const TensorHaoRef<T,D>& A) {TensorHao<T,D> C=A; C*=B; return C;}

 //for minus: tensor / scalar
 template <class T, size_t D>
 TensorHao<T,D> operator / (const TensorHao<T,D>& A,T B) {TensorHao<T,D> C=A; C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (TensorHao<T,D>&& A, T B)     {TensorHao<T,D> C=std::move(A); C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (T B,const TensorHao<T,D>& A) {TensorHao<T,D> C=A; C.inv_div_equal(B);return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (T B,TensorHao<T,D>&& A)      {TensorHao<T,D> C=std::move(A);C.inv_div_equal(B);return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (const TensorHaoRef<T,D>& A,T B) {TensorHao<T,D> C=A; C/=B; return C;}
 template <class T, size_t D>
 TensorHao<T,D> operator / (T B,const TensorHaoRef<T,D>& A) {TensorHao<T,D> C=A; C.inv_div_equal(B);return C;}

 //for diff: return the different elements in two Tensors
 template <class T, size_t D>
 size_t diff(const TensorCore<T,D>& A, const TensorCore<T,D>& B, double eta)
 {
    //Use std::abs instead of abs is very important here since it is in header file
    //For normal cpp file, if we use " using namespace std; ", we are using std:abs
    //To see the difference, run the following line:
    //std::cout<<abs(0.123)<<" "<<std::abs(0.123)<<std::endl;
    //The result is 0 and 0.123

     size_t flag=0; double abs_eta=myabs(eta);

    for(size_t i=0; i<D; i++) { if(A.rank(i) != B.rank(i) ) flag++; }
    for(size_t i=0; i<D; i++) { if(A.rankStep(i) != B.rankStep(i) ) flag++; }
    if(A.size() != B.size() ) flag++;
    const T* A_p = A.data(); const T* B_p = B.data();
    for(size_t i=0; i<A.size(); i++) { if( myabs( A_p[i]- B_p[i] )> abs_eta  ) flag++; }
    return flag;
 }

 //for cout
 template <class T, size_t D>
 std::ostream& operator<< (std::ostream &out, const TensorCore<T,D>& object)
 {
     out<<"Dimen: "<<D<<"\n";
     out<<"Rank: "; for (size_t i = 0; i<D; ++i) out<<object.rank(i)<<" "; out<<"\n";

     out<<"Size: "<<object.size()<<"\n";
     out<<"Data: ";
     size_t L = object.size(); const T* object_p = object.data();
     for (size_t i = 0; i<L; ++i) out<<object_p[i]<<" ";
     return out;
 }

} //end namespace tensorHao

#endif
