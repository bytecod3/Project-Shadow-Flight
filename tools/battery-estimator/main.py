"""
:brief Battery estimation tool for electrical power supply
:author Edwin Mwiti
"""

import sys

from PyQt5.QtSensors import QMagnetometer
from PyQt5.QtWidgets import QApplication, QWidget, QButtonGroup, QGroupBox, QVBoxLayout, QPushButton, QHBoxLayout

title = "Cubesat EPS solver"

class ApplicationWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initialize_ui()

    def initialize_ui(self):
        """
        initialize the window and display its contents on to the screen
        """

        self.setGeometry(700, 100, 1100, 600)
        self.setWindowTitle(title)


        # main layout
        main_layout = QHBoxLayout()
        self.setLayout(main_layout)

        # create side panel for sub-system selection
        side_panel = self.create_side_tree_panel()
        main_layout.addWidget(side_panel)


        self.show()

    def create_side_tree_panel(self):
        """
        create subsystems tree on the left side panel
        """

        # Side tree view for subsystems select
        subsystems_groupbox = QGroupBox("Subsystems")
        subsystems_layout = QVBoxLayout()
        subsystems_groupbox.setLayout(subsystems_layout)

        # create side buttons and add them to the groupbox layout
        obc_sys_select_btn = QPushButton("Onboard Computer")
        comms_sys_select_btn = QPushButton("Communication System")
        adcu_sys_select_btn = QPushButton("Attitude Determination and Control")
        eps_sys_select_btn = QPushButton("Electrical Power Supply")
        magnetorquer_sys_select_btn = QPushButton("Magnetorquer")
        add_sys_select_btn = QPushButton("+ Add new")

        # add buttons to the layout
        subsystems_layout.addWidget(obc_sys_select_btn)
        subsystems_layout.addWidget(comms_sys_select_btn)
        subsystems_layout.addWidget(adcu_sys_select_btn)
        subsystems_layout.addWidget(eps_sys_select_btn)
        subsystems_layout.addWidget(magnetorquer_sys_select_btn)
        subsystems_layout.addWidget(add_sys_select_btn)

        # append buttons to button group
        sub_sys_button_group = QButtonGroup(subsystems_groupbox)
        sub_sys_button_group.addButton(obc_sys_select_btn)
        sub_sys_button_group.addButton(comms_sys_select_btn)

        return subsystems_groupbox

# run
if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = ApplicationWindow()
    sys.exit(app.exec())
