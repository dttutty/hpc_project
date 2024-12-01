for i in {1..5}; do
    output_file="result/jacobi_omp_different_size_of_matrix/$i.csv"
    echo "Matrix Size,Execution Time (ms)" >$output_file
    for size in {100..1000..100}; do
        output=$(./main.out 0100 $size 0 -v)
        exec_time=$(echo "$output" | grep "jacobi_omp execution time" | awk '{print $4}')
        echo "Experiment $i, Matrix size: $size, Execution time: $exec_time ms"
        echo "$size,$exec_time" >>$output_file
    done
done
