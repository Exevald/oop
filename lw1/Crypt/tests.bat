@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM �������� ���������� ���������� �������. ��������� ������ ���������� ���� ������
%MyProgram% encrypt 7 > "%TEMP%\output.txt" && goto err
fc test-data\invalid-usage-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 1 passed

REM ������� ����� ���� ��� ����������. ��������� ������ ���������� ���� ������
%MyProgram% encrypt test-data\input.txt test-data\output.txt !!! > "%TEMP%\output.txt" && goto err
fc test-data\invalid-key-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 2 passed

REM ������� ����� ���� ��� ����������. ��������� ������ ���������� ���� ������
%MyProgram% encrypt test-data\input.txt test-data\output.txt 256 > "%TEMP%\output.txt" && goto err
fc test-data\invalid-key-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 3 passed

REM ������� ����� ���� ��� ����������. ��������� ������ ���������� ���� ������
%MyProgram% encrypt test-data\input.txt test-data\output.txt -1 > "%TEMP%\output.txt" && goto err
fc test-data\invalid-key-error.txt "%TEMP%\output.txt" > nul || goto err 
echo Test 4 passed

REM ������� ����� ����� ������ ���������. ��������� ������ ���������� ���� ������
%MyProgram% write test-data\input.txt test-data\output.txt 5 > "output.txt" && goto err
fc test-data\invalid-mode-error.txt "output.txt" > nul || goto err 
echo Test 5 passed

REM ���������� ��������� �����. ������� � ������������ ���� ������ ���������.
%MyProgram% encrypt test-data\input.txt test-data\encrypt-output.txt 255 || goto err
%MyProgram% decrypt test-data\encrypt-output.txt test-data\decrypt-output.txt 255 || goto err
fc test-data\input.txt test-data\decrypt-output.txt > nul || goto err 
echo Test 6 passed

REM ���������� � ������������ ��������� ����� � ������� �������. ������������� � ������� ���� ������ �����������
%MyProgram% encrypt test-data\input.txt test-data\encrypt-output.txt 255 || goto err
%MyProgram% decrypt test-data\encrypt-output.txt test-data\decrypt-output.txt 55 || goto err
fc test-data\input.txt test-data\decrypt-output.txt > nul && goto err 
echo Test 7 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1