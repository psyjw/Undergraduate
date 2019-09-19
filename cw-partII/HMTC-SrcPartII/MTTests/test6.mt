// Basic tests for the Part I and Part II extensions.

let
    var c : Character := 'x';
    var n : Integer;
    fun odd(n : Integer) : Boolean = !((n / 2) * 2 == n)
in begin
    if true then
        putint(1)
    elsif true then
        putint(2)
    else
        getint(n);
    repeat
        begin
            n := odd(n) ? n * 3 + 1 : n / 2;
            putint(n)
        end
    until n == 1;
    putchr(c)
end

    
