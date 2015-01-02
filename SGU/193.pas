{ SGU 193 Chinese Girls' Amusement }
program sgu193;
const 
	Max = 2005;
type
	BIGNUM= record
		d:array[1..Max] of integer;
		len:integer;
	end;
 
procedure minus1(var num:BIGNUM);
var
	i:integer;
begin
	for i := 1 to num.len do
	begin
		if num.d[i] > 0 then
		begin
			dec(num.d[i]);
			break;
		end;
		num.d[i]:= 9;
	end;
	if num.d[num.len] = 0 then
		dec(num.len);
end;
 
procedure div2(var num:BIGNUM);
var 
	i, t:integer;
begin
	t:= 0;
	with num do
	begin
		for i:= len downto 1 do
		begin
			t:= 10 * t + d[i];
			d[i] := t shr 1; 
			t := t and 1;
		end;
		while d[len] = 0 do
			dec(len);
	end;
end;
 
function strtobignum(var s:string):BIGNUM;
var 
	res:BIGNUM;
	i, j, l:integer;
begin
	fillchar(res, sizeof(res), 0);
	l := length(s);
	j:=1;
	for i:= l downto 1 do
	begin
		res.d[j]:= ord(s[i]) - ord('0');
		inc(j);
	end;
	res.len := l;
	strtobignum:= res;
end;
 
procedure print(var num:BIGNUM);
var 
	i:integer;
begin
	for i:= num.len downto 1 do
		write(num.d[i]);
end;
 
var 
	s:string;
	x:BIGNUM;
begin
	readln(s);
	x:= strtobignum(s);
	if (x.d[1] and 1 = 1) then begin
		div2(x);
	end else begin
		div2(x);
		if (x.d[1] and 1 = 0) then
		begin
			minus1(x);
		end
		else
		begin
			minus1(x);
			minus1(x);
		end
	end;
	print(x);
end.
