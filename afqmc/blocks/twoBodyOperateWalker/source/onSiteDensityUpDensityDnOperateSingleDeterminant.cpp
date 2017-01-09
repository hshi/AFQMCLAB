//
// Created by boruoshihao on 1/9/17.
//

#include "../include/onSiteDensityUpDensityDnOperateSingleDeterminant.h"

using namespace std;
using namespace tensor_hao;

tuple<complex<double>,
    TensorHao<complex<double>, 1>,
    TensorHao<complex<double>, 1>,
    TensorHao<complex<double>, 1>,
    TensorHao<complex<double>, 1>>
OnSiteDensityUpDensityDnToOneBody(const OnSiteDensityUpDensityDnOperator &twoBody, const OnSiteDensityUpDensityDnOperatorAux &field)
{
    if(  field.size() != twoBody.getL() )
    {
        cout<<"Error!!! Size not consistent in OnSiteDensityUpDensityDnToOneBody!"<<endl;
        exit(1);
    }

    complex<double> logw;
    TensorHao<complex<double>,1> onebody00, onebody10, onebody01, onebody11;

    const size_t & L = twoBody.getL();
    const string & decompType = twoBody.getDecompType();

    return make_tuple( move(logw),  move(onebody00), move(onebody10), move(onebody01), move(onebody11) );
}

void  applyTwoBodyToRightWalker(const SingleDeterminant &walker, SingleDeterminant &walkerNew,
                                const OnSiteDensityUpDensityDnOperator &twoBody,
                                const OnSiteDensityUpDensityDnOperatorAux &field)
{

}