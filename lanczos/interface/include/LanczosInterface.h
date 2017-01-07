//
// Created by boruoshihao on 9/24/16.
//

#ifndef AFQMCLAB_LANCZOSINTERFACE_H
#define AFQMCLAB_LANCZOSINTERFACE_H

#include <cstddef>
#include <tuple>
#include "LanczosExcepts.h"
#include "LanczosParam.h"
#include "modelInterface.h"

class Lanczos
{
 private:
    const ModelInterface * model;
    size_t wfSize;
    std::string lanStatus;  //recurse, full, both, none, recurseConverged, fullConverged, bothConverged
    std::vector<double> lana, lanb;
    std::vector<LanczosBasisWf> lanwfs;
    std::vector<double> eigenvalues;
    std::vector<LanczosBasisWf> eigenstates;

 public:
    Lanczos();
    Lanczos(const ModelInterface & modelInterface);

    void set(const ModelInterface & modelInterface);
    size_t getEigenSize() const;
    double getEigenvalue(size_t eigenIndex) const;
    const LanczosBasisWf& getEigenstate(size_t eigenIndex) const;
    std::tuple<const std::vector<double> &, const std::vector<double> &> getLanElements() const;
    LanczosBasisWf & getLanWavefunction(size_t lanIndex);

    void readEigens(size_t numberOfWaveFunctions = 1);
    void writeEigens(size_t startIndex = 0) const ;
    void readLanMatrix(std::string prefixName="lanczosMatrix");
    void writeLanMatrix(std::string prefixName="lanczosMatrix") const;
    void writeLanWavefunction(const std::string &filename, size_t lanIndex=0 ) const;

    void reserve(size_t targetLanSize, size_t targetEigenSize);
    void clear();

    void randomWfInit();
    void readWfInit(const std::string &filename);
    void inputWfInit(LanczosBasisWf &wfNew);
    void readLanInit();

    void findEigen(const size_t L=1, LanczosParam lanczosParam = {20, 1e-10, 'E', 100, 0.01, 'F'} );
    void FindOneEigen(LanczosParam lanczosParam = {20, 1e-10, 'E', 100, 0.01, 'F'} );

    std::tuple<const std::vector<double> &, const std::vector<double> &>
    getLanczosMatrix(size_t L, double accuracy = 1e-10, double litForProjection = 0.01, char wfFlag = 'F');

 private:
    double initLanczosMatrixFromLanwfsZero();
    int getLanczosMatrixFull(size_t L, double accuracy = 1e-10, double litForProjection = 0.01);
    int getLanczosMatrixRecurse(size_t L, double accuracy = 1e-10, double litForProjection = 0.01);
    void getNewLanwfsZero(const std::vector<double> &vec, double litForProjection);
    void getNewLanwfsZeroFull(const std::vector<double> &vec);
    void getNewLanwfsZeroRecurse(const std::vector<double> &vec, double litForProjection);
    void getNewLanwfsZeroRecurseZeroToThree(const std::vector<double> &vec, double litForProjection);
    void getNewLanwfsZeroRecurseThreeToMatrixSize(const std::vector<double> &vec, double litForProjection);

    void readEigenValues(size_t numberOfWaveFunctions);
    void readEigenStates(size_t numberOfWaveFunctions);
    void writeEigenValues(size_t startIndex = 0) const;
    void writeEigenStates(size_t startIndex = 0) const;
    void readLanMatrixStatus(const std::string &prefixName);
    void readLanMatrixElements(const std::string &prefixName);
    void readLanMatrixWavefunctions(const std::string &prefixName);
    void writeLanMatrixStatus(const std::string &prefixName) const;
    void writeLanMatrixElements(const std::string &prefixName) const;
    void writeLanMatrixWavefunctions(const std::string &prefixName) const;

    void prepareLanReturn(std::string defaultStatus);
    void projectWaveFunctionUpdateLanb(size_t lanwfsIndex);
    double projectWaveFunction(size_t lanwfsIndex);
    void saveToEigen();
    void checkConvergedStatusAndChangetoNoneConvergedStatus();
    void changeLanStatusToRecurse();
    void recurseWaveFunctions();
    void getLanczosHtoWf(size_t i);
    double getLanczosOrthonormalWf(size_t i, double a, double b);
    void getLanczosDiagonalElement(size_t i);
    void getLanczosOffdiagonalElement(size_t i);

    Lanczos(const Lanczos& x);
    Lanczos & operator  = (const Lanczos& x);
};

#endif //AFQMCLAB_LANCZOS_H