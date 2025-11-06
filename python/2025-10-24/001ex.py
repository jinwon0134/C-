import cv2 as cv
#%%
image = cv.imread("test.png", cv.IMREAD_GRAYSCALE)
#%%
cv.imshow("Window", image)
cv.waitKey(0)
cv.destroyAllWindows()
#%%
image = cv.resize(image, (28,28))
#%%
cv.imshow("Window", image)
cv.waitKey(0)
cv.destroyAllWindows()
#%%
image = image.astype('float32')
#%%
image = image.reshape(1, 28*28)