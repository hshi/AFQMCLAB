//
// Created by boruoshihao on 4/30/17.
//

#include "../include/ghfMethod.h"

using namespace std;

GhfMethod::GhfMethod()
{

}

GhfMethod::~GhfMethod()
{

}

void GhfMethod::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    file>>initialType;
    file>>convergeType;
    file>>convergeTolerance;
    file>>maxIterateStep;
    file>>annealMagnitude;
    file>>annealStep;
    file>>seed;

    file.close();

    analysis();
}

#ifdef MPI_HAO
void MPIBcast(GhfMethod &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast(buffer.initialType);
    MPIBcast(buffer.convergeType);
    MPIBcast(buffer.convergeTolerance);
    MPIBcast(buffer.maxIterateStep);
    MPIBcast(buffer.annealMagnitude);
    MPIBcast(buffer.annealStep);
    MPIBcast(buffer.seed);
}
#endif

void GhfMethod::analysis()
{
    if( convergeTolerance < 0.0 )
    {
        cout<<"Errorr!!! convergeTolerance can not be negative!"<<endl;
        exit(1);
    }
}