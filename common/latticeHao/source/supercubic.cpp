//
// Created by boruoshihao on 12/20/16.
//

#include <fstream>
#include <tuple>
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
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file >> Dimen;
    n.resize(Dimen);
    for(size_t i = 0; i < n.size(); ++i) file >> n(i);
    L = 1; for(size_t i = 0; i < n.size(); ++i) L *= n(i);
    file.close();
}

void Supercubic::write(const string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    file<<n.size()<<"\n";
    for(size_t i = 0; i < n.size(); ++i) file<<n(i)<<" "; file<<"\n";
    file.close();
}

void MPIBcast(Supercubic &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.n, root, comm );
    MPIBcast( buffer.L, root, comm );
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

tuple<TensorHao<size_t, 1>, TensorHao<size_t, 1>, TensorHao<complex<double>, 1> >
getNearestNeighborHopping(const Supercubic &latt, double t1, const TensorHao<double, 1> &k)
{
    size_t dimen = latt.getDimen(); size_t L = latt.getL(); const TensorHao<int, 1> &n = latt.getN();
    complex<double> Xi(0,1);
    double PI = 3.14159265358979324;

    size_t Nhop = 2*L*dimen;
    TensorHao<size_t, 1> sit_i(Nhop), sit_j(Nhop);
    TensorHao<complex<double>, 1> hop(Nhop);

    TensorHao<int,1> coor_i, coor_j; size_t hopIndex(0);
    for(size_t lattIndex = 0; lattIndex < L; ++lattIndex)
    {
        coor_i = latt.coor( lattIndex );
        for(size_t dimenIndex = 0; dimenIndex < dimen; ++dimenIndex)
        {
            for(int direction = -1; direction <2 ; direction+=2)
            {
                coor_j =  coor_i;
                coor_j(dimenIndex) =  latt.bound( coor_i(dimenIndex) + direction, n(dimenIndex) );

                sit_i( hopIndex ) = lattIndex;
                sit_j( hopIndex ) = latt.index( coor_j );
                hop( hopIndex ) = -t1*exp( direction * 1.0 * Xi* k(dimenIndex)*2.0*PI/( n(dimenIndex)*1.0 ) );

                hopIndex++;
            }
        }
    }

    return make_tuple( move(sit_i),  move(sit_j), move(hop) );
}

TensorHao<double, 1> getNearestNeighborDispersion(const Supercubic &latt, double t1, const TensorHao<double, 1> &k)
{
    size_t dimen = latt.getDimen(); size_t L = latt.getL(); const TensorHao<int, 1> &n = latt.getN();
    double PI = 3.14159265358979324;

    double ek;
    TensorHao<int,1> kcoor;
    TensorHao<double, 1> dispersion(L);

    for(size_t i = 0; i < L; ++i)
    {
        kcoor = latt.coor(i);
        ek = 0.0;
        for(size_t j = 0; j < dimen; ++j)
        {
            ek += cos( ( kcoor(j)+k(j) ) * 2.0 * PI / n(j)  );
        }
        dispersion(i) = -2.0 * t1 * ek;
    }
    return dispersion;
}

TensorHao<double, 1> getContinuousDispersion(const Supercubic &latt, double t1, const TensorHao<double, 1> &k)
{
    size_t dimen = latt.getDimen(); size_t L = latt.getL(); const TensorHao<int, 1> &n = latt.getN();
    double PI = 3.14159265358979324;

    double ek, km;
    TensorHao<int,1> kcoor;
    TensorHao<double, 1> dispersion(L);

    for(size_t i = 0; i < L; ++i)
    {
        kcoor = latt.coor(i);
        ek = 0.0;
        for(size_t j = 0; j < dimen; ++j)
        {
            km = ( kcoor(j)+k(j) ) * 2.0 * PI / n(j);
            if( km >= PI ) km -= 2.0*PI;
            ek += km * km;
        }
        dispersion(i) = t1 * ek;
    }
    return dispersion;
}