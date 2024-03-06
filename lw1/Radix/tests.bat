@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Не заданы системы счисления. Программа должна прекратить свою работу
%MyProgram% F > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

REM Не задано число для перевода. Программа должна прекратить свою работу
%MyProgram% 10 12 > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM Некорректно задано число для перевода. Программа должна прекратить свою работу
%MyProgram% 2 10 !!!! > "%TEMP%\output.txt" && goto err
echo Test 3 passed

REM Некорректно задана система счисления для перевода. Программа должна прекратить свою работу
%MyProgram% !!!10 16 -0123 > "%TEMP%\output.txt" && goto err
echo Test 4 passed

REM Перевод числа из двоичной системы счисления в десятичную систему счисления
%MyProgram% 2 10 101 > "%TEMP%\output.txt" || goto err
fc test-data\value-5.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 5 passed

REM Перевод отрицательного числа в другую систему счисления
%MyProgram% 2 10 -101 > "%TEMP%\output.txt" || goto err
fc test-data\negative-value-5.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 6 passed

REM Перевод нуля в другую систему счисления
%MyProgram% 2 10 -0 > "%TEMP%\output.txt" || goto err
fc test-data\zero-value.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 7 passed

REM Перевод числа в ту же самую систему счисления
%MyProgram% 10 10 2 > "%TEMP%\output.txt" || goto err
fc test-data\value-2.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 8 passed

REM Число превышает максимальное значение типа int. Программа должна прекратить свою работу
%MyProgram% 10 16 2147483647 > "%TEMP%\output.txt" && goto err
fc test-data\value-overflow.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 9 passed

REM Число превышает максимальное значение типа int. Программа должна прекратить свою работу
%MyProgram% 10 16 2147483646 > "%TEMP%\output.txt" || goto err
echo Test 10 passed

REM Число превышает максимальное значение типа int. Программа должна прекратить свою работу
%MyProgram% 10 16 -2147483648 > "%TEMP%\output.txt" && goto err
fc test-data\value-overflow.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 11 passed

REM Число превышает максимальное значение типа int. Программа должна прекратить свою работу
%MyProgram% 10 16 -2147483647 > "%TEMP%\output.txt" || goto err
echo Test 12 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1