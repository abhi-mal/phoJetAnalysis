import os

dataset = {
  "GJets_1j_Gpt-100To250_5f_NLO":"datasets/private-nlo/",
  "GJets_1j_Gpt-250To400_5f_NLO":"datasets/private-nlo/",
  "GJets_1j_Gpt-400To650_5f_NLO":"datasets/private-nlo/",
  "GJets_1j_Gpt-650ToInf_5f_NLO":"datasets/private-nlo/"
}

if __name__ == '__main__':
  from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
from multiprocessing import Process

config = config()
name = 'MC-NLO2018_Autumn18_Jul2020'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.inputFiles = ['Autumn18_V19_MC.db']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data') 
config.Data.publication = False
# config.Data.inputDBS = 'gsiftp://se01.cmsaf.mit.edu:2811/cms/store/user/bmaier/monojet20/'
user_path = 'gsiftp://se01.cmsaf.mit.edu:2811/cms/store/user/bmaier/monojet20/{db}_Autumn18/miniaod/{fn}'
config.Data.splitting = 'FileBased'

config.Site.storageSite = 'T2_US_Wisconsin'
#config.Site.whitelist = ["T2_US_Wisconsin"]
#config.Site.blacklist = ['T2_CH_CERN']

listOfSamples = ["GJets_1j_Gpt-100To250_5f_NLO","GJets_1j_Gpt-250To400_5f_NLO","GJets_1j_Gpt-400To650_5f_NLO","GJets_1j_Gpt-650ToInf_5f_NLO"]

for sample in listOfSamples:
  os.popen('cp run_102X_mc2018.py run_102X_mc2018_'+sample+'.py')
  with open('run_102X_mc2018_'+sample+'.py') as oldFile:
    newText = oldFile.read().replace('Ntuple_mc.root','MC_'+sample+'.root')
  with open('run_102X_mc2018_'+sample+'.py', 'w') as newFile:
    newFile.write(newText)

  config.General.requestName = 'job_'+sample
  
  config.JobType.psetName = 'run_102X_mc2018_'+sample+'.py'
  config.JobType.outputFiles = ['MC_'+sample+'.root']
  
  # config.Data.inputDataset   = dataset[sample]
  config.Data.outputPrimaryDataset = sample
  config.Data.userInputFiles = [ user_path.format(db=sample,fn=fn.strip()) for fn in open(dataset[sample]+"/"+sample+".txt","r").readlines() if '.root' in fn ]
  config.Data.unitsPerJob = 10000
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/ekoenig/'+name
  p = Process(target=submit, args=(config,))
  p.start()
  p.join()
