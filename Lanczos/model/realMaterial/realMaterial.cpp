//
// Created by boruoshihao on 10/27/16.
//

#include "realMaterial.h"

using namespace std;
using namespace tensor_hao;

RealMaterial::RealMaterial(): L(0), Nup(0), Ndn(0) { setFromLNupNdn(); }
RealMaterial::RealMaterial(size_t L, size_t Nup, size_t Ndn): L(L), Nup(Nup), Ndn(Ndn) { setFromLNupNdn(); }
RealMaterial::RealMaterial(const std::string &filename) { read(filename); }

size_t RealMaterial::getL() const    { return L;   }
size_t RealMaterial::getNup() const  { return Nup; }
size_t RealMaterial::getNdn() const  { return Ndn; }
const std::vector<OneBody> &RealMaterial::getUp() const   { return up; }
const std::vector<OneBody> &RealMaterial::getDn() const   { return dn; }
const std::vector<TwoBody> &RealMaterial::getUpup() const { return upUp; }
const std::vector<TwoBody> &RealMaterial::getUpdn() const { return upDn; }
const std::vector<TwoBody> &RealMaterial::getDnup() const { return dnUp; }
const std::vector<TwoBody> &RealMaterial::getDndn() const { return dnDn; }
size_t RealMaterial::getWfSize()   const { return NHilbert;   }
size_t RealMaterial::getNHilbertUp() const { return NHilbertUp; }
size_t RealMaterial::getNHilbertDn() const { return NHilbertDn; }

void RealMaterial::setUp(const vector<OneBody> &up)     { RealMaterial::up = up; }
void RealMaterial::setDn(const vector<OneBody> &dn)     { RealMaterial::dn = dn; }
void RealMaterial::setUpup(const vector<TwoBody> &upup) { RealMaterial::upUp = upup; }
void RealMaterial::setUpdn(const vector<TwoBody> &updn) { RealMaterial::upDn = updn; }
void RealMaterial::setDnup(const vector<TwoBody> &dnup) { RealMaterial::dnUp = dnup; }
void RealMaterial::setDndn(const vector<TwoBody> &dndn) { RealMaterial::dnDn = dndn; }

RealMaterial::RealMaterial(const RealMaterial &x) { }
RealMaterial &RealMaterial::operator=(const RealMaterial &x) { return *this; }