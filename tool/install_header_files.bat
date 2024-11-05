@REM Windows 下安装头文件的脚本
@REM 参数 1：头文件搜索路径；参数 2：头文件安装目录

@echo off

if "%~2"=="" (
  echo Error: Two command line arguments are required.
  echo eg. install_header_files.bat source_dir dest_dir
  exit /b 1
)

set source_dir=%1
set dest_dir=%2

echo source_dir: %source_dir%
echo dest_dir: %dest_dir%

if exist %dest_dir% (
    rmdir /s /q %dest_dir%
    echo Old %dest_dir% has been removed.
)
mkdir %dest_dir%

xcopy /s /e "%source_dir%\*.h" "%dest_dir%"
