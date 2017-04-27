cd build &&
cmake ../C++ -DBoost_INCLUDE_DIR=~/Documents/boost_1_62_0/ -DCMAKE_CXX_FLAGS=-std=c++14 -DCMAKE_BUILD_TYPE=Debug &&
make -j9 &&
cd -
