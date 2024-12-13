import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget
from PySide6.QtCore import QTimer
import random  # ダミーデータ生成用、本番ではロボットからのデータ取得処理に置き換える

class RobotDataReceiver:
    """
    ロボットからデータを受信するクラス。
    ここではダミーデータを返します。
    本番環境では、通信プロトコルに応じて適切な受信処理を実装してください。
    """
    def get_data(self):
        # ダミーデータ生成
        return {
            "temperature": round(random.uniform(20.0, 30.0), 2),
            "distance": round(random.uniform(1.0, 10.0), 2),
            "status": random.choice(["Idle", "Moving", "Error"])
        }

class RobotDataGUI(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Robot Data Viewer")

        # レイアウトとウィジェットの作成
        self.central_widget = QWidget()
        self.layout = QVBoxLayout()

        self.label_temperature = QLabel("Temperature: N/A")
        self.label_distance = QLabel("Distance: N/A")
        self.label_status = QLabel("Status: N/A")

        self.layout.addWidget(self.label_temperature)
        self.layout.addWidget(self.label_distance)
        self.layout.addWidget(self.label_status)

        self.central_widget.setLayout(self.layout)
        self.setCentralWidget(self.central_widget)

        # データ受信クラスのインスタンスを作成
        self.receiver = RobotDataReceiver()

        # タイマーを設定して定期的にデータを更新
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_data)
        self.timer.start(1000)  # 1秒ごとに更新

    def update_data(self):
        # データを取得してラベルを更新
        data = self.receiver.get_data()
        self.label_temperature.setText(f"Temperature: {data['temperature']} °C")
        self.label_distance.setText(f"Distance: {data['distance']} m")
        self.label_status.setText(f"Status: {data['status']}")

if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = RobotDataGUI()
    window.show()

    sys.exit(app.exec())
