__author__ = 'sbeltran'

import forecastio
import time
import serial
from multiprocessing import Pool

###############################################################################
# Code needs to get data from weather sources
# as well as control thermostat system on Honeywell
# MSP TASK:
#   - Get current state
#   - Report to Communicator program. All work should be done on the MSP front
#   - Request information as needed from the communicator program
###############################################################################

######## CHARACTER MAP #########
# r : POOR WEATHER CONDITIONS
# g : NORMAL WEATHER CONDITIONS
# o : TEMPERATURE UNIT IS "ON"
# f : TEMPERATURE UNIT IS "OFF"
# < to Z (ASCII MAP) TEMPERATURE VALUE IN DEGREES F
#
################################

# Weather API details
api_key = "4ce266bf131d9db5244d447812c8afc1"
lat = -42.3496
lng = 71.0997

homeTempArray = [65, 70, 70, 70, 68, 66, 65, 63, 64, 65, 67, 68, 70, 70, 70, 71, 74, 76, 78, 78, 78, 70]
forecast = forecastio.load_forecast(api_key, lat, lng, units='us')
bluetoothSerial = serial.Serial( "/dev/tty.HC-06-DevB", baudrate=9600)

def readSerial():
    return bluetoothSerial.readline()


def getWeatherSimple():
    byHour = forecast.hourly()
    weather_icon = byHour.icon

    #for hourlyData in byHour.data:
    #    print hourlyData.temperature

    if weather_icon is "rain" or "snow" or "sleet" or "hail":
        # Character code for poor weather conditions outside
        return "r"
    else:
        return "g"


def getTEMPStatus():
    i = 0
    while i < len(homeTempArray):
        time.sleep(40)
        weatherStatus = getWeatherSimple()
        temperature = str(unichr(homeTempArray[0]))
        i += 1
        bluetoothSerial.write(temperature)
        bluetoothSerial.write(weatherStatus)
    getTEMPStatus()

#getTEMPStatus()

bluetoothSerial.write("A")
time.sleep(10)
bluetoothSerial.write("B")
print bluetoothSerial.read()
time.sleep(10)
bluetoothSerial.write("F")




