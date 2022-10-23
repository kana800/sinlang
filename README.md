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


### Table Of Content

- [Chapter 4: Scanner](https://github.com/kana800/sinlang/tree/chp4)
- [Chapter 5: Representing Code](https://github.com/kana800/sinlang/tree/chp4)


### [Introduction to Grammars and BNF](https://www.youtube.com/watch?v=F25ez8s3AsQ)

#### Syntax

syntax of language is the structure of a language.

Example: 
>The girl ate the pasta
correct syntax
> girl pasta the ate the 
incorrect syntax

#### Semantics

semantics is the meaning of the language.

- wrong syntax results in no meaning
- In English(NL), correct syntax could also result in something meaningless. **We need to avoid this in programming**. 
- syntax impacts the semantics

#### Terminals or Terminal Symbols

- Base tokens of the language. For a programming language these can be
    - keywords
    - operators and other symbols
    - the character that can be used in identifiers, numbers, or other program elements

#### Nonterminals or Nonterminal Symbols

- Represent pieces of the structure for a grammar.
- For English these would include:
    - noun 
    - verb
    - noun phrase, verb phase
- For Programming Language
    - statements
    - conditions
    - subroutine

#### Productions, or Production Rules

- These are rules that make up the grammar. 
- They translate a nonterminal to a sequence of one or more nonterminals or terminals

Example:
- A sentence is a noun phrase followed by a verb phrase
- A verb phrase is a verb or a verb followed by a noun phrase
- A verb is one of list of words

#### Expressing a Grammar

##### Elements of BNF
 

### Running

I have set the `GenerateAst.cpp` in the `tools` directory; To build the `GenerateAst.cpp` You need to
