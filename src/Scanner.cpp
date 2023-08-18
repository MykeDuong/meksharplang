#include "./include/Scanner.h"

#include <cctype>
#include <string>
#include <unordered_map>
#include <vector>
#include "./include/TokenType.h"
#include "./include/Token.h"
#include "./include/ErrorHandler.h"
#include "./include/LiteralValue.h"
#include "./include/util.h"

std::unordered_map<std::string, TokenType> Scanner::keywords = {
  { "and", AND },
  { "break", BREAK },
  { "class", CLASS },
  { "else", ELSE},
  { "false", FALSE},
  { "for", FOR },
  { "fun", FUN },
  { "if", IF },
  { "nah", NAH },
  { "or", OR },
  { "print", PRINT },
  { "return", RETURN },
  { "super", SUPER },
  { "this", THIS },
  { "true", TRUE },
  { "var", VAR },
  { "while", WHILE } 
};

Scanner::Scanner(std::string source) : source(source) {}

std::vector<Token*> Scanner::scanTokens() {
  while (!isAtEnd()) {
    this->start = this->current;
    this->scanToken();
  }

  this->tokens.push_back(new Token(END_OF_FILE, "", new LiteralValue(), this->line));
  return tokens;
}

bool Scanner::isAtEnd() {
  return this->current >= this->source.length();
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
    case '(': addToken(LEFT_PAREN); break;
    case ')': addToken(RIGHT_PAREN); break;
    case '{': addToken(LEFT_BRACE); break;
    case '}': addToken(RIGHT_BRACE); break;
    case ',': addToken(COMMA); break;
    case '.': addToken(DOT); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case ';': addToken(SEMICOLON); break;
    case '*': addToken(STAR); break;
    case '?': addToken(QUESTION); break;
    case ':': addToken(COLON); break;
    case '!':
      addToken(match('=') ? BANG_EQUAL : BANG);
      break;
    case '=':
      addToken(match('=') ? EQUAL_EQUAL : EQUAL);
      break;
    case '<':
      addToken(match('=') ? LESS_EQUAL : LESS);
      break;
    case '>':
      addToken(match('=') ? GREATER_EQUAL : GREATER);
      break;
    case '/':
      if (match('/')) {
        // Ignore line as comment
        while (peek() != '\n' && !isAtEnd()) advance();
      } else if (match('*')) {
        blockComment();
      } else {
        addToken(SLASH);
      }
      break;
    case ' ':
    case '\t':
    case '\r':
      break;
    case '\n':
      this->line++;
      break;
    case '"': string(); break;
    default:
      if (util::isDigit(c)) {
        number(); 
      } else if (util::isAlpha(c)) {
        identifier();
      }else {
        ErrorHandler::error(line, "Unexpected character.");
      }
      break;
  }
}

void Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') this->line++;
    advance();
  }

  if (isAtEnd()) {
    ErrorHandler::error(line, "Unterminated String");
    return;
  }

  // The closing "
  advance();

  // Trim quotes
  std::string value = source.substr(start + 1, current - start - 2);
  this->addToken(STRING, new LiteralValue(value));
}

void Scanner::number() {
  while (util::isDigit(peek())) advance(); 

  if (peek() == '.' && std::isdigit(peekNext())) {
    // consume '.'
    advance();
    // continue with the number
    while (util::isDigit(peek())) advance();
  }

  addToken(
    NUMBER, 
    new LiteralValue(std::stod(source.substr(start, current - start)))
  );
}

void Scanner::identifier() {
  while (util::isAlphaNumeric(peek())) advance();
  
  std::string text = source.substr(start, current - start);

  TokenType type = keywords.find(text) == keywords.end() ? IDENTIFIER : keywords[text];
  addToken(type);
}

void Scanner::blockComment() {
  int count = 1;
  while (count != 0) {
    while (!isAtEnd() && (peek() != '*' && peek() != '/')) {
      if (peek() == '\n') line++;
      advance();
    };

    if (isAtEnd()) {
      ErrorHandler::error(line, "Unterminated Block Comment");
      return;
    }
    if (peek() == '*' && peekNext() == '/') {
      // Consume *
      advance();
      // Consume / 
      advance();
      count--;
    } else if (peek() == '/' && peekNext() == '*') {
      advance();
      advance();
      count++;
    } else {
      advance();
    }
  }
}

char Scanner::advance() {
  this->current++;
  return source.at(current - 1);
}

void Scanner::addToken(TokenType type) {
  addToken(type, new LiteralValue());
}

void Scanner::addToken(TokenType type, LiteralValue* literal) {
  std::string text = source.substr(this->start, this->current - this->start);
  this->tokens.push_back(new Token(type, text, literal, line));
}

bool Scanner::match(char expected) {
  if (this->isAtEnd()) return false;
  if (source.at(current) != expected) return false;

  current++;
  return true;
}

char Scanner::peek() {
  if (this->isAtEnd()) return '\0';
  return this->source.at(this->current);
}

char Scanner::peekNext() {
  if (current + 1 > source.length()) return '\0';
  return source.at(current + 1);
}

