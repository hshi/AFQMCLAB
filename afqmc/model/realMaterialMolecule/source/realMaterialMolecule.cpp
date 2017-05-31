//
// Created by boruoshihao on 5/30/17.
//

#include "../include/realMaterialMolecule.h"

using namespace std;
using namespace tensor_hao;

RealMaterialMolecule::RealMaterialMolecule():L(0), Nup(0), Ndn(0) { }

RealMaterialMolecule::RealMaterialMolecule(const std::string &filename) { read(filename); }

RealMaterialMolecule::~RealMaterialMolecule() { }

void RealMaterialMolecule::read(const std::string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    readFile( L, file );
    readFile( Nup, file );
    readFile( Ndn, file );
    readFile( choleskyNumber, file );
    K.resize(L, L); readFile( K.size(),  K.data(),  file );
    choleskyVecs.resize(L, L, choleskyNumber); readFile(choleskyVecs.size(), choleskyVecs.data(), file);
    choleskyBg.resize(choleskyNumber); readFile(choleskyBg.size(), choleskyBg.data(), file);

    file.close();
}

void RealMaterialMolecule::write(const std::string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    writeFile( L, file );
    writeFile( Nup, file );
    writeFile( Ndn, file );
    writeFile( choleskyNumber, file );
    writeFile( K.size(),  K.data(),  file );
    writeFile( choleskyVecs.size(), choleskyVecs.data(), file);
    writeFile( choleskyBg.size(), choleskyBg.data(), file);

    file.close();
}

#ifdef MPI_HAO
void MPIBcast(RealMaterialMolecule &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast(buffer.L);
    MPIBcast(buffer.Nup);
    MPIBcast(buffer.Ndn);
    MPIBcast(buffer.choleskyNumber);
    MPIBcast(buffer.K);
    MPIBcast(buffer.choleskyVecs);
    MPIBcast(buffer.choleskyBg);
}
#endif

RealMaterialMolecule::RealMaterialMolecule(const RealMaterialMolecule &x)  { }

RealMaterialMolecule &RealMaterialMolecule::operator=(const RealMaterialMolecule &x) { return *this; }