###
 # @Author: SourDumplings
 # @Date: 2021-11-01 17:00:49
 # @Link: https://github.com/SourDumplings/
 # @Email: sourdumplings@qq.com
 # @Description: 运行 Python3 测试脚本，必须要先构建（与 Asan 不兼容）
### 

ulimit -c unlimited

project_base_dir=$(cd $(dirname $0)/..;pwd)
cd $project_base_dir/test/python

export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

python3 main.py