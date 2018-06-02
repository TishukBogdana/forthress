: string-hash 
  0 >r 
  repeat 
    dup c@ dup 
    if 
        r> 13 * + 65537 % 
        >r 1 +  0 
    else 
         drop drop r> 1
    then 
  until
;
