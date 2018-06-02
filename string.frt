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
: mcopy  over c@ over c! 2inc ;
: length
  0 swap 
	repeat dup c@ 0 = 
		if 1 
		else 1 + swap 1 + swap 0 
		then 
	until 
  drop ;
: string-copy 
	repeat 
	2dup 
        c@ >r r@ swap c!
	2inc
    r> not
	until  
2drop ;

: ?dup dup if dup then ; 
: ?prints dup if prints else ." <NULL> " drop then ;


: string-eq ( s1 s2 == ? )
	repeat
	over c@ over c@ = if ( x[i] = y[i] ) 
			dup c@ not  if 
				( end of string, return 1 )
				2drop 1 1 
				else 
				2inc 0  
				then 
		else 2drop 0 1
		then
	until
;

: string-prefix ( s1 prefix -  0 1)
	repeat
    dup c@ if 
        over c@ over c@ = not if ( x[i] = y[i] ) 
            2drop 0 1 
            else 2inc 0  
            then 
    else 2drop 1 1 then
	until
;



: string-allot 
    dup count 1 + allot dup >r swap string-copy r> ;

: string-new 
    dup count 1 + heap-alloc  >r r@ swap string-copy r> ;


: h" compiling not if 
    0 
    repeat readc dup QUOTE = if                     
        drop 
        dup dp @ + 0 swap c!
        1 + heap-alloc dup dp @ string-copy 1 
    else 
        >r dup dp @ + r> swap c! 
        1 + 
    0
    then
    until 
else
' " execute ' string-new ,
then
; IMMEDIATE 

: string-empty? 
    c@ 0 = ; 


