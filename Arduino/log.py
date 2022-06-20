from base64 import decode
from tempfile import tempdir
import serial
import string
import requests
import json
import datetime
import time

ser = serial.Serial("COM5", 9600)
url = "http://graw.io/api/data/upload"
apikey = "IHatePython"
while True:
     incomingdata = ser.readline().decode('utf-8').strip()
     list = incomingdata.split(',')

     temp = int(list[0])
     humid = int(list[1])
     light = int(list[2])

     headers = {"Content-Type": "application/json"}

     datajson = {
  "acess": apikey,
  "data": 
  {
    "date": str(datetime.datetime.utcnow()),
    "temperature": temp,
    "humidity": humid,
    "brightness": light
  }
  }


     test = json.dumps(datajson)
     #print(test)
     r = requests.post(url, test, headers=headers)
     print(r.status_code)
     #print(r.headers)
     print(list[0])
     print(list[1])
     print(list[2])
     time.sleep(60)

     
