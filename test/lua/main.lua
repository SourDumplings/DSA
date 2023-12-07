function Main(projectSourceDir)
    package.path = package.path .. ";" .. projectSourceDir .. "/test/lua/?.lua"
    local luaScriptName = "test_sayhi_add" -- 要执行的 lua 脚本

    print("--------- lua script called begin ---------")
    -- print("projectSourceDir: ", projectSourceDir)
    -- print("package.path: ", package.path)
    package.loaded[luaScriptName] = nil      -- 删除缓存
    local luaScript = require(luaScriptName) -- 重新加载文件
    if not luaScript then
        print("Error! No script: ", luaScriptName)
        return
    end

    Test()

    print("--------- lua script called end ---------")
end
