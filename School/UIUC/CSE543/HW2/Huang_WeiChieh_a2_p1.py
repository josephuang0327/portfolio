import numpy as np
import cv2
import os
import time
import matplotlib.pyplot as plt
from scipy.ndimage import gaussian_filter

# start_time = time.time()
start_time = time.time()

print(os.path.exists('Assignment2\\data\\00125v.jpg'))
img = plt.imread('Assignment2\\data\\00125v.jpg')
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

# mainly use for merging orignial BGR channels to compare with the result image
def merge(img1, img2, img3):
    # b1,g1,r1 = cv2.split(img1)
    # b2,g2,r2 = cv2.split(img2)
    # b3,g3,r3 = cv2.split(img3)
    merged = cv2.merge([img1,img2,img3])
    # merged = cv2.merge([b1,g2,r3])
    cv2.imshow('merge', merged)
    return merged

# shifting/offset method
def shifting(img, shiftx, shifty):
    rows, cols = img.shape
    shiftAmount = np.float32([[1,0,shiftx],[0,1,shifty]])
    shiftResult = cv2.warpAffine(img,shiftAmount,(cols,rows))
    return shiftResult

# find the offset of image
def displacement(invTrans):
    # argmax gives cordinate and unravel_index get indices
    Cord = np.log(abs(invTrans))
    unravCord = np.unravel_index(Cord.argmax(), Cord.shape)
    print(unravCord)
    return unravCord

################## main code ##################
scale = 20

# divide 3 channels
b, g, r = divideCh(img)

# crop the image to same size and get rid of border
b = cropImg(b, scale)
g = cropImg(g, scale)
r = cropImg(r, scale)

# getting 2d FT
ftb = (np.fft.fftshift(np.fft.fft2(b)))
ftg = (np.fft.fftshift(np.fft.fft2(g)))
ftr = (np.fft.fftshift(np.fft.fft2(r)))

# get conjugate
ftgCon = np.conjugate(ftg)
ftrCon = np.conjugate(ftr)

# compute product using blue as base channel
prodbg = ftb * ftgCon
prodbr = ftb * ftrCon

# compute inverse transforms
invbg = np.fft.ifft2(prodbg)
invbr = np.fft.ifft2(prodbr)

# find displacement
# bgCord = displacement(invbg)
# brCord = displacement(invbr)

# show image WITHOUT preprocessing
# plt.imshow(np.log(abs(invbg)))
# plt.show()
# plt.imsave('1861abg.jpg', (np.log(abs(invbg))))

# plt.imshow(np.log(abs(invbr)))
# plt.show()
# plt.imsave('1861abr.jpg', (np.log(abs(invbr))))


# show image WITH preprocessing
filterb = gaussian_filter(np.fft.fftshift(np.fft.fft2(b)), sigma= 3)
filterg = gaussian_filter(np.fft.fftshift(np.fft.fft2(g)), sigma= 3)
filterr = gaussian_filter(np.fft.fftshift(np.fft.fft2(r)), sigma= 3)

filtergCon = np.conjugate(filterg)
filterrCon = np.conjugate(filterr)

filterprodbg = filterb * filtergCon
filterprodbr = filterb * filterrCon

filterinvbg = np.fft.ifft2(filterprodbg)
filterinvbr = np.fft.ifft2(filterprodbr)

bgCord = displacement(filterinvbg)
brCord = displacement(filterinvbr)

# plt.imshow(np.log(abs(filterinvbg)))
# plt.show()
# plt.imsave('125vfilterbg.jpg', (np.log(abs(filterinvbg))))

# plt.imshow(np.log(abs(filterinvbr)))
# plt.show()
# plt.imsave('125vvfilterbr.jpg', (np.log(abs(filterinvbr))))



# shifting
gShift = shifting(g, bgCord[1], bgCord[0])
rShift = shifting(r, brCord[1], brCord[0])

# merge image
merged = merge(b,gShift,rShift)
# cv2.imwrite('1047uResult.jpg', merged) #divide 255 for .tif images --> merged/255

end_time = time.time()
total_time = end_time - start_time
print(total_time)


cv2.waitKey(0)