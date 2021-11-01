###
 # @Author: SourDumplings
 # @Date: 2021-11-01 16:50:45
 # @Link: https://github.com/SourDumplings/
 # @Email: changzheng300@foxmail.com
 # @Description: 构建脚本
### 

sh clean.sh

cd ..
mkdir build
cd build
cmake ..
make
make install