@echo off
cls

g++ -o plot plot.cpp

echo Running the progrma
plot.exe
echo Finish running!

echo Start plot
python plot.py
echo End plot

