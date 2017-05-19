set PROGRAM="%~1"

%PROGRAM% 6 > %TEMP%\6-Flip.txt
if %ERRORLEVEL% EQU 1 goto err 
fc.exe %TEMP%\6-Flip.txt 6-Out.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% 96 > %TEMP%\96-Flip.txt
if %ERRORLEVEL% EQU 1 goto err 
fc.exe %TEMP%\96-Flip.txt 96-Out.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% 35 > %TEMP%\35-Flip.txt
if %ERRORLEVEL% EQU 1 goto err 
fc.exe %TEMP%\35-Flip.txt 35-Out.txt
if %ERRORLEVEL% EQU 1 goto err


%PROGRAM% 0 > %TEMP%\0-Flip.txt
if %ERRORLEVEL% EQU 1 goto err 
fc.exe %TEMP%\0-Flip.txt 0-Out.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% 255 > %TEMP%\255-Flip.txt
if %ERRORLEVEL% EQU 1 goto err 
fc.exe %TEMP%\255-Flip.txt 255-Out.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% -10 > %TEMP%\minus-10-Flip.txt
if %ERRORLEVEL% NEQ 1 goto err 
fc.exe %TEMP%\minus-10-Flip.txt incorrect-out.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% 1000 > %TEMP%\1000-Flip.txt
if %ERRORLEVEL% NEQ 1 goto err 
fc.exe %TEMP%\1000-Flip.txt incorrect-out.txt
if %ERRORLEVEL% EQU 1 goto err

echo "Program testing succeeded"
exit 0

:err
echo "Program testing failed"
exit 1