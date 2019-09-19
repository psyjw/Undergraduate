let
    var m : Integer;
    proc fac(n : Integer, var r : Integer)
        if n <= 1 then
            r := 1
        else begin
            fac(n - 1, r);
            r := n * r
        end;
    var x : Integer
in begin
    getint(m);
    fac(m, x);
    putint(x)
end
