import sys
import socket
from PySide6.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget
from PySide6.QtCore import QTimer, Qt
from PySide6.QtGui import QPainter, QColor

class RobotDataReceiver:
    """
    ロボットからデータを受信するクラス。
    Wi-Fi経由でESP32からデータを受信します。
    """
    def __init__(self, esp32_ip="192.168.4.1", port=8000):
        self.esp32_ip = esp32_ip
        self.port = port
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connected = False

    def connect(self):
        try:
            self.client.connect((self.esp32_ip, self.port))
            self.connected = True
        except Exception as e:
            print(f"Error connecting to ESP32: {e}")
            self.connected = False

    def get_data(self):
        if not self.connected:
            return None

        try:
            self.client.sendall(b"GET_DATA")  # 必要に応じてコマンドを送信
            response = self.client.recv(4096).decode('utf-8')
            # 受信データを辞書にパース（例: "10,-20,50,45,52.3,120.5"）
            data_parts = response.split(',')
            return {
                "line_position": float(data_parts[0]),
                "left_motor_target_speed": float(data_parts[1]),
                "left_motor_actual_speed": float(data_parts[2]),
                "right_motor_target_speed": float(data_parts[3]),
                "right_motor_actual_speed": float(data_parts[4]),
                "elapsed_time": float(data_parts[5])
            }
        except Exception as e:
            print(f"Error receiving data: {e}")
            self.connected = False
            return None

class LinePositionWidget(QWidget):
    """
    ラインの位置をアニメーションで表示するウィジェット。
    """
    def __init__(self):
        super().__init__()
        self.line_position = 0  # 初期位置

    def set_position(self, position):
        self.line_position = position
        self.update()  # 再描画を要求

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        # 背景を塗りつぶす
        painter.fillRect(self.rect(), QColor(240, 240, 240))

        # ウィジェットの幅と高さを取得
        width = self.width()
        height = self.height()

        # 中心線を描画
        center_x = width // 2
        painter.setPen(Qt.gray)
        painter.drawLine(center_x, 0, center_x, height)

        # ラインの位置を描画
        circle_x = center_x + int(self.line_position * (width / 100))  # -50mm〜50mmをウィジェット幅にマッピング
        circle_y = height // 2
        radius = 10

        painter.setBrush(QColor(255, 0, 0))
        painter.setPen(Qt.NoPen)
        painter.drawEllipse(circle_x - radius, circle_y - radius, radius * 2, radius * 2)

class RobotDataGUI(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Robot Data Viewer")

        # レイアウトとウィジェットの作成
        self.central_widget = QWidget()
        self.layout = QVBoxLayout()

        self.connection_status_label = QLabel("Connecting...")
        self.line_position_widget = LinePositionWidget()
        self.line_position_widget.setMinimumHeight(100)

        self.label_left_motor = QLabel("Left Motor: Target N/A, Actual N/A")
        self.label_right_motor = QLabel("Right Motor: Target N/A, Actual N/A")
        self.label_elapsed_time = QLabel("Elapsed Time: N/A")

        self.layout.addWidget(self.connection_status_label)
        self.layout.addWidget(self.line_position_widget)
        self.layout.addWidget(self.label_left_motor)
        self.layout.addWidget(self.label_right_motor)
        self.layout.addWidget(self.label_elapsed_time)

        self.central_widget.setLayout(self.layout)
        self.setCentralWidget(self.central_widget)

        # データ受信クラスのインスタンスを作成
        self.receiver = RobotDataReceiver()

        # 接続試行
        self.receiver.connect()
        if self.receiver.connected:
            self.connection_status_label.setText("Connected")
        else:
            self.connection_status_label.setText("Connection Failed")

        # タイマーを設定して定期的にデータを更新
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_data)
        self.timer.start(100)  # 100msごとに更新

    def update_data(self):
        # 接続状態の確認
        if not self.receiver.connected:
            self.connection_status_label.setText("Connecting...")
            self.receiver.connect()
            if self.receiver.connected:
                self.connection_status_label.setText("Connected")
            else:
                self.connection_status_label.setText("Connection Failed")
            return

        # データを取得してラベルを更新
        data = self.receiver.get_data()
        if data:
            self.line_position_widget.set_position(data['line_position'])
            self.label_left_motor.setText(
                f"Left Motor: Target {data['left_motor_target_speed']} mm/s, Actual {data['left_motor_actual_speed']} mm/s")
            self.label_right_motor.setText(
                f"Right Motor: Target {data['right_motor_target_speed']} mm/s, Actual {data['right_motor_actual_speed']} mm/s")
            self.label_elapsed_time.setText(f"Elapsed Time: {data['elapsed_time']} s")
        else:
            self.label_left_motor.setText("Left Motor: Target Error, Actual Error")
            self.label_right_motor.setText("Right Motor: Target Error, Actual Error")
            self.label_elapsed_time.setText("Elapsed Time: Error")

if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = RobotDataGUI()
    window.show()

    sys.exit(app.exec())
