local function is_sorted(table)
    local n = #table
    -- print("n is " .. n)
    for i = 1, n - 1, 1 do
        if table[i + 1] < table[i] then
            return false
        end
    end
    return true
end

local function test_correctiness()
    local myTable = { 5, 2, 8, 3, 1 }
    print("myTable is sorted? ", is_sorted(myTable))

    local sortedTable = DSALuaDLL.Sort_int(myTable)
    print("sortedTable is sorted? ", is_sorted(sortedTable))

    -- Access the sorted values
    for i = 1, #sortedTable do
        print(sortedTable[i])
    end
end

local function test_sort_prof()
    local testNo = 10
    local NUMS = 10000000
    local MAX_NUM = 10000
    for i = 1, testNo, 1 do
        local nums = {}
        for i = 1, NUMS do
            nums[i] = math.random(0, MAX_NUM)
        end

        local start = os.time()
        local sortedNumsByCpp = DSALuaDLL.Sort_int(nums)
        local finish = os.time()

        if not is_sorted(sortedNumsByCpp) then
            print("Error for Cpp sort!")
            return false
        end

        print("Cpp sort costs " .. (finish - start) .. " seconds")

        start = os.time()
        table.sort(nums)
        finish = os.time()

        if not is_sorted(nums) then
            print("Error for Lua sort!")
            return false
        end

        print("Lua sort costs " .. (finish - start) .. " seconds")
    end
    return true
end
--[[ 
测试结果：
    local testNo = 10
    local NUMS = 10000000
    local MAX_NUM = 10000

--------------------------------------------------------
Operating System: Linux
CPU Architecture: x86-64, 64-bit
Compiler: GCC, Version: 8.3.1
Cpp version: 201103
------------------ Test on RELEASE mode ------------------
--------------------- Test start -----------------------
--------------------------------------------------------
--------------------------------------------------------
PROJECT_SOURCE_DIR = /root/DSA
--------- lua script called begin ---------
Cpp sort costs 3 seconds
Lua sort costs 5 seconds
Cpp sort costs 3 seconds
Lua sort costs 5 seconds
Cpp sort costs 2 seconds
Lua sort costs 5 seconds
Cpp sort costs 3 seconds
Lua sort costs 5 seconds
Cpp sort costs 3 seconds
Lua sort costs 5 seconds
Cpp sort costs 2 seconds
Lua sort costs 6 seconds
Cpp sort costs 3 seconds
Lua sort costs 5 seconds
Cpp sort costs 3 seconds
Lua sort costs 5 seconds
Cpp sort costs 2 seconds
Lua sort costs 6 seconds
Cpp sort costs 2 seconds
Lua sort costs 5 seconds
--------- lua script called end ---------
--------------------------------------------------------
--------------------------------------------------------
--------------------- Test finish ----------------------
--------------------------------------------------------


--------------------------------------------------------
Operating System: Linux
CPU Architecture: x86-64, 64-bit
Compiler: GCC, Version: 8.3.1
Cpp version: 201103
------------------ Test on DEBUG mode ------------------
--------------------- Test start -----------------------
--------------------------------------------------------
--------------------------------------------------------
PROJECT_SOURCE_DIR = /root/DSA
--------- lua script called begin ---------
Cpp sort costs 13 seconds
Lua sort costs 5 seconds
Cpp sort costs 13 seconds
Lua sort costs 6 seconds
Cpp sort costs 13 seconds
Lua sort costs 5 seconds
Cpp sort costs 14 seconds
Lua sort costs 5 seconds
Cpp sort costs 14 seconds
Lua sort costs 5 seconds
Cpp sort costs 13 seconds
Lua sort costs 6 seconds
Cpp sort costs 13 seconds
Lua sort costs 5 seconds
Cpp sort costs 13 seconds
Lua sort costs 5 seconds
Cpp sort costs 13 seconds
Lua sort costs 5 seconds
Cpp sort costs 13 seconds
Lua sort costs 5 seconds
--------- lua script called end ---------
--------------------------------------------------------
--------------------------------------------------------
--------------------- Test finish ----------------------
--------------------------------------------------------
 ]]

function Test()
    test_sort_prof()
end
