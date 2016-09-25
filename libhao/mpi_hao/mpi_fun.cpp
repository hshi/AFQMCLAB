#include <iostream>
#include "mpi_fun.h"

#ifdef MPI_HAO
using std::complex;

void MPIInit(int& argc,char** & argv) {MPI_Init(&argc,&argv);}
void MPIInitFunnel(int& argc,char** & argv) 
{
    int provided; MPI_Init_thread(&argc,&argv,MPI_THREAD_FUNNELED,&provided);
    //if(provided!=MPI_THREAD_FUNNELED)
    //{
    //    if(MPIRank()==0) std::cout<<"WARNING!!!!The Marchine does not supply MPI_THREAD_FUNNELED, only supply to: "
    //                              <<provided<<"-th level!"<<std::endl;
    //}
}
int MPISize(const MPI_Comm& comm) {int size;MPI_Comm_size(comm, &size);return size;}
int MPIRank(const MPI_Comm& comm) {int rank;MPI_Comm_rank(comm, &rank);return rank;}
void MPIBarrier(const MPI_Comm& comm) {MPI_Barrier(comm);}
void MPIFinalize() {MPI_Finalize();}


void MPIBcast(int& buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(&buffer, 1, MPI_INT, root, comm); 
}

void MPIBcast(long& buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(&buffer, 1, MPI_LONG, root, comm);
}

void MPIBcast(long long& buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(&buffer, 1, MPI_LONG_LONG, root, comm);
}

void MPIBcast(size_t& buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(&buffer,sizeof(buffer), MPI_BYTE, root, comm);
}

void MPIBcast(float& buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(&buffer, 1, MPI_FLOAT, root, comm);
}

void MPIBcast(double& buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(&buffer, 1, MPI_DOUBLE, root, comm);
}

void MPIBcast(complex<float>& buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(&buffer, 1, MPI_COMPLEX, root, comm);
}

void MPIBcast(complex<double>& buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(&buffer, 1, MPI_DOUBLE_COMPLEX, root, comm);
}


void MPIBcast(int N, int* buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(buffer, N, MPI_INT, root, comm);
}

void MPIBcast(int N, double* buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(buffer, N, MPI_DOUBLE, root, comm);
}


void MPIBcast(int N, complex<double>* buffer, int root, const MPI_Comm& comm )
{
    MPI_Bcast(buffer, N, MPI_DOUBLE_COMPLEX, root, comm);
}


int MPISum(const int& sendbuf, int root,  const MPI_Comm& comm)
{
    int recvbuf=0;
    MPI_Reduce(&sendbuf, &recvbuf, 1 , MPI_INT, MPI_SUM, root, comm);
    return recvbuf;
}

long MPISum(const long& sendbuf, int root,  const MPI_Comm& comm)
{
    long recvbuf=0;
    MPI_Reduce(&sendbuf, &recvbuf, 1 , MPI_LONG, MPI_SUM, root, comm);
    return recvbuf;
}

long long MPISum(const long long& sendbuf, int root,  const MPI_Comm& comm)
{
    long long recvbuf=0;
    MPI_Reduce(&sendbuf, &recvbuf, 1 , MPI_LONG_LONG, MPI_SUM, root, comm);
    return recvbuf;
}

float MPISum(const float& sendbuf, int root,  const MPI_Comm& comm)
{
    float recvbuf=0;
    MPI_Reduce(&sendbuf, &recvbuf, 1 , MPI_FLOAT, MPI_SUM, root, comm);
    return recvbuf;
}

double MPISum(const double& sendbuf, int root,  const MPI_Comm& comm)
{
    double recvbuf=0;
    MPI_Reduce(&sendbuf, &recvbuf, 1 , MPI_DOUBLE, MPI_SUM, root, comm);
    return recvbuf;
}

complex<float> MPISum(const complex<float>& sendbuf, int root,  const MPI_Comm& comm)
{
    complex<float> recvbuf={0,0};
    MPI_Reduce(&sendbuf, &recvbuf, 1 , MPI_COMPLEX, MPI_SUM, root, comm);
    return recvbuf;
}

complex<double> MPISum(const complex<double>& sendbuf, int root,  const MPI_Comm& comm)
{
    complex<double> recvbuf={0,0};
    MPI_Reduce(&sendbuf, &recvbuf, 1 , MPI_DOUBLE_COMPLEX, MPI_SUM, root, comm);
    return recvbuf;
} 

void MPISum(int N, const double* sendbuf, double* recvbuf, int root, const MPI_Comm& comm)
{
    MPI_Reduce(sendbuf, recvbuf, N , MPI_DOUBLE, MPI_SUM, root, comm);
}

void MPISum(int N, const complex<double>* sendbuf, complex<double>*recvbuf, int root, const MPI_Comm& comm)
{
    MPI_Reduce(sendbuf, recvbuf, N , MPI_DOUBLE_COMPLEX, MPI_SUM, root, comm);
}


void MPIGather(const double& sendbuf, double* recvbuf, int root, const MPI_Comm& comm)
{
    MPI_Gather(&sendbuf,1,MPI_DOUBLE,recvbuf,1,MPI_DOUBLE,root,comm);
}

void MPIGather(const complex<double>& sendbuf, complex<double>* recvbuf, int root, const MPI_Comm& comm)
{
    MPI_Gather(&sendbuf,1,MPI_DOUBLE_COMPLEX,recvbuf,1,MPI_DOUBLE_COMPLEX,root,comm);
}

#else
void MPIInit(int& argc,char** & argv){return;}
void MPIInitFunnel(int& argc,char** & argv) {return;}
int MPISize() {return 1;}
int MPIRank() {return 0;}
void MPIBarrier() {return;}
void MPIFinalize() {return;}
#endif
