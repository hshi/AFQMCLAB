//
// Created by boruoshihao on 5/19/17.
//

#ifndef AFQMCLAB_LOGHOP2ISSD2ISOPERATION_H
#define AFQMCLAB_LOGHOP2ISSD2ISOPERATION_H

#include "../../../oneBodyOperator/logHop2is/include/logHop2is.h"
#include "../../../walker/SD2is/include/SD2is.h"

// Three different type of operation.
// flag: fixedOrder, taylorOrder>0. Always use the input taylorOrder order.
// flag: fixedOrder, taylorOrder=0. Determine the taylor order from accuracy and baseTaylorOrder and always use it.
// flag: dynamicOrder. Determine the taylor order from accuracy and baseTaylorOrder in all the operations.

class LogHop2isSD2isOperation
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
    LogHop2isSD2isOperation(std::string flag="dynamicOrder", size_t taylorOrder=0, double accuracy=1e-10, size_t baseTaylorOrder=3);
    ~LogHop2isSD2isOperation();

    void reset(std::string flag="dynamicOrder", size_t taylorOrder=0, double accuracy=1e-10, size_t baseTaylorOrder=3);
    void applyToRight(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew);
    void applyToLeft(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew);
    void print();
    size_t getCurrentOrder() const;

 private:
    void checkAndResize(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew) const;

    void addOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody);
    void determinantAndAddFixedOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody);
    void initialAndAddFixedOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, size_t maxOrder, char TRANSOneBody);
    void initialAndAddDynamicOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody);

    void initialZeroOrder(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody);
    void addFixedOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, size_t maxOrder, char TRANSOneBody);
    void addDynamicOrders(const LogHop2is &oneBody, const SD2is &walker, SD2is &walkerNew, char TRANSOneBody);
    bool isConverged();
    void clearWfTemp();

    LogHop2isSD2isOperation(const LogHop2isSD2isOperation& x);
    LogHop2isSD2isOperation & operator  = (const LogHop2isSD2isOperation& x);
};

#endif //AFQMCLAB_LOGHOP2ISSD2ISOPERATION_H
