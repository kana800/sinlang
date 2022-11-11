 <!-- PROJECT LOGO -->
<br />
<p style="text-align: center" align="center">
  <a href="https://github.com/kana800/sinlang">
  <img src=".images/sinlang.png" alt="logo"> 
  </a>

  <h3 align="center">cpplox</h3>
  <p align="center">
    <br />
    <a href="https://github.com/kana800/sinlang/issues">Report Bug</a>
  </p>
</p>


## Table Of Content

- [Chapter 4: Scanner](https://github.com/kana800/sinlang/tree/chp4)
- [Chapter 5: Representing Code](https://github.com/kana800/sinlang/tree/chp5)
- [Chapter 6: Parsing Expressions](https://github.com/kana800/sinlang/tree/chp6)

---


> Purpose of parse is show how the sentence and grammar are related. 
"How the grammar of the sentences matches the grammar that I have". 

### Precedence and Associativity

- Precedence determines which operator is evaluated first 
in an expression containing a mixture of operators.

- Associativity determines which operator is evaluated if the given
operators have the same precedence level. When an operator is 
**left-associative** (*left-to-right*), operators on the left evaluate
before those on the right. 

For example:

```
5 - 3 - 1 -> (5 - 3) - 1 // left associative
a = b = c -> a = (b = c) // right associative
```

The [reason](https://craftinginterpreters.com/parsing-expressions.html#ambiguity-and-the-parsing-game) 
we are using precedence levels and associativity;

Take the string `6 / 3 - 1` the syntax tree generated from the grammar can be
- (6 / 3) - 1
- 6 / ( 3 - 1 )

To avoid expression getting parsed into different syntax trees; we will be using 
precedence levels and associativity.

For `Lox` we will be using `C` precedence rules.

|Name|Operators|Associates|
|----|---------|----------|
|Equality| `== !=` | left |
|Comparison| `> >= < <=` | left |
|Term | `- +` | left |
|Factor | `/ *` | left |
|Unary | `! -` | right |

---

```
expression     → equality ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
               | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;
```

---


> A parser has two jobs: 
1. Given a valid sequence of tokens, produce a corresponding syntax tree.
2. Given an invalid sequence of tokens, detect any errors and tell the 
user about their mistakes.

### [Types of Languages/Grammar](https://youtu.be/SToUyjAsaFk?t=1487)

Parser can be categorized into:

- LL 
- LR
- Ambiguous Grammars
- Ambiguous Languages

- LL
    - LL(k) LL(1): One token look-ahead, Top-Down Recursive Descent. Simple fast
    algorithms. Good error reporting. East for humans to Parse. 
    
- LR
    - LR(k)
    - SLR
    - LALR

### References

- [Parse Trees](https://www.youtube.com/watch?v=SYQVxGnlpZM&t=9s)
- [Recursive Descent Parsing](https://www.youtube.com/watch?v=SToUyjAsaFk)
- [Recursive Descent Parser Example](https://www.youtube.com/watch?v=eVwl0hkI21Y)

