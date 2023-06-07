# Libraries you will find useful
import numpy as np
import scipy 
import skimage as sk
import matplotlib.pyplot as plt
import os
import time
import cv2

start_time = time.time()

# Starter code for Assignment 2 Part 2: Scale-space blob detection
print(os.path.exists('part2_images\\butterfly.jpg'))
img = sk.io.imread('part2_images\\butterfly.jpg')/255


# convert images to grayscale
# rescale the intensities to between 0 and 1 (simply divide them by 255 should do the trick)
grayImg = sk.color.rgb2gray(img)

# Create the Laplacian filter
# Pay careful attention to setting the right filter mask size. Hint: Should the filter width be odd or even?
from scipy.ndimage.filters import gaussian_laplace


# filtering the image (two implementations)
# one that increases filter size, and one that downsamples the image
# For timing, use time.time()

# nonmaximum suppression in scale space
def nms(slice2d):
    nmsResult = scipy.ndimage.filters.rank_filter(slice2d, rank = -1, size=(3,3)) #find max
    return nmsResult

# increasing kernel funciton
def increaseKernel(img, levels):
    h, w = img.shape
    sigma = 1
    k = 1.414
    scaleSpace = np.empty((h, w, level))

    # do filter on every layer
    for i in range(levels):
        scaleSigma = sigma * k**(i)
        filterImg = gaussian_laplace(img, sigma=scaleSigma)
        scaleNormalize = (scaleSigma**2) * filterImg
        scaleSpace[:,:,i] = scaleNormalize

    # perform nms on each 2d slice
    nmsResult = np.empty((h, w, level))
    for i in range(scaleSpace.shape[2]):
        temp = nms(scaleSpace[:,:,i]) #2d
        nmsResult[:,:,i] = temp
    # print(temp.shape)
    
    # find the indices of the blob
    x = []
    y = []
    rad = []
    cordinate = []

    cp_scale_space = np.zeros((h,w,levels))
    for i in range(0, h):
        for j in range(0, w):
            maxValue = max(nmsResult[i,j,:])
            maxIndex = np.where(nmsResult[i,j,:] == maxValue)[0][0]
            if maxValue >= 0.015 and maxValue == scaleSpace[i,j,maxIndex]:
                cp_scale_space[i,j,maxIndex] = maxValue
    
    for i in range(0, h):
        for j in range(0, w):
            # pixelValues = nms(scaleSpace[i,j,:])
            pixelValues = cp_scale_space[i,j,:] # each layers pixel values at certain pixel position
            if(np.max(pixelValues) >= 0.015):
                # print(((np.argmax(pixelValues))))
                rad.append(k**(np.argmax(pixelValues)))
                x.append(i)
                y.append(j)

    cordinate.append(x)
    cordinate.append(y)
    cordinate.append(rad)

    return cordinate

# laplacian pyramid(downscale)
def laplacianPyr(img, levels):
    h, w = img.shape
    print(h,w)
    sigma = 1
    k = 1.414
    scaleSpace = np.empty(levels, dtype=object) # creates an object array with n "slots"
    for i in range(levels):
        scaleSigma = sigma * (k**i)
        resizeImg = sk.transform.resize(img, (img.shape[0]// scaleSigma, img.shape[1] // scaleSigma))
        filterImg = gaussian_laplace(resizeImg, sigma=scaleSigma)
        scaleSpace[i] = filterImg # store a matrix at level i
    # print("scalespace shape: ", scaleSpace.shape)
   
    nmsResult = np.empty(levels, dtype=object)
    for i in range(scaleSpace.shape[0]):
        nmsResult[i] = nms(scaleSpace[i])
    # print(nmsResult[0].shape)
    
    x = []
    y = []
    rad = []
    cordinate = []

    cp_scale_space = np.zeros((h,w,levels))
    # for i in range(0, h):
    #     for j in range(0, w):
    #         maxValue = max(nmsResult[i])
    #         maxIndex = np.where(nmsResult[i] == maxValue)[0][0]
    #         if maxValue >= 0.015 and maxValue == scaleSpace[i,j,maxIndex]:
    #             cp_scale_space[i,j,maxIndex] = maxValue

    # for lvl in range(levels):
    #     height, width = nmsResult[lvl].shape
    #     for ht in range(height):
    #         for wd in range(width):
    #             maxValue = max(nmsResult[lvl][ht][wd])


    for i in range(0, h):
        for j in range(0, w):
            # pixelValues = nms(scaleSpace[i,j,:])
            pixelValues = cp_scale_space[i,j,:] # each layers pixel values at certain pixel position
            if(np.max(pixelValues) >= 0.015):
                # print(((np.argmax(pixelValues))))
                rad.append(k**(np.argmax(pixelValues)))
                x.append(i)
                y.append(j)

    cordinate.append(x)
    cordinate.append(y)
    cordinate.append(rad)
    return cordinate

# you may find functions scipy.ndimage.filters.rank_filter or scipy.ndimage.filters.generic_filter useful

# To display the detected regions as circle
from matplotlib.patches import Circle
def show_all_circles(image, cx, cy, rad, color='r'):
    """
    image: numpy array, representing the grayscsale image
    cx, cy: numpy arrays or lists, centers of the detected blobs
    rad: numpy array or list, radius of the detected blobs
    """
    fig, ax = plt.subplots()
    ax.set_aspect('equal')
    ax.imshow(image, cmap='gray')
    for x, y, r in zip(cx, cy, rad):
        circ = Circle((x, y), r, color=color, fill=False)
        ax.add_patch(circ)
    # plt.savefig("butterflyPyr.jpg")
    plt.title('%i circles' % len(cx))
    plt.show()

################## main code ##################
level = 13

cordinates = increaseKernel(grayImg, level)
# pyramid = laplacianPyr(grayImg, level)

# show circle
draw = show_all_circles(grayImg, cordinates[1], cordinates[0], cordinates[2])
# draw = show_all_circles(grayImg, pyramid[1], pyramid[0], pyramid[2])

end_time = time.time()
total_time = end_time - start_time
print("time:", total_time)

