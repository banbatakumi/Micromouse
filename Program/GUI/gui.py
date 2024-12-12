import socket

from PySide6 import QtCore, QtGui
from PySide6.QtWidgets import (QApplication, QLabel, QWidget, QMessageBox, QFileDialog)
import os
import sys

# PySide6のアプリ本体（ユーザがコーディングしていく部分）
class MainWindow(QWidget):
      def __init__(self, parent=None):
            # 親クラスの初期化
            super().__init__(parent)
            
            self.setGeometry(100, 100, 800, 600)
            self.setWindowTitle("MycroMouse System Viewr")

            self.SetLabel()

            # ラベルは別のメソッドに分けました
      def SetLabel(self):
            # ラベルを使うことを宣言
            label = QLabel(self)
            
            # ラベルの見た目をQt Style Sheetで設定
            labelStyle = """QLabel {
                  color:            #FFFFFF;  /* 文字色 */
                  font-size:        15px;     /* 文字サイズ */
            }"""
            
            # 見た目の設定をラベルに反映させる
            label.setStyleSheet(labelStyle)
            
            # ラベルに文字を指定
            label.setText("Connecting to robot...")

      def paintEvent(self, event):
            painter = QtGui.QPainter(self)
            painter.begin(self)
         
            painter.setBrush(QtCore.Qt.lightGray)
            painter.setPen(QtCore.Qt.black)
         
            rectangle = QtCore.QRectF(10.0, 20.0, 80.0, 60.0)
            painter.drawEllipse(rectangle)


def main():
      # 環境変数にPySide6を登録
      # dirname = os.path.dirname(PySide6.__file__)
      # plugin_path = os.path.join(dirname, 'plugins', 'platforms')
      # os.environ['QT_QPA_PLATFORM_PLUGIN_PATH'] = plugin_path

      # ESP32のIPアドレス
      esp32_ip = "192.168.4.1"
      port = 8000

      # ESP32に接続
      # client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      # client.connect((esp32_ip, port))
      
      # データを受信して表示
      # response = client.recv(4096)
      # print(response.decode())

      app = QApplication(sys.argv)    # PySide6の実行
      window = MainWindow()           # ユーザがコーディングしたクラス
      window.show()                   # PySide6のウィンドウを表示
      sys.exit(app.exec())            # PySide6の終了


if __name__ == "__main__":
      main()




