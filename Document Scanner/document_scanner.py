import cv2 as cv
import numpy as np
from imutils.perspective import four_point_transform
from PIL import Image
from PIL import ImageTk
import easyocr
from spellchecker import SpellChecker
import tkinter as tk

WIDTH, HEIGHT = 800, 600
OCR_MODEL = 'craft_mlt_25k.pth'
IMAGE_NAME = 'test1.jpg'
OUTPUT_TXT = 'output.txt'
OUTPUT_WITH_SPELLCHECK = 'output_spellcheck.jpg'

class DocumentScanner:
    def __init__(self) -> None:
         self.doc_contour = np.array([[0,0],[WIDTH,0],[WIDTH,HEIGHT],[0,HEIGHT]])
         self.spell = SpellChecker()
         self.cap = cv.VideoCapture(1)
         self.cap.set(cv.CAP_PROP_FRAME_WIDTH, WIDTH) 
         self.cap.set(cv.CAP_PROP_FRAME_HEIGHT, HEIGHT)
         self.frame_copy = None
         self.frame = None

    def scan_detection(self,image):

        gray = cv.cvtColor(image,cv.COLOR_BGR2GRAY)
        blur = cv.GaussianBlur(gray, (5,5), 0)
        _, thresh = cv.threshold(blur, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)

        contours, _ = cv.findContours(thresh, cv.RETR_LIST, cv.CHAIN_APPROX_SIMPLE)
        contours = sorted(contours, key=cv.contourArea, reverse=True)

        max_area = 0
        for i in contours:
            area = cv.contourArea(i)
            if area > 5000:
                peri = cv.arcLength(i, True)
                approx = cv.approxPolyDP(i, 0.015 * peri, True)
                if area > max_area and len(approx) == 4:
                    self.doc_contour = approx
                    max_area = area 
        
        cv.drawContours(self.frame, [self.doc_contour], -1, (0,255,0), 4)

    def run(self):
        while True:
            _,self.frame = self.cap.read()
            self.frame_copy = self.frame.copy()

            self.scan_detection(self.frame_copy)
            cv.imshow("input", self.frame)

            if cv.waitKey(20) & 0xFF == 27:
                break
        cv.destroyAllWindows()
        self.cap.release()
    
    def take_snapshot(self):
        warped = four_point_transform(self.frame_copy, self.doc_contour.reshape(4,2))
        gray = cv.cvtColor(warped,cv.COLOR_BGR2GRAY)
        _, thresh = cv.threshold(gray, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)
    
        filename =  IMAGE_NAME
        cv.imwrite(filename, thresh)
        return thresh 
    
    def txt_detection(self):
        reader = easyocr.Reader(['en'], gpu=True, download_enabled=False, model_storage_directory='./')

        result = reader.readtext(IMAGE_NAME)

        f = open(OUTPUT_TXT, "w")

        for detection in result:
            value = detection[1]
            f.write(value + "\n")
        
        f.close()
        

    def spell_check(self):
        reader = easyocr.Reader(['en'], gpu=True, download_enabled=False, model_storage_directory='./')

        # Read the image
        image = cv.imread(IMAGE_NAME)
        result = reader.readtext(IMAGE_NAME)

        f = open(OUTPUT_TXT, "w")

        for detection in result:
            value = detection[1]
            f.write(value + "\n")
        
        f.close()

        for detection in result:
            box = detection[0]
            value = detection[1].lower()
            ans = self.spell.correction(value)
           
            if (value == ans):
                cv.rectangle(image, (int(box[0][0]), int(box[0][1])), (int(box[2][0]), int(box[2][1])), (0, 255, 0), 2)
            else:
                cv.rectangle(image, (int(box[0][0]), int(box[0][1])), (int(box[2][0]), int(box[2][1])), (0, 0, 255), 2)
                cv.putText(image,ans,(int(box[0][0])-10, int(box[0][1])-20),cv.FONT_HERSHEY_SIMPLEX,1,(255,0,0),2,cv.LINE_AA)    

        cv.imwrite(OUTPUT_WITH_SPELLCHECK, image)
        return image

class GUI:
    def __init__(self) -> None:
        self.doc_scanner = DocumentScanner()
        # Here's the frame

        self.root = tk.Tk()
        self.root.title("Document Scanner")
        root_width = self.root.winfo_screenwidth()
        self.root.geometry("%dx900" % root_width)

        # create a frame to hold the video feed and pack it to the left of the window
        self.main_frame = tk.Frame(self.root, bd=1, relief=tk.RAISED)
        self.main_frame.pack()

        # create the canvas and pack it into the video frame
        self.video_feed = tk.Canvas(self.main_frame, width=800, height=600)
        self.video_feed.pack(side=tk.LEFT)

        # create an empty frame and pack it to the right of the window
        self.empty_frame = tk.Label(self.main_frame, bd=1, relief=tk.RAISED)
        self.empty_frame.pack(side=tk.RIGHT)

        # create a frame to hold the buttons and pack it at the bottom of the window
        self.toolbar = tk.Frame(self.root, bd=1, relief=tk.RAISED)
        self.toolbar.pack(side=tk.BOTTOM, fill=tk.X)

        # create three buttons and add them to the toolbar
        btn1 = tk.Button(self.toolbar, text="Save", command=self.save, width=10, height=2)
        btn1.pack(side=tk.LEFT, padx=50, pady=10)

        btn2 = tk.Button(self.toolbar, text="Detect Text", command=self.doc_scanner.txt_detection, width=10, height=2)
        btn2.pack(side=tk.LEFT, padx=50, pady=10)

        btn3 = tk.Button(self.toolbar, text="SpellCheck",command=self.spell_check, width=10, height=2)
        btn3.pack(side=tk.LEFT, padx=50, pady=10)

        self.run()

    def save(self):
        img = self.doc_scanner.take_snapshot()

        img = cv.resize(img, (400,600))
        img = Image.fromarray(img)
        img = ImageTk.PhotoImage(img)
        self.empty_frame.image = img
        self.empty_frame.configure(image=self.empty_frame.image)

    def spell_check(self):
        img = self.doc_scanner.spell_check()

        img = cv.resize(img, (400,600))
        img = Image.fromarray(img)
        img = ImageTk.PhotoImage(img)
        self.empty_frame.image = img
        self.empty_frame.configure(image=self.empty_frame.image)
    
    def run(self):
        while True:
            _,self.doc_scanner.frame = self.doc_scanner.cap.read()
            self.doc_scanner.frame_copy = self.doc_scanner.frame.copy()

            self.doc_scanner.scan_detection(self.doc_scanner.frame_copy)
            img = cv.cvtColor(self.doc_scanner.frame, cv.COLOR_BGR2RGB)
            img = cv.resize(img, (800, 600))
            img = Image.fromarray(img)
            img = ImageTk.PhotoImage(img)

            self.video_feed.create_image(0, 0, anchor=tk.NW, image=img)
            self.root.update()
            
            if cv.waitKey(20) & 0xFF == 27:
                break
        cv.destroyAllWindows()
        self.doc_scanner.cap.release()
        self.root.quit() 

gui = GUI()