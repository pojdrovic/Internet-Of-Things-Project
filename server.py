from flask import Flask
from flask import render_template
from flask import jsonify, request, redirect
import serial
import random

import threading, Queue

import logging
logging.basicConfig(filename=__file__.replace('.py','.log'),level=logging.DEBUG,format='%(asctime)s [%(name)s.%(funcName)s] %(levelname)s: %(message)s', datefmt='%m/%d/%Y %I:%M:%S %p', filemode='a')

browserButton = None

class BTSerialThread(threading.Thread):
    def __init__(self, dataQ, errQ, port=None, baudrate=None):
        self.logger = logging.getLogger('BTSerialThread')
        self.logger.debug('initializing')
        threading.Thread.__init__(self)
        self.ser = serial.Serial()
        self.ser.timeout = None
        if port is None:
            self.ser.port = "/dev/tty.HC-06-DevB"
        else:
            self.ser.port = port
        if baudrate is None:
            self.baudrate = 9600
        else:
            self.baudrate = baudrate
        self.sleepDurSec = 5
        self.dataQ = dataQ
        self.errQ = errQ
        self.keepAlive = True
        self.stoprequest = threading.Event()
        self.setDaemon(True)
        self.dat = ''
        self.inputStarted = False
        self.blankfirst = 0
        self.homeTemps = ['A','a','w', '?', 'M', ']', '+', 'P', ';', 'r']
        self.browserControl = False
        self.browserTemp = None

    def run(self):
        self.logger.debug('running')
        dataIn = False
        while not self.stoprequest.isSet():
            try:
                self.ser.open()
            except:
                exit(2)
            #time.sleep(self.sleepDurSec)
            while self.keepAlive:
                dat = ''
                if (self.blankfirst == 0) or self.browserControl:
                    if self.browserTemp is None:
                        self.ser.write(random.choice(self.homeTemps))
                    else:
                        self.ser.write(self.browserTemp)
                    self.browserControl = False
                    self.browserTemp = None
                    self.blankfirst = 1
                while dat == '':
                    bytesToRead = self.ser.inWaiting()
                    dat = self.ser.read(bytesToRead)
                print ("IN: " + dat)
                #    dat = self.ser.readline()
                self.dataQ.put(dat)
                self.logger.debug('reading' + dat)
            self.inputStarted = True
            self.dat.close()
            self.close()
            self.join_fin()



app = Flask(__name__, static_folder="public", template_folder="templates")

dataQ = Queue.Queue()
errQ = Queue.Queue()
ser = BTSerialThread(dataQ, errQ)
ser.daemon = True
ser.start()

@app.route("/")
def index():
    return render_template('master.html')

@app.route("/reset")
def reset():
    ser.browserControl = True
    return redirect("/")

@app.route("/set_temp")
def settemp():
    temp = request.args.get('temp')
    ser.browserTemp = chr(int(temp))
    ser.browserControl = True
    return redirect("/")


@app.route("/temp")
def tempcontrol():
    temp = read_from_serial()
    tempHold = ''
    try:
        temp = ord(temp)
        tempHold = temp
    except:
        temp = tempHold

    if temp == 70:
        return jsonify(status="off", temp=temp)
    else:
        return jsonify(status="on", temp=temp)


def read_from_serial():
        a = dataQ.get()
        print str(a)
        return a


if __name__ == '__main__':
    app.run()