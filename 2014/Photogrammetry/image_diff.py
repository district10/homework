# Usage: python image_diff.py <pic1> <pic2>
import cv2, numpy, os, sys

cv2.namedWindow('Origin')

image1 = cv2.imread(sys.argv[1])

array1 = bytearray(image1)

# print image1.ndim

cv2.imwrite('Pic_diff.png', image_diff)
image_diff= cv2.imread('Pic_diff.png')
cv2.imshow('Pic A', image1)
cv2.imshow('Pic B', image2)
cv2.imshow('Pic diff', image_diff)
cv2.waitKey(0)
