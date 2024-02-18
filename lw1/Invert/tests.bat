@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Не задан файл для считывания матрицы. Программа должна прекратить свою работу
%MyProgram% > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

%MyProgram% test-data\invalidFile.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-matrix-file.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM Задан файл с пустой матрицей. Программа должна завершить свою работу
%MyProgram% test-data\empty.txt > "%TEMP%\output.txt" && goto err
fc test-data\empty-matrix-file.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 3 passed

REM Поиск обратной матрицы
%MyProgram% test-data\matrix.txt > "%TEMP%\output.txt" || goto err
fc test-data\correct-inverted-matrix.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 4 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1