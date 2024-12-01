import pandas as pd
import matplotlib.pyplot as plt

# 数据
data = """
Matrix Size,Sparsity,Partitions Number,Gauss-Seidel OMP Execution Time (ms)
10000,0.1,10000,112192
10000,0.2,2337,29679
10000,0.3,1699,23483
10000,0.4,1305,18174
10000,0.5,1007,16065
10000,0.6,770,11221
10000,0.7,563,9674
10000,0.8,376,6258
10000,0.9,203,3818
10000,0.91,183,4138
10000,0.92,167,3929
10000,0.93,149,3766
10000,0.94,131,3273
10000,0.95,113,3044
10000,0.96,94,2661
10000,0.97,76,2506
10000,0.98,56,2068
10000,0.99,34,1688
10000,0.999,9,1445
10000,0.9999,4,1530
10000,0.99999,2,1845
10000,0.999999,2,1929
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
plt.savefig("gaussomp_partition_numbers_sparsity.png")
