#ifdef USE_MAGMA

#include "../include/tensor_2d_bl_cpu.h"
#include "../include/tensor_2d_bl_magma.h"
#include "../include/tensor_fill.h"
#include "magma.h"

using namespace std;
using namespace tensor_hao;

size_t i_max=3136;

void gmm_float_timing(size_t M, size_t N, size_t K)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<float,2> a(M, K); randomFill(a);
    TensorHao<float,2> b(K, N); randomFill(b);
    TensorHao<float,2> c_cpu(M, N), c_magma(M, N);

    cpu_time = magma_wtime();
    gmm_cpu(a,b,c_cpu);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    gmm_magma(a,b,c_magma);
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(c_cpu,c_magma,1e-4);  

    //if(M==3136) 
    //{
    //    TensorHao<float,2> test=c_cpu-c_magma;
    //    for(size_t j=0; j<N; j++)
    //    {
    //        for(size_t i=0; i<N; i++)
    //        {
    //            if(abs(test(i,j))> 1e-3) cout<<test(i,j)<<endl;
    //        }
    //    }
    //}

    cout<<setw(16)<<M<<setw(16)<<N<<setw(16)<<K<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}

void gmm_float_timing_loop()
{
    cout<<"Timing gmm float:"<<endl;
    cout<<setw(16)<<"M"<<setw(16)<<"N"<<setw(16)<<"K"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 8; i <= 1087; i *= 2)       gmm_float_timing(i, i, i);
    for (size_t i = 1088; i <= i_max; i += 1024) gmm_float_timing(i, i, i);
    cout<<"\n\n\n"<<endl;
}


void gmm_double_timing(size_t M, size_t N, size_t K)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<double,2> a(M, K); randomFill(a);
    TensorHao<double,2> b(K, N); randomFill(b);
    TensorHao<double,2> c_cpu(M, N), c_magma(M, N);

    cpu_time = magma_wtime();
    gmm_cpu(a,b,c_cpu);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    gmm_magma(a,b,c_magma);
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(c_cpu,c_magma,1e-10);
    cout<<setw(16)<<M<<setw(16)<<N<<setw(16)<<K<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}

void gmm_double_timing_loop()
{
    cout<<"Timing gmm double:"<<endl;
    cout<<setw(16)<<"M"<<setw(16)<<"N"<<setw(16)<<"K"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 8; i <= 1087; i *= 2)       gmm_double_timing(i, i, i);
    for (size_t i = 1088; i <= i_max; i += 1024) gmm_double_timing(i, i, i);
    cout<<"\n\n\n"<<endl;
}



void gmm_complexfloat_timing(size_t M, size_t N, size_t K)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<complex<float>,2> a(M, K); randomFill(a);
    TensorHao<complex<float>,2> b(K, N); randomFill(b);
    TensorHao<complex<float>,2> c_cpu(M, N), c_magma(M, N);

    cpu_time = magma_wtime();
    gmm_cpu(a,b,c_cpu);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    gmm_magma(a,b,c_magma);
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(c_cpu,c_magma,1e-4);
    cout<<setw(16)<<M<<setw(16)<<N<<setw(16)<<K<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}

void gmm_complexfloat_timing_loop()
{
    cout<<"Timing gmm complexfloat:"<<endl;
    cout<<setw(16)<<"M"<<setw(16)<<"N"<<setw(16)<<"K"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 8; i <= 1087; i *= 2)       gmm_complexfloat_timing(i, i, i);
    for (size_t i = 1088; i <= i_max; i += 1024) gmm_complexfloat_timing(i, i, i);
    cout<<"\n\n\n"<<endl;
}



void gmm_complexdouble_timing(size_t M, size_t N, size_t K)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<complex<double>,2> a(M, K); randomFill(a);
    TensorHao<complex<double>,2> b(K, N); randomFill(b);
    TensorHao<complex<double>,2> c_cpu(M, N), c_magma(M, N);

    cpu_time = magma_wtime();
    gmm_cpu(a,b,c_cpu);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    gmm_magma(a,b,c_magma);
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(c_cpu,c_magma,1e-10);
    cout<<setw(16)<<M<<setw(16)<<N<<setw(16)<<K<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}

void gmm_complexdouble_timing_loop()
{
    cout<<"Timing gmm complexdouble:"<<endl;
    cout<<setw(16)<<"M"<<setw(16)<<"N"<<setw(16)<<"K"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 8; i <= 1087; i *= 2)       gmm_complexdouble_timing(i, i, i);
    for (size_t i = 1088; i <= i_max; i += 1024) gmm_complexdouble_timing(i, i, i);
    cout<<"\n\n\n"<<endl;
}


