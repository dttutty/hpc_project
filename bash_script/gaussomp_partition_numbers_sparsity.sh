output_file="result/gaussomp_partition_numbers_sparsity_.csv"
echo "Matrix Size,Sparsity,Partitions Number,Gauss-Seidel OMP Execution Time (ms)" >$output_file
for sparse in 0.1 0.2; do
    output=$(./main.out 0001 10000 $sparse -v)
    gauss_seidel_omp_exec_time=$(echo "$output" | grep "gauss_seidel_omp execution time" | awk '{print $4}')
    partitions_number=$(echo "$output" | grep "Partitions number" | awk '{print $3}')
    echo "Matrix size: 10000, Sparsity: $sparse, Partitions Number: $partitions_number Gauss-Seidel OMP execution time: $gauss_seidel_omp_exec_time ms"
    echo "10000,$sparse,$partitions_number,$gauss_seidel_omp_exec_time" >>$output_file
done
