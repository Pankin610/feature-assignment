# Getting list of tests
source ./test_list.sh

mkdir $1

bazel build ...

for test in ${tests[@]}; 
do
    echo Running $test
    touch $1/$test
    ./bazel-bin/binary/run_solution < $test_dir/$test > $1/$test
done