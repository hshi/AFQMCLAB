//
// Created by boruoshihao on 10/27/16.
//

#include "realMaterial.h"

using namespace std;
using namespace tensor_hao;

RealMaterial::RealMaterial(): L(0), Nup(0), Ndn(0) { setSizeofHilbertSpace(); }
RealMaterial::RealMaterial(size_t L, size_t Nup, size_t Ndn): L(L), Nup(Nup), Ndn(Ndn) { setSizeofHilbertSpace(); }

size_t RealMaterial::getL() const    { return L;   }
size_t RealMaterial::getNup() const  { return Nup; }
size_t RealMaterial::getNdn() const  { return Ndn; }
const std::vector<OneBody> &RealMaterial::getUp() const   { return up; }
const std::vector<OneBody> &RealMaterial::getDn() const   { return dn; }
const std::vector<TwoBody> &RealMaterial::getUpup() const { return upUp; }
const std::vector<TwoBody> &RealMaterial::getUpdn() const { return upDn; }
const std::vector<TwoBody> &RealMaterial::getDnup() const { return dnUp; }
const std::vector<TwoBody> &RealMaterial::getDndn() const { return dnDn; }

void RealMaterial::setL(size_t L)     { RealMaterial::L = L; }
void RealMaterial::setNup(size_t Nup) { RealMaterial::Nup = Nup; }
void RealMaterial::setNdn(size_t Ndn) { RealMaterial::Ndn = Ndn; }
void RealMaterial::setUp(const vector<OneBody> &up)     { RealMaterial::up = up; }
void RealMaterial::setDn(const vector<OneBody> &dn)     { RealMaterial::dn = dn; }
void RealMaterial::setUpup(const vector<TwoBody> &upup) { RealMaterial::upUp = upup; }
void RealMaterial::setUpdn(const vector<TwoBody> &updn) { RealMaterial::upDn = updn; }
void RealMaterial::setDnup(const vector<TwoBody> &dnup) { RealMaterial::dnUp = dnup; }
void RealMaterial::setDndn(const vector<TwoBody> &dndn) { RealMaterial::dnDn = dndn; }

RealMaterial::RealMaterial(const RealMaterial &x) { }
RealMaterial &RealMaterial::operator=(const RealMaterial &x) { return *this; }