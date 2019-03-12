temp=""
while getopts "ecap:" o; do
    case "${o}" in
        e) # build leetcode only
            leetcode_only="-Dbuild_leetcode_only=ON"
            ;;
        c) # build codeforces only
            codeforces_only="-Dbuild_codeforces_only=ON"
            ;;
        a) # build algorithms only
            algorithms_only="-Dbuild_algorithms_only=ON"
            ;;
        p)
            temp=${OPTARG}
            ;;

    esac
done
shift $((OPTIND-1))

target="$1"
if [ -z $target ];
then
    target="all"
fi

export CXX="clang++"
export CC="clang"

cmake -H"C++" -Bbuild $algorithms_only $codeforces_only $leetcode_only -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBOOST_ROOT=$(pwd)/C++/third_party -DCMAKE_CXX_FLAGS=-std=c++17 -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug --target $target -- -j 8
