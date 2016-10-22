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
    size_t matrixSize;        //Lanczos matrix size
    double accuracy;          //when new b smaller than accuracy, converge
    char convergeFlag;        //'E' or 'W', converge by wave function or energy
    size_t maxLoop;           //The max Lanczos matrix loop
    double litForProjection;  //When b is smaller, we need to project wave function.
    char lanwfsFlag;          //'R' or 'F', 'R' use recurse wf, 'F' store full Lanczos wf
};

class Lanczos
{
 private:
    const ModelInterface * model;
    size_t wfSize;
    char lanStatus;  //'R' for recurse, 'F' for full storage, 'B' for both,  'N' for none
    std::vector<double> lana, lanb;
    std::vector<LanczosBasisWf> lanwfs;
    std::vector<double> eigenvalues;
    std::vector<LanczosBasisWf> eigenstates;

 public:
    Lanczos(const ModelInterface & modelInterface);

    size_t getEigenSize() const;
    double getEigenvalue(size_t eigenIndex) const;
    const LanczosBasisWf& getEigenstate(size_t eigenIndex) const;
    std::tuple<const std::vector<double> &, const std::vector<double> &> getLanElements() const;
    const LanczosBasisWf& getLanWavefunction(size_t lanIndex) const;

    void readEigens(size_t numberOfWaveFunctions = 1);
    void writeEigens(size_t startIndex = 0) const ;
    void readLanMatrix();
    void writeLanMatrix() const;

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
    void readLanMatrixStatus();
    void readLanMatrixElements();
    void readLanMatrixWavefunctions();
    void writeLanMatrixStatus() const;
    void writeLanMatrixElements() const;
    void writeLanMatrixWavefunctions() const;

    void prepareLanReturn(char defaultStatus);
    void projectWaveFunctionUpdateLanb(size_t lanwfsIndex);
    double projectWaveFunction(size_t lanwfsIndex);
    void saveToEigen();
    void changeLanStatusToRecurse();
    void recurseWaveFunctions();
    void getLanczosHtoWf(size_t i);
    double getLanczosOrthonormalWf(size_t i, double a, double b);
    void getLanczosDiagonalElement(size_t i);
    void getLanczosOffdiagonalElement(size_t i);
    Lanczos(const Lanczos& x);
    Lanczos & operator  = (const Lanczos& x);
};

//TODO: Write Lanwf[0] to the file, for re-run the simulations
//TODO: Update Test library to a real code ==> Diagonalize a Hermition matrix. ==> Store H_{i,j}
//TODO: Check wether in R or F in getLanMatrix
//TODO: CHANGE INIT to reserve, randomwfinit, readwfinit
//TODO: Use diagonalize Lanczos Matrix to get second initial state.
//TODO: PRINT inside getLanczosMatrixRecurse to see logical correct or not?
//TODO: In recurse, stable with wf before.
//TODO: Lanczos prepare==> Reserve eigenstate and LanWf to better efficiency
//TODO: Set wfOne, wfTwo ... into vector<LanczosBasisWf> lanczosWfs
//TODO: Add eigenvalues
//TODO: Whether we need to vary lanM or not?
//TODO: Do we need to project symmetry in getNewLanwfsZero?
//TODO: CHECK LANM size=2 case
//TODO: Show how to use lan.init(1000, 2000);

//TODO: WRITE EXAMPLES ABOUT HOW TO USE THE CODE:
//FindOneEigen() need init
//FIndEigen does not need init
//randomWfInit(); FindOneEigen();
//findEigen(5);
//readConvergedWfs(2); findEigen(6);
//readConvergedWfs(2); readWfInit("NAME"); FindOneEigen();
#endif //AFQMCLIB_LANCZOS_H