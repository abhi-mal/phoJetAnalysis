#include "phoJetAnalysis/TauWidthCalculator/interface/TauWidthCalculator.hh"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include <math.h>

TauWidthCalculator::TauWidthCalculator(const pat::Tau& tau) {
  IsolationCalculation(tau);
  SignalCalculation(tau);
}

TauWidthCalculator::~TauWidthCalculator(){
}

void TauWidthCalculator::IsolationCalculation(const pat::Tau& tau) {
  // printf("Tau Isolation Calculation\n");
  float pfCand1pt_      = 0.;
  float pfCand2pt_      = 0.;  
 
  float etSum_          = 0.;
  float etaSum_         = 0.;
  float etaSqSum_       = 0.;
  float phiSum_         = 0.;
  float phiSqSum_       = 0.;
  
  iso_etaWidth_              = 0.;
  iso_phiWidth_              = 0.;

  iso_ptSum_                 = 0.;
  iso_pfCand12PtSum_         = 0.;
  iso_pt12ratio_             = 0.;

  iso_nPhotons_              = 0;
  iso_nCHPions_              = 0;
  iso_nMiscParticles_        = 0;

  iso_ConstPt_         .clear();
  iso_ConstEt_         .clear();
  iso_ConstEta_        .clear();
  iso_ConstPhi_        .clear();
  iso_ConstPdgId_      .clear();
  iso_MiscPdgId_       .clear();

  std::vector<std::pair<float, const reco::Candidate*>> tauDaughters;
  const uint32_t packedCands = tau.isolationCands().size();
  if (packedCands == 0) return;
  // printf("nCands: %i\n",packedCands);
  for(uint32_t i = 0; i < packedCands; i++) {
    // printf("iCand:  %i\n",i);
    const reco::Candidate* pfCand = tau.isolationCands()[i].get();
    
    tauDaughters.push_back({pfCand->pt(), pfCand});

    //if(abs(pfCand->pdgId()) == 211){
    //  nCHPions_++;
    //} else if(pfCand->pdgId() == 22){
    //  nPhotons_++;
    //}
    //else{
    //  nMiscParticles_++;
    //  MiscPdgId_ .push_back(pfCand->pdgId());
    //}
    
    etSum_ += pfCand->et();
    iso_ptSum_ += pfCand->pt();
    
    etaSum_   += (pfCand->eta() * pfCand->et());
    etaSqSum_ += (pfCand->eta() * pfCand->eta() * pfCand->et());
    
    phiSum_   += (pfCand->phi() * pfCand->et());
    phiSqSum_ += (pfCand->phi() * pfCand->phi() * pfCand->et());
  }

  std::sort(tauDaughters.begin(),tauDaughters.end(),[](const auto& p1, const auto& p2){return p1.first>p2.first;});
  for(uint32_t j = 0; j < tauDaughters.size(); j++){
    const reco::Candidate* pfCand = tauDaughters[j].second;

    iso_ConstPt_    .push_back(pfCand->pt());
    iso_ConstEt_    .push_back(pfCand->et());
    iso_ConstEta_   .push_back(pfCand->eta());
    iso_ConstPhi_   .push_back(pfCand->phi());
    iso_ConstPdgId_ .push_back(pfCand->pdgId());
  }

 
  if (packedCands>1){
    pfCand1pt_  = tau.isolationCands()[0]->pt();
    pfCand2pt_  = tau.isolationCands()[1]->pt();
  }
  else{
    pfCand1pt_ = tau.isolationCands()[0]->pt(); 
  }

  iso_pfCand12PtSum_ = pfCand1pt_ + pfCand2pt_;
  iso_pt12ratio_     = (iso_pfCand12PtSum_/iso_ptSum_);
  
  if(etSum_ < 0.000001) etSum_ = 0.000001; // To avoid NaNs
  float etaAve_   = etaSum_/etSum_;
  float etaSqAve_ = etaSqSum_/etSum_;
  iso_etaWidth_        = sqrt(etaSqAve_ - (etaAve_ * etaAve_));
  
  float phiAve_   = phiSum_ / etSum_;
  float phiSqAve_ = phiSqSum_ / etSum_;
  iso_phiWidth_        = sqrt(phiSqAve_ - (phiAve_ * phiAve_));
}

