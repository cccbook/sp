# 語法

Hack 語言的結構

```
class ClassName
{
  field variable declarations;
  static variable declarations;
  constructor type { parameterList ) {
    local variable declarations;
    statements
  }
  method type { parameterList ) {
    local variable declarations;
    statements
  }
  function type { parameterList ) {
    local variable declarations;
    statements
  }
}
```

## 典型的語法範例

```
program: statement;
statement: whileStatement
        | ifStatement
        | // other statement possibilities ...
        | '{' statementSequence '}'
whileStatement: 'while' '(' expression ')' statement
ifStatement: simpleIf
        | ifElse
simpleIf: 'if' '(' expression ')' statement
ifElse: 'if' '(' expression ')' statement
        'else' statement
statementSequence: '' // null, i.e. the empty sequence
        | statement ';' statementSequence
expression: // definition of an expression comes here
        // more definitions follow
```

## Jack 的 BNF

https://github.com/wokibe/Jack2C/blob/master/bnf.txt

```
; BNF definitions for the Jack2 language
;=======================================

; kittekat jan/2017

; additions to Jack from http://nand2tetris.org/:
;   named constants
;   character constants
;   break

; my xBNF syntax:
;   'xxxx'   terminal value, text enclosed in quotes will appear
;   xxxx     non-terminal value, will be replaced by other constructs
;   x y      concatenation, sequence of constructs
;   x | y    either x or y can appear
;   x?       x appears 0 or 1 times
;   x*       x appears 0 or more times
;   ( )      parentheses are used for grouping of constructs
;   %xab     shorthand for hex representation of character, e.g.: %x61 for 'a'
;   %xab-cd  value range, e.g.: %x30-33 for '0' | '1' | '2' | '3'

; Syntax for the Tokenizer
;-------------------------
token           = whitespace | integerConstant | stringConstant | keyword |
                  keywordConstant | symbol | identifier
symbol          = '{' | '}' | '(' | ')' | '[' | ']' | '.' | ',' | ';' | '+' |
                  '-' | '*' | '/' | '&' | '|' | '<' | '>' | '=' | '~' | quote
keyword         = 'class' | 'constructor' | 'function' | 'method' | 'static ' |
                  'field' | 'void' | 'int' | 'char' | 'boolean' | 'let' |
                  'do' | 'if' | ‘else’ | 'while' | 'return' | 'break' | 'const'
keywordConstant = 'true' | 'false' |'null' | 'this'

; Syntax for the Parser
;----------------------
class           = 'class' className '{' (classVarDec | constDec)*
                  subroutineDec* '}'
classVarDec     = ( 'static' | 'field' ) type varName ( ',' varName )* ';'
type            = 'int' | 'char' | 'boolean' | className
subroutineDec   = ( 'constructor' | 'function' | 'method' )
                  ( 'void' | type ) subroutineName '(' parameterList ')'
                  subroutineBody
parameterList   = (( type varName ) ( ',' type varName )* )?
subroutineBody  = '{' (varDec | constDec)* statements '}'
varDecl         = 'var' type varName ( ',' varName )* ';'
constDec        = 'const' '=' constValue ';'
constValue      = constName '=' (('-'* integerConstant) | charConstant) ';'
className       = identifier
subroutineName  = identifier
varName         = identifier
constName       = identifier
statements      = statement*
statement       = letStatement | ifStatement | whileStatement |
                  doStatement | returnStatement
letStatement    = 'let' varName ( '[' expression ']')? = expression ';'
ifStatement     = 'if' '(' expression ')' '{' statements '}'
                  ( 'else' '{' statements '}' )?
whileStatement  = 'while' '(' expression ')' '{' whileBody '}'
whileBody       = statements ('break' statements)*
doStatement     = 'do' subroutineCall ';'
returnStatement = 'return' expression? ';'
expression      = term (op term)*
term            = integerConstant | stringConstant | keywordConstant |
                  charConstant | varName ( ‘[’ expression ']' )? |
                  subroutineCall | '(' expression ')' | unaryOp term
subroutineCall  = subroutineName '(' expressionList ')' | ( className |
                  varName ) '.' subroutineName '(' expressionList ')'
expressionList  = ( expression ( ',' expression )* )?
op              = '+' | '-' | '*' | '/' | '&' | '|' | '<' | '>' | '='
unaryOp         = '-' | '~'
keywordConstant = 'true' | 'false' | 'null' | 'this'
integerConstant = digit (digit)*          ; in the range -32767..32767
stringConstant  = '"' ( stringCharacter )* '"'
charConstant    = quote printable quote
identifier      = ( letter | underscore) (letter | digit | underscore)*
letter          = %x41-5A | %x61-7A       ; A..Z, a..z
digit           = %x30-39                 ; 0..9
underscore      = '_'
stringCharacter = ' ' | '!' | %x23-7E     ; #..~ (= all printable except ")
quote           = %x27
whiteSpace      = ( blank | tab ) ( blank | tab )*
blank           = ' '
tab             = %x0B
comment         = eolComment | longComment
eolComment      = '//' printable* newline           ; comment till End of Line
longComment     = '/*' (printable | newline)* '*/'  ; not nestable
printable       = %x20-7e
newline         = %x0D                              ; for *nix OS sytems
```


