local function test_sayhi_add()
    DSALuaDLL.SayHi()

    local sum = DSALuaDLL.Add(1, 8)
    print("Sum of (1, 8) is: ", sum)
end

function Test()
    test_sayhi_add()
end
