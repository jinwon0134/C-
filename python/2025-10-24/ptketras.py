import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import matplotlib.pyplot as plt
from matplotlib import rc

# 한글 폰트 설정
rc('font', family='Malgun Gothic')  # Windows 기본 한글 폰트

# === 0. GPU/CPU 확인 ===
gpus = tf.config.list_physical_devices('GPU')
if gpus:
    print(f"✅ GPU 사용 중: {gpus[0].name}")
else:
    print("⚠️ GPU를 찾을 수 없습니다. CPU로 실행합니다.")

# === 1. 데이터 불러오기 ===
(train_images, train_labels), (test_images, test_labels) = keras.datasets.mnist.load_data()

# === 2. 데이터 전처리 ===
train_images = train_images.reshape((60000, 28 * 28)).astype("float32") / 255.0
test_images = test_images.reshape((10000, 28 * 28)).astype("float32") / 255.0

# === 3. 모델 구성 ===
model = keras.Sequential(name="MNIST_Model")
model.add(layers.Input(shape=(28 * 28,)))
model.add(layers.Dense(512, activation="relu"))
model.add(layers.Dense(256, activation="relu"))
model.add(layers.Dense(10, activation="softmax"))

# === 4. 모델 컴파일 ===
model.compile(
    optimizer="adam",
    loss="sparse_categorical_crossentropy",
    metrics=["accuracy"]
)

# === 5. 모델 학습 ===
print("\n✅ 모델 학습 중...\n")
history = model.fit(train_images, train_labels, epochs=5, batch_size=128, verbose=1)

# === 6. 평가 ===
print("\n✅ 테스트 데이터로 평가 중...\n")
test_loss, test_acc = model.evaluate(test_images, test_labels, verbose=0)
print(f"🎯 테스트 정확도: {test_acc * 100:.2f}%")

# === 7. 예측 및 시각화 ===
predictions = model.predict(test_images[:5])

for i in range(5):
    plt.imshow(test_images[i].reshape(28, 28), cmap="gray")
    plt.title(f"예측: {predictions[i].argmax()} / 실제: {test_labels[i]}")
    plt.axis("off")
    plt.show()

