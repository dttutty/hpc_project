import pandas as pd
import matplotlib.pyplot as plt

# 从文件中读取数据
file_path = './result/jacobi_omp_different_threads.csv' 
file_name = file_path.split('/')[-1].split('.')[0]
title = file_name.replace('_', ' ').title()
data = pd.read_csv(file_path)

# 转换为 DataFrame
df = pd.DataFrame(data)

# 绘制图形
plt.figure(figsize=(10, 6))
plt.plot(df["OMP_NUM_THREADS"], df["Execution Time (ms)"], marker="o", label="Execution Time")
plt.title(title, fontsize=14)
plt.xlabel("OMP_NUM_THREADS", fontsize=12)
plt.ylabel("Execution Time (ms)", fontsize=12)
plt.grid(True, linestyle="--", alpha=0.7)
plt.legend(fontsize=12)
plt.tight_layout()

# 显示图形
plt.savefig("./result/" + file_name +".png")

