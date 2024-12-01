import pandas as pd
import matplotlib.pyplot as plt
import os 

# 文件路径
script_dir = os.path.dirname(os.path.abspath(__file__))

file_paths = [
    script_dir + '/jacobi/mean.csv',
    script_dir + '/jacobi_omp/mean.csv',
]
print(file_paths)
# 读取数据并处理
dfs = []
labels = ['Jacobi', 'Jacobi OMP'] 
for file_path in file_paths:
    file_name = file_path.split('/')[-1].split('.')[0]
    data = pd.read_csv(file_path)
    dfs.append(pd.DataFrame(data))

# 绘制图形
plt.figure(figsize=(10, 6))
for df, label in zip(dfs, labels):
    plt.plot(df["Matrix Size"], df["Mean Execution Time (ms)"], marker="o", label=label)
    for i in range(len(df)):
        plt.text(df["Matrix Size"][i], df["Mean Execution Time (ms)"][i], f'{df["Mean Execution Time (ms)"][i]:.2f} ms', fontsize=9, ha='right')

# 添加标题和标签
plt.title("Matrix Size vs Execution Time (Comparison)", fontsize=14)
plt.xlabel("Matrix Size", fontsize=12)
plt.ylabel("Execution Time (ms)", fontsize=12)
plt.grid(True, linestyle="--", alpha=0.7)
plt.legend(fontsize=12)
plt.tight_layout()

# 保存图形
plt.savefig(os.path.join(script_dir, 'result.png'))
