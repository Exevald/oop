@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Сравниваем два пустых файла
%MyProgram% empty.txt empty.txt > "%TEMP%\output.txt" || goto err
fc output_empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Сравниваем два одинаковых файла
%MyProgram% input1_ok.txt input2_ok.txt > "%TEMP%\output.txt" || goto err
fc output_ok.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM Сравниваем два разных файла
%MyProgram% input1_diff.txt input2_diff.txt > "%TEMP%\output.txt" || goto err
fc output_diff.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

REM Сравниваем отсутсвующие файлы, программа должна прекратить работу
%MyProgram% MissingFile.txt MissingFile.txt && goto err
echo Test 5 passed

REM Не задан один из файлов для сравнения, программа должна прекратить работу
%MyProgram% input1_ok.txt && goto err
echo Test 6 passed

REM Не заданы оба файла для сравнения, программа должна прекратить работу
%MyProgram% && goto err
echo Test 7 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1