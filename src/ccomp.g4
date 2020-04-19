grammar ccomp;

axiom : function_definition+ ;

function_definition : TYPE NAME '(' ')' '{' (instruction)* '}' ;

instruction :
  RETURN expr ';'           #return
| TYPE NAME (',' NAME)* ';' #declaration
| NAME '=' expr ';'         #affectation
;

expr :
  CONST #constant
;

TYPE :
  'int32_t'
| 'int64_t'
;

RETURN : 'return' ;
CONST : [0-9]+ ;
NAME : [a-zA-Z][a-zA-Z0-9_]*;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
