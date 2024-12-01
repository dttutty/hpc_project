import pandas as pd
import matplotlib.pyplot as plt
import os

# 数据文件
script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'mean.csv')  # 假设数据存储在 data.csv 中

# 从文件中读取数据
df = pd.read_csv(file_path)

# 绘制图形
plt.figure(figsize=(10, 6))
plt.plot(df["Matrix Size"], df["Jacobi OMP Execution Time (ms)"], marker="o", label="Jacobi OMP")
plt.plot(df["Matrix Size"], df["Gauss-Seidel OMP Execution Time (ms)"], marker="s", label="Gauss-Seidel OMP")
plt.title("Matrix Size vs Execution Time", fontsize=14)
plt.xlabel("Matrix Size", fontsize=12)
plt.ylabel("Execution Time (ms)", fontsize=12)
plt.xscale("log")  # 对数刻度
plt.yscale("log")  # 对数刻度
plt.grid(True, linestyle="--", alpha=0.7)
plt.legend(fontsize=12)
plt.tight_layout()

# 保存图形
output_file = os.path.join(script_dir, 'execution_time_comparison.png')
plt.savefig(output_file)
plt.show()

print(f"Plot saved to {output_file}")
