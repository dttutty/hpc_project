for i in {2..5}; do
    output_file="result/jacobi_omp_and_gauss_omp_scability_test_on_very_sparse_matrix/$i.csv"
    echo "Matrix Size,Sparsity,Jacobi OMP Execution Time (ms),Gauss-Seidel OMP Execution Time (ms)" >$output_file
    for sparse in 0.99999; do
        for size in 100 300 1000 3000 10000 30000 100000; do
            output=$(./main.out 0101 $size $sparse -v)
            jacobi_omp_exec_time=$(echo "$output" | grep "jacobi_omp execution time" | awk '{print $4}')
            gauss_seidel_omp_exec_time=$(echo "$output" | grep "gauss_seidel_omp execution time" | awk '{print $4}')
            echo "Experiment $i: Matrix size: $size, Sparsity: $sparse, Jacobi OMP execution time: $jacobi_omp_exec_time ms, Gauss-Seidel OMP execution time: $gauss_seidel_omp_exec_time ms"
            echo "$size,$sparse,$jacobi_omp_exec_time,$gauss_seidel_omp_exec_time" >>$output_file
        done
    done
done
