#include "../include/threadErrorAnalysis.h"

using namespace std;

complex<double> calculateMeanBetweenThreads(complex<double> valueEachThread)
{
#ifdef MPI_HAO
    complex<double> mean;
    MPIAllreduce(valueEachThread, mean, MPI_SUM);
    mean /= ( MPISize() * 1.0 );
    return mean;
#else
    return valueEachThread;
#endif
}

complex<double> calculateVarianceBetweenThreads(complex<double> valueEachThread, complex<double> mean)
{
#ifdef MPI_HAO
    complex<double> varEachThread=norm(valueEachThread-mean);
    return MPISum(varEachThread) / ( MPISize() * 1.0 );
#else
    return 0.0;
#endif
}

complex<double> calculateErrorBetweenThreads(complex<double> valueEachThread, complex<double> mean)
{
    complex<double> var = calculateVarianceBetweenThreads( valueEachThread, mean);
    int size = MPISize();
    return (size!=1) ? sqrt( var / ( size-1.0) ): 0.0;
}

tuple< complex<double>, complex<double> > calculateMeanErrorBetweenThreads(complex<double> valueEachThread)
{
    complex<double> mean = calculateMeanBetweenThreads(valueEachThread);
    complex<double> err =  calculateErrorBetweenThreads(valueEachThread, mean);
    return make_tuple(mean, err);
}


vector< complex<double> > calculateMeanBetweenThreads(size_t N, const complex<double> *valueEachThread)
{
#ifdef MPI_HAO
    int size = MPISize();
    vector< complex<double> > mean(N);
    MPIAllreduce(N, valueEachThread, mean.data(), MPI_SUM);
    for(size_t i=0; i<N; i++) mean[i]/=(size*1.0);
    return mean;
#else
    vector< complex<double> > mean(N);
    for(size_t i=0; i<N; i++) mean[i]=valueEachThread[i];
    return mean;
#endif
}

vector< complex<double> > calculateVarianceBetweenThreads(size_t N, const complex<double> *valueEachThread,
                                                          const complex<double> * mean)
{
#ifdef MPI_HAO
    vector< complex<double> > variance; if( MPIRank()==0 ) variance.resize(N);

    int size = MPISize();
    vector< complex<double> > varEachThread(N);
    for(size_t i=0; i<N; i++) varEachThread[i]=norm( valueEachThread[i] - mean[i] );
    MPISum( N, varEachThread.data(), variance.data() );

    if( MPIRank()==0 )
    {
        for(size_t i=0; i<N; i++) variance[i] /= ( size*1.0 );
    }
    return variance;
#else
    vector< complex<double> > variance(N);
    for(size_t i=0; i<N; i++) variance[i]=0.0;
    return variance;
#endif
}


vector< complex<double> > calculateErrorBetweenThreads(size_t N, const complex<double> *valueEachThread,
                                                       const complex<double> * mean)
{
    vector< complex<double> > err = calculateVarianceBetweenThreads(N, valueEachThread, mean);

    int rank = MPIRank(); int size = MPISize();

    if(size!=1)
    {
        if(rank==0)
        {
            for(size_t i=0; i<N; i++) err[i]=sqrt( err[i]/(size-1.0) );
        }
    }
    return err;
}

tuple<  vector< complex<double> >, vector< complex<double> >  >
calculateMeanErrorBetweenThreads(size_t N, const complex<double> *valueEachThread)
{
    vector< complex<double > > mean = calculateMeanBetweenThreads( N, valueEachThread );
    vector< complex<double > > err = calculateErrorBetweenThreads( N, valueEachThread, mean.data() );
    return make_tuple( move(mean),  move(err) );
}


vector< complex<double> > calculateMeanBetweenThreads(const vector<complex<double> > &valueEachThread)
{
    return calculateMeanBetweenThreads( valueEachThread.size(), valueEachThread.data() );
}

vector< complex<double> > calculateVarianceBetweenThreads(const vector<complex<double> > &valueEachThread,
                                                          const vector<complex<double> > &mean)
{
    if( valueEachThread.size() != mean.size() )
    {
        cerr<<"Size of vector is not consistent in calculateVarianceBetweenThreads!"<<endl;
        exit(1);
    }
    return calculateVarianceBetweenThreads(valueEachThread.size(), valueEachThread.data(), mean.data() );
}

vector< complex<double> > calculateErrorBetweenThreads(const vector<complex<double> > &valueEachThread,
                                                                 const vector<complex<double> > &mean)
{
    if( valueEachThread.size() != mean.size() )
    {
        cerr<<"Size of vector is not consistent in calculateErrorBetweenThreads!"<<endl;
        exit(1);
    }
    return calculateErrorBetweenThreads(valueEachThread.size(), valueEachThread.data(), mean.data() );
}


tuple<  vector< complex<double> >, vector< complex<double> >  >
calculateMeanErrorBetweenThreads(const vector<complex<double> > &valueEachThread)
{
    return calculateMeanErrorBetweenThreads( valueEachThread.size(), valueEachThread.data() );
}