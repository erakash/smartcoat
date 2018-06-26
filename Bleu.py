import struct
from bluepy.btle import *

# callback class
class MyDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleNotification(self, cHandle, data):
        if (str(data.decode("utf-8"))):
            print(data.decode("utf-8"))
        
per = Peripheral("c8:df:84:2a:48:8d", "public")

try:
    per.setDelegate(MyDelegate())
    setup_data = b"\x01\x00"
    notify = per.getCharacteristics(uuid='0000ffe1-0000-1000-8000-00805f9b34fb')[0]
    notify_handle = notify.getHandle() + 1
    per.writeCharacteristic(notify_handle, setup_data, withResponse=True)
    c = per.getCharacteristics(uuid='0000ffe1-0000-1000-8000-00805f9b34fb')[0]

    while True:
        c.write(b"COMMAND1\n")
        c.write(b"READ\n")
        if per.waitForNotifications(1):
            continue
        
finally:
    per.disconnect()
