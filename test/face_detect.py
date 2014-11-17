import sys.os
import cv

def detectObject(image):
	size = cv.GetSize(image)
	grayscale = cv.CreateImage(size, 8, 1)
	cv.cvtColor(image, grayscale, cv.CV_BGR2GRAY)
	storage = cv.CreateMemStorage(0)
	cv.EqualizeHist(grayscale, grayscale)
	cascade = cv.Load("haarcascade_frontalface_alt.xml")
	faces = cv.HarrDetectObjects(grayscale, cascade, storage, 1.2, 2
								cv.CV_HAAR_DO_CANNY_PRUNING, (100, 100))								
	for i in faces:
		((x, y, w, h), d) = i
		cv.Rectangle(image, (int(x), int(y)),
					(int(x+w), int(y+h)),
					cv.CV_RGB(0, 255, 0), 3, 8, 0)

def displayObject(image):
	cv.ShowImage("face", image)
	cv.WaitKey(0)
	
if __name__ == "__main__":
	image = cv.LoadImage("face.png")
	detectObject(image)
	displayObject(image)
