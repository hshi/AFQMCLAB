//
// Created by boruoshihao on 9/22/16.
//
#include <fstream>
#include "../../../common/tensorHao/include/tensor_all.h"
#include "realMaterialHamiltonian.h"

using namespace std;
using namespace tensor_hao;

RealMaterialHamiltonian::RealMaterialHamiltonian() {}

RealMaterialHamiltonian::RealMaterialHamiltonian(const std::string &filename)
{
    ifstream file;
    if( MPIRank() ==0 )
    {
        file.open(filename, ios::in);
        if ( ! file.is_open() ) {cout << "Error opening file!!!"; exit(1);}
    }

    readBasisSizeAndInteractionSize(file);

    allocateKTensorandPTensorDEigen();

    readKTensorPTensorDEigen(file);

    if( MPIRank() == 0 ) file.close();
}

RealMaterialHamiltonian::RealMaterialHamiltonian(const RealMaterialHamiltonian &x)
{
    copyDeep(x);
}

RealMaterialHamiltonian::RealMaterialHamiltonian(RealMaterialHamiltonian &&x)
{
    moveDeep(x);
}

RealMaterialHamiltonian& RealMaterialHamiltonian::operator=(const RealMaterialHamiltonian& x)
{
    copyDeep(x);
    return *this;
}

RealMaterialHamiltonian& RealMaterialHamiltonian::operator=(RealMaterialHamiltonian&& x)
{
    moveDeep(x);
    return *this;
}

size_t RealMaterialHamiltonian::getBasisSize() const
{
    return basisSize;
}

size_t RealMaterialHamiltonian::getInteractionSize() const
{
    return interactionSize;
}

const tensor_hao::TensorHao<std::complex<double>, 3> &RealMaterialHamiltonian::getKTensor() const
{
    return KTensor;
}

const tensor_hao::TensorHao<std::complex<double>, 4> &RealMaterialHamiltonian::getPTensor() const
{
    return PTensor;
}

const TensorHao<complex<double>, 1> &RealMaterialHamiltonian::getDEigen() const
{
    return DEigen;
}

void RealMaterialHamiltonian::readBasisSizeAndInteractionSize(ifstream &file)
{
    if( MPIRank() == 0)
    {
        file >> basisSize;
        file >> interactionSize;
        if( interactionSize > basisSize*basisSize*4 ) { cout << "Interaction size too big!!!"; exit(1); }
    }

    MPIBcast(basisSize);
    MPIBcast(interactionSize);
}

void RealMaterialHamiltonian::allocateKTensorandPTensorDEigen()
{
    KTensor = TensorHao<complex<double>, 3> (basisSize, basisSize, 2);
    PTensor = TensorHao<complex<double>, 4> (basisSize, basisSize, 2, interactionSize);
    DEigen  = TensorHao<complex<double>, 1> (interactionSize);
}

void RealMaterialHamiltonian::readKTensorPTensorDEigen(ifstream &file)
{
    if( MPIRank() == 0 )
    {
        double real, imag;

        for(size_t i = 0; i < KTensor.size(); ++i)
        {
            file >> real >> imag;
            KTensor.data()[i] = complex<double>(real, imag);
        }

        for(size_t i = 0; i < PTensor.size(); ++i)
        {
            file >> real >> imag;
            PTensor.data()[i] = complex<double>(real, imag);
        }

        for(size_t i = 0; i < DEigen.size(); ++i)
        {
            file >> real >> imag;
            DEigen.data()[i] = complex<double>(real, imag);
        }
    }

    MPIBcast(KTensor);
    MPIBcast(PTensor);
    MPIBcast(DEigen);
    MPIBarrier();
}

void RealMaterialHamiltonian::copyDeep(const RealMaterialHamiltonian &x)
{
    basisSize = x.basisSize;
    interactionSize = x.interactionSize;
    KTensor = x.KTensor;
    PTensor = x.PTensor;
    DEigen  = x.DEigen;
}

void RealMaterialHamiltonian::moveDeep(RealMaterialHamiltonian &x)
{
    basisSize = x.basisSize;
    interactionSize = x.interactionSize;
    KTensor = move(x.KTensor );
    PTensor = move(x.PTensor );
    DEigen  = move(x.DEigen );
}