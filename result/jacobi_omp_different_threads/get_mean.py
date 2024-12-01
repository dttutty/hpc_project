import csv
import os

# Input and output paths
input_folder = os.path.dirname(os.path.abspath(__file__))
output_file = os.path.join(input_folder, 'mean.csv')

# List of input files
input_files = [os.path.join(input_folder, f'{i}.csv') for i in range(1, 6)]

# Initialize a list to store sums for each row
row_sums = []
row_counts = 0

# Read each input file and accumulate the sums row by row
for file in input_files:
    with open(file, 'r') as csvfile:
        reader = csv.reader(csvfile)
        header = next(reader)  # Skip the header
        if not row_sums:  # Initialize sums based on the first file
            for row in reader:
                row_sums.append([int(row[0]), float(row[1])])
            row_counts += 1
        else:
            for i, row in enumerate(reader):
                row_sums[i][1] += float(row[1])
            row_counts += 1

# Calculate the means
row_means = [[row[0], row[1] / row_counts] for row in row_sums]

# Write the mean values to the output file
with open(output_file, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['OMP_NUM_THREADS', 'Mean Execution Time (ms)'])
    writer.writerows(row_means)

print(f"Mean values have been written to {output_file}")