void TauWidthCalculator::SignalCalculation(const pat::Tau& tau) {
  // printf("Tau Signal Calculation\n");

  float pfCand1pt_      = 0.;
  float pfCand2pt_      = 0.;  
 
  float etSum_          = 0.;
  float etaSum_         = 0.;
  float etaSqSum_       = 0.;
  float phiSum_         = 0.;
  float phiSqSum_       = 0.;
  
  sig_etaWidth_              = 0.;
  sig_phiWidth_              = 0.;

  sig_ptSum_                 = 0.;
  sig_pfCand12PtSum_         = 0.;
  sig_pt12ratio_             = 0.;

  sig_nPhotons_              = 0;
  sig_nCHPions_              = 0;
  sig_nMiscParticles_        = 0;

  sig_ConstPt_         .clear();
  sig_ConstEt_         .clear();
  sig_ConstEta_        .clear();
  sig_ConstPhi_        .clear();
  sig_ConstPdgId_      .clear();
  sig_MiscPdgId_       .clear();

  std::vector<std::pair<float, const reco::Candidate*>> tauDaughters;
  const uint32_t packedCands = tau.signalCands().size();
  if (packedCands == 0) return;
  // printf("nCands: %i\n",packedCands);
  for(uint32_t i = 0; i < packedCands; i++) {
    // printf("iCand:  %i\n",i);
    const reco::Candidate* pfCand = tau.signalCands()[i].get();
    
    tauDaughters.push_back({pfCand->pt(), pfCand});

    //if(abs(pfCand->pdgId()) == 211){
    //  nCHPions_++;
    //} else if(pfCand->pdgId() == 22){
    //  nPhotons_++;
    //}
    //else{
    //  nMiscParticles_++;
    //  MiscPdgId_ .push_back(pfCand->pdgId());
    //}
    
    etSum_ += pfCand->et();
    sig_ptSum_ += pfCand->pt();
    
    etaSum_   += (pfCand->eta() * pfCand->et());
    etaSqSum_ += (pfCand->eta() * pfCand->eta() * pfCand->et());
    
    phiSum_   += (pfCand->phi() * pfCand->et());
    phiSqSum_ += (pfCand->phi() * pfCand->phi() * pfCand->et());
  }

  std::sort(tauDaughters.begin(),tauDaughters.end(),[](const auto& p1, const auto& p2){return p1.first>p2.first;});
  for(uint32_t j = 0; j < tauDaughters.size(); j++){
    const reco::Candidate* pfCand = tauDaughters[j].second;

    sig_ConstPt_    .push_back(pfCand->pt());
    sig_ConstEt_    .push_back(pfCand->et());
    sig_ConstEta_   .push_back(pfCand->eta());
    sig_ConstPhi_   .push_back(pfCand->phi());
    sig_ConstPdgId_ .push_back(pfCand->pdgId());
  }

 
  if (packedCands>1){
    pfCand1pt_  = tau.signalCands()[0]->pt();
    pfCand2pt_  = tau.signalCands()[1]->pt();
  }
  else{
    pfCand1pt_ = tau.signalCands()[0]->pt(); 
  }

  sig_pfCand12PtSum_ = pfCand1pt_ + pfCand2pt_;
  sig_pt12ratio_     = (sig_pfCand12PtSum_/sig_ptSum_);
  
  if(etSum_ < 0.000001) etSum_ = 0.000001; // To avoid NaNs
  float etaAve_   = etaSum_/etSum_;
  float etaSqAve_ = etaSqSum_/etSum_;
  sig_etaWidth_        = sqrt(etaSqAve_ - (etaAve_ * etaAve_));
  
  float phiAve_   = phiSum_ / etSum_;
  float phiSqAve_ = phiSqSum_ / etSum_;
  sig_phiWidth_        = sqrt(phiSqAve_ - (phiAve_ * phiAve_));
}
