//
// Created by boruoshihao on 5/19/17.
//

#include <climits>
#include "../include/logHop2ISSD2ISOperation.h"
#include "../../../../../common/common.h"

using namespace std;
using namespace tensor_hao;

LogHop2ISSD2ISOperation::LogHop2ISSD2ISOperation(std::string flag, size_t taylorOrder, double accuracy, size_t baseTaylorOrder)
{
    LogHop2ISSD2ISOperation::flag = flag;
    LogHop2ISSD2ISOperation::taylorOrder = taylorOrder;
    LogHop2ISSD2ISOperation::accuracy = accuracy;
    LogHop2ISSD2ISOperation::baseTaylorOrder = baseTaylorOrder;

    operationNumber  = 0;
    minTaylorOrder   = INT_MAX;
    maxTaylorOrder   = 0;
    totalTaylorOrder = 0;

    if( flag != "fixedOrder" && flag != "dynamicOrder" )
    {
        cout<<"Error!!! Do not know the input flag for LogHop2ISSD2ISOperation: "<<flag<<endl;
        exit(1);
    }
}

LogHop2ISSD2ISOperation::~LogHop2ISSD2ISOperation() { }

void LogHop2ISSD2ISOperation::applyToRight(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew)
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! LogHop2IS size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize( L, Nup, Ndn );

    char TRANSOneBody='N';
    addOrders(oneBody, walker, walkerNew, TRANSOneBody);
    walkerNew.logwRef() = oneBody.logw + walker.getLogw();
}

void LogHop2ISSD2ISOperation::applyToLeft(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew)
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! LogHop2IS size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize( L, Nup, Ndn );

    char TRANSOneBody='C';
    addOrders(oneBody, walker, walkerNew, TRANSOneBody);
    walkerNew.logwRef() = conj( oneBody.logw ) + walker.getLogw();
}

void LogHop2ISSD2ISOperation::print()
{
    if( flag == "fixedOrder" )
    {
        if( MPIRank() == 0 )
        {
            if( taylorOrder == 0 ) cout<<"Use fixed order, the order is not determined yet."<<endl;
            else cout<<"Use fixedOrder, the order is "<<taylorOrder<<endl;
        }
    }
    else if( flag == "dynamicOrder" )
    {
        size_t globalNumber, globalMin, globalMax, globalTotal;
        globalNumber = MPISum( operationNumber );
#ifdef MPI_HAO
        MPIReduce(minTaylorOrder, globalMin, MPI_MIN);
        MPIReduce(maxTaylorOrder, globalMax, MPI_MAX);
#else
        globalMin = minTaylorOrder;
        globalMax = maxTaylorOrder;
#endif
        globalTotal  = MPISum( totalTaylorOrder );

        if( MPIRank() == 0 )
        {
            cout<<"Use dynamicOrder. "<<endl;
            cout<<"The base order is "<<baseTaylorOrder<<endl;
            cout<<"The min order is "<<globalMin<<endl;
            cout<<"The max order is "<<globalMax<<endl;
            cout<<"The average order is "<< globalTotal*1.0/globalNumber <<endl;
        }
    }
}

size_t LogHop2ISSD2ISOperation::getCurrentOrder() const { return currentOrder; }

void LogHop2ISSD2ISOperation::addOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody)
{
    if( flag == "fixedOrder" )
    {
        if( taylorOrder==0 ) determinantAndAddFixedOrders(oneBody, walker, walkerNew, TRANSOneBody);
        else initialAndAddFixedOrders(oneBody, walker, walkerNew, taylorOrder, TRANSOneBody);
        operationNumber++;
    }
    else if( flag == "dynamicOrder" )
    {
        initialAndAddDynamicOrders(oneBody, walker, walkerNew, TRANSOneBody);
        minTaylorOrder = min( minTaylorOrder, currentOrder );
        maxTaylorOrder = max( maxTaylorOrder, currentOrder );
        totalTaylorOrder += currentOrder;
        operationNumber++;
    }
    else
    {
        cout<<"Error!!! Do not know the input flag for LogHop2ISSD2ISOperation: "<<flag<<endl;
        exit(1);
    }
    clearWfTemp();
}

void LogHop2ISSD2ISOperation::determinantAndAddFixedOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody)
{
    initialAndAddFixedOrders(oneBody, walker, walkerNew, baseTaylorOrder, TRANSOneBody);
    addDynamicOrders(oneBody, walker, walkerNew, TRANSOneBody);

#ifdef MPI_HAO
    MPIReduce(currentOrder, taylorOrder, MPI_MAX);
#else
    taylorOrder = currentOrder;
#endif
}

void LogHop2ISSD2ISOperation::initialAndAddFixedOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, size_t maxOrder, char TRANSOneBody)
{
    initialZeroOrder(oneBody, walker, walkerNew, TRANSOneBody);
    addFixedOrders(oneBody, walker, walkerNew, maxOrder, TRANSOneBody);
}

void LogHop2ISSD2ISOperation::initialAndAddDynamicOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody)
{
    initialAndAddFixedOrders(oneBody, walker, walkerNew, baseTaylorOrder, TRANSOneBody);
    addDynamicOrders(oneBody, walker, walkerNew, TRANSOneBody);
}

void LogHop2ISSD2ISOperation::initialZeroOrder(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody)
{
    size_t L = walker.getWf().rank(0);
    size_t N = walker.getWf().rank(1);
    if( wfTempNew.rank(0) != L || wfTempNew.rank(1) != N ) wfTempNew.resize( L, N );
    if( wfTempOld.rank(0) != L || wfTempOld.rank(1) != N ) wfTempOld.resize( L, N );

    walkerNew.wfRef() = walker.getWf();
    wfTempOld = walker.getWf();
    currentOrder = 0;
}

void LogHop2ISSD2ISOperation::addFixedOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, size_t maxOrder, char TRANSOneBody)
{
    while( currentOrder < maxOrder )
    {
        BL_NAME(gmm)( oneBody.matrix, wfTempOld, wfTempNew, TRANSOneBody, 'N', 1.0/(currentOrder+1.0) );
        walkerNew.wfRef() += wfTempNew;
        wfTempOld = move( wfTempNew );
        currentOrder++;
    }
}

void LogHop2ISSD2ISOperation::addDynamicOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody)
{
    do
    {
        BL_NAME(gmm)( oneBody.matrix, wfTempOld, wfTempNew, TRANSOneBody, 'N', 1.0/(currentOrder+1.0) );
        walkerNew.wfRef() += wfTempNew;
        wfTempOld = move( wfTempNew );
        currentOrder++;
    } while( ! isConverged() );
}

bool LogHop2ISSD2ISOperation::isConverged()
{
    size_t L = wfTempOld.rank(0);
    size_t N = wfTempOld.rank(1);

    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < L; ++j)
        {
            if( abs( wfTempOld(j,i) ) > accuracy  ) return false;
        }
    }

    return true;
}

void LogHop2ISSD2ISOperation::clearWfTemp()
{
    wfTempOld.resize(1,1);
    wfTempNew.resize(1,1);
}

LogHop2ISSD2ISOperation::LogHop2ISSD2ISOperation(const LogHop2ISSD2ISOperation &x) { }

LogHop2ISSD2ISOperation &LogHop2ISSD2ISOperation::operator=(const LogHop2ISSD2ISOperation &x) { return *this; }