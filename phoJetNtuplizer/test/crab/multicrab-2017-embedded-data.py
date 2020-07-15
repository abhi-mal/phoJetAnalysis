import os

dataset = {
  'EmbeddedMuTau2017B': '/EmbeddingRun2017B/MuTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER',
  'EmbeddedMuTau2017C': '/EmbeddingRun2017C/MuTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER',
  'EmbeddedMuTau2017D': '/EmbeddingRun2017D/MuTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER',
  'EmbeddedMuTau2017E': '/EmbeddingRun2017E/MuTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER',
  'EmbeddedMuTau2017F': '/EmbeddingRun2017F/MuTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER',
}

if __name__ == '__main__':
  from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
from multiprocessing import Process

config = config()
name = 'Run2017_31Mar2018_Jul2020'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.inputFiles = ['Fall17_17Nov2017_V32_102X_DATA.db']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data') 
config.Data.publication = False
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'

config.Site.storageSite = 'T2_US_Wisconsin'
#config.Site.whitelist = ["T2_US_Wisconsin"]
#config.Site.blacklist = ['T2_CH_CERN']

listOfSamples = ['EmbeddedMuTau2017B','EmbeddedMuTau2017C','EmbeddedMuTau2017D','EmbeddedMuTau2017E','EmbeddedMuTau2017F']

for sample in listOfSamples:  
  os.popen('cp run_102X_data2017-embedded.py run_102X_data2017_'+sample+'.py')
  with open('run_102X_data2017_'+sample+'.py') as oldFile:
    newText = oldFile.read().replace('Ntuple_data2017.root','Data_'+sample+'.root')
  with open('run_102X_data2017_'+sample+'.py', 'w') as newFile:
    newFile.write(newText)

  config.General.requestName = 'job_'+sample
  
  config.JobType.psetName = 'run_102X_data2017_'+sample+'.py'
  config.JobType.outputFiles = ['Data_'+sample+'.root']
  
  config.Data.inputDataset   = dataset[sample]
  config.Data.unitsPerJob = 10
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/ekoenig/'+name
  p = Process(target=submit, args=(config,))
  p.start()
  p.join()
