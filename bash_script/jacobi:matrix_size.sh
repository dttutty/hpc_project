output_file="result/jacobi_different_size_of_matrix.csv"
echo "Matrix Size,Execution Time (ms)" > $output_file
for size in {100..1000..100}; do
    output=$(./main.out 1000 $size 0 -v)
    exec_time=$(echo "$output" | grep "jacobi execution time" | awk '{print $4}')
    echo "Matrix size: $size, Execution time: $exec_time ms"
    echo "$size,$exec_time" >> $output_file
done