void eigen_double_timing(size_t N)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<double,2>  a_cpu(N,N), a_magma(N,N);
    TensorHao<double,1>  w_cpu(N),   w_magma(N);

    //Get a real symmetry a_cpu and a_magma
    randomFill(a_cpu);
    for (size_t j=0; j<N; j++) {for (size_t i=j+1; i<N; i++) a_cpu(i,j)=a_cpu(j,i);}
    a_magma=a_cpu;

    cpu_time = magma_wtime();
    eigen_cpu(a_cpu,w_cpu);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    eigen_magma(a_magma,w_magma);
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(w_cpu,w_magma,1e-10);
    cout<<setw(16)<<N<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}

void eigen_double_timing_loop()
{
    cout<<"Timing eigen double:"<<endl;
    cout<<setw(16)<<"N"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 210; i <= 1000; i += 200)     eigen_double_timing(i);
    for (size_t i = 1088; i <= i_max; i += 1024)   eigen_double_timing(i);
    cout<<"\n\n\n"<<endl;
}


void eigen_complexdouble_timing(size_t N)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<complex<double>,2>  a_cpu(N,N), a_magma(N,N);
    TensorHao<double,1>           w_cpu(N),   w_magma(N);

    //Get a Hermition matrix a_cpu and a_magma
    randomFill(a_cpu); 
    for (size_t j=0; j<N; j++)
    {
        a_cpu(j,j)=a_cpu(j,j).real();
        for (size_t i=j+1; i<N; i++) a_cpu(i,j)=conj(a_cpu(j,i));
    }
    a_magma=a_cpu;
    checkHermitian(a_cpu); 

    cpu_time = magma_wtime();
    eigen_cpu(a_cpu,w_cpu);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    eigen_magma(a_magma,w_magma);
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(w_cpu,w_magma,1e-10);
    cout<<setw(16)<<N<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}

void eigen_complexdouble_timing_loop()
{
    cout<<"Timing eigen complex double:"<<endl;
    cout<<setw(16)<<"N"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 210; i <= 1000; i += 200)     eigen_complexdouble_timing(i);
    for (size_t i = 1088; i <= i_max; i += 1024)   eigen_complexdouble_timing(i);
    cout<<"\n\n\n"<<endl;
}

void LUconstruct_timing(size_t N)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<complex<double>,2>  X(N,N); randomFill(X);

    cpu_time = magma_wtime();
    LUDecomp<complex<double>> LU_cpu=LUconstruct_cpu(X);
    cpu_time = magma_wtime() - cpu_time;      

    magma_time = magma_wtime();
    LUDecomp<complex<double>> LU_magma=LUconstruct_magma(X);
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(LU_cpu.A, LU_magma.A,1e-10);
    cout<<setw(16)<<N<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl; 
}

void LUconstruct_timing_loop()
{
    cout<<"Timing LUconstruct complex double:"<<endl;
    cout<<setw(16)<<"N"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 16; i <= 1087; i += 128)     LUconstruct_timing(i);
    for (size_t i = 1088; i <= i_max; i += 1024)  LUconstruct_timing(i);
    cout<<"\n\n\n"<<endl;
}


void inverse_timing(size_t N)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<complex<double>,2> X(N,N); randomFill(X);
    TensorHao<complex<double>,2> A_cpu(N,N), A_magma(N,N);
    LUDecomp<complex<double>> LU_cpu=LUconstruct_cpu(X);
    LUDecomp<complex<double>> LU_magma=LUconstruct_magma(X);
    
    cpu_time = magma_wtime();
    A_cpu=inverse_cpu( LU_cpu );
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    A_magma=inverse_magma( LU_magma );
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(A_cpu, A_magma,1e-10);
    cout<<setw(16)<<N<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}


void inverse_timing_loop()
{
    cout<<"Timing inverse complex double:"<<endl;
    cout<<setw(16)<<"N"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 16; i <= 1087; i += 128)     inverse_timing(i);
    for (size_t i = 1088; i <= i_max; i += 1024)  inverse_timing(i);
    cout<<"\n\n\n"<<endl;
}


void solve_lineq_timing(size_t N, size_t M)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<complex<double>,2> X(N,N); randomFill(X);
    LUDecomp<complex<double>> LU_cpu=LUconstruct_cpu(X);
    LUDecomp<complex<double>> LU_magma=LUconstruct_magma(X);
    TensorHao<complex<double>,2> B(N,M); randomFill(B);
    TensorHao<complex<double>,2> A_cpu(N,M), A_magma(N,M);

    cpu_time = magma_wtime();
    A_cpu=solve_lineq_cpu( LU_cpu , B);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    A_magma=solve_lineq_magma( LU_magma , B);
    magma_time = magma_wtime() - magma_time;

    size_t flag=diff(A_cpu, A_magma,1e-10);
    cout<<setw(16)<<N<<setw(16)<<M<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}


