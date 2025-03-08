import numpy as np
import imageio.v3 as imageio  # Read image
import matplotlib.pyplot as plt

image = imageio.imread("/home/sjyoti/Desktop/LAA/Albert_Einstein_Head.jpg")
plt.imshow(image, cmap='gray')
plt.title("Original Image")
plt.show()

# dimensions of the image
print("Image dimensions:", image.shape)

# type of the array
print("Image type:", image.dtype)

# grayscaling
if len(image.shape) == 3:  
    image_gray = np.mean(image, axis=2).astype(np.uint8)
else:
    image_gray = image
plt.imshow(image_gray, cmap='gray')
plt.title("Grayscale Image")
plt.show()

# increasing and decreasing brightness
lightened = np.clip(image_gray + 50, 0, 255) 
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.imshow(lightened, cmap='gray')
plt.title("Lightened Image")

darkened = np.clip(image_gray - 50, 0, 255)  
plt.subplot(1, 2, 2)
plt.imshow(darkened, cmap='gray')
plt.title("Darkened Image")
plt.show()

# contrast
high_contrast = np.clip(1.5 * (image_gray - 128) + 128, 0, 255)
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.imshow(high_contrast, cmap='gray')
plt.title("High Contrast")

low_contrast = np.clip(0.5 * (image_gray - 128) + 128, 0, 255)
plt.subplot(1, 2, 2)
plt.imshow(low_contrast, cmap='gray')
plt.title("Low Contrast")
plt.show()

# crop image
cropped = image_gray[50:100, 50:200] 
plt.imshow(cropped, cmap='gray')
plt.title("Cropped Image")
plt.show()

# flip 
flipped = np.flip(image_gray, axis=1)  
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.imshow(flipped, cmap='gray')
plt.title("Flipped Image")

# rotate
rotated = np.rot90(image_gray)  
plt.subplot(1, 2, 2)
plt.imshow(rotated, cmap='gray')
plt.title("Rotated Image")
plt.show()
