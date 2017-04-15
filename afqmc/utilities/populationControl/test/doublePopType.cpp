#include "../../../../common/mpiHao/include/mpi_fun.h"
#include "doublePopType.h"

using namespace std;

DoublePop::DoublePop() { setNbuf(); }

DoublePop::DoublePop(double& number_in) { setNbuf(); number=&number_in;}

DoublePop::~DoublePop() {}

int DoublePop::getNbuf() const { return Nbuf; }

DoublePop& DoublePop::operator  = (const DoublePop& x)
{
    *number=*(x.number);
    return *this;
}

#ifdef MPI_HAO

vector<char> DoublePop::pack() const
{
    vector<char> buf(Nbuf);

    int posit=0;
    MPI_Pack(number, 1, MPI_DOUBLE, buf.data(), Nbuf, &posit, MPI_COMM_WORLD);
    if(posit!=Nbuf) {cout<<"ERROR in pack!!! posit does not equal Nbuf! "<<endl; exit(1);}

    return buf;
}

void DoublePop::unpack(const vector<char>& buf)
{
    int bufSize=buf.size();
    if(bufSize!=Nbuf) {cout<<"ERROR in unpack!!! Size of input buf does not equal Nbuf! "<<endl; exit(1);}

    int posit=0;
    MPI_Unpack(buf.data(), Nbuf, &posit, number, 1, MPI_DOUBLE, MPI_COMM_WORLD);
    if(posit!=Nbuf) {cout<<"ERROR in unpack!!! posit does not equal Nbuf! "<<endl; exit(1);}
}

#endif

void DoublePop::setNbuf() { Nbuf = 8; }