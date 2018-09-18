for file in $(find . -name "*.hpp" -o -name "*.cpp"); do 
    clang-format -i $file
done
