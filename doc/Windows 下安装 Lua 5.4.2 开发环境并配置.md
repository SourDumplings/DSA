# 下载解压
在[LuaBinaries Files](https://sourceforge.net/projects/luabinaries/files/5.4.2/Windows%20Libraries/Dynamic/)即可下载 Lua 5.4.2 for Windows 的开发包，将其解压。

开发包安装后其安装目录下的结构为：
```
│  lua54.dll
│  lua54.lib
│
└─include
        lauxlib.h
        lua.h
        lua.hpp
        luaconf.h
        lualib.h
```

# 修改配置
修改项目宏定义`LuaLibPath`为 Lua 开发包的安装路径即可。

可以在 VS 中修改每个项目的`PropertySheet`：
View -> Other Windows -> Property Manager 即可找到各项目 `Property Sheet`，修改用户自定义宏即可。

也可以直接修改配置文件`PropertySheet.props`（推荐）中的`LuaLibPath`的值。