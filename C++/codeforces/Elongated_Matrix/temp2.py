import matplotlib.pyplot as plt
x1, y1 = [-1, 12], [1, 10]
x2, y2 = [-1, 10], [3, -1]
plt.xlim(0, 8), plt.ylim(-2, 8)
plt.plot(x1, y1, x2, y2, marker = 'o')
plt.show()
