@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM �� ������ ������� ���������. ��������� ������ ���������� ���� ������
%MyProgram% F && goto err
echo Test 1 passed

REM �� ������ ����� ��� ��������. ��������� ������ ���������� ���� ������
%MyProgram% 10 12 && goto err
echo Test 2 passed

REM ����������� ������ ����� ��� ��������. ��������� ������ ���������� ���� ������
%MyProgram% 2 10 !!!! && goto err
echo Test 3 passed

REM ����������� ������ ����� ��� ��������. ��������� ������ ���������� ���� ������
%MyProgram% 10 16 -0123 && goto err
echo Test 4 passed

REM ������� ����� �� �������� ������� ��������� � ���������� ������� ���������
%MyProgram% 2 10 101 || goto err
echo Test 5 passed

REM ������� �������������� ����� � ������ ������� ���������
%MyProgram% 2 10 -101 || goto err
echo Test 6 passed

REM ������� ���� � ������ ������� ���������
%MyProgram% 2 10 0 || goto err
echo Test 7 passed

REM ������� ����� � �� �� ����� ������� ���������
%MyProgram% 10 10 2 || goto err
echo Test 8 passed

REM ����� ��������� ������������ �������� ���� int. ��������� ������ ���������� ���� ������
%MyProgram% 10 16 2147483650 && goto err	
echo Test 9 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1