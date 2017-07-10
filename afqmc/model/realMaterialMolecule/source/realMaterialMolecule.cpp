//
// Created by boruoshihao on 5/30/17.
//

#include "../include/realMaterialMolecule.h"

using namespace std;
using namespace H5;
using namespace tensor_hao;

RealMaterialMolecule::RealMaterialMolecule():L(0), Nup(0), Ndn(0) { }

RealMaterialMolecule::RealMaterialMolecule(const string &filename) { read(filename); }

RealMaterialMolecule::~RealMaterialMolecule() { }

size_t RealMaterialMolecule::getL() const { return L; }

size_t RealMaterialMolecule::getNup() const { return Nup; }

size_t RealMaterialMolecule::getNdn() const { return Ndn; }

size_t RealMaterialMolecule::getCholeskyNumber() const { return choleskyNumber; }

const TensorHao<double,2> &RealMaterialMolecule::getT() const { return t; }

const TensorHao<double,2> &RealMaterialMolecule::getK() const { return K; }

const TensorHao<double,3> &RealMaterialMolecule::getCholeskyVecs() const { return choleskyVecs; }

const TensorHao<double,1> &RealMaterialMolecule::getCholeskyBg() const { return choleskyBg; }

size_t RealMaterialMolecule::getKpEigenStatus() const { return KpEigenStatus; }

const TensorHao<double,2> &RealMaterialMolecule::getKp() const { return Kp; }

const TensorHao<double,1> &RealMaterialMolecule::getKpEigenValue() const { return KpEigenValue; }

const TensorHao<double, 2> &RealMaterialMolecule::getKpEigenVector() const { return KpEigenVector; }

void RealMaterialMolecule::read(const string &filename)
{
    H5File file(filename, H5F_ACC_RDONLY);

    readFile(L, file, "L");
    readFile(Nup, file, "Nup");
    readFile(Ndn, file, "Ndn");
    readFile(choleskyNumber, file, "choleskyNumber");
    t.resize(L, L); readFile( t.size(),  t.data(),  file, "t" );
    K.resize(L, L); readFile( K.size(),  K.data(),  file, "K" );
    choleskyVecs.resize(L, L, choleskyNumber); readFile(choleskyVecs.size(), choleskyVecs.data(), file, "choleskyVecs");
    choleskyBg.resize(choleskyNumber); readFile(choleskyBg.size(), choleskyBg.data(), file, "choleskyBg");

    file.close();

    KpEigenStatus = 0;
    Kp.resize(0,0);
    KpEigenValue.resize( static_cast<size_t>(0) );
    KpEigenVector.resize( 0, 0 );
}

void RealMaterialMolecule::write(const string &filename) const
{
    H5File file(filename, H5F_ACC_TRUNC);

    writeFile( L, file, "L" );
    writeFile( Nup, file, "Nup" );
    writeFile( Ndn, file, "Ndn" );
    writeFile( choleskyNumber, file, "choleskyNumber" );
    writeFile( t.size(),  t.data(),  file, "t" );
    writeFile( K.size(),  K.data(),  file, "K" );
    writeFile( choleskyVecs.size(), choleskyVecs.data(), file, "choleskyVecs");
    writeFile( choleskyBg.size(), choleskyBg.data(), file, "choleskyBg");

    file.close();
}

#ifdef MPI_HAO
void MPIBcast(RealMaterialMolecule &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast(buffer.L);
    MPIBcast(buffer.Nup);
    MPIBcast(buffer.Ndn);
    MPIBcast(buffer.choleskyNumber);
    MPIBcast(buffer.t);
    MPIBcast(buffer.K);
    MPIBcast(buffer.choleskyVecs);
    MPIBcast(buffer.choleskyBg);
    MPIBcast(buffer.KpEigenStatus);
    MPIBcast(buffer.Kp);
    MPIBcast(buffer.KpEigenValue);
    MPIBcast(buffer.KpEigenVector);
}
#endif

void RealMaterialMolecule::writeBackGround(const string &filename) const
{
    H5File file(filename, H5F_ACC_RDWR);
    writeFile( choleskyBg.size(), choleskyBg.data(), file, "choleskyBg");
    file.close();
}

void RealMaterialMolecule::updateBackGround(const TensorHao<double, 1> &background)
{
    if( background.size() != choleskyNumber ) {cout<<"Error!!! Background size is not choleskyNumber!"<<endl; exit(1);}
    KpEigenStatus = 0;
    choleskyBg = background;
}

void RealMaterialMolecule::updateBackGround(TensorHao<double, 1> &&background)
{
    if( background.size() != choleskyNumber ) {cout<<"Error!!! Background size is not choleskyNumber!"<<endl; exit(1);}
    KpEigenStatus = 0;
    choleskyBg = move(background);
}

Hop2is RealMaterialMolecule::returnExpMinusAlphaK(double alpha)
{
    setKpEigenValueAndVector();

    TensorHao<double,2> matrix(L,L);
    BL_NAME(gmm)( KpEigenVector, dMultiMatrix( exp(-alpha*KpEigenValue), trans(KpEigenVector) ), matrix );

    Hop2is hop2is(L);
    double bg2(0.0); for(size_t i = 0; i < choleskyNumber; ++i) bg2 += choleskyBg(i) * choleskyBg(i);
    hop2is.logw = alpha*0.5*bg2;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j) hop2is.matrix(j,i) = matrix(j,i);
    }
    return hop2is;
}

LogHop2is RealMaterialMolecule::returnLogExpMinusAlphaK(double alpha)
{
    setKp();

    LogHop2is logHop2is(L);
    double bg2(0.0); for(size_t i = 0; i < choleskyNumber; ++i) bg2 += choleskyBg(i) * choleskyBg(i);
    logHop2is.logw = alpha*0.5*bg2;
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j) logHop2is.matrix(j,i) = -alpha*Kp(j,i);
    }
    return logHop2is;
}

CholeskyReal RealMaterialMolecule::returnExpMinusAlphaV(double alpha)
{
    return CholeskyReal(alpha, choleskyVecs, choleskyBg);
}

RealMaterialMolecule::RealMaterialMolecule(const RealMaterialMolecule &x)  { }

RealMaterialMolecule &RealMaterialMolecule::operator=(const RealMaterialMolecule &x) { return *this; }

void RealMaterialMolecule::setKp()
{
    if( KpEigenStatus >=1 ) return;

    size_t L2 = L*L;

    Kp = K;
    TensorHaoRef<double,2> vecs(L2, choleskyNumber); vecs.point( choleskyVecs.data() );
    TensorHaoRef<double,1> vecsBg(L2); vecsBg.point( Kp.data() );
    BL_NAME(gemv)(vecs, choleskyBg, vecsBg, 'N', 1.0, 1.0);
    checkSymmetry(Kp);

    KpEigenStatus=1;
}

void RealMaterialMolecule::setKpEigenValueAndVector()
{
    if( KpEigenStatus >=2 ) return;

    setKp();
    KpEigenVector = Kp;
    KpEigenValue.resize(L);
    BL_NAME(eigen)(KpEigenVector, KpEigenValue);

    KpEigenStatus = 2;
}

double RealMaterialMolecule::getMemory() const
{
    double mem(0.0);

    mem += 8.0*4;
    mem += t.getMemory() + K.getMemory();
    mem += choleskyVecs.getMemory();
    mem += choleskyBg.getMemory();

    mem += 8.0;
    mem += Kp.getMemory();
    mem += KpEigenValue.getMemory();
    mem += KpEigenVector.getMemory();

    return mem;
}