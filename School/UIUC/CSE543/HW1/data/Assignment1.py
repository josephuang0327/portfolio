import numpy as np
import cv2
import os
import sys
from PIL import Image, ImageChops
import time

start_time = time.time()

print(os.path.exists('Assignement1\\data\\00125v.jpg'))
img = cv2.imread('Assignement1\\data\\00125v.jpg')
# print(img.shape)

# divide to 3 channel
def divideCh(img):
    height = np.floor(img.shape[0] / 3).astype(int)
    b = img[:height, :]
    g = img[height:(height*2), :]
    r = img[(height*2):(height*3), :]
    return b, g, r

# crop image to same size and get rid of border with some scale
def cropImg(img, scale):
    height = np.floor(img.shape[0]).astype(int)
    width = np.floor(img.shape[1]).astype(int)
    cropHeight = np.floor(img.shape[0] / scale).astype(int)
    cropWidth = np.floor(img.shape[1] / scale).astype(int)
    return img[cropHeight:(height - cropHeight), cropWidth:(width - cropWidth)]

# normalize
def avgmethod(img):
    # mean = np.mean(img)
    # return np.divide(img, mean)
    norm = cv2.normalize(img, None, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_32F)
    return norm

# roll img 
def rollImg(img, x, y):
    xRoll = np.roll(img, x, axis = 1)
    return np.roll(xRoll, y, axis = 0)

# ssd method
def ssd(img1, img2, posOff, searchWindow):
    xStart, yStart = posOff[0], posOff[1]
    err = sys.maxsize
    offset = posOff

    for i in range(xStart - searchWindow, xStart + searchWindow + 1):
        for j in range(yStart - searchWindow, yStart + searchWindow + 1):
            currentErr = np.sum((rollImg(img1, i, j) - img2)**2)
            if currentErr < err:
                err = currentErr
                offset = [i,j]
    print(offset)
    return offset

# ncc method
def ncc(img1, img2, posOff, searchWindow):
    xStart, yStart = posOff[0], posOff[1]
    corelation = 0
    offset = 0
    for i in range(xStart - searchWindow, xStart + searchWindow + 1):
            for j in range(yStart - searchWindow, yStart + searchWindow + 1):
                result = cv2.matchTemplate(rollImg(img1, i, j), img2, cv2.TM_CCOEFF_NORMED)
                # print(result)
                if result > corelation:
                    corelation = result
                    offset = [i,j]
    # print(offset)
    return offset

# image pyramid method
def imagePyramid(img1, img2, posOff, searchWindow, count):
    if(img1.shape[0] < 256):
        return ssd(img1, img2, posOff, searchWindow)
    else:
        lower_res1 = cv2.pyrDown(img1)
        lower_res2 = cv2.pyrDown(img2)
        newOff = np.multiply(imagePyramid(lower_res1, lower_res2, posOff, searchWindow, count - 1), 2)
        searchWindow = int(20/count)
        return ssd(img1, img2, newOff, searchWindow)

# mainly use for merging orignial BGR channels to compare with the result image
def merge(img1, img2, img3):
    b1,g1,r1 = cv2.split(img1)
    b2,g2,r2 = cv2.split(img2)
    b3,g3,r3 = cv2.split(img3)
    merged = cv2.merge([b1,g2,r3])
    # cv2.imshow('merge', merged)
    return merged

# shifting/offset method
def shifting(img, shiftx, shifty):
    rows, cols, c = img.shape
    shiftAmount = np.float32([[1,0,shiftx],[0,1,shifty]])
    shiftResult = cv2.warpAffine(img,shiftAmount,(cols,rows))
    return shiftResult

# merging BGR channels after shifting
def shiftmerge(img1, img2, img3):
    b1,g1,r1 = cv2.split(img1)
    b2,g2,r2 = cv2.split(img2)
    b3,g3,r3 = cv2.split(img3)
    shiftmerge = cv2.merge([b1,g2,r3])
    cv2.imshow('Shiftmerge', shiftmerge)
    return shiftmerge

################## main code ##################
scale = 20
posOff = [-5,5]
searchWindow = 20

# divide 3 channels
b, g, r = divideCh(img)

# crop the image to same size and get rid of border
b = cropImg(b, scale)
g = cropImg(g, scale)
r = cropImg(r, scale)

# normalize each channel
b = avgmethod(b)
g = avgmethod(g)
r = avgmethod(r)
# merged = merge(b, g, r)
# cv2.imwrite('01861aOriginal.jpg', 255*merged)

# call for ncc method
# gResult = ncc(b, g, posOff, searchWindow)
# rResult = ncc(b, r, posOff, searchWindow)
# gShift = shifting(g, -gResult[0], -gResult[1])
# rShift = shifting(r, -rResult[0], -rResult[1])

# call for ssd method and shifting method
# gbOffset = ssd(b, g, posOff, searchWindow)
# rbOffset = ssd(b, r, posOff, searchWindow)
# gShift = shifting(g, -gbOffset[0], -gbOffset[1])
# rShift = shifting(r, -rbOffset[0], -rbOffset[1])

# call for image pyramid method
gbPyramid = imagePyramid(b, g, posOff, searchWindow, 10)
rbPyramid = imagePyramid(b, r, posOff, searchWindow, 10)
gShift = shifting(g, -gbPyramid[0], -gbPyramid[1])
rShift = shifting(r, -rbPyramid[0], -rbPyramid[1])

# # merge 3 channels after shifting
shiftmerged = shiftmerge(b, gShift, rShift)

# return/output image by * 25 to get [0:255]
# cv2.imwrite('ssd125vResult.jpg', 255*shiftmerged)

end_time = time.time()
total_time = end_time - start_time
print(total_time)

cv2.waitKey(0)
