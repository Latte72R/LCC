
#ifndef _9CC_H_
#define _9CC_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Tokenizer
//

typedef enum {
  TK_RESERVED, // 記号
  TK_IDENT,    // 識別子
  TK_NUM,      // 整数トークン
  TK_RETURN,   // return
  TK_IF,
  TK_WHILE,
  TK_FOR,
  TK_EOF, // 入力の終わりを表すトークン
} TokenKind;

// Token type
typedef struct Token Token;
struct Token {
  TokenKind kind; // Token kind
  Token *next;    // Next token
  int val;        // If kind is TK_NUM, its value
  char *str;      // Token string
  int len;        // Token length
};

// Reports an error and exit.
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
void expect(char *op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
bool startswith(char *p, char *q);
Token *tokenize();

// ローカル変数の型
typedef struct LVar LVar;

struct LVar {
  LVar *next; // 次の変数かNULL
  char *name; // 変数の名前
  int len;    // 名前の長さ
  int offset; // RBPからのオフセット
};

//
// Parser
//

typedef enum {
  ND_ADD,     // +
  ND_SUB,     // -
  ND_MUL,     // *
  ND_DIV,     // /
  ND_EQ,      // ==
  ND_NE,      // !=
  ND_LT,      // <
  ND_LE,      // <=
  ND_ASSIGN,  // =
  ND_LVAR,    // ローカル変数
  ND_NUM,     // 整数
  ND_IF,      // if
  ND_ELSE,    // else
  ND_WHILE,   // while
  ND_FOR,     // for
  ND_RETURN,  // return
  ND_FUNCALL, // 関数呼び出し
  ND_BLOCK,   // { ... }
  ND_NONE,    // 空のノード
} NodeKind;

typedef struct Node Node;

// 抽象構文木のノード
struct Node {
  NodeKind kind; // ノードの型
  Node *lhs;     // 左辺
  Node *rhs;     // 右辺
  int val; // kindがND_NUMの場合はその数値, ND_FUNCALLの場合は関数名の長さ
  char *name; // kindがND_FUNCALLの場合のみ使う
  int offset; // kindがND_LVARの場合のみ使う
  int id;     // kindがND_IF, ND_WHILE, ND_FORの場合のみ使う
  Node *cond; // kindがND_IF, ND_WHILE, ND_FORの場合のみ使う
  Node *then; // kindがND_IFの場合のみ使う
  Node *els;  // kindがND_IFの場合のみ使う
  Node *init; // kindがND_FORの場合のみ使う
  Node *inc;  // kindがND_FORの場合のみ使う
  Node *body; // kindがND_BLOCKの場合のみ使う
};

Node *new_node(NodeKind kind);
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_num(int val);

Node *stmt();
Node *assign();
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

void program();

void gen(Node *node);

#endif
