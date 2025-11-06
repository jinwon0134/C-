from matplotlib import pyplot as plt
from sklearn.linear_model import LinearRegression
import numpy as np

# 예시 데이터
x = np.array([[1], [2], [3], [4], [5]])
y = np.array([2, 4, 6, 8, 10])

# 모델 생성 및 학습
model = LinearRegression()
model.fit(x, y)

# 예측
y_hat = model.predict(x)

# 그래프 출력
plt.scatter(x, y, color='blue', label='Real data')
plt.plot(x, y_hat, color='red', label='Predicted line')
plt.legend()
plt.show()

