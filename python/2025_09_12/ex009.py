import random

balls = [ball for ball in range(1,46)]
print(balls)
random.shuffle(balls)
print(balls)
choice_balls = []
for _ in range(6):
    random.shuffle(balls)
    choice_balls.append(balls.pop())
print(choice_balls)
choice_balls.sort()
print(choice_balls)