#include "../include/thread_error_analysis.h"
#include "../include/error_analysis.h"

using namespace std;

/*
void calculate_mean_err_between_thread_complexdouble_test()
{
     int rank=0; int size=1; 
#ifdef MPI_HAO
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif
     vector< complex<double> > vec(size); for(int i=0; i<size; i++) vec[i]=complex<double>(i,i+1);
     complex<double> mean_exact;
     double err_exact;
     error_analysis(vec, mean_exact, err_exact);

     complex<double> value_thread(rank, rank+1);
     complex<double> mean;
     double err;
     calculate_mean_err_between_thread(value_thread, mean, err);

     if(rank==0)
     {
         size_t flag=0;
         if( abs(mean_exact-mean)>1e-12 ) flag++;
         if( abs(err_exact-err)>1e-12 ) flag++;
         if(flag==0) cout<<"PASSED! Calculate_mean_err_between_thread passed complexdouble test!"<<endl;
         else cout<<"WARNING!!!!!!!!! Calculate_mean_err_between_thread failed complexdouble test!"<<endl;
     }
 
}


void calculate_mean_err_between_thread_vector_test()
{
     int rank=0; int size=1;
#ifdef MPI_HAO
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif
     vector< complex<double> > mean_exact(3);
     vector< double >          err_exact(3);
     vector< complex<double> > vec(size); 
     for(int i_array=0; i_array<3; i_array++)
     {
         for(int i=0; i<size; i++) vec[i]=complex<double>(i+i_array,i+i_array+2);
         error_analysis(vec, mean_exact[i_array], err_exact[i_array]);
     }

     vector< complex<double> > value_thread(3);
     vector< complex<double> > mean(3);
     vector< double > err(3);
     for(int i_array=0; i_array<3; i_array++) value_thread[i_array]=complex<double>(rank+i_array, rank+i_array+2);
     calculate_mean_err_between_thread(value_thread, mean, err);
     //calculate_mean_err_between_thread(3, value_thread.data(), mean.data(), err.data());

     if(rank==0)
     {
         size_t flag=0;
         for(int i_array=0; i_array<3; i_array++)
         {
            if( abs(mean_exact[i_array]-mean[i_array])>1e-12 ) flag++;
            if( abs(err_exact[i_array]-err[i_array])>1e-12 ) flag++;
            //cout<<err_exact[i_array]<<" "<<err[i_array]<<endl;
         }
         if(flag==0) cout<<"PASSED! Calculate_mean_err_between_thread passed vector test!"<<endl;
         else cout<<"WARNING!!!!!!!!! Calculate_mean_err_between_thread failed vector test!"<<endl;
     }
 
}


void calculate_mean_err_between_thread_test()
{
    int rank=0;
#ifdef MPI_HAO
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    calculate_mean_err_between_thread_complexdouble_test();
    calculate_mean_err_between_thread_vector_test();

    if(rank==0) cout<<" "<<endl;
}

 */