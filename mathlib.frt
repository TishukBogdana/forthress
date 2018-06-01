
: pow ( число степень )
 swap dup rot 
 dup 0 = if 1 
  else 
  1 for over * endfor 
-rot drop drop
  then ;
 ( x -operations )
: xdup 0 for dup endfor ;
: xdrop 0 for drop endfor ;
: xsum 0 for + endfor ;
: xmul 0 for * endfor ;
: xover 0 for over endfor ;

: mod2 dup 2 % not ; ( четность )

: prim ( простота )
 dup 2 = not 
 if dup 2 < not 
	if dup dup 2 / 2 do  if dup r@ % else 0 then cr loop
 	else 0 then else 1 then ;

: primal ( примарность )
dup 0 < if dup 2 * - then
2
repeat 
 over over  
	dup * %
 	if 1 + over over dup * < if 1 1 else 0 then 
        else 0 1 then 
   until ;

: nod ( наибольший общий длитель )
over over < if swap then  
 repeat over over % dup if swap drop 0 else drop 1 then until ;

: nok ( наименьшее общее кратное)
over over nod -rot * swap / ; 




























