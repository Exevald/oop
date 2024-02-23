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
fc test-data\invalid-usage-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

REM Файла для считывания матрицы не существует. Программа должна прекратить свою работу
%MyProgram% test-data\invalidFile.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-matrix-file-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM Задан файл с пустой матрицей. Программа должна прекратить свою работу
%MyProgram% test-data\empty.txt > "%TEMP%\output.txt" && goto err
fc test-data\empty-matrix-file-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 3 passed

REM Определитель матрицы равен 0. Программа должна вывести сообщение
%MyProgram% test-data\zero-determinant-matrix.txt > "%TEMP%\output.txt" || goto err
fc test-data\zero-determinant-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 4 passed

REM Поиск обратной матрицы
%MyProgram% test-data\matrix.txt > "%TEMP%\output.txt" || goto err
fc test-data\correct-inverted-matrix.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 5 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1