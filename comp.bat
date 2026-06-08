cd .\src
g++ main.cpp global.cpp visual.cpp ascii.cpp -o ../start -finput-charset=utf-8 -fexec-charset=gbk -static
cd ..\
start "" "start.exe"
