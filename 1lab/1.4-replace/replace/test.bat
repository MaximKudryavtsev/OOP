set PROGRAM="%~1" 

rem Normal replace
%PROGRAM% in1.txt %TEMP%\out1.txt "maks" "sasha"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out1.txt ex1.txt
if ERRORLEVEL 1 goto err

rem Repetitive replace
%PROGRAM% in2.txt %TEMP%\out2.txt "ma" "mama"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out2.txt ex2.txt
if ERRORLEVEL 1 goto err

rem inpust is empty
%PROGRAM% in3.txt %TEMP%\out3.txt "ma" "mama"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out3.txt ex3.txt
if ERRORLEVEL 1 goto err

rem substring
%PROGRAM% in4.txt %TEMP%\out4.txt "1231234" "substring"
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\out4.txt ex4.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1