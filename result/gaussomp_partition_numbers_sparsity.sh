for i in {1..5}; do
    output_file="result/experiments/gaussomp_partition_numbers_sparsity/$i.csv"
    echo "Matrix Size,Sparsity,Partitions Number,Gauss-Seidel OMP Execution Time (ms)" >$output_file
    for sparse in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.91 0.92 0.93 0.94 0.95 0.96 0.97 0.98 0.99 0.999; do
        output=$(./main.out 0001 10000 $sparse -v)
        gauss_seidel_omp_exec_time=$(echo "$output" | grep "gauss_seidel_omp execution time" | awk '{print $4}')
        partitions_number=$(echo "$output" | grep "Partitions number" | awk '{print $3}')
        echo "Experiment $i: Matrix size: 10000, Sparsity: $sparse, Partitions Number: $partitions_number Gauss-Seidel OMP execution time: $gauss_seidel_omp_exec_time ms"
        echo "10000,$sparse,$partitions_number,$gauss_seidel_omp_exec_time" >>$output_file
    done
done
