local function test_is_prime_correctiness()
    local MAX = 100
    local isPrimeMethod = 1
    print("Test is prime: max num is: ", MAX)
    for i = 1, MAX, 1 do
        if DSALuaDLL.Is_prime(i, isPrimeMethod) then
            print(i, " is prime.")
        end
    end
end

function Test()
    test_is_prime_correctiness()
end
