@REM Windows 下安装第三方 dll 库文件的脚本
@REM 参数 1：第三方库文件的安装目录；参数 2~N：要安装的 dll 路径们

@echo off

if "%~2"=="" (
  echo Error: At least two command line arguments are required.
  echo eg. install_external_dlls.bat dest_dir dll1_path dll2_path...
  exit /b 1
)

set dest_dir=%1
for %%a in (%*) do (
    echo install dll: %%a to %dest_dir%
    copy /Y %%a %dest_dir%
)
