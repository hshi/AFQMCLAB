//
// Created by boruoshihao on 1/10/17.
//

#include "../include/NiupNidnSDOperation.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

NiupNidnSampleSDOperation::NiupNidnSampleSDOperation()  { }

NiupNidnSampleSDOperation::~NiupNidnSampleSDOperation() { }

void NiupNidnSampleSDOperation::applyToRight(const NiupNidnSample &oneBody, const SD &walker, SD &walkerNew) const
{
    size_t L = walker.getL(); size_t N = walker.getN(); size_t halfL = oneBody.getL();

    if( L != halfL*2 ) { cout<<"Error!!! NiupNidnSample size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getN() != N ) walkerNew.wfRef().resize( L, N );

    const TensorHao<complex<double>,2> &wf = walker.getWf();
    TensorHao<complex<double>,2> &wfNew = walkerNew.wfRef();

    const TensorHao<complex<double>,1> &diag00 = oneBody.diag00;
    const TensorHao<complex<double>,1> &diag10 = oneBody.diag10;
    const TensorHao<complex<double>,1> &diag01 = oneBody.diag01;
    const TensorHao<complex<double>,1> &diag11 = oneBody.diag11;

    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < halfL; ++i)
        {
            wfNew(i,j)        = diag00(i) * wf(i,j) + diag01(i)*wf(i+halfL, j);
            wfNew(i+halfL, j) = diag10(i) * wf(i,j) + diag11(i)*wf(i+halfL, j);
        }
    }

    walkerNew.logwRef() = oneBody.logw + walker.getLogw();

}

void NiupNidnSampleSDOperation::applyToLeft(const NiupNidnSample &oneBody, const SD &walker, SD &walkerNew) const
{
    size_t L = walker.getL(); size_t N = walker.getN(); size_t halfL = oneBody.getL();

    if( L != halfL*2 ) { cout<<"Error!!! NiupNidnSample size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getN() != N ) walkerNew.wfRef().resize( L, N );

    const TensorHao<complex<double>,2> &wf = walker.getWf();
    TensorHao<complex<double>,2> &wfNew = walkerNew.wfRef();

    const TensorHao<complex<double>,1> diag00 = conj( oneBody.diag00 );
    const TensorHao<complex<double>,1> diag10 = conj( oneBody.diag01 );
    const TensorHao<complex<double>,1> diag01 = conj( oneBody.diag10 );
    const TensorHao<complex<double>,1> diag11 = conj( oneBody.diag11 );

    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < halfL; ++i)
        {
            wfNew(i,j)        = diag00(i) * wf(i,j) + diag01(i)*wf(i+halfL, j);
            wfNew(i+halfL, j) = diag10(i) * wf(i,j) + diag11(i)*wf(i+halfL, j);
        }
    }

    walkerNew.logwRef() = conj( oneBody.logw ) + walker.getLogw();
}

