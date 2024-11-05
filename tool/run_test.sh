###
 # @Author: SourDumplings
 # @Date: 2021-11-01 17:00:49
 # @Link: https://github.com/SourDumplings/
 # @Email: sourdumplings@qq.com
 # @Description: 运行测试程序，必须要先构建
### 

source /etc/profile
source .bashrc

export ASAN_OPTIONS=abort_on_error=1:disable_coredump=0:unmap_shadow_on_exit=1

ulimit -c unlimited

project_base_dir=$(cd $(dirname $0)/..;pwd)
cd $project_base_dir/build/test/bin

./dsa-test
