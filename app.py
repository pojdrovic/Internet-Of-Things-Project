__author__ = 'sbeltran'

from flask import Flask
from flask import jsonify
from flask import request
import serial

homeTempArray = [65, 70, 70, 70, 68, 66, 65, 63, 64, 65, 67, 68, 70, 70, 70, 71, 74, 76, 78, 78, 78, 70]
#Connect to Bluetooth Module
try:
    bluetoothSerial = serial.Serial( "/dev/tty.HC-06-DevB", baudrate=9600)
except:
    exit(1)

# Initialize base variables
systemStatus = 0
systemTemperature = homeTempArray[0]
systemSetTemperature = 70

app = Flask(__name__)

@app.route('/')
def hello_world():
    bluetoothSerial.write("B")
    msg = bluetoothSerial.read()
    return "Hello World" + msg

@app.route('/get_temperature')
def get_temperature():
    return jsonify(temp="70")

@app.route('/get_status')
def get_status():
    return jsonify(status=systemStatus, temp=systemTemperature)

@app.route('/post_systempower')
def post_system_power():
    state = request.args.get('state')
    #If off send 'f' else turn on 'o'
    if state == "f":
        bluetoothSerial.write("f")
        msg = bluetoothSerial.read()
    else:
        bluetoothSerial.write("o")
        msg = bluetoothSerial.read()

    msg = getResponseMessage(msg)

    return jsonify(status=systemStatus, temp=systemTemperature)

@app.route('/post_on')
def post_system_power_on():
    bluetoothSerial.write("o")
    return jsonify(status=systemStatus, temp=systemTemperature)


@app.route('/post_temp')
def post_system_temp():
    bluetoothSerial.write("o")
    return jsonify(status=systemStatus, temp=systemTemperature)


if __name__ == '__main__':
    app.run()