//void getForce(NiupNidnForce& force, const NiupNidn &twoBody, SDSDOperation &sdsdOperation )
//{
//    size_t halfL = twoBody.getL();
//
//    if( force.size() != halfL ) force.resize(halfL);
//
//    const string &decompType = twoBody.getDecompType();
//
//    if( decompType == "densityCharge" )
//    {
//        const TensorHao< complex<double>, 1 > &greenDiagonal = sdsdOperation.returnGreenDiagonal();
//        for(size_t i = 0; i < halfL; ++i) force(i) = greenDiagonal(i) + greenDiagonal(i+halfL) -1.0;
//    }
//    else if( decompType == "densitySpin" )
//    {
//        const TensorHao< complex<double>, 1 > &greenDiagonal = sdsdOperation.returnGreenDiagonal();
//        for(size_t i = 0; i < halfL; ++i) force(i) = greenDiagonal(i) - greenDiagonal(i+halfL);
//    }
//    else if( decompType == "hopCharge" )
//    {
//        const TensorHao< complex<double>, 1 > &greenOffDiagonal = sdsdOperation.returnGreenOffDiagonal();
//        for(size_t i = 0; i < halfL; ++i) force(i) = greenOffDiagonal(i) + greenOffDiagonal(i+halfL);
//    }
//    else if( decompType == "hopSpin" )
//    {
//        const TensorHao< complex<double>, 1 > &greenOffDiagonal = sdsdOperation.returnGreenOffDiagonal();
//        for(size_t i = 0; i < halfL; ++i) force(i) = greenOffDiagonal(i) - greenOffDiagonal(i+halfL);
//    }
//    else
//    {
//        cout<<"Error! Can not find the matched decompType! "<<decompType<<endl;
//        exit(1);
//    }
//}
//
//
//void getForce(NiupNidnForce& force, const NiupNidn &twoBody, const SD &walkerLeft, const SD &walkerRight)
//{
//    size_t L = walkerLeft.getL(); size_t N = walkerLeft.getN(); size_t halfL = twoBody.getL();
//
//    if( walkerRight.getL() != L ) { cout<<"Error!!! Walker size is not consistent!"<<endl; exit(1); }
//    if( walkerRight.getN() != N ) { cout<<"Error!!! Walker size is not consistent!"<<endl; exit(1); }
//    if( L != halfL*2 ) { cout<<"Error!!! NiupNidn size is not consistent with walker!"<<endl; exit(1); }
//
//    if( force.size() != halfL ) force.resize(halfL);
//
//    const string &decompType = twoBody.getDecompType();
//    SDSDOperation sdsdOperation(walkerLeft, walkerRight);
//
//    if( decompType == "densityCharge" )
//    {
//        const TensorHao< complex<double>, 1 > &greenDiagonal = sdsdOperation.returnGreenDiagonal();
//        for(size_t i = 0; i < halfL; ++i) force(i) = greenDiagonal(i) + greenDiagonal(i+halfL) -1.0;
//    }
//    else if( decompType == "densitySpin" )
//    {
//        const TensorHao< complex<double>, 1 > &greenDiagonal = sdsdOperation.returnGreenDiagonal();
//        for(size_t i = 0; i < halfL; ++i) force(i) = greenDiagonal(i) - greenDiagonal(i+halfL);
//    }
//    else if( decompType == "hopCharge" )
//    {
//        const TensorHao< complex<double>, 1 > &greenOffDiagonal = sdsdOperation.returnGreenOffDiagonal();
//        for(size_t i = 0; i < halfL; ++i) force(i) = greenOffDiagonal(i) + greenOffDiagonal(i+halfL);
//    }
//    else if( decompType == "hopSpin" )
//    {
//        const TensorHao< complex<double>, 1 > &greenOffDiagonal = sdsdOperation.returnGreenOffDiagonal();
//        for(size_t i = 0; i < halfL; ++i) force(i) = greenOffDiagonal(i) - greenOffDiagonal(i+halfL);
//    }
//    else
//    {
//        cout<<"Error! Can not find the matched decompType! "<<decompType<<endl;
//        exit(1);
//    }
//}
//
//void applyOneBodyPartInTwoBodyToRightWalker(const SD &walker, SD &walkerNew, const NiupNidn &niupNidn)
//{
//    size_t L = walker.getL(); size_t N = walker.getN(); size_t halfL = niupNidn.getL();
//
//    if( L != halfL*2 ) { cout<<"Error!!! niupNidn size is not consistent with walker!"<<endl; exit(1); }
//    if( walkerNew.getL() != L  ||  walkerNew.getN() != N ) walkerNew.wfRef().resize( L, N );
//
//    TensorHao<complex<double>,1> expHalfDtU(halfL);
//    const TensorHao<double,1> &dtU = niupNidn.getDtU();
//    for(size_t i = 0; i < halfL; ++i) expHalfDtU(i) = exp( dtU(i) * 0.5 );
//
//    TensorHao<complex<double>,1> diag00 = niupNidn.getConstDiag00() * expHalfDtU;
//    TensorHao<complex<double>,1> diag11 = niupNidn.getConstDiag11() * expHalfDtU;
//
//    const TensorHao<complex<double>,1> &diag10 = niupNidn.getConstDiag10();
//    const TensorHao<complex<double>,1> &diag01 = niupNidn.getConstDiag01();
//
//    const TensorHao<complex<double>,2> &wf = walker.getWf();
//    TensorHao<complex<double>,2> &wfNew = walkerNew.wfRef();
//    for(size_t j = 0; j < N; ++j)
//    {
//        for(size_t i = 0; i < halfL; ++i)
//        {
//            wfNew(i,j)        = diag00(i) * wf(i,j) + diag01(i)*wf(i+halfL, j);
//            wfNew(i+halfL, j) = diag10(i) * wf(i,j) + diag11(i)*wf(i+halfL, j);
//        }
//    }
//
//    walkerNew.logwRef() = walker.getLogw();
//}
//
//complex<double> measureFirstOrder(const TensorHao< complex<double>, 2 > &green,  const NiupNidn &niupNidn)
//{
//    size_t L = niupNidn.getL();
//    const TensorHao<double,1> &dtU = niupNidn.getDtU();
//
//    complex<double> minusDtU(0.0,0.0);
//    for(size_t i = 0; i < L; ++i)
//    {
//        minusDtU += -dtU(i)*( green(i,i)*green(i+L,i+L) - green(i,i+L)*green(i+L,i) );
//    }
//    return minusDtU;
//}
//
//complex<double> measureSecondOrder(const TensorHao< complex<double>, 2 > &green,  const NiupNidn &niupNidn)
//{
//    size_t L = niupNidn.getL();
//    const TensorHao<double,1> &dtU = niupNidn.getDtU();
//
//    complex<double> minusDtU2(0.0,0.0);
//    complex<double> temp;
//    for(size_t i = 0; i < L; ++i)
//    {
//        for(size_t j = 0; j < L; ++j)
//        {
//            if( i== j )
//            {
//                temp = green(i,i)*green(i+L,i+L) - green(i,i+L)*green(i+L, i);
//            }
//            else
//            {
//                temp = 0.0;
//                //Total 24 contractions!
//                //<niup njup> <nidn njdn>
//                temp += ( green(i,i)*green(j,j)-green(i,j)*green(j,i) )*( green(i+L,i+L)*green(j+L,j+L)-green(i+L,j+L)*green(j+L,i+L) );
//                //<niup nidn> <njup njdn>
//                temp += ( green(i,i)*green(i+L,i+L)-green(i,i+L)*green(i+L,i) )*( green(j,j)*green(j+L,j+L)-green(j,j+L)*green(j+L,j) );
//                //<niup njdn> <njup nidn>
//                temp += ( green(i,i)*green(j+L,j+L)-green(i,j+L)*green(j+L,i) )*( green(i+L,i+L)*green(j,j)-green(i+L,j)*green(j,i+L) );
//                //<niup> <nidn> <njup> <njdn> (additional counts before)
//                temp -= 2.0*green(i,i)*green(i+L,i+L)*green(j,j)*green(j+L,j+L);
//                //<niup> <nidn njup njdn> (3 inter contractions)
//                temp += green(i,i) * ( green(i+L,j)*green(j,j+L)*green(j+L,i+L)+green(i+L,j+L)*green(j+L,j)*green(j,i+L) );
//                //<nidn> <niup njup njdn> (3 inter contractions)
//                temp += green(i+L,i+L) * ( green(i,j)*green(j,j+L)*green(j+L,i)+green(i,j+L)*green(j+L,j)*green(j,i) );
//                //<njup> <njdn niup nidn> (3 inter contractions)
//                temp += green(j,j) * ( green(j+L,i)*green(i,i+L)*green(i+L,j+L)+green(j+L,i+L)*green(i+L,i)*green(i,j+L) );
//                //<njdn> <njup niup nidn> (3 inter contractions)
//                temp += green(j+L,j+L) * ( green(j,i)*green(i,i+L)*green(i+L,j)+green(j,i+L)*green(i+L,i)*green(i,j) );
//                //<niup nidn njup njdn> (4 inter contractions)
//                temp += green(i,i+L)*( -green(i+L,j)*green(j,j+L)*green(j+L,i) - green(i+L,j+L)*green(j+L,j)*green(j,i) );
//                temp += green(i,j)*( -green(j,i+L)*green(i+L,j+L)*green(j+L,i) - green(j,j+L)*green(j+L,i+L)*green(i+L,i));
//                temp += green(i,j+L)*( -green(j+L,i+L)*green(i+L,j)*green(j,i) - green(j+L,j)*green(j,i+L)*green(i+L,i));
//            }
//            minusDtU2 += dtU(i)*dtU(j)* temp;
//        }
//    }
//    return minusDtU2;
//}
//
//tuple<complex<double>, complex<double>> measureLogTwoBodySecondOrder(const SD &walkerLeft, const SD &walkerRight, const NiupNidn &niupNidn)
//{
//    SD walkerRightNew;
//    applyOneBodyPartInTwoBodyToRightWalker(walkerRight, walkerRightNew, niupNidn);
//
//    SDSDOperation sdsdOperation(walkerLeft, walkerRightNew);
//    complex<double> logOverlap = sdsdOperation.returnLogOverlap();
//
//    const TensorHao< complex<double>, 2 > &greenMatrix = sdsdOperation.returnGreenMatrix();
//    complex<double> firstOrder  = measureFirstOrder(greenMatrix, niupNidn);
//    complex<double> secondOrder = measureSecondOrder(greenMatrix, niupNidn);
//
//    complex<double> background, expand;
////    background = -0.25*niupNidn.getDtUSum();
//
//    background = firstOrder+1.0-sqrt(firstOrder*firstOrder+1.0-secondOrder);
//    expand  = 1.0 + (firstOrder-background) + 0.5*(secondOrder-2.0*firstOrder*background+background*background);
//    complex<double> measureOne = background + log(expand);
//
//    background = firstOrder;
//    expand  = 1.0 + (firstOrder-background) + 0.5*(secondOrder-2.0*firstOrder*background+background*background);
//    complex<double> measureTwo = background + log(expand);
//
//    complex<double> logTwoBodyAvg = measureOne +logOverlap;
//
//    double criteria_real = max( measureOne.real(), measureTwo.real() );
//    double criteria_imag = max( measureOne.imag(), measureTwo.imag() );
//    complex<double>  criteria(criteria_real, criteria_imag);
//
//    return make_tuple(logTwoBodyAvg, criteria);
//}
//
//complex<double> measureLogTwoBodyForceBiasSample(const SD &walkerLeft, const SD &walkerRight,
//                                                 const NiupNidn &niupNidn, double sampleCap, size_t sampleSize)
//{
//    NiupNidnForce force;
//    NiupNidnAux aux;
//    NiupNidnSample sample;
//    SD walkerRightTemp;
//    SDSDOperation sdsdTempOperation(walkerLeft, walkerRightTemp);
//
//    //Note: Separate logW outside to avoid NAN problem!
//    SDSDOperation sdsdOperation(walkerLeft, walkerRight);
//    complex<double> logW = sdsdOperation.returnLogOverlap();
//
//    NiupNidnSampleSDOperation twoBodyWalkerOperation;
//    getForce(force, niupNidn, walkerLeft, walkerRight);
//    complex<double> num(0,0), den(0,0);
//    for(size_t i = 0; i < sampleSize; ++i)
//    {
//        aux = niupNidn.sampleAuxFromForce(force, sampleCap);
//        sample = niupNidn.getTwoBodySampleFromAux(aux);
//        twoBodyWalkerOperation.applyToRight(sample, walkerRight, walkerRightTemp);
//
//        num += exp( sdsdTempOperation.returnLogOverlap() -logW - niupNidn.logProbOfAuxFromForce(aux, force, sampleCap) );
//        den += 1.0;
//
//        sdsdTempOperation.reSet();
//    }
//
//    complex<double> logTwoBodyAvg = log( num/den * niupNidn.sumOfAuxFromForce(force, sampleCap) ) + logW;
//
//    return logTwoBodyAvg;
//}
