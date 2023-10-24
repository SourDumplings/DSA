###
 # @Author: SourDumplings
 # @Date: 2021-11-01 17:00:49
 # @Link: https://github.com/SourDumplings/
 # @Email: changzheng300@foxmail.com
 # @Description: 运行测试程序并使用 gperftools 生成性能分析报告，必须要先构建
### 

# gperftools 貌似和 Asan 有很多冲突，不要用编了 Asan 的版本运行
# export ASAN_OPTIONS=abort_on_error=1:disable_coredump=0:unmap_shadow_on_exit=1:detect_leaks=0
# export LD_PRELOAD=/usr/lib64/libasan.so.5:/usr/local/lib/libprofiler.so.0
# export CPUPROFILE=./dsa-test.prof

ulimit -c unlimited

project_base_dir=$(cd $(dirname $0)/..;pwd)
cd $project_base_dir/build/test/bin

LD_PRELOAD=/usr/local/lib/libtcmalloc.so:/usr/local/lib/libprofiler.so.0 CPUPROFILE=./dsa-test-cpu.prof HEAPPROFILE=./dsa-test-mem ./dsa-test

if [ -e "./dsa-test-cpu.prof" ]; then
    pprof --pdf ./dsa-test ./dsa-test-cpu.prof > ./dsa-test-cpu.pdf
else
    echo "Error for generating dsa-test-cpu.prof!"
fi

if [ ! -e "./dsa-test-mem.0001.heap" ]; then
    echo "Error for generating dsa-test-mem.0001.heap!"
fi

for file in dsa-test-mem*.heap; do
    if [[ -f "$file" ]]; then
        pprof --pdf ./dsa-test $file > $file.pdf
    fi
done
