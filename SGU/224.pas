{ SGU 297 Little Queens }
program sgu224;
var 
	n, k :integer;
	ans:longint;
	vx, vy :array[1..10] of boolean;
	vo1: array[-10..10] of boolean;
	vo2: array[2..20] of boolean;
procedure dfs(x,d:integer);
var
	i, j:integer;
begin
	if d = k then
	begin
		inc(ans);
		exit;
	end;
	if (d > n) or (n - x + 1+ d < k) then
		exit;
	for i := x to n do
	begin
		for j := 1 to n do
		begin
			if (vy[j] = true) or (vo1[i - j] = true) or (vo2[j + i] = true) then continue;
			vx[i] := true; vy[j] := true; vo1[i - j] := true; vo2[j + i] := true;
			dfs(i+1,d + 1);
			vx[i] := false; vy[j] := false; vo1[i - j] := false; vo2[j + i] := false;
		end;
	end;
 
end;
 
begin
	read(n, k);
	fillchar(vx, sizeof(vx), 0);
	fillchar(vy, sizeof(vy), 0);
	fillchar(vo1, sizeof(vo1), 0);
	fillchar(vo2, sizeof(vo2), 0);
	ans:= 0;
	dfs(1, 0);
	writeln(ans);
end.
