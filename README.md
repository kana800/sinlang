<!-- PROJECT LOGO -->
<br />
<p style="text-align: center" align="center">
  <a href="https://github.com/kana800/sinlang">
  <img src="images/sinlang.png" alt="logo"> 
  </a>

  <h3 align="center">cpplox</h3>
  <p align="center">
    <br />
    <a href="https://github.com/kana800/sinlang/issues">Report Bug</a>
  </p>
</p>

### Scanning

Main focus of this chapter was to build the scanner. The scanner will break 
down the *string* you enter into *tokens*. The function `scanTokens()` will scan the 
*string* and tokens to the list. 

Each Token consists of `TokenType`, `lexeme`, `literal` and `line`.
- `TokenType`: Type of the [token](https://github.com/kana800/sinlang/blob/505c2d7bbef2e5e4318a8cd9148b3a84fde3fc0c/cpplox/TokenType.hpp#L6)
- [`Lexeme`](https://craftinginterpreters.com/scanning.html#lexemes-and-tokens): The lexemes are only the raw substrings of the source code
> `var lng = lox;` In this lexemes would be `var`, `lng`, `=`, `lox`, `;`
- `literal`: `lexemes` but for literal values. such as `numbers`, `strings`
- `line`: number of the line

### References

- [cpplox the-lambda-way](https://github.com/the-lambda-way/CppLox)
- [crafting interpreters](https://craftinginterpreters.com/scanning.html)
