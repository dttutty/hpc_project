import csv
import os

input_folder = os.path.dirname(os.path.abspath(__file__))
output_file = os.path.join(input_folder, 'mean.csv')


# List of input files
input_files = [os.path.join(input_folder, f'{i}.csv') for i in range(1, 6)]

# Initialize a dictionary to store the sums and counts
data = {}

# Read each input file and accumulate the sums and counts
for file in input_files:
    with open(file, 'r') as csvfile:
        reader = csv.reader(csvfile)
        header = next(reader)  # Skip the header
        for row in reader:
            key = (row[0], row[1])  # Matrix Size and Sparsity as key
            values = list(map(float, row[2:]))  # Convert the last three columns to float
            if key not in data:
                data[key] = {'sum': [0, 0, 0], 'count': 0}
            data[key]['sum'] = [data[key]['sum'][i] + values[i] for i in range(3)]
            data[key]['count'] += 1

# Calculate the means and write to the output file
with open(output_file, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['Matrix Size', 'Sparsity', 'Jacobi OMP Execution Time (ms)', 'Gauss-Seidel Execution Time (ms)', 'Gauss-Seidel OMP Execution Time (ms)'])
    for key, value in data.items():
        mean_values = [value['sum'][i] / value['count'] for i in range(3)]
        writer.writerow(list(key) + mean_values)
        print(f"Mean values have been written to {output_file}")
