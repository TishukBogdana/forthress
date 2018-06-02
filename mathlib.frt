( целочисленная библиотека )
: pow ( число степень )
 swap 
 dup
 rot 
 dup 0 = if 1 
  else 
  1 for over * endfor 
	swap drop
  then ;
 ( x -operations )
: xdup 0 for dup endfor ;
: xdrop 0 for drop endfor ;
: xsum 0 for + endfor ;
: xmul 0 for * endfor ;
: 2inc 
	>r 1 + r> 1 + ;
: 2dec
	>r 1 - r> 1 - ;
( блок проверок чисел на свойства )

: mod2 dup 2 % not ; ( четность )

: prim ( простота )
 dup 2 = not 
 if dup 2 < not 
	if dup dup 2 / 2 
		do  
			if dup r@ % 
			else 0 then 
		cr loop
 	else 0 then 
else 1 then  swap drop ;

: primal ( примарность )
dup 0 < if dup 2 * - then
2
   repeat 
 	over over  
	dup * %
 	if 1 + over over dup * <
	 if 1 1 
	 else 0 then 
        else 0 1 then 
   until ;

: lack ( проверка является ли число недостаточным )
1 0 -rot
over over 
	do over over % not
 	  if rot over + -rot 1 +  
	  else 1 + 
	  then 
	loop 
drop <  ;
      
: perfect ( совершенное число )
1 0 -rot
over over 
	do over over % not
 	  if rot over + -rot 1 +  
	  else 1 + 
	  then 
	loop 
drop = ;

: excess ( избыточное число )
dup lack 
swap perfect 
lor not ;
( поиск)
: nod ( наибольший общий длитель )
over over < 
if swap then  
 repeat 
 over over % dup 
	if swap drop 0 
	else drop 1 
	then
until ;

: nok ( наименьшее общее кратное)
over 
over 
nod 
-rot * 
swap / ; 

: aryph_prog_member ( a1 d num n-й член арифметической прогрессии)
1 - * + ;

: aryph_sum ( сумма n 1-х членов арифметической прогрессии a1 d n )
>r over over r@ -rot r>
aryph_prog_member
rot drop
rot + * 2 / ;

: geom_prog_member ( b1 q num n-й член геометрической прогрессии)
1 - pow * ;
: geom_sum ( b1 q n сумма n 1-х членов геометрической прогрессии)
over swap pow 
1 swap - 
rot * 
swap 1 swap - / ; 
( генераторы )

: fact ( факториал )
dup 
if 1 1 rot 0 
	do 
	dup 
	rot * 
	swap 1 + 
	loop 
    drop 
else drop 1 
then ;

: primgen ( возвращает простое число по номеру)
0 1 
	repeat dup prim 
		if swap 1 + swap 
		then  -rot over over - 0 = 
		if rot 1 
		else rot 1 + 0
		then
	until 
-rot drop drop ;

: fib ( Фибонначи )
  dup 0 < if ." Neg " else   
  dup 2 <   if  drop 1  
     else >r 1 1 r> 1 
	do swap over + loop 
            swap drop 
    then 
then ; 

: primalgen ( возвращает примарное число по номеру)
0 1 
	repeat dup prim 
		if swap 1 + swap 
		then  -rot over over - 0 = 
		if rot 1 
		else rot 1 + 0
		then
	until 
-rot drop drop ;




























 























