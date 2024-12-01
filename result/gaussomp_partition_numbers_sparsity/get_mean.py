import csv
import os

# Input and output paths
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
        for index, row in enumerate(reader):
            key = index  # Use the row index as the key to ensure the same order
            values = list(map(float, row[2:]))  # Convert the last two columns to float
            if key not in data:
                data[key] = {'sum': [0, 0], 'count': 0, 'metadata': row[:2]}  # Metadata for the first two columns
            data[key]['sum'] = [data[key]['sum'][i] + values[i] for i in range(2)]
            data[key]['count'] += 1

# Calculate the means and write to the output file
with open(output_file, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['Matrix Size', 'Sparsity', 'Partitions Number', 'Gauss-Seidel OMP Execution Time (ms)'])
    for key, value in sorted(data.items()):
        mean_values = [value['sum'][i] / value['count'] for i in range(2)]
        writer.writerow(value['metadata'] + mean_values)

print(f"Mean values have been written to {output_file}")
