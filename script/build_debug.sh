###
 # @Author: SourDumplings
 # @Date: 2021-11-01 16:50:45
 # @Link: https://github.com/SourDumplings/
 # @Email: changzheng300@foxmail.com
 # @Description: 构建脚本
### 

project_base_dir=$(cd $(dirname $0)/..;pwd)
# sh $project_base_dir/script/clean.sh

echo "project_base_dir: $project_base_dir" 

cd $project_base_dir

if [ ! -d "doc" ]; then  
    mkdir -p "doc"
    echo "Directory created: doc"
fi

if [ ! -d "build" ]; then  
    mkdir -p "build"
    echo "Directory created: build"
fi

cd build
cmake .. -DBUILD_TYPE=Debug --graphviz=dsa.dot
dot -Tpng dsa.dot.dsa-test > dsa-test_dependencies.png
make
make install