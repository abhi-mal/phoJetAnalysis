#MiniAOD analyzer for all physics objects 

Instructions:
```
cmsrel CMSSW_10_2_10
cd CMSSW_10_2_10/src
cmsenv
git cms-init

#https://twiki.cern.ch/twiki/bin/view/CMS/DeepJet#94X_installation_recipe_X_10
#for DeepCSV
git cms-addpkg RecoBTag/TensorFlow
git cherry-pick 94ceae257f846998c357fcad408986cc8a039152

#For 2017 data-taking
git clone -b 102X_2017 https://github.com/varuns23/phoJetAnalysis.git

scram b -j10
```

For Electrons and Photons:
[1]-https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2
[2]-https://twiki.cern.ch/twiki/bin/view/CMS/Egamma2017DataRecommendations
[3]-https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2

For MET:
[4]-https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETUncertaintyPrescription#Instructions_for_9_4_X_X_9_for_2

For Taus:
[5]-https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#Rerunning_of_the_tau_ID_on_M_AN1
[6]-https://twiki.cern.ch/twiki/pub/CMSPublic/SWGuidePFTauID/2017v2-recipe.pdf

For Muons:
[7]-https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2


Data set Info:
DATA:
DAS query: dataset=/*/Run2017*31Mar2018*/MINIAOD
Produced with CMSSW 9_4_5; Global tag: 94X_dataRun2_v6, cmsDriver eras Run2_2017,run2_miniAOD_94XFall17
JECs used: Fall17_17Nov2017BCDEF_V6_DATA
Recommended release: 9_4_6_patch1 or later, Global tag: 94X_dataRun2_v6

MC:
DAS query: dataset=/*/RunIIFall17*12Apr2018*/MINIAODSIM
Produced with CMSSW 9_4_6; Global tag: 94X_mc2017_realistic_v14, cmsDriver eras Run2_2017,run2_miniAOD_94XFall17
JECs used: Fall17_17Nov2017_V6_MC
Recommended release: 9_4_6_patch1 or later, Global tag: 94X_mc2017_realistic_v14
