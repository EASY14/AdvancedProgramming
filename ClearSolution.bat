::Creator XuYicheng
::ClearSolution For Alice
::echo off

attrib -S -H *.suo
del /S /Q *.suo

del /S /Q *.ncb

del /S /Q *.aps

del /s /Q *cache.dat
del /s /Q *.ilk
del /s /Q *.pdb
del /s /Q BuildLog.htm
del /s /Q *.obj
del /s /Q mt.dep
del /s /Q *.manifest
del /s /Q *.res
del /s /Q *.pch
del /s /Q *.idb
del /s /Q *.sdf

del /s /Q *.xlog

RD /S /Q debug
RD /S /Q release

for /f "delims=" %%a in ('dir /s /b /ad Debug Release') do (
rd /s /q "%%a"
)

RD /S /Q Autotext
RD /S /Q Dict
RD /S /Q Misc
