for file in $(find . -name "*.hpp" -o -name "*.cpp"); do 
    clang-format -style="{IndentWidth: 2}" -i $file
done
