//
// Created by Hao Shi on 8/4/17.
//

#include "../include/afqmcConstraintPath.h"
#include "../include/afqmcBackPropagationPop.h"

using namespace std;
using namespace tensor_hao;

void AfqmcConstraintPath::prepareBackPropagation()
{
    isBP = true;
    BPIndex = 0;

    for (int i = 0; i < method.walkerSizePerThread; ++i)
    {
        walkerBackup[i] = walker[i];
    }
}

void AfqmcConstraintPath::prepareBackPropagationMeasAndNextBackup()
{
    swap(walkerBPMeasure, walkerBackup);
    if( method.backPropagationStep>=method.measureSkipStep)
        twoBodyAuxBPMeasure = twoBodyAuxBackup;
    else
    {
        swap(twoBodyAuxBPMeasure, twoBodyAuxBackup);
    }

    vector<int> table;
    for (size_t i = 0; i < method.backPropagationStep; ++i)
    {
        if( tablePerThreadBackup[i].size() != 0 )
        {
#ifdef MPI_HAO
            if( MPIRank()==0 ) table.resize( method.walkerSize );
            MPI_Gather( tablePerThreadBackup[i].data(), method.walkerSizePerThread, MPI_INT,
                        table.data(), method.walkerSizePerThread, MPI_INT, 0, MPI_COMM_WORLD );
#else
            table = tablePerThreadBackup[i];
#endif
            vector<AfqmcBackPropagationPop> BPPop;
            BPPop.reserve( method.walkerSizePerThread );
            for(int j=0; j<method.walkerSizePerThread; j++)
            {
                BPPop.push_back( AfqmcBackPropagationPop( i+1, twoBodyAuxBPMeasure[j], walkerBPMeasure[j]) );
            }
            populationControl(BPPop, table);
        }

        if( (i+1) == method.measureSkipStep )
        {
            generateWalkerBackupFromWalkerBPMeasure();
        }
    }

    if( method.backPropagationStep >= method.measureSkipStep )
    {
        BPIndex = method.backPropagationStep-method.measureSkipStep;

        for (size_t i = 0; i < method.backPropagationStep-method.measureSkipStep; ++i)
        {
            tablePerThreadBackup[i] = move( tablePerThreadBackup[i+method.measureSkipStep] );

            for (int j = 0; j < method.walkerSizePerThread; ++j)
            {
                twoBodyAuxBackup[j][i] = move( twoBodyAuxBackup[j][i+method.measureSkipStep] );
            }
        }
    }
    else
    {
        isBP = false;
    }
}

void AfqmcConstraintPath::generateWalkerBackupFromWalkerBPMeasure()
{
    WalkerRight walkerTemp;
    for(int i=0; i<method.walkerSizePerThread; i++)
    {
        walkerBackup[i] = walkerBPMeasure[i];
        for (size_t j = 0; j < method.measureSkipStep; ++j)
        {
            if( twoBodyAuxBPMeasure[i][j].size() == model.getL() )
            {
                twoBodySample = expMinusDtV.getTwoBodySampleFromAux( twoBodyAuxBPMeasure[i][j] );
                twoBodySampleWalkerRightOperation.applyToRight(twoBodySample, walkerBackup[i], walkerTemp);
                oneBodyWalkerRightOperation.applyToRight(expMinusDtK, walkerTemp, walkerBackup[i] );
            }

            if( j%method.mgsStep==0 ) walkerBackup[i].normalize();
        }
    }
}
