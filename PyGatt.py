import pygatt
from binascii import b2a_uu
import time

adapter = pygatt.GATTToolBackend()
SensorJsonValue = ""

def handle_data(handle, value):
    """
    handle -- integer, characteristic read handle the data was received on
    value -- bytearray, the data returned in the notification
    """
    global SensorJsonValue
    if not value.decode("utf-8").endswith("}"):
        SensorJsonValue = SensorJsonValue + value.decode("utf-8")
    else:
        SensorJsonValue = SensorJsonValue + value.decode("utf-8")
        print(SensorJsonValue)
        SensorJsonValue = ""
#print("Received data: %s"% value.decode("utf-8"))

try:
    adapter.start()
    device = adapter.connect('c8:df:84:2a:48:8d')
    device.subscribe("0000ffe1-0000-1000-8000-00805f9b34fb",
                     callback=handle_data)
    while True:
        device.char_write("0000ffe1-0000-1000-8000-00805f9b34fb",b"READ\n",wait_for_response=False)
        device.char_write("0000ffe1-0000-1000-8000-00805f9b34fb",b"COMMAND1\n",wait_for_response=False)
        time.sleep(0.1)
finally:
    adapter.stop()
