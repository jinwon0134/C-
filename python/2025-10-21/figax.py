import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots(2,2)

x= np.random.randn(100)
y= np.random.randn(100)
ax[0,0].scatter(x,y)
x= np.arange(10)
y= np.random.uniform(1,10,10)
ax[0,1].bar(x,y)
x = np.linspace(0,10,100)
y = np.cos(x)
ax[1,0].plot(x,y)
z = np.random.uniform(0,1,(5,5))
ax[1,1].imshow(z)

data = np.random.randn(10, 10)
plt.imshow(data)
plt.colorbar()

f1 = np.random.randn(100000)
plt.hist(f1, bins=200, color ='red', alpha = 7,\
         label='avg = 0 , std = 1')
plt.axis([-8,8,-2,2500])

plt.show()
