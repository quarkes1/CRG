cd .\src
g++ main.cpp global.cpp visual.cpp ascii.cpp -o ../main -finput-charset=utf-8 -fexec-charset=gbk 
cd ..\
start "" "main.exe"
