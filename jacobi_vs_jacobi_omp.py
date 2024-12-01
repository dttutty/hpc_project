import pandas as pd
import matplotlib.pyplot as plt

# 文件路径
file_paths = [
    './result/jacobi_different_size_of_matrix.csv',
    './result/jacobi_omp_different_size_of_matrix.csv'
]

# 读取数据并处理
dfs = []
labels = []
for file_path in file_paths:
    file_name = file_path.split('/')[-1].split('.')[0]
    labels.append(file_name.replace('_', ' ').title())
    data = pd.read_csv(file_path)
    dfs.append(pd.DataFrame(data))

# 绘制图形
plt.figure(figsize=(10, 6))
for df, label in zip(dfs, labels):
    plt.plot(df["Matrix Size"], df["Execution Time (ms)"], marker="o", label=label)

# 添加标题和标签
plt.title("Matrix Size vs Execution Time (Comparison)", fontsize=14)
plt.xlabel("Matrix Size", fontsize=12)
plt.ylabel("Execution Time (ms)", fontsize=12)
plt.grid(True, linestyle="--", alpha=0.7)
plt.legend(fontsize=12)
plt.tight_layout()

# 保存图形
output_path = "./result/matrix_execution_time_comparison.png"
plt.savefig(output_path)
plt.show()

output_path
