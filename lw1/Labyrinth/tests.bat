@echo off

REM Путь к тестируемой программе передаётся через 1-ый аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Задано неверное количество параметров для запуска. Программа должна прекратить свою работу
%MyProgram% test-data\input.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

REM Задано неверное количество параметров для запуска. Программа должна прекратить свою работу
%MyProgram% test-data\invalidFile.txt test-data\output.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-input-file-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM Добавить тест на некорректный лабиринт
%MyProgram% test-data\invalid-labyrinth.txt test-data\output.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-labyrinth-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 3 passed

REM Поиск кратчайшего пути в лабиринте
%MyProgram% test-data\input.txt test-data\output.txt || goto err
echo Test 4 passed

REM Кратчайшего пути не существует. Программа должна вывестки исходный лабиринт
%MyProgram% test-data\imposible-path.txt test-data\output.txt || goto err
fc test-data\output.txt test-data\imposible-path.txt > nul || goto err
echo Test 5 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибки
:err
echo Test failed
exit /B 1