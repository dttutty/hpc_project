output_file="result/jacobi_omp_different_threads.csv"
echo "OMP_NUM_THREADS,Execution Time (ms)" > $output_file
matrix_size=600  # Set your fixed matrix size here
for threads in 1 2 {4..128..4}; do
    export OMP_NUM_THREADS=$threads
    output=$(./main.out 0100 $matrix_size 0 -v)
    exec_time=$(echo "$output" | grep "jacobi_omp execution time" | awk '{print $4}')
    echo "OMP_NUM_THREADS: $threads, Execution time: $exec_time ms"
    echo "$threads,$exec_time" >> $output_file
done
