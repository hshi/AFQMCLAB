//
// Created by boruoshihao on 9/26/16.
//

#include <fstream>
#include "../include/LanczosBasisWf.h"

using namespace std;
using namespace tensor_hao;

LanczosBasisWf::LanczosBasisWf()
{
}

LanczosBasisWf::LanczosBasisWf(size_t L)
{
    wf = TensorHao<complex<double>, 1>(L);
}

LanczosBasisWf::LanczosBasisWf(const TensorHao<complex<double>, 1> &wf)
{
    LanczosBasisWf::wf = TensorHao<complex<double>, 1>( wf.getRank() );
    copy_cpu(wf, LanczosBasisWf::wf);
}

LanczosBasisWf::LanczosBasisWf(TensorHao<complex<double>, 1> &&wf) : wf( move(wf) )
{
}

LanczosBasisWf::LanczosBasisWf(const LanczosBasisWf &x)
{
    copyDeep(x);
}

LanczosBasisWf::LanczosBasisWf(LanczosBasisWf &&x)
{
    moveDeep(x);
}

LanczosBasisWf& LanczosBasisWf::operator=(const LanczosBasisWf& x)
{
    copyDeep(x);
    return *this;
}

LanczosBasisWf& LanczosBasisWf::operator=(LanczosBasisWf&& x)
{
    moveDeep(x);
    return *this;
}

const tensor_hao::TensorHao<std::complex<double>, 1> &LanczosBasisWf::getWf() const
{
    return wf;
}

void LanczosBasisWf::normalize()
{
    complex<double> inverseNorm = 1.0 / norm_cpu(wf);
    scal_cpu(inverseNorm, wf);
}

complex<double> LanczosBasisWf::calculateOverlapWith(const LanczosBasisWf &wfRight) const
{
    return dotc_cpu(wf, wfRight.wf);
}

void LanczosBasisWf::orthogonalizeWith(const LanczosBasisWf &wfBase)
{
    complex<double> minusOverlap = -wfBase.calculateOverlapWith(*this);
    axpy_cpu(minusOverlap, wfBase.wf, wf);
}

void LanczosBasisWf::read(const std::string& filename)
{
    if(MPIRank()==0)
    {
        ifstream wf_file;
        double read_r, read_i;
        wf_file.open(filename, ios::in);
        if(!wf_file.is_open())
        {
            cout << "Error opening file in read main thread!!!";
            exit(1);
        }
        size_t L = wf.size();
        for(size_t i = 0; i < L; i++)
        {
            wf_file >> read_r >> read_i;
            wf(i) = complex<double>(read_r, read_i);
        }
        wf_file.close();
    }
    MPIBcast(wf);
}

void LanczosBasisWf::write(const std::string& filename) const
{
    if(MPIRank()==0)
    {
        ofstream wf_file;
        wf_file.open(filename, ios::out|ios::trunc);
        if( !wf_file.is_open() )
        {
            cout << "Error opening file in write main thread!!!";
            exit(1);
        }
        wf_file<<setprecision(16)<<scientific;
        size_t L = wf.size();
        for(size_t i=0; i<L; i++) wf_file<<setw(26)<<wf(i).real()<<setw(26)<<wf(i).imag()<<"\n";
        wf_file.close();
    }
}

void LanczosBasisWf::copyDeep(const LanczosBasisWf &x)
{
    if( wf.size() != x.wf.size() )
    {
        wf = TensorHao<complex<double>, 1>(x.wf.size());
    }

    copy_cpu(x.wf, wf);
}

void LanczosBasisWf::moveDeep(LanczosBasisWf &x)
{
    wf = move(x.wf);
}