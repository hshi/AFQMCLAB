#ifndef AFQMCLAB_MPI_FUN_HAO_H
#define AFQMCLAB_MPI_FUN_HAO_H
#include <algorithm> 

#ifdef MPI_HAO
#include <mpi.h>
#include <complex>

void MPIInit(int& argc,char** & argv);
void MPIInitFunnel(int& argc,char** & argv);
int MPISize(const MPI_Comm& comm=MPI_COMM_WORLD);
int MPIRank(const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBarrier(const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIFinalize();

void MPIBcast(bool                  & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(int                   & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(long                  & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(long long             & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(size_t                & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(float                 & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(double                & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(std::complex<float>   & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(std::complex<double>  & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(std::string & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(size_t count, int *buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(size_t count, size_t *buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIBcast(size_t count, double *buffer, int root = 0, const MPI_Comm &comm = MPI_COMM_WORLD);
void MPIBcast(size_t count, std::complex<double> *buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);

void MPIReduce(const size_t &sendbuf, size_t &recvbuf, MPI_Op op, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);

void MPIAllreduce(const double &sendbuf, double &recvbuf, MPI_Op op, const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIAllreduce(const std::complex<double> &sendbuf, std::complex<double> &recvbuf, MPI_Op op, const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIAllreduce(size_t count, const double *sendbuf, double *recvbuf, MPI_Op op, const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIAllreduce(size_t count, const std::complex<double> *sendbuf, std::complex<double> *recvbuf,
                  MPI_Op op, const MPI_Comm& comm=MPI_COMM_WORLD);

void MPIGather(const double& sendbuf, double* recvbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
void MPIGather(const std::complex<double>& sendbuf, std::complex<double>* recvbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);

int                  MPISum(const int                  & sendbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
long                 MPISum(const long                 & sendbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
long long            MPISum(const long long            & sendbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
size_t               MPISum(const size_t               & sendbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
float                MPISum(const float                & sendbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
double               MPISum(const double               & sendbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
std::complex<float>  MPISum(const std::complex<float>  & sendbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
std::complex<double> MPISum(const std::complex<double> & sendbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
void MPISum(size_t count, const double* sendbuf, double* recvbuf, int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);
void MPISum(size_t count, const std::complex<double>* sendbuf, std::complex<double>* recvbuf,
                                      int root=0, const MPI_Comm& comm=MPI_COMM_WORLD);

#else
void MPIInit(int& argc,char** & argv);
void MPIInitFunnel(int& argc,char** & argv);
int MPISize();
int MPIRank();
void MPIBarrier();
void MPIFinalize();
template<class T> void MPIBcast(const T & buffer) {}
template<class T> void MPIBcast(size_t N, const T* buffer) {}
template<class T> T MPISum(const T & sendbuf) {return sendbuf;}
template<class T> void MPISum(size_t N, const T* sendbuf, T* recvbuf) { std::copy(sendbuf, sendbuf+N, recvbuf); }
#endif  //For MPI and Serial 

#endif
