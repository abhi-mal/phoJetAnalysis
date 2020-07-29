user_path=gsiftp://se01.cmsaf.mit.edu:2811/cms/store/user/bmaier/monojet20/
user_path=root://xrootd.cmsaf.mit.edu://store/user/bmaier/monojet20/
campaign=Autumn18

build() {
    db=$(basename $1)
    db="${db/.txt/}"_$campaign
    filelist=$(cat $1 | grep .root | xargs)
    output="${1/.txt/.in}"
    echo $db
    for file in ${filelist[@]}; do echo $user_path$db/miniaod/$file; done > $output
}

for f in $@; do build $f; done
