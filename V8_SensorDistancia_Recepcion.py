import serial
import time
from turtle import *

                
def grafico(dis):
    x1 = 217-233-dis
    x4 = 217-dis
    x3 = x4
    x2 = x1

    y1 = -69
    y2 = 69
    y4 = y1
    y3 = y2
    setup (434, 200, 0, 0)
    screensize(433, 200 )
    title("EL TWIZY QUE APARCA")
    hideturtle()

    pencolor("red")
    pensize(5)
    begin_fill()
    goto (x4, y1)
    goto (x3, y3)
    goto (x2, y2)
    goto (x1, y1)
    end_fill
    return


arduino=serial.Serial('/dev/ttyUSB0', baudrate=9600, timeout = 3.0)
"""arduino.open()"""
txt=''

while True:
	
	time.sleep(0.01)
	while arduino.inWaiting()>0:
		txt += arduino.read(1)
		distancia = arduino.read(1)
		if distancia > 2:
                    distancia = 2
                    
		grafico(distancia)
		
		print txt
		txt = ''

	


                arduino.close()











