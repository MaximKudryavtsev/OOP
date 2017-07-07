set PROGRAM="%~1"

rem Checking with non existing bmp file
%PROGRAM% some-non-existing-bmp-file.bmp
if NOT ERRORLEVEL 1 goto err

rem Checking with 2 color bmp file
%PROGRAM% 2-color.bmp > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt 2-color-bmp-file-info.txt
if ERRORLEVEL 1 goto err

rem Checking with 16 color bmp file
%PROGRAM% 16-color.bmp > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt 16-color-bmp-file-info.txt
if ERRORLEVEL 1 goto err

rem Checking with 256 color bmp file
%PROGRAM% 256-color.bmp > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt 256-color-bmp-file-info.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded!
exit 0

:err
echo Program testing failed...
exit 1
