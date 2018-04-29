@echo off
setlocal
path C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\;C:\MinGW\bin;C:\Users\yifan wang\ECE150\MinGW\bin\;%path%
g++ %1.cpp -o %1.exe
endlocal
echo on
