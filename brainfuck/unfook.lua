-----------------------------
-- A brainfuck interpreter --
-----------------------------
function unfoock(bf)
    if bf == nil then print("Excusa?");return end
    local ch = bf:read(1)
    repeat
        if      ch == '+' then c[p] = c[p] + 1
        elseif  ch == '-' then c[p] = c[p] - 1 
        elseif  ch == '>' then p = p + 1
        elseif  ch == '<' then p = p - 1
        elseif  ch == '.' then io.write(c[p])
        elseif  ch == ',' then 
            if #b == 0 then
                for chara in io.read() do
                    table.insert(b, chara)
                end
            else
                c[p] = table.remove(b)
            end
        elseif  ch == '[' then
            curr = bf:seek()
            table.insert(t, tonumber(curr))
        elseif  ch == ']' then
            po = table.remove(t)
            if tonumber(c[p]) > 0 then
                bf:seek("set", po - 1)
            end
        end

        ch = bf:read(1)
    until ch == nil or ch == "\n"
    bf:close()
end
-- meta --
ascii = string.char
c = {}
t = {}
b = {}
p = 1
f = io.open(arg[1] or 0, "r")
for i=0, 30000 do c[i] = 0 end

unfoock(f)
