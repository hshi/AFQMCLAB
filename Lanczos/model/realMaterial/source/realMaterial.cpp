//
// Created by boruoshihao on 10/27/16.
//

#include "../include/realMaterial.h"

using namespace std;
using namespace tensor_hao;

RealMaterial::RealMaterial(size_t L, size_t Nup, size_t Ndn): L(L), Nup(Nup), Ndn(Ndn) { setFromLNupNdn(); }
RealMaterial::RealMaterial(const std::string &filename) { read(filename); }

size_t RealMaterial::getL() const    { return L;   }
size_t RealMaterial::getNup() const  { return Nup; }
size_t RealMaterial::getNdn() const  { return Ndn; }
const std::vector<LanOneBody> &RealMaterial::getUp() const   { return up; }
const std::vector<LanOneBody> &RealMaterial::getDn() const   { return dn; }
const std::vector<LanTwoBody> &RealMaterial::getUpUp() const { return upUp; }
const std::vector<LanTwoBody> &RealMaterial::getUpDn() const { return upDn; }
const std::vector<LanTwoBody> &RealMaterial::getDnDn() const { return dnDn; }
size_t RealMaterial::getWfSize()   const { return NHilbert;   }
size_t RealMaterial::getNHilbertUp() const { return NHilbertUp; }
size_t RealMaterial::getNHilbertDn() const { return NHilbertDn; }

void RealMaterial::setUp(const vector<LanOneBody> &up)     { RealMaterial::up = up; }
void RealMaterial::setDn(const vector<LanOneBody> &dn)     { RealMaterial::dn = dn; }
void RealMaterial::setUpUp(const vector<LanTwoBody> &upUp) { RealMaterial::upUp = upUp; }
void RealMaterial::setUpDn(const vector<LanTwoBody> &upDn) { RealMaterial::upDn = upDn; }
void RealMaterial::setDnDn(const vector<LanTwoBody> &dnDn) { RealMaterial::dnDn = dnDn; }

RealMaterial::RealMaterial(const RealMaterial &x) { }
RealMaterial &RealMaterial::operator=(const RealMaterial &x) { return *this; }