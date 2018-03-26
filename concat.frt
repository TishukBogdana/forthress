
: cp
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
: concat 
       over over count swap count +
       rot rot swap 
	5 heap-alloc  
        cp cp swap - ;
 	
