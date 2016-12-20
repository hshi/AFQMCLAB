//
// Created by boruoshihao on 12/20/16.
//

#include <fstream>

#ifdef MPI_HAO
#include <mpi.h>
#endif

#include "../include/supercubic.h"

using namespace std;
using namespace tensor_hao;

Supercubic::Supercubic(): L(0)  {}

Supercubic::Supercubic(const TensorHao<int, 1> &n): n(n)
{
    L = 1; for(size_t i = 0; i < n.size(); ++i) L *= n(i);
}

Supercubic::Supercubic(const string &filename) { read(filename); }

Supercubic::Supercubic(const Supercubic &x) { copy_deep(x); }

Supercubic::Supercubic(Supercubic &&x) { move_deep(x); }

Supercubic::~Supercubic()  {}

Supercubic &Supercubic::operator=(const Supercubic &x) { copy_deep(x); return *this; }

Supercubic &Supercubic::operator=(Supercubic &&x) { move_deep(x); return *this; }

const TensorHao<int, 1> &Supercubic::getN() const { return n; }

size_t Supercubic::getDimen() const { return n.size(); }

size_t Supercubic::getL() const { return L; }

TensorHao<int, 1> Supercubic::coor(int lattice_index) const
{
    TensorHao<int,1> coordinate( n.size() ); int den=L;
    for(int i=n.size()-1; i>=0; i--)
    {
        den /= n(i);
        coordinate(i) = lattice_index/den;
        lattice_index %= den;
    }
    return coordinate;
}

int Supercubic::index(const TensorHao<int, 1> &lattice_coor) const
{
    if( lattice_coor.size() != n.size() )
    {
        cout<<"Input for index in Supercubic error! Size of lattice_coor != dimen. "<<endl;
        exit(1);
    }

    int Dimen = n.size(); int lattice_index=0; int den=1;
    for(int i=0; i<Dimen; i++)
    {
        lattice_index += ( lattice_coor(i)*den );
        den*=n(i);
    }
    return lattice_index;
}

int Supercubic::bound(const int i, const int i_max) const
{
    int i_bound = (i>=0) ? i%i_max : i%i_max+i_max;
    if(i_bound==i_max) i_bound=0;
    return i_bound;
}

TensorHao<int, 1> Supercubic::coor_relat(const TensorHao<int, 1> &coor_i,
                                         const TensorHao<int, 1> &coor_j) const
{
    if( coor_i.size() != n.size() || coor_j.size() != n.size() )
    {
        cout<<"Input for coor_relat in Supercubic error! Size of coor_i or coor_j !=dimen. " <<endl;
        exit(1);
    }

    int dimen = n.size();
    TensorHao<int,1> dist(dimen);
    for(int i=0; i<dimen; i++) dist(i) = bound( coor_j(i)-coor_i(i), n(i) );
    return dist;
}

TensorHao<int, 1> Supercubic::coor_abs_relat(const TensorHao<int, 1> &coor_i, const TensorHao<int, 1> &coor_j) const
{
    if( coor_i.size() != n.size() || coor_j.size() != n.size() )
    {
        cout<<"Input for coor_relat in Supercubic error! Size of coor_i or coor_j !=dimen. " <<endl;
        exit(1);
    }

    int dimen = n.size();
    TensorHao<int,1> dist(dimen);
    for(int i=0; i<dimen; i++)
    {
        dist(i) = min( bound( coor_j(i)-coor_i(i), n(i) ),
                       bound( coor_i(i)-coor_j(i), n(i) ) );
    }
    return dist;
}

int Supercubic::inverse(int lattice_index) const
{
    int dimen = n.size();
    TensorHao<int,1> coordinate=this->coor(lattice_index);
    for(int i=0; i<dimen; i++) coordinate(i)=this->bound(-coordinate(i),n(i));
    return this->index(coordinate);
}

void Supercubic::read(const string &filename)
{
    int Dimen;
    if( MPIRank() == 0 )
    {
        ifstream file;
        file.open(filename, ios::in);
        if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
        file >> Dimen;
        n.resize(Dimen);
        for(size_t i = 0; i < n.size(); ++i) file >> n(i);
        L = 1; for(size_t i = 0; i < n.size(); ++i) L *= n(i);
        file.close();
    }

    MPIBcast( Dimen );
    n.resize( Dimen );
    MPIBcast( n );
    MPIBcast( L );
}

void Supercubic::copy_deep(const Supercubic &x)
{
    n = x.n;
    L = x.L;
}

void Supercubic::move_deep(Supercubic &x)
{
    n = move( x. n );
    L = x.L;
}