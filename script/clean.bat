@echo off
set project_base_dir=%~dp0\..
cd /d %project_base_dir%
if exist build rmdir /s /q build
if exist dist rmdir /s /q dist