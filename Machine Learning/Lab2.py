import numpy as np
a = np.array([[1, 2, 3], [4, 5, 6]])
print(a.shape)
x = np.eye(3)
y = x[0:2, 1:3]
print(x)
print(y)
y[0, 0] = 5  # se schimba si in x si in y
print(x)
print(y)