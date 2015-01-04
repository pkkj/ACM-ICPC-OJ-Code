{
POJ 1662
POJ Monthly--2004.05.15: Coins
}
program pku1662;
{$APPTYPE CONSOLE}

var
    m,t:Int64;
    i:longint;
function so1ve(m:Int64):Int64;
    var i,t,d:Int64;
        flag:boolean;
begin
    if (m=1)then
    so1ve:= 2
    else
    begin
        d:=2*m+1;
        t:= 2;
        i:= 1;
        flag:=False;
        repeat
            if (t=1)then
            begin
                so1ve:= i*m;
                flag:=True;
            end
            else if (t=2*m)then
            begin
                so1ve:=i*m-1;
                flag:=True;
            end
            else
                t:= (t*2)mod d ;
                i:=i+1;
        until flag;
    end
end;
begin
    read(t);
    for i:= 1 to t do
    begin
        read (m);
        writeln ( so1ve(m) );
    end;
end.
