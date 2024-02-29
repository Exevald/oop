@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Неверное количество аргументов запуска. Программа должна прекратить свою работу
%MyProgram% encrypt 7 > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

REM Неверно задан ключ для шифрования. Программа должна прекратить свою работу
%MyProgram% encrypt test-data\input.txt test-data\output.txt !!! > "%TEMP%\output.txt" && goto err
fc test-data\invalid-key-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM Неверно задан ключ для шифрования. Программа должна прекратить свою работу
%MyProgram% encrypt test-data\input.txt test-data\output.txt 256 > "%TEMP%\output.txt" && goto err
fc test-data\invalid-key-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 3 passed

REM Неверно задан ключ для шифрования. Программа должна прекратить свою работу
%MyProgram% encrypt test-data\input.txt test-data\output.txt -1 > "%TEMP%\output.txt" && goto err
fc test-data\invalid-key-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 4 passed

REM Неверно задан режим работы программы. Программа должна прекратить свою работу
%MyProgram% write test-data\input.txt test-data\output.txt 5 > "output.txt" && goto err
fc test-data\invalid-mode-error.txt "output.txt" > nul || goto err 
echo Test 5 passed

REM Шифрование бинарного файла. Искомый и дешифрованый файл должны совпадать.
%MyProgram% encrypt test-data\input.txt test-data\encrypt-output.txt 255 || goto err
%MyProgram% decrypt test-data\encrypt-output.txt test-data\decrypt-output.txt 255 || goto err
fc test-data\input.txt test-data\decrypt-output.txt > nul || goto err 
echo Test 6 passed

REM Шифрование и дешифрование бинарного файла с разными ключами. Дешифрованный и искомый файл должны различаться
%MyProgram% encrypt test-data\input.txt test-data\encrypt-output.txt 255 || goto err
%MyProgram% decrypt test-data\encrypt-output.txt test-data\decrypt-output.txt 55 || goto err
fc test-data\input.txt test-data\decrypt-output.txt > nul && goto err 
echo Test 7 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1