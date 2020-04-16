#!/bin/bash

resubmit_failed() {
    jobDir=${2}
    status=$(crab status -d ${1}/${jobDir} | grep "Status on the scheduler:")
    if [[ "$status" != *"COMPLETED"* ]]; then
	echo $jobDir "|" $status
	crab resubmit -d ${1}/${jobDir}
    fi 
}
 
for jobDir in `ls ${1}`; do
    resubmit_failed ${1} $jobDir &
done

wait
