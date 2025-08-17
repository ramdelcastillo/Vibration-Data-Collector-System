import serial, csv, json, os
from datetime import datetime

filename = f'vibration_logs_{datetime.now().strftime("%Y%m%d_%H%M%S")}.csv'
filename2 = f'temphumid_logs_{datetime.now().strftime("%Y%m%d_%H%M%S")}.csv'

serport = serial.Serial('COM8', 115200)

firsttime = None
firsttime2 = None

with open(filename, 'w', newline='') as csvfile:
    fieldnames = ['time', 'x', 'y', 'z']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    try:
        while True:
            buffer = serport.readline().decode().strip()
            try:
                data = json.loads(buffer)

                if firsttime is None:
                    firsttime = data['time']

                adjusted_time = data['time'] - firsttime
                data['time'] = adjusted_time

                print(f"Data: {data}")

                writer.writerow(data)
            except json.JSONDecodeError as e:
                continue

    except KeyboardInterrupt:
        pass
    finally:
        serport.close()

print(f"Program stopped. The CSV file is saved in {os.path.abspath(filename)}.")