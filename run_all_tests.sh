# Getting list of tests
source ./test_list.sh

mkdir $1

for test in ${tests[@]}; 
do
    echo $test
    touch $1/$test
    bazel run binary:run_solution < $test_dir/$test > $1/$test
done