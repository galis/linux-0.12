#GDB script
set print element 0
define ass
    disas /r
end

define pint
    x/1dw $arg0
end

define aa
    i r
    x /4
end

define ts
    si
    ass
end