void solve_lineq_timing_loop()
{
    cout<<"Timing solve_lineq complex double:"<<endl;
    cout<<setw(16)<<"N"<<setw(16)<<"M"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 8; i <= 1087; i *= 2)        solve_lineq_timing(i,i);
    for (size_t i = 1088; i <= i_max; i += 1024)  solve_lineq_timing(i,i);
    cout<<"\n\n\n"<<endl;
}


void QRMatrix_timing(size_t N, size_t M)
{
    real_Double_t cpu_time, magma_time;
    double det_cpu,det_magma;
    TensorHao<complex<double>,2> ph_cpu(N,M), ph_magma(N,M);
    randomFill(ph_cpu); ph_magma=ph_cpu;

    cpu_time = magma_wtime();
    det_cpu=QRMatrix_cpu(ph_cpu);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    det_magma=QRMatrix_magma(ph_magma);
    magma_time = magma_wtime() - magma_time;

    size_t flag=0; 
    for(size_t j=0; j<M; j++)
    {
        for(size_t i=0; i<N; i++) {if(abs(abs(ph_cpu(i,j))-abs(ph_magma(i,j)))>1e-10) flag++;}
    }
    if(abs((det_cpu-det_magma)/det_magma)>1e-10) {flag++;}

    //In large system, the cpu part will have infinite, magma will have finite value:
    //It might be a bug from magma, here we are using magma_zgeqrf_gpu and magma_zungqr_gpu
    //If we use magma_zgeqrf and magma_zungqr2, it will be the same with cpu.
    //Example about output:
    //N=128 M=128 det_cpu=9.0991e+229 det_magma=1.14202e+14
    //N=256 M=256 det_cpu=inf det_magma=1.07379e+14
    //if(abs((det_cpu-det_magma)/det_magma)>1e-10) flag++;
    //cout<<det_cpu<<endl;
    //cout<<det_magma<<endl; 
    cout<<setw(16)<<N<<setw(16)<<M<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}


void QRMatrix_timing_loop()
{
    cout<<"Timing QRMatrix complex double:"<<endl;
    cout<<setw(16)<<"N"<<setw(16)<<"M"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 8; i <= 1087; i *= 2)        QRMatrix_timing(i,i);
    for (size_t i = 1088; i <= i_max; i += 1024)  QRMatrix_timing(i,i);
    cout<<"\n\n\n"<<endl;
}

void SVDMatrix_timing(size_t N)
{
    real_Double_t cpu_time, magma_time;
    TensorHao<complex<double>,2> U_cpu(N,N), U_magma(N,N);
    TensorHao<complex<double>,2> V_cpu(N,N), V_magma(N,N);
    TensorHao<double,1> D_cpu(N), D_magma(N);
    randomFill(U_cpu); U_magma=U_cpu;

    cpu_time = magma_wtime();
    SVDMatrix_cpu(U_cpu, D_cpu, V_cpu);
    cpu_time = magma_wtime() - cpu_time;

    magma_time = magma_wtime();
    SVDMatrix_magma(U_magma, D_magma, V_magma);
    magma_time = magma_wtime() - magma_time;

    size_t flag=0;
    for(size_t j=0; j<N; j++)
    {
        for(size_t i=0; i<N; i++) {if(abs(abs(U_cpu(i,j))-abs(U_magma(i,j)))>1e-10) flag++;}
    }
    flag += diff(D_cpu, D_magma, 1e-10);

    cout<<setw(16)<<N<<setw(16)<<cpu_time<<setw(16)<<magma_time<<setw(16)<<flag<<endl;
}

void SVDMatrix_timing_loop()
{
    cout<<"Timing SVDMatrix complex double:"<<endl;
    cout<<setw(16)<<"N"<<setw(16)<<"cpu_time"<<setw(16)<<"magma_time"<<setw(16)<<"flag"<<endl;
    for (size_t i = 8; i <= 1087; i *= 2)        SVDMatrix_timing(i);
    for (size_t i = 1088; i <= i_max; i += 1024)  SVDMatrix_timing(i);
    cout<<"\n\n\n"<<endl;
}


void bl_cpu_magma_timing()
{
   gmm_float_timing_loop();
   gmm_double_timing_loop();
   gmm_complexfloat_timing_loop();
   gmm_complexdouble_timing_loop();
   eigen_double_timing_loop();
   eigen_complexdouble_timing_loop();
   LUconstruct_timing_loop();
   inverse_timing_loop();
   solve_lineq_timing_loop();
   QRMatrix_timing_loop();
   SVDMatrix_timing_loop();
}


#endif
