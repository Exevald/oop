@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Копируем пустой файл
%MyProgram% empty.txt "%TEMP%\output.txt" || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Копируем файл из одной строки
%MyProgram% one-line.txt "%TEMP%\output.txt" || goto err
fc one-line.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM Копируем файл из нескольких строк
%MyProgram% multiline.txt "%TEMP%\output.txt" || goto err
fc multiline.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

REM Копируем отсутствующий файл, программа должна прекратить работу
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto err
echo Test 4 passed

REM Не задан файл для вывода, программа должна прекратить работу
%MyProgram% MissingFile.txt && goto err
echo Test 5 passed

REM Не заданы файлы для ввода и вывода, программа должна прекратить работу
%MyProgram% && goto err
echo Test 6 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1