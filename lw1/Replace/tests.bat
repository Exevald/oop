@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM �� ������ ����� ��� ����� � ������, ��������� ������ ���������� ������
%MyProgram% && goto err
echo Test 1 passed

REM ��� ������� � ����������� ����������� ��������� ��������� ��� ��������
%MyProgram% test-data\favourite-language.txt "%TEMP%\favourite-language.txt" PHP GO || goto err
fc test-data\favourite-language-replace-php-with-golang.txt "%TEMP%\favourite-language.txt" > nul || goto err
echo Test 2 passed

REM ��� ������������ ��������� � ������ ��������� ������ ������� ������� �����
%MyProgram% test-data\favourite-language.txt "%TEMP%\favourite-language.txt" Python GO || goto err
fc test-data\favourite-language.txt "%TEMP%\favourite-language.txt" > nul || goto err
echo Test 3 passed

REM �������� �� ���������� ������������ ��������� ��� ������ 1231234 � ������ 12312312345 
%MyProgram% test-data\number-string.txt "%TEMP%\number-string.txt" 1231234 111 || goto err
fc test-data\number-string-replace-1231234-with-111.txt "%TEMP%\number-string.txt" > nul || goto err
echo Test 4 passed

REM �������� �� ���������� ������������ ��������� ��� ������ ma � ������ mama
%MyProgram% test-data\mother.txt "%TEMP%\mother.txt" ma mama || goto err
fc test-data\mother-replace-ma-with-mama.txt "%TEMP%\mother.txt" > nul || goto err
echo Test 5 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1