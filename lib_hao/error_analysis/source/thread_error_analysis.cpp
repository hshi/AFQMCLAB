#include "../include/thread_error_analysis.h"

using namespace std;

void calculateMeanErrorBetweenThread(complex<double> value_thread, complex<double> &mean, double &err)
{
#ifdef MPI_HAO
    int size = MPISize();

    //Calculate mean, send to all the tread
    MPI_Allreduce(&value_thread, &mean, 1, MPI_DOUBLE_COMPLEX, MPI_SUM, MPI_COMM_WORLD);
    mean/= (size*1.0);

    //Calculate err, only send to main thread
    if(size!=1)
    {
        double diff_thread=norm(value_thread-mean);
        MPI_Reduce(&diff_thread, &err, 1 , MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        if( MPIRank()==0 ) err = sqrt( err / ( size*(size-1.0) ) );
    }
    else
    {
        err = 0.0;
    }
#else
    mean=value_thread; err=0.0;
#endif
}


void calculateMeanErrorBetweenThread(int N, const complex<double> *value_thread, complex<double> *mean, double *err)
{
#ifdef MPI_HAO
    int size = MPISize();

    //Calculate mean, send to all the tread
    MPI_Allreduce(value_thread, mean, N, MPI_DOUBLE_COMPLEX, MPI_SUM, MPI_COMM_WORLD); 
    for(int i=0; i<N; i++) mean[i]/=(size*1.0);

    //Calculate err, only send to main thread
    if(size!=1)
    {
        vector<double> diff_thread(N);
        for(int i=0; i<N; i++) diff_thread[i]=norm( value_thread[i] - mean[i] );
        MPI_Reduce(diff_thread.data(), err, N , MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        if( MPIRank()==0 )
        {
            for(int i=0; i<N; i++) err[i]=sqrt( err[i]/( size*(size-1.0) ) );
        }
    }
    else
    {
        for(int i=0; i<N; i++) err[i]=0.0;
    }
#else
    for(int i=0; i<N; i++)
    {
        mean[i]=value_thread[i]; err[i]=0.0;
    }
#endif
}


void calculateMeanErrorBetweenThread(const vector<complex<double> > &value_thread,
                                     vector<complex<double> > &mean, vector<double> &err)
{
    int N_value=value_thread.size(); int N_mean=mean.size(); int N_err=err.size();

    if( N_value != N_mean )
    {
        cout<<"Input mean size is not consistent in calculateMeanErrorBetweenThread vector! "<<N_value<<" "<<N_mean<<endl;
        exit(1);
    }

    if( MPIRank() == 0 )
    {
        if (N_value != N_err)
        {
            cout << "Input err size is not consistent in calculateMeanErrorBetweenThread vector! " << N_value << " " << N_err << endl;
            exit(1);
        }
    }

    calculateMeanErrorBetweenThread(N_value, value_thread.data(), mean.data(), err.data());
}