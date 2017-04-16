#ifndef AFQMC_DOUBLEPOPTYPE_H
#define AFQMC_DOUBLEPOPTYPE_H

#include <iostream>
#include <vector>

class DoublePop
{
    int Nbuf;
    double* number;

   public:
    DoublePop();
    DoublePop(double& number_in);
    ~DoublePop();

    int getNbuf() const;

    DoublePop& operator  = (const DoublePop& x);
#ifdef MPI_HAO
    std::vector<char> pack() const;
    void unpack(const std::vector<char>& buf);
#endif

 private:
    void setNbuf();
};

#endif