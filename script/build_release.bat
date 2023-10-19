@echo off
set project_base_dir=%~dp0\..
echo project_base_dir: %project_base_dir%

cd /d %project_base_dir%
if not exist doc mkdir doc
if not exist build mkdir build
cd build
cmake -G "MinGW Makefiles" .. -DBUILD_TYPE=Release --graphviz=dsa.dot
dot -Tpng dsa.dot.dsa-test > dsa-test_dependencies.png
make
make install
