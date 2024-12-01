import csv
import os

input_folder = os.path.dirname(os.path.abspath(__file__))
output_file = os.path.join(input_folder, 'mean.csv')

# List of input files
input_files = [os.path.join(input_folder, f'{i}.csv') for i in range(1, 6)]

# Initialize lists to store the sums and counts
sums = []
counts = []

# Read each input file and accumulate the sums and counts
for idx, file in enumerate(input_files):
    with open(file, 'r') as csvfile:
        reader = csv.reader(csvfile)
        header = next(reader)  # Skip the header
        for line_idx, row in enumerate(reader):
            if idx == 0:  # Initialize sums and counts on the first file
                sums.append(float(row[1]))
                counts.append(1)
            else:
                sums[line_idx] += float(row[1])
                counts[line_idx] += 1

# Calculate the means and write to the output file
with open(output_file, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['Matrix Size', 'Mean Execution Time (ms)'])

    with open(input_files[0], 'r') as csvfile_first:
        reader_first = csv.reader(csvfile_first)
        header = next(reader_first)  # Skip the header
        for idx, row in enumerate(reader_first):
            mean_value = sums[idx] / counts[idx]
            writer.writerow([row[0], mean_value])

print(f"Mean values have been written to {output_file}")
