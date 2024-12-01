for i in {1..5}; do
    output_file="result/experiments/compare_jacobiomp_gauss_gaussomp/$i.csv"
    echo "Matrix Size,Sparsity,Jacobi OMP Execution Time (ms),Gauss-Seidel Execution Time (ms),Gauss-Seidel OMP Execution Time (ms)" >$output_file
    for sparse in 0.1 0.9 0.99; do
        for size in {100..2000..100}; do
            output=$(./main.out 0111 $size $sparse -v)
            jacobi_omp_exec_time=$(echo "$output" | grep "jacobi_omp execution time" | awk '{print $4}')
            gauss_seidel_exec_time=$(echo "$output" | grep "gauss_seidel execution time" | awk '{print $4}')
            gauss_seidel_omp_exec_time=$(echo "$output" | grep "gauss_seidel_omp execution time" | awk '{print $4}')
            echo "Experiment $i: Matrix size: $size, Sparsity: $sparse, Jacobi OMP execution time: $jacobi_omp_exec_time ms, Gauss-Seidel execution time: $gauss_seidel_exec_time ms, Gauss-Seidel OMP execution time: $gauss_seidel_omp_exec_time ms"
            echo "$size,$sparse,$jacobi_omp_exec_time,$gauss_seidel_exec_time,$gauss_seidel_omp_exec_time" >>$output_file
        done
    done
done
