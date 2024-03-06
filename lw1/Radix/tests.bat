@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM �� ������ ������� ���������. ��������� ������ ���������� ���� ������
%MyProgram% F > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

REM �� ������ ����� ��� ��������. ��������� ������ ���������� ���� ������
%MyProgram% 10 12 > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM ����������� ������ ����� ��� ��������. ��������� ������ ���������� ���� ������
%MyProgram% 2 10 !!!! > "%TEMP%\output.txt" && goto err
echo Test 3 passed

REM ����������� ������ ������� ��������� ��� ��������. ��������� ������ ���������� ���� ������
%MyProgram% !!!10 16 -0123 > "%TEMP%\output.txt" && goto err
echo Test 4 passed

REM ������� ����� �� �������� ������� ��������� � ���������� ������� ���������
%MyProgram% 2 10 101 > "%TEMP%\output.txt" || goto err
fc test-data\value-5.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 5 passed

REM ������� �������������� ����� � ������ ������� ���������
%MyProgram% 2 10 -101 > "%TEMP%\output.txt" || goto err
fc test-data\negative-value-5.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 6 passed

REM ������� ���� � ������ ������� ���������
%MyProgram% 2 10 -0 > "%TEMP%\output.txt" || goto err
fc test-data\zero-value.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 7 passed

REM ������� ����� � �� �� ����� ������� ���������
%MyProgram% 10 10 2 > "%TEMP%\output.txt" || goto err
fc test-data\value-2.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 8 passed

REM ����� ��������� ������������ �������� ���� int. ��������� ������ ���������� ���� ������
%MyProgram% 10 16 2147483647 > "%TEMP%\output.txt" && goto err
fc test-data\value-overflow.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 9 passed

REM ����� ��������� ������������ �������� ���� int. ��������� ������ ���������� ���� ������
%MyProgram% 10 16 2147483646 > "%TEMP%\output.txt" || goto err
echo Test 10 passed

REM ����� ��������� ������������ �������� ���� int. ��������� ������ ���������� ���� ������
%MyProgram% 10 16 -2147483648 > "%TEMP%\output.txt" && goto err
fc test-data\value-overflow.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 11 passed

REM ����� ��������� ������������ �������� ���� int. ��������� ������ ���������� ���� ������
%MyProgram% 10 16 -2147483647 > "%TEMP%\output.txt" || goto err
echo Test 12 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1