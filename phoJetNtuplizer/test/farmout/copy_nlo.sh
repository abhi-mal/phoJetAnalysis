hdfs=/hdfs/store/user/ekoenig/MINIAOD/
campaign=Autumn18

function copyfile() {
    base=$(basename $1)
    echo $1
    globus-url-copy -v $1 $2/$base
    if [[ "$3" -eq "5" ]]; then return; fi
    if [[ ! "$?" -eq "0" ]]; then
	echo Resubmitting $3
	copyfile $1 $2 $(($3 + 1))
	# globus-url-copy -v $1 $2/$base
    fi	
}

export -f copyfile

copysample() {
    sample=$(basename $sample)
    sample="${sample/.in/}"_${campaign}
    mkdir -pv $hdfs/$sample
    input=$(head -n 1 $1)
    input=$(dirname $input)/
    # globus-url-copy -p 10 -vb $input $hdfs/$sample/
    cat $1 | parallel -j2 copyfile {} $hdfs/$sample
    # cat $1 | head | parallel -j1 copyfile {} $hdfs/$sample
}

for sample in $@; do copysample $sample; done
