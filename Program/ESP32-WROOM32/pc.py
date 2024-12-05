import socket

# ESP32のIPアドレス
esp32_ip = "192.168.4.1"
port = 8000

# ESP32に接続
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((esp32_ip, port))

while True:      
      # データを受信して表示
      response = client.recv(4096)
      print(response.decode())
