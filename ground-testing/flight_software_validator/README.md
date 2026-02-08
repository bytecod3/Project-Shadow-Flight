## converting from UI file to python logic
```c
pyuic ui_file.ui -o ui_file.py
```

- Create main.py 
- import Ui_MainWindow in main.py 
- create a MainWindow class and subclass ```QtWidgets.QMainWindow, Ui_MainWindow``` e.g 
```class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow): ...```

### bundling into a distributable 
1. install pyinstaller ```pip3 install PyInstaller```
2. run ```pyinstaller main.py```
3. edit ```main.spec``` sheet to add relevant app data


### creating a windows executable 
1. Download installforge from the site below
https://youtu.be/d_HlPboLRL8?list=RDMMdm5bAaawfUg

2. 