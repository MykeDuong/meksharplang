### Mek# - A programming language with curly braces syntax and elegance of Lua.

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
- this keyword
- Initializer inherited from superclass' constructor.
- Inheritance with < operator.

## Standard Library - ?

## Precedence (bottom to top):
- program        → statement* EOF ;
- statement      → exprStmt | printStmt ;
- exprStmt       → expression ";" ;
- printStmt      → "print" expression ";" ;
- expression     → comma ;
- comma          → ternary ( "," ternary )* ;
- ternary        → equality ("?" expression ":" ternary)?
- equality       → comparison ( ( "!=" | "==" ) comparison )* ;
- comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
- term           → factor ( ( "-" | "+" ) factor )* ;
- factor         → unary ( ( "/" | "*" ) unary )* ;
- unary          → ( "!" | "-" ) unary | primary ;
- primary        → NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;
