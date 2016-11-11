//
// Created by boruoshihao on 10/30/16.
//

#include "realMaterial.h"

using namespace std;
using namespace tensor_hao;

void RealMaterial::applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
{
    if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
}
