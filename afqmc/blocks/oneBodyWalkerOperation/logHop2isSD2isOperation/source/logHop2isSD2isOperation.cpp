//
// Created by boruoshihao on 5/19/17.
//

#include <climits>
#include "../include/logHop2isSD2isOperation.h"
#include "../../../../../common/common.h"

using namespace std;
using namespace tensor_hao;

LogHop2isSD2isOperation::LogHop2isSD2isOperation(std::string flag, size_t taylorOrder, double accuracy, size_t baseTaylorOrder)
{
    reset(flag, taylorOrder, accuracy, baseTaylorOrder);
}

LogHop2isSD2isOperation::~LogHop2isSD2isOperation() { }

void LogHop2isSD2isOperation::reset(string flag, size_t taylorOrder, double accuracy, size_t baseTaylorOrder)
{
    LogHop2isSD2isOperation::flag = flag;
    LogHop2isSD2isOperation::taylorOrder = taylorOrder;
    LogHop2isSD2isOperation::accuracy = accuracy;
    LogHop2isSD2isOperation::baseTaylorOrder = baseTaylorOrder;

    operationNumber  = 0;
    minTaylorOrder   = INT_MAX;
    maxTaylorOrder   = 0;
    totalTaylorOrder = 0;

    if( flag != "fixedOrder" && flag != "dynamicOrder" )
    {
        cout<<"Error!!! Do not know the input flag for LogHop2isSD2isOperation: "<<flag<<endl;
        exit(1);
    }
}

void LogHop2isSD2isOperation::applyToRight(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew)
{
    checkAndResize(oneBody, walker, walkerNew);

    char TRANSOneBody='N';
    addOrders(oneBody, walker, walkerNew, TRANSOneBody);
    walkerNew.logwRef() = oneBody.logw + walker.getLogw();
}

void LogHop2isSD2isOperation::applyToLeft(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew)
{
    checkAndResize(oneBody, walker, walkerNew);

    char TRANSOneBody='C';
    addOrders(oneBody, walker, walkerNew, TRANSOneBody);
    walkerNew.logwRef() = conj( oneBody.logw ) + walker.getLogw();
}

void LogHop2isSD2isOperation::print()
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

size_t LogHop2isSD2isOperation::getCurrentOrder() const { return currentOrder; }

void LogHop2isSD2isOperation::checkAndResize(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew) const
{
    size_t L = walker.getL(); size_t Nup = walker.getNup(); size_t Ndn = walker.getNdn();
    if( oneBody.getL() !=  L ) {cout<<"Error!!! LogHop2is size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getNup() != Nup || walkerNew.getNdn() != Ndn ) walkerNew.resize( L, Nup, Ndn );
}

void LogHop2isSD2isOperation::addOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody)
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
        cout<<"Error!!! Do not know the input flag for LogHop2isSD2isOperation: "<<flag<<endl;
        exit(1);
    }
    clearWfTemp();
}

void LogHop2isSD2isOperation::determinantAndAddFixedOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody)
{
    initialAndAddFixedOrders(oneBody, walker, walkerNew, baseTaylorOrder, TRANSOneBody);
    addDynamicOrders(oneBody, walker, walkerNew, TRANSOneBody);

#ifdef MPI_HAO
    MPIReduce(currentOrder, taylorOrder, MPI_MAX);
#else
    taylorOrder = currentOrder;
#endif
}

void LogHop2isSD2isOperation::initialAndAddFixedOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, size_t maxOrder, char TRANSOneBody)
{
    initialZeroOrder(oneBody, walker, walkerNew, TRANSOneBody);
    addFixedOrders(oneBody, walker, walkerNew, maxOrder, TRANSOneBody);
}

void LogHop2isSD2isOperation::initialAndAddDynamicOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody)
{
    initialAndAddFixedOrders(oneBody, walker, walkerNew, baseTaylorOrder, TRANSOneBody);
    addDynamicOrders(oneBody, walker, walkerNew, TRANSOneBody);
}

void LogHop2isSD2isOperation::initialZeroOrder(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody)
{
    size_t L = walker.getWf().rank(0);
    size_t N = walker.getWf().rank(1);
    if( wfTempNew.rank(0) != L || wfTempNew.rank(1) != N ) wfTempNew.resize( L, N );
    if( wfTempOld.rank(0) != L || wfTempOld.rank(1) != N ) wfTempOld.resize( L, N );

    walkerNew.wfRef() = walker.getWf();
    wfTempOld = walker.getWf();
    currentOrder = 0;
}

void LogHop2isSD2isOperation::addFixedOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, size_t maxOrder, char TRANSOneBody)
{
    while( currentOrder < maxOrder )
    {
        BL_NAME(gmm)( oneBody.matrix, wfTempOld, wfTempNew, TRANSOneBody, 'N', 1.0/(currentOrder+1.0) );
        walkerNew.wfRef() += wfTempNew;
        wfTempOld = move( wfTempNew );
        currentOrder++;
    }
}

void LogHop2isSD2isOperation::addDynamicOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody)
{
    do
    {
        BL_NAME(gmm)( oneBody.matrix, wfTempOld, wfTempNew, TRANSOneBody, 'N', 1.0/(currentOrder+1.0) );
        walkerNew.wfRef() += wfTempNew;
        wfTempOld = move( wfTempNew );
        currentOrder++;
    } while( ! isConverged() );
}

bool LogHop2isSD2isOperation::isConverged()
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

void LogHop2isSD2isOperation::clearWfTemp()
{
    wfTempOld.resize(0,0);
    wfTempNew.resize(0,0);
}

LogHop2isSD2isOperation::LogHop2isSD2isOperation(const LogHop2isSD2isOperation &x) { }

LogHop2isSD2isOperation &LogHop2isSD2isOperation::operator=(const LogHop2isSD2isOperation &x) { return *this; }