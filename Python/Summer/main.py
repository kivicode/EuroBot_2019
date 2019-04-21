import numpy as np
import cv2
from matplotlib import pyplot as plt

img1 = cv2.imread('field.png')  # queryImage
img2 = cv2.imread('img.jpg')  # queryImage

orb = cv2.ORB_create()
kp1, des1 = orb.detectAndCompute(img1, None)
kp2, des2 = orb.detectAndCompute(img2, None)

# Brute Force Matching
bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)
matches = bf.match(des1, des2)
matches = sorted(matches, key=lambda x: x.distance)

matching_result = cv2.drawMatches(img1, kp1, img2, kp2, matches[:50], None, flags=2)

# cv2.imshow("Img1", img1)
# cv2.imshow("Img2", img2)
cv2.imshow("Matching result", matching_result)
cv2.waitKey(0)
cv2.destroyAllWindows()
