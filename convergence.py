import matplotlib.pyplot as plt

# Jacobi residuals
jacobi_residuals = [
    1.37536, 0.933051, 0.662512, 0.465914, 0.328243, 0.231221, 0.162868,
    0.114725, 0.0808123, 0.0569242, 0.0400974, 0.0282446, 0.0198954,
    0.0140143, 0.00987166
]

# Gauss-Seidel residuals
gauss_residuals = [
    1.71458, 1.5948, 1.28699, 1.23005, 1.02065, 0.70366, 0.617681,
    0.558495, 0.558342, 0.340837, 0.213406, 0.0803558, 0.0663173,
    0.0651182, 0.0649677, 0.0646184, 0.0563178, 0.0486954, 0.0436822,
    0.0136707, 0.0122601, 0.0119704, 0.0113947, 0.0103165, 0.00935256
]

# Plotting the convergence graphs
plt.figure(figsize=(10, 6))

# Jacobi residuals
plt.plot(range(len(jacobi_residuals)), jacobi_residuals, marker='o', label='Jacobi')

# Gauss-Seidel residuals
plt.plot(range(len(gauss_residuals)), gauss_residuals, marker='s', label='Gauss-Seidel')

# Adding labels and title
plt.title("Convergence of Jacobi and Gauss-Seidel Methods", fontsize=14)
plt.xlabel("Iteration", fontsize=12)
plt.ylabel("Residual", fontsize=12)
plt.yscale('log')  # Using a logarithmic scale for better visualization of convergence
plt.grid(True, linestyle="--", alpha=0.7)
plt.legend(fontsize=12)
plt.tight_layout()

# Display the plot
plt.savefig('convergence.png')
