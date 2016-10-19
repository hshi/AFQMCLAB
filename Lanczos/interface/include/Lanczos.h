//
// Created by boruoshihao on 9/24/16.
//

#ifndef AFQMCLIB_LANCZOS_H
#define AFQMCLIB_LANCZOS_H

#include <cstddef>
#include <tuple>
#include "LanczosExcepts.h"
#include "modelInterface.h"

struct LanczosParam
{
    size_t matrixSize;
    double accuracy;
    char convergeFlag;
    size_t maxLoop;
    double litForProjection;  //When b is smaller, we need to project wave function.
};

class Lanczos
{
 private:
    const ModelInterface * model;
    size_t wfSize;
    std::vector<LanczosBasisWf> eigenstates;
    LanczosBasisWf wfOne, wfTwo, wfThree;

 public:
    Lanczos(const ModelInterface & modelInterface);

    void randomInitWf();
    void readInitWf(const std::string& filename);
    void readConvergedWfs(size_t numberOfWaveFunctions = 1);
    void writeWf(const std::string &filename) const ;
    void writeAllWfs(size_t startIndex = 0) const ;

    void findEigen(const size_t L=1, LanczosParam lanczosParam = {20, 1e-10, 'E', 100, 0.01} );
    void FindOneEigen(LanczosParam lanczosParam = {20, 1e-10, 'E', 100, 0.01} );
    std::tuple< std::vector<double>, std::vector<double> > getLanczosMatrix(size_t L, double accuracy = 1e-10,
                                                                            double litForProjection = 0.01);

 private:
    double getLanczosDiagonalElement();
    double getLanczosOffdiagonalElement(std::complex<double> a, std::complex<double> b=0);
    void recurseWaveFunctions();

    std::tuple< double, std::vector<double> > diagonalizeLanczosMatrix(std::vector<double> a, std::vector<double > b ) const;
    void getNewEigenstate(const std::vector<double> &a, const std::vector<double> &b, const std::vector<double> &vec);
    void projectWaveFunction(LanczosBasisWf &wfToProject);

    Lanczos(const Lanczos& x);
    Lanczos & operator  = (const Lanczos& x);
};

//Eigenstates.reserve? Eigenvalues.reserve?
//LanWf reserve?


//TODO: Set wfOne, wfTwo ... into vector<LanczosBasisWf> lanczosWfs
//TODO: Add eigenvalues
//TODO: Whether we need to vary lanM or not?
//TODO: Do we need to project symmetry in getNewEigenstate?

//TODO: WRITE EXAMPLES ABOUT HOW TO USE THE CODE:
//FindOneEigen() need init
//FIndEigen does not need init
//randomInitWf(); FindOneEigen();
//findEigen(5);
//readConvergedWfs(2); findEigen(6);
//readConvergedWfs(2); readInitWf("NAME"); FindOneEigen();
#endif //AFQMCLIB_LANCZOS_H