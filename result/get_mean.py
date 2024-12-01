import csv
import os
import argparse

parser = argparse.ArgumentParser(description="Compute the mean of specified columns in CSV files.")
parser.add_argument("-n", type=int, default=1, help="Number of columns from the end to calculate mean (default: 1)")
parser.add_argument("-input_folder", type=str, default=None, help="Folder containing input CSV files (default: current directory)")
args = parser.parse_args()

n = args.n
input_folder = args.input_folder if args.input_folder else os.path.dirname(os.path.abspath(__file__))

# Output file path
output_file = os.path.join(input_folder, 'mean.csv')

# List of input files
input_files = [os.path.join(input_folder, f'{i}.csv') for i in range(1, 6)]

# Initialize a list to store sums for the last n columns and other row data
row_sums = []
row_counts = 0
header = []

# Read the first file to get the header
with open(input_files[0], 'r') as csvfile:
    reader = csv.reader(csvfile)
    header = next(reader)  # Read and store the header
    for row in reader:
        # Store row data (excluding the last n columns) and sums for the last n columns
        non_target_columns = row[:-n] if n < len(row) else []
        target_columns = list(map(float, row[-n:]))
        row_sums.append(non_target_columns + target_columns)  # Initialize sums with first file
    row_counts += 1

# Read remaining files and accumulate the sums for the last n columns
for file in input_files[1:]:
    with open(file, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)  # Skip the header
        for i, row in enumerate(reader):
            target_columns = list(map(float, row[-n:]))
            row_sums[i][-n:] = [row_sums[i][-n:][j] + target_columns[j] for j in range(n)]
        row_counts += 1

# Calculate the means for the last n columns
row_means = [
    row[:-n] + [value / row_counts for value in row[-n:]]
    for row in row_sums
]

# Write the mean values to the output file
with open(output_file, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(header)  # Write the header from the first file
    writer.writerows(row_means)

print(f"Mean values have been written to {output_file}")
