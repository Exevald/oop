@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Не заданы файлы для ввода и вывода, программа должна прекратить работу
%MyProgram% && goto err
echo Test 1 passed

REM При запуске с правильными параметрами ожидается ненулевой код возврата
%MyProgram% test-data\favourite-language.txt "%TEMP%\favourite-language.txt" PHP GO || goto err
fc test-data\favourite-language-replace-php-with-golang.txt "%TEMP%\favourite-language.txt" > nul || goto err
echo Test 2 passed

REM При ненахождении подстроки в строке программа должна вывести искомый текст
%MyProgram% test-data\favourite-language.txt "%TEMP%\favourite-language.txt" Python GO || goto err
fc test-data\favourite-language.txt "%TEMP%\favourite-language.txt" > nul || goto err
echo Test 3 passed

REM Проверка на отсутствие зацикливания программы при замене 1231234 в строке 12312312345 
%MyProgram% test-data\number-string.txt "%TEMP%\number-string.txt" 1231234 111 || goto err
fc test-data\number-string-replace-1231234-with-111.txt "%TEMP%\number-string.txt" > nul || goto err
echo Test 4 passed

REM Проверка на отсутствие зацикливания программы при замене ma в строке mama
%MyProgram% test-data\mother.txt "%TEMP%\mother.txt" ma mama || goto err
fc test-data\mother-replace-ma-with-mama.txt "%TEMP%\mother.txt" > nul || goto err
echo Test 5 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1