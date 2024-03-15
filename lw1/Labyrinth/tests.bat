@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM ������ �������� ���������� ���������� ��� �������. ��������� ������ ���������� ���� ������
%MyProgram% test-data\input.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

REM ������ �������� ���������� ���������� ��� �������. ��������� ������ ���������� ���� ������
%MyProgram% test-data\invalidFile.txt test-data\output.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-input-file-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM �������� ���� �� ������������ ��������
%MyProgram% test-data\invalid-labyrinth.txt test-data\output.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-labyrinth-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 3 passed

REM ����� ����������� ���� � ���������
%MyProgram% test-data\input.txt test-data\output.txt || goto err
echo Test 4 passed

REM ����������� ���� �� ����������. ��������� ������ �������� �������� ��������
%MyProgram% test-data\imposible-path.txt test-data\output.txt || goto err
fc test-data\output.txt test-data\imposible-path.txt > nul || goto err
echo Test 5 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1