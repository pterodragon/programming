if [ -d "boost_1_62_0" ]; then
    cd boost_1_62_0 &&
    ./b2 --with-test --with-filesystem --with-regex --prefix=$(pwd)/build
    cd -
else
    echo "boost_1_62_0 dir not found"
fi
