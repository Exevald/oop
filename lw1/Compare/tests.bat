@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM ���������� ��� ������ �����
%MyProgram% empty.txt empty.txt > "%TEMP%\output.txt" || goto err
fc output_empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM ���������� ��� ���������� �����
%MyProgram% input1_ok.txt input2_ok.txt > "%TEMP%\output.txt" || goto err
fc output_ok.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM ���������� ��� ������ �����
%MyProgram% input1_diff.txt input2_diff.txt > "%TEMP%\output.txt" || goto err
fc output_diff.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

REM ���������� ������������ �����, ��������� ������ ���������� ������
%MyProgram% MissingFile.txt MissingFile.txt && goto err
echo Test 5 passed

REM �� ����� ���� �� ������ ��� ���������, ��������� ������ ���������� ������
%MyProgram% input1_ok.txt && goto err
echo Test 6 passed

REM �� ������ ��� ����� ��� ���������, ��������� ������ ���������� ������
%MyProgram% && goto err
echo Test 7 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1