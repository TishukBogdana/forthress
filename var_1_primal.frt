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
 
