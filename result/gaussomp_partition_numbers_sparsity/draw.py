import pandas as pd
import matplotlib.pyplot as plt
import os
# 数据
data = """
Matrix Size,Sparsity,Partitions Number,Gauss-Seidel OMP Execution Time (ms)
10000,0.2,2328.6,29032.2
10000,0.3,1694.4,23021.0
10000,0.4,1303.2,17813.0
10000,0.5,1010.2,16039.8
10000,0.6,768.8,11974.0
10000,0.7,563.6,9544.4
10000,0.8,376.4,6905.0
10000,0.9,202.2,4113.0
10000,0.91,184.6,3948.4
10000,0.92,167.0,3828.2
10000,0.93,149.2,3637.0
10000,0.94,130.8,3380.4
10000,0.95,113.8,3169.4
10000,0.96,94.6,2842.2
10000,0.97,76.0,2554.6
10000,0.98,56.0,2041.4
10000,0.99,34.0,1865.0
10000,0.999,9.0,1547.6
"""

# 读取数据
from io import StringIO
df = pd.read_csv(StringIO(data))

# 绘制图形
fig, ax1 = plt.subplots(figsize=(12, 8))

# 主坐标轴：运行时间
ax1.set_xlabel("Sparsity (log scale)", fontsize=12)
ax1.set_ylabel("Execution Time (ms) (log scale)", fontsize=12, color="tab:blue")
ax1.plot(df["Sparsity"], df["Gauss-Seidel OMP Execution Time (ms)"], marker='o', color="tab:blue", label="Execution Time")
ax1.set_xscale("log")
ax1.set_yscale("log")
ax1.tick_params(axis='y', labelcolor="tab:blue")
ax1.grid(True, which="both", linestyle="--", alpha=0.7)

# 次坐标轴：分区数量
ax2 = ax1.twinx()
ax2.set_ylabel("Partitions Number (log scale)", fontsize=12, color="tab:orange")
ax2.plot(df["Sparsity"], df["Partitions Number"], marker='s', color="tab:orange", label="Partitions Number")
ax2.set_yscale("log")
ax2.tick_params(axis='y', labelcolor="tab:orange")

# 标题和布局
plt.title("Sparsity vs Execution Time and Partitions Number (Log Scale)", fontsize=14)
fig.tight_layout()

# 显示图形
script_dir = os.path.dirname(os.path.abspath(__file__))
plt.savefig(os.path.join(script_dir, 'result.png'))
