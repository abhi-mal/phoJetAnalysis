#ifndef TauWidthCalculator_hh
#define TauWidthCalculator_hh

// This is a simple helper class to compute energy weighted eta and phi
// widths of a jet.  Width in ECal and HCal are available

#include "DataFormats/PatCandidates/interface/Tau.h"
#include <vector>
using namespace std;

class TauWidthCalculator {

public:

  TauWidthCalculator(const pat::Tau&);
  
  virtual ~TauWidthCalculator();

  float getIsolationEtaWidth()       {return iso_etaWidth_;}
  float getIsolationPhiWidth()       {return iso_phiWidth_;}

  float getIsolationPFCandsPtSum()   {return iso_ptSum_;}
  float getIsolationPFCand12PtSum()  {return iso_pfCand12PtSum_;}
  float getIsolationPFCand12Ratio()  {return iso_pt12ratio_;}


  int getIsolationnPhotons()       {return iso_nPhotons_;}
  int getIsolationnCHPions()       {return iso_nCHPions_;}
  int getIsolationnMiscParticles() {return iso_nMiscParticles_;}
  int getIsolationnCands()       {return iso_nCands_;}


  vector<float> getIsolationConstPt()         {return iso_ConstPt_;}
  vector<float> getIsolationConstEt()         {return iso_ConstEt_;}
  vector<float> getIsolationConstEta()        {return iso_ConstEta_;}
  vector<float> getIsolationConstPhi()        {return iso_ConstPhi_;}
  vector<int>   getIsolationConstPdgId()      {return iso_ConstPdgId_;}
  vector<int>   getIsolationMiscPdgId()       {return iso_MiscPdgId_;}

  float getSignalEtaWidth()       {return sig_etaWidth_;}
  float getSignalPhiWidth()       {return sig_phiWidth_;}

  float getSignalPFCandsPtSum()   {return sig_ptSum_;}
  float getSignalPFCand12PtSum()  {return sig_pfCand12PtSum_;}
  float getSignalPFCand12Ratio()  {return sig_pt12ratio_;}


  int getSignalnPhotons()       {return sig_nPhotons_;}
  int getSignalnCHPions()       {return sig_nCHPions_;}
  int getSignalnMiscParticles() {return sig_nMiscParticles_;}
  int getSignalnCands()       {return sig_nCands_;}


  vector<float> getSignalConstPt()         {return sig_ConstPt_;}
  vector<float> getSignalConstEt()         {return sig_ConstEt_;}
  vector<float> getSignalConstEta()        {return sig_ConstEta_;}
  vector<float> getSignalConstPhi()        {return sig_ConstPhi_;}
  vector<int>   getSignalConstPdgId()      {return sig_ConstPdgId_;}
  vector<int>   getSignalMiscPdgId()       {return sig_MiscPdgId_;}

private:
                                        
  // No default constructor is possible
  TauWidthCalculator();

  // No copy constructor is needed
  TauWidthCalculator(const TauWidthCalculator&);

  // No equality operator is needed
  const TauWidthCalculator& operator=(const TauWidthCalculator&);

  void IsolationCalculation(const pat::Tau&);
  void SignalCalculation(const pat::Tau&);

  float iso_etaWidth_;
  float iso_phiWidth_;

  float iso_ptSum_;
  float iso_pfCand12PtSum_;
  float iso_pt12ratio_;

  int iso_nPhotons_;
  int iso_nCHPions_;
  int iso_nMiscParticles_;
  int iso_nCands_;

  vector<float> iso_ConstPt_;
  vector<float> iso_ConstEt_;
  vector<float> iso_ConstEta_;
  vector<float> iso_ConstPhi_;
  vector<int> iso_ConstPdgId_;
  vector<int> iso_MiscPdgId_;
  
  float sig_etaWidth_;
  float sig_phiWidth_;

  float sig_ptSum_;
  float sig_pfCand12PtSum_;
  float sig_pt12ratio_;

  int sig_nPhotons_;
  int sig_nCHPions_;
  int sig_nMiscParticles_;
  int sig_nCands_;

  vector<float> sig_ConstPt_;
  vector<float> sig_ConstEt_;
  vector<float> sig_ConstEta_;
  vector<float> sig_ConstPhi_;
  vector<int> sig_ConstPdgId_;
  vector<int> sig_MiscPdgId_;
};

#endif
