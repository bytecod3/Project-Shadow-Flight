"""
:brief Battery estimation tool for electrical power supply
:author Edwin Mwiti
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget

title = "EPS Battery Estimator"

class ApplicationWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initialize_ui()

    def initialize_ui(self):
        """
        initialize the window and display its contents on to the screen
        """
        self.setGeometry(100,100,400,300)
        self.setWindowTitle(title)
        self.show()


# run
if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = ApplicationWindow()
    sys.exit(app.exec())
