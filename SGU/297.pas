{ SGU 297 Fair-play }
program sgu297;
var 
	n, m, x, sum:longint;
begin
	readln(n, m);
	sum := 0;
	repeat
		read(x);
		inc(sum, x);
		dec(m);
	until m = 0;
	writeln(sum mod n);
end.
