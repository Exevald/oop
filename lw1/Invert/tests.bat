@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM �� ����� ���� ��� ���������� �������. ��������� ������ ���������� ���� ������
%MyProgram% > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

REM ����� ��� ���������� ������� �� ����������. ��������� ������ ���������� ���� ������
%MyProgram% test-data\invalidFile.txt > "%TEMP%\output.txt" && goto err
fc test-data\invalid-matrix-file-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM ����� ���� � ������ ��������. ��������� ������ ���������� ���� ������
%MyProgram% test-data\empty.txt > "%TEMP%\output.txt" && goto err
fc test-data\empty-matrix-file-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 3 passed

REM ������������ ������� ����� 0. ��������� ������ ������� ���������
%MyProgram% test-data\zero-determinant-matrix.txt > "%TEMP%\output.txt" || goto err
fc test-data\zero-determinant-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 4 passed

REM ����� �������� �������
%MyProgram% test-data\matrix.txt > "%TEMP%\output.txt" || goto err
fc test-data\correct-inverted-matrix.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 5 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1