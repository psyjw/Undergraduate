let
    var m : Integer;
    var n : Integer;
    proc p(x : Integer) : Integer begin
        if x == 1 then
           p(x) := 1
        else
           p(x) := x * p(x-1)
    end
in begin
    getint(n);
    m := p(n);
    putint(m)
end
    