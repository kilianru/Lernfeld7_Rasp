import serial
import time
import mysql.connector as database
from datetime import datetime

try:
    connection = database.connect(
        user="root",
        password="99Luca99.",
        host="localhost",
        port=3306,
        database="krautundrueben")
except database.Error as e:
    print(f"Error connecting to MariaDB Platform: {e}")
cursor = connection.cursor()
# adapt name (baud rate has to be the same than in the arduino sketch)
s = serial.Serial('/dev/ttyACM0', 9600)
DATUM = datetime.now().date()
ZEIT = datetime.now().time()

# Arduino resets after a serial connection
print("Waiting 5s for Arduino...")
time.sleep(5)

try:
    while True:
        print("Add Data to Database...")
        response = s.readline()
        temp = str(response).replace("b'", "")
        temp2 = temp[:-5]
        Luftfeuchtigkeit, Temperatur, level, Bodenfeuchtigkeit = temp2.split(",")
        statment = "INSERT INTO krautundrueben.MESSWERTE (DATUM, ZEIT, LUFTFEUCHTIGKEIT, TEMPERATUR, WASSERSTAND, BODENFEUCHTIGKEIT) VALUES (%s,%s,%s,%s,%s,%s)"
        data = (DATUM, ZEIT, Luftfeuchtigkeit, Temperatur, level, Bodenfeuchtigkeit )
        cursor.execute(statment, data)
        connection.commit()
        print("Successfully!")


except KeyboardInterrupt:
    s.close()