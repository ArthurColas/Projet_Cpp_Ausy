import smbus
import time
 
BUS_NUM = 1  # généralement 1 pour les nouveaux Raspberry Pi
UPS_ADDRESS = 0x17  # l'adresse I2C de votre UPS
is_charging = 'False'
lastIsError = False
bus = smbus.SMBus(BUS_NUM)
 
 
try:
 
    percent1 = bus.read_byte_data(UPS_ADDRESS, 0x13)
    percent2 = bus.read_byte_data(UPS_ADDRESS, 0x14)
 
    charg1_c = bus.read_byte_data(UPS_ADDRESS, 0x07)
    charg2_c = bus.read_byte_data(UPS_ADDRESS, 0x08)
 
    percent = percent2 << 8 | percent1
    charg = charg2_c << 8 | charg1_c
 
    if(charg > 500):
        is_charging = 'True'
    else:
        is_charging = 'False'
    print("Pourcent de batterie : ",percent , " % --------------- En charge : ", is_charging)
 
 
 
 
 
 
 
except Exception as e:
   if not lastIsError:
            print('Error obtaining powerplant info: ' + str(e))
            lastIsError = True

