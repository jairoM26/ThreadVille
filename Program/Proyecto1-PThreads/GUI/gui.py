from tkinter import *
import os
from threading import Thread
import threading
import random
import time
from datetime import datetime
import tkinter.scrolledtext as tkst

'''
* CONSTANTS
'''
TIMEOUT = 1
DATA_PATH = "../data.txt"

'''
*  load_img
*  Method that allows the load of an image (png or gif) file.
*  @param name: the name of the file that is inside the imgs directory
*  @returns img: the img load in the respective memory space
'''
def load_img(name):
    path = os.path.join("images",name)
    img = PhotoImage(file = path)
    return img

'''
*  start mainWindow
*  Creates the main program window
*  Also holds the methods for the simulator logic, such as the movement
*  of the cars, status of the traffic lights and police officer position.
'''

def startWindow():
    mainWindow = Tk()
    mainWindow.title("Threadville")
    mainWindow.minsize(400,400)
    mainWindow.resizable(width=False,height=False)
    mainWindow.geometry("801x676")    

    #Creation of the canvas for the simulation objects
    contenedor = Canvas(mainWindow, width=1100, height=650, bg="#FFFFFF")
    contenedor.place(x=-1,y=-1)
    backgroundImage = load_img("background.png")

    contenedor.create_image(0,0,image=backgroundImage,anchor=NW)

    #Images files load
    carLeftImage = load_img("carDer.png")
    carRightImage = load_img("carIzq.png")
    ambulanceLeftImage = load_img("ambDer.png")
    ambulanceRightImage = load_img("ambIzq.png")
    radioactiveLeftImage = load_img("radioactiveDer.png")
    radioactiveRightImage = load_img("radioactiveIzq.png")
    emptyImage = load_img("null.png")    
    redLightImage = load_img("redLight.png")
    greenLightImage = load_img("greenLight.png")
    officerStopImage = load_img("stop.png")
    officerGoImage = load_img("go.png")
    takeCareSignImage = load_img("road-sign.png")
    notAllowedImage = load_img("roadsign.png")

    #Definition and positions of the images objects

    ############################ Bridge 1 ##################################

    ## BRIDGE 1 Right Queue
    b1_r1 = contenedor.create_image(575,215,image=emptyImage,anchor=NW)
    b1_r2 = contenedor.create_image(630,215,image=emptyImage,anchor=NW)
    b1_r3 = contenedor.create_image(690,215,image=emptyImage,anchor=NW)
    b1_r4 = contenedor.create_image(750,215,image=emptyImage,anchor=NW)
    b1_rr = contenedor.create_image(575,160,image=emptyImage,anchor=NW)   #LUZ SALIDA

    ## BRIDGE 1 inside Bridge
    b1_c1  = contenedor.create_image(500,190,image=emptyImage,anchor=NW)
    b1_c2  = contenedor.create_image(445,190,image=emptyImage,anchor=NW)
    b1_c3  = contenedor.create_image(385,190,image=emptyImage,anchor=NW)    
    b1_c4  = contenedor.create_image(330,190,image=emptyImage,anchor=NW)                                    
    b1_c5  = contenedor.create_image(280,190,image=emptyImage,anchor=NW)  #LUZ SALIDA

    ## BRIDGE 1 Left Queue
    b1_l1  = contenedor.create_image(190,215,image=emptyImage,anchor=NW)
    b1_l2  = contenedor.create_image(130,215,image=emptyImage,anchor=NW)
    b1_l3  = contenedor.create_image(60,215,image=emptyImage,anchor=NW)
    b1_l4  = contenedor.create_image(0,215,image=emptyImage,anchor=NW)
    b1_ll  = contenedor.create_image(190,160,image=emptyImage,anchor=NW)
                                    #190,170
    

    ############################ Bridge 2 ##################################

    ## Right Queue
    b2_r1  = contenedor.create_image(575,345,image=emptyImage,anchor=NW)
    b2_r2  = contenedor.create_image(630,345,image=emptyImage,anchor=NW)
    b2_r3  = contenedor.create_image(690,345,image=emptyImage,anchor=NW)
    b2_r4  = contenedor.create_image(750,345,image=emptyImage,anchor=NW)
    b2_rr  = contenedor.create_image(575,295,image=emptyImage,anchor=NW)

    ## Inside Bridge
    b2_c1  = contenedor.create_image(500,320,image=emptyImage,anchor=NW)
    b2_c2  = contenedor.create_image(445,320,image=emptyImage,anchor=NW)
    b2_c3  = contenedor.create_image(385,320,image=emptyImage,anchor=NW)
    b2_c4  = contenedor.create_image(330,320,image=emptyImage,anchor=NW)
    b2_c5  = contenedor.create_image(280,320,image=emptyImage,anchor=NW)

    
    ## Left Queue
    b2_l1  = contenedor.create_image(190,345,image=emptyImage,anchor=NW)
    b2_l2  = contenedor.create_image(130,345,image=emptyImage,anchor=NW)
    b2_l3  = contenedor.create_image(60,345,image=emptyImage,anchor=NW)
    b2_l4  = contenedor.create_image(0,345,image=emptyImage,anchor=NW)
    b2_ll  = contenedor.create_image(190,295,image=emptyImage,anchor=NW)
                                    #190,300
    ############################ Bridge 3 ##################################

    ## Right Queue
    b3_r1  = contenedor.create_image(575,485,image=emptyImage,anchor=NW)
    b3_r2  = contenedor.create_image(630,485,image=emptyImage,anchor=NW)
    b3_r3  = contenedor.create_image(690,485,image=emptyImage,anchor=NW)
    b3_r4  = contenedor.create_image(750,485,image=emptyImage,anchor=NW)
    b3_rr  = contenedor.create_image(575,430,image=emptyImage,anchor=NW)

    ## Inside Bridge
    b3_c1  = contenedor.create_image(500,460,image=emptyImage,anchor=NW)
    b3_c2  = contenedor.create_image(445,460,image=emptyImage,anchor=NW)
    b3_c3  = contenedor.create_image(385,460,image=emptyImage,anchor=NW)
    b3_c4  = contenedor.create_image(330,460,image=emptyImage,anchor=NW)
    b3_c5  = contenedor.create_image(280,460,image=emptyImage,anchor=NW)

    #### Left Queue
    b3_l1  = contenedor.create_image(190,485,image=emptyImage,anchor=NW)
    b3_l2  = contenedor.create_image(130,485,image=emptyImage,anchor=NW)
    b3_l3  = contenedor.create_image(60,485,image=emptyImage,anchor=NW)
    b3_l4  = contenedor.create_image(0,485,image=emptyImage,anchor=NW)
    b3_ll  = contenedor.create_image(190,430,image=emptyImage,anchor=NW)
                                    #190, 435
    #b1_police = contenedor.create_image(535,-1,image=imgPoliceRight,anchor=NW)
    #b2_police = contenedor.create_image(535,210,image=imgPoliceRight,anchor=NW)
    #b3_police = contenedor.create_image(535,415,image=imgPoliceRight,anchor=NW)

    #Variables for the current waiting cars at each side of the bridges
    #global txt_b1a,txt_b1b,txt_b2a,txt_b2b,txt_b3a,txt_b3b

    global bridge1_type,bridge2_type,bridge3_type,bridge1_status,bridge2_status,bridge3_status
    bridge1_type   = 0
    bridge2_type   = 0
    bridge3_type   = 0
    bridge1_status = 0
    bridge2_status = 0
    bridge3_status = 0

    bridge1 = [b1_l4,b1_l3,b1_l2,b1_l1,b1_ll,b1_c5,b1_c4,b1_c3,b1_c2,b1_c1,b1_rr,b1_r1,b1_r2,b1_r3,b1_r4]
    bridge2 = [b2_l4,b2_l3,b2_l2,b2_l1,b2_ll,b2_c5,b2_c4,b2_c3,b2_c2,b2_c1,b2_rr,b2_r1,b2_r2,b2_r3,b2_r4]
    bridge3 = [b3_l4,b3_l3,b3_l2,b3_l1,b3_ll,b3_c5,b3_c4,b3_c3,b3_c2,b3_c1,b3_rr,b3_r1,b3_r2,b3_r3,b3_r4]
    bridge1_data = ['n','n','n','n','n','n','n','n','n','n','n','n','n','n','n']
    bridge2_data = ['n','n','n','n','n','n','n','n','n','n','n','n','n','n','n']
    bridge3_data = ['n','n','n','n','n','n','n','n','n','n','n','n','n','n','n']
    
    '''
    * Method that handles the movement of the cars in the bridges
    * the status of the traffic lights and police officers (if available)
    '''
    def moveBridges():
        global bridge1_old,bridge1_new
        #global txt_b1a,txt_b1b,txt_b2a,txt_b2b,txt_b3a,txt_b3b
        
        
        while(True):
            for i in range(0,len(bridge1)):
                if(bridge1_data[i] == 'n'):
                    contenedor.itemconfig(bridge1[i], image = emptyImage)
                elif(bridge1_data[i] == 'c'):
                    contenedor.itemconfig(bridge1[i], image = carRightImage)
                elif(bridge1_data[i] == 'a'):
                    contenedor.itemconfig(bridge1[i], image = ambulanceRightImage)
                elif(bridge1_data[i] == 'r'):
                    contenedor.itemconfig(bridge1[i], image = radioactiveRightImage)
                elif(bridge1_data[i] == 'C'):
                    contenedor.itemconfig(bridge1[i], image = carLeftImage)
                elif(bridge1_data[i] == 'A'):
                    contenedor.itemconfig(bridge1[i], image = ambulanceLeftImage)
                elif(bridge1_data[i] == 'R'):
                    contenedor.itemconfig(bridge1[i], image = radioactiveLeftImage)
                elif(bridge1_data[i] == '1'):
                    contenedor.itemconfig(bridge1[i], image = greenLightImage)
                elif(bridge1_data[i] == '0'):
                    contenedor.itemconfig(bridge1[i], image = redLightImage)

                #Changes by the type of the bridge    
                if(bridge1_type == '0'):                    
                    if(bridge1_data[i] == '1'):
                        contenedor.itemconfig(bridge1[i], image = greenLightImage)
                    elif(bridge1_data[i] == '0'):
                        contenedor.itemconfig(bridge1[i], image = redLightImage)
                elif(bridge1_type == '1'):    
                    if(bridge1_data[i] == '1'):
                        contenedor.itemconfig(bridge1[i], image = officerGoImage)
                    elif(bridge1_data[i] == '0'):
                        contenedor.itemconfig(bridge1[i], image = officerStopImage)
                elif(bridge1_type == '2'):    
                    if(bridge1_data[i] == '1'):
                        contenedor.itemconfig(bridge1[i], image = takeCareSignImage)
                    elif(bridge1_data[i] == '0'):
                        contenedor.itemconfig(bridge1[i], image = notAllowedImage)

            for i in range(0,len(bridge2)):
                if(bridge2_data[i] == 'n'):
                    contenedor.itemconfig(bridge2[i], image = emptyImage)
                elif(bridge2_data[i] == 'c'):
                    contenedor.itemconfig(bridge2[i], image = carRightImage)
                elif(bridge2_data[i] == 'a'):
                    contenedor.itemconfig(bridge2[i], image = ambulanceRightImage)
                elif(bridge2_data[i] == 'r'):
                    contenedor.itemconfig(bridge2[i], image = radioactiveRightImage)
                elif(bridge2_data[i] == 'C'):
                    contenedor.itemconfig(bridge2[i], image = carLeftImage)
                elif(bridge2_data[i] == 'A'):
                    contenedor.itemconfig(bridge2[i], image = ambulanceLeftImage)
                elif(bridge2_data[i] == 'R'):
                    contenedor.itemconfig(bridge2[i], image = radioactiveLeftImage)

                #Changes by the type of the bridge    
                if(bridge2_type == '0'):                    
                    if(bridge2_data[i] == '1'):
                        contenedor.itemconfig(bridge2[i], image = greenLightImage)
                    elif(bridge2_data[i] == '0'):
                        contenedor.itemconfig(bridge2[i], image = redLightImage)
                elif(bridge2_type == '1'):    
                    if(bridge2_data[i] == '1'):
                        contenedor.itemconfig(bridge2[i], image = officerGoImage)
                    elif(bridge2_data[i] == '0'):
                        contenedor.itemconfig(bridge2[i], image = officerStopImage)
                elif(bridge2_type == '2'):    
                    if(bridge2_data[i] == '1'):
                        contenedor.itemconfig(bridge2[i], image = takeCareSignImage)
                    elif(bridge2_data[i] == '0'):
                        contenedor.itemconfig(bridge2[i], image = notAllowedImage)

                
            for i in range(0,len(bridge3)):
                if(bridge3_data[i] == 'n'):
                    contenedor.itemconfig(bridge3[i], image = emptyImage)
                elif(bridge3_data[i] == 'c'):
                    contenedor.itemconfig(bridge3[i], image = carRightImage)
                elif(bridge3_data[i] == 'a'):
                    contenedor.itemconfig(bridge3[i], image = ambulanceRightImage)
                elif(bridge3_data[i] == 'r'):
                    contenedor.itemconfig(bridge3[i], image = radioactiveRightImage)
                elif(bridge3_data[i] == 'C'):
                    contenedor.itemconfig(bridge3[i], image = carLeftImage)
                elif(bridge3_data[i] == 'A'):
                    contenedor.itemconfig(bridge3[i], image = ambulanceLeftImage)
                elif(bridge3_data[i] == 'R'):
                    contenedor.itemconfig(bridge3[i], image = radioactiveLeftImage)
                elif(bridge3_data[i] == '1'):
                    contenedor.itemconfig(bridge3[i], image = greenLightImage)
                elif(bridge3_data[i] == '0'):
                    contenedor.itemconfig(bridge3[i], image = redLightImage)

                #Changes by the type of the bridge    
                if(bridge3_type == '0'):                    
                    if(bridge3_data[i] == '1'):
                        contenedor.itemconfig(bridge3[i], image = greenLightImage)
                    elif(bridge3_data[i] == '0'):
                        contenedor.itemconfig(bridge3[i], image = redLightImage)
                elif(bridge3_type == '1'):    
                    if(bridge3_data[i] == '1'):
                        contenedor.itemconfig(bridge3[i], image = officerGoImage)
                    elif(bridge3_data[i] == '0'):
                        contenedor.itemconfig(bridge3[i], image = officerStopImage)
                elif(bridge3_type == '2'):    
                    if(bridge3_data[i] == '1'):
                        contenedor.itemconfig(bridge3[i], image = takeCareSignImage)
                    elif(bridge3_data[i] == '0'):
                        contenedor.itemconfig(bridge3[i], image = notAllowedImage)

            time.sleep(TIMEOUT) 

    '''
    * Method that read the input data from the file specified in the
    * variable DATA_PATH, and loads the data in the variables needed by
    * the program to show the simulation on the screen
    '''
    def readInput():        
        global bridge1_type,bridge2_type,bridge3_type,bridge1_status,bridge2_status,bridge3_status
        while(True):
            file = open(DATA_PATH, "r")
            readData = file.readline()
            bridgesData = readData.split("#") #Data separated by bridge
            
            #Data from the bridges
            bridge1_predata = (bridgesData[0].split(':'))#bridge1
            bridge2_predata = (bridgesData[1].split(':'))#bridge2
            bridge3_predata = (bridgesData[2].split(':'))#bridge3
            
            bridge1_type = bridge1_predata[0] + '' 
            bridge2_type = bridge2_predata[0] + '' 
            bridge3_type = bridge3_predata[0] + ''

            bridge1_str = bridge1_predata[1]#Bridge1's Cars positions and car type
            bridge2_str = bridge2_predata[1]#Bridge2's Cars positions and car type
            bridge3_str = bridge3_predata[1]#Bridge3's Cars positions and car type

            #Update the data for all the bridges about the waiting cars outside the simulation fieldview            
                        
            #Separes the string into an array for an easier data inspection when needed
            for i in range(0,len(bridge1_str)):
                
                bridge1_data[i] = bridge1_str[i]+''
                bridge2_data[i] = bridge2_str[i]+''
                bridge3_data[i] = bridge3_str[i]+''
            
            """print(bridge1_type)
            print(bridge2_type)
            print(bridge3_type)"""
            file.close()
            #Sleep
            time.sleep(TIMEOUT)
    
    #Threads needed for the GUI
    t= Thread(target=moveBridges, args=())
    t.start()
    t2= Thread(target=readInput, args=())
    t2.start()    

    mainWindow.mainloop()


startWindow()

