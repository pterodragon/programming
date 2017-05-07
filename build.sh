mkdir -p build &&
cd build &&
cmake ../C++ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBOOST_ROOT=~/Documents/boost_1_62_0/ -DCMAKE_CXX_FLAGS=-std=c++14 -DCMAKE_BUILD_TYPE=Debug &&
make -j9 $@ && # user can choose the targets
cd -
