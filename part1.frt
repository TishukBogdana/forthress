( check if number is even )
: mod2 dup 2 % not ;

( check if number is prime/простое )
: prim
 dup 2 = not 
 if dup 2 < not 
	if dup dup 2 / 2 do  if dup r@ % else 0 then cr loop
 	else 0 then else 1 then ;

( allot )
: send
	cell% allot
	dup
	rot swap
	! 
;

( concat task )
: cp ( copies chars )
  repeat
    dup rot dup c@
    dup if
      rot
      c! 1 + swap
      1 +  0
    else drop swap 1
    then
  until
  drop drop
;
: concat ( concats strings )
       over over count swap count +
       rot rot swap 
	5 heap-alloc  
        cp cp swap - ;

( var 1 " tishuck" проверка на примарность)
: primal
dup 0 < if dup 2 * - then
2
repeat 
 over over  
	dup * %
 	if 1 + over over dup * < if 1 1 else 0 then 
        else 0 1 then 
   until ;
