# HPC Project

## Compilation Instructions

To compile the project, use the following command:

```sh
g++ main.cpp lib/gauss.cpp lib/jacobi.cpp -I./lib lib/residual.cpp lib/gen_random.cpp lib/coloring.cpp lib/print_time.cpp -o main.out -fopenmp
```

## Usage
To run the program, use the following command:

```sh
./main <flags> <matrix_size> <sparse_ratio> [-v]
```

- **flags**: A 4-digit string containing only 0s and 1s, where each digit corresponds to a method.
- **methods**: `jacobi`, `jacobi_omp`, `gauss_seidel`, `gauss_seidel_omp`
- **matrix_size**: The size of the matrix to be processed.
- **sparse_ratio**: The ratio of sparsity in the matrix.
- **-v**: (Optional) Enable verbose mode.

### Example

To run the program with `jacobi` and `gauss_seidel` methods:

```sh
./main 1010 1000 0.1 -v
```

## Batch Script Usage

To use the batch shell script, ensure you are in the `hpc_project` directory and execute the following command:

```sh
bash bash_script/***.sh
```
# Detail
because residual caculation is time_consuming:
for compare_jacobiomp_gauss_gaussomp experiment: 
jacobi iteration number < gauss iteration number

jacobi: caculate residual every 10 iteration  
jacobi_omp: caculate residual every 10 iteration  
gauss: caculate residual when (iter * n + i) % 100 == 0  
gauss_omp: caculate residual when (iter * partitions_size + current_partition_index) == 0  
