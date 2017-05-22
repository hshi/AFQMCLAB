//
// Created by boruoshihao on 5/19/17.
//

#ifndef AFQMCLAB_LOGHOP2ISSD2ISOPERATION_H
#define AFQMCLAB_LOGHOP2ISSD2ISOPERATION_H

#include "../../../oneBodyOperator/logHop2IS/include/logHop2IS.h"
#include "../../../walker/SD2IS/include/SD2IS.h"

// Three different type of operation.
// flag: fixedOrder, taylorOrder>0. Always use the input taylorOrder order.
// flag: fixedOrder, taylorOrder=0. Determine the taylor order from accuracy and baseTaylorOrder and always use it.
// flag: dynamicOrder. Determine the taylor order from accuracy and baseTaylorOrder in all the operations.

class LogHop2ISSD2ISOperation
{
 private:
    std::string flag; //"fixedOrder", "dynamicOrder"
    size_t taylorOrder;
    double accuracy;
    size_t baseTaylorOrder;

    size_t operationNumber;
    size_t minTaylorOrder, maxTaylorOrder, totalTaylorOrder;

    size_t currentOrder;
    tensor_hao::TensorHao<std::complex<double>,2> wfTempOld, wfTempNew;

 public:
    LogHop2ISSD2ISOperation(std::string flag, size_t taylorOrder=0, double accuracy=1e-8, size_t baseTaylorOrder=3);
    ~LogHop2ISSD2ISOperation();

    void applyToRight(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew);
    void applyToLeft(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew);
    void print();
    size_t getCurrentOrder() const;

 private:
    void addOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody);
    void determinantAndAddFixedOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody);
    void initialAndAddFixedOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, size_t maxOrder, char TRANSOneBody);
    void initialAndAddDynamicOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody);

    void initialZeroOrder(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody);
    void addFixedOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, size_t maxOrder, char TRANSOneBody);
    void addDynamicOrders(const LogHop2IS &oneBody, const SD2IS &walker, SD2IS &walkerNew, char TRANSOneBody);
    bool isConverged();
    void clearWfTemp();

    LogHop2ISSD2ISOperation(const LogHop2ISSD2ISOperation& x);
    LogHop2ISSD2ISOperation & operator  = (const LogHop2ISSD2ISOperation& x);
};

#endif //AFQMCLAB_LOGHOP2ISSD2ISOPERATION_H
