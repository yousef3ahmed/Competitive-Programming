set -e
g++-11 -std=c++17 code.cpp -o code
g++-11 -std=c++17 gen.cpp -o gen
g++-11 -std=c++17 brute.cpp -o brute

test=0

for((i = 1; ; ++i)); do
    test=$i
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
       
    if cmp -s myAnswer correctAnswer ; then
        echo "Files are equal."
    else
        break
    fi
    echo "Passed test: "  $i
done

echo "-------------------------------" 

echo "WA on the following test:" $test
cat input_file
echo
echo "Your answer is:"
cat myAnswer
echo
echo "Correct answer is:"
cat correctAnswer
echo

echo "-------------------------------" 