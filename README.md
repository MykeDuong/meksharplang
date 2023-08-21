### Mek# - A programming language with curly braces syntax inspired by Lua.

## Data types:
- Booleans: true/false.
- Numbers: double-precision floating points.
- Strings: within double quote.
- Nah: null value.

## Expressions:
- Arithmetic: Plus, Minus, Multiplication, Division
- Comparison & Equality: ==, >=, <=, <, >. No implicit conversion
- Logical Operators: and, or, not. Short-circuit supported.
- Precedence & Grouping: ()


## Statements:
- Expressions with semi-colon

## Variables:
- var keyword
- nah if left uninitialized
- Access and assign

## Control Flow:
- IF Statements
- While Loop
- For Loop

## Functions:
- Mandatory Parenthesis
- Declared with fun keyword 
- Closures: Functions are first-class
  + Referenced, passed around, stored in variables 
  + Local functions

## Object Orientation
- Class-based
- Methods are declared without fun keyword
- States: Assigning will create it if it does not exist yet.
- "this" keyword
- Initializer inherited from superclass' constructor.
- Inheritance with < operator.

## Standard Library - ?

## Precedence (bottom to top):
- program        → declaration* EOF ;
- declaration    → funDecl | varDecl | statement ;
- classDecl      → "class" IDENTIFIER "{" function* "}" ;
- funDecl        → "fun" function ;
- function       → IDENTIFIER "(" parameters? ")" block ;
- parameters     → IDENTIFIER ( "," IDENTIFIER )* ;
- varDecl        → "var" IDENTIFIER ( "=" expression )? ";" ;
- statement      → exprStmt | ifStmt | printStmt | whileStmt | breakStmt | returnStmt | block;
- exprStmt       → expression ";" ;
- breakStmt      → "break;" ;
- ifStmt         → "if" "(" expression ")" statement ( "else" statement )? ;
- printStmt      → "print" expression ";" ;
- whileStmt      → "while" "(" expression ")" statement ;
- block          → "{" declaration* "}" ;
- expression     → comma ;
- comma          → assignment ( "," assignment )* ;
- assignment     → (call ".") ? IDENTIFIER "=" assignment | ternary ;
- ternary        → equality ("?" expression ":" ternary)?
- logic_or       → logic_and ( "or" logic_and )* ;
- logic_and      → equality ( "and" equality )* ;
- equality       → comparison ( ( "!=" | "==" ) comparison )* ;
- comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
- term           → factor ( ( "-" | "+" ) factor )* ;
- factor         → unary ( ( "/" | "*" ) unary )* ;
- unary          → ( "!" | "-" ) unary | primary ;
- call           → primary ( "(" arguments? ")" )* | "." IDENTIFIER )* ;
- arguments      → assignment ( "," assignment )* ;
- function (expr)→ "(" parameters? ")" block | array;
- array          → '[' + element? + ']' | arrayElement;
- element        → assignment (',' + assignment)*;
- array element  → IDENTIFIER '[' expression + ']' | primary;
- primary        → NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" | IDENTIFIER | ;
