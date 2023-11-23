# 下载解压源码
在`/usr/local`目录下运行：
```sh
wget http://www.lua.org/ftp/lua-5.4.4.tar.gz
tar -zxvf lua-5.4.4.tar.gz
```

# 修改配置
我们需要编译生成 Lua 的动态库，需要修改配置。
## 1. `Makefile`
```makefile
TO_LIB= liblua.a liblua-5.4.4.so
```

## 2. `src/Makefile`
```makefile
$(LUA_A): $(BASE_O)
    $(AR) $@ $(BASE_O)
    $(RANLIB) $@
    $(CC) -shared -ldl -Wl,-soname,$(LUA_SO) -o $(LUA_SO) $? -lm $(MYLDFLAGS)

clean:
    $(RM) $(ALL_T) $(ALL_O) $(LUA_SO)
```

# 编译安装
回到源码根目录下，执行：
```sh
make "MYCFLAGS=-fPIC"
make install
```

同样我们可以在源码根目录下执行`make uninstall`可以进行卸载。

# 参考资料
1. https://blog.spreendigital.de/2020/05/24/how-to-compile-lua-5-4-0-for-linux-as-a-shared-library/
2. [centos下安装lua5.1.4](https://blog.csdn.net/weixin_34242658/article/details/92457503)