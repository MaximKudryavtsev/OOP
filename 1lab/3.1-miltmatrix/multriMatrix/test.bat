set PROGRAM="%~1"
 
rem "test invalid count of arguments"
%PROGRAM% in1.txt
if %ERRORLEVEL% NEQ 1 goto err 

rem "test invalid file name"
%PROGRAM% in10.txt in2.txt
if %ERRORLEVEL% NEQ 1 goto err 

rem "test mult matrix1 matrix2"
%PROGRAM% in1.txt in2.txt > %TEMP%\out1.txt
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\out1.txt ex1-2.txt
if %ERRORLEVEL% EQU 1 goto err

rem "test mult matrix2 matrix3"
%PROGRAM% in2.txt in3.txt > %TEMP%\out2.txt
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\out2.txt ex2-3.txt
if %ERRORLEVEL% EQU 1 goto err
 
rem "test mult matrix2 matrix3"
%PROGRAM% in2.txt in1.txt > %TEMP%\out3.txt
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\out3.txt ex2-1.txt
if %ERRORLEVEL% EQU 1 goto err

echo "Program testing succeeded"
exit 0

:err
echo "Program testing failed"
exit 1