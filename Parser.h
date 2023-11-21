/****************************************************************
 *Code for SDF File Parser
****************************************************************/
#include <iostream>
#include <stdio.h>
#include <vector>
#include "lexer.h"
#include "MathUtils.h"
#include "Primitive.h"
#include "Light.h"

using namespace std;

typedef struct {
  int height;
  int width;
  int FOV;
  double ambient;
  Camera *camera;
  vector<Primitive*> prims;
  vector<Light*> lights;
} ParseData;

extern "C" {
  extern FILE *yyin;
  extern FILE *yyout;
  extern int yylen;
  extern char *yytext;
  extern int yylineno;
  extern int yylex();
}

int parseFile(char* filename, ParseData &data);
