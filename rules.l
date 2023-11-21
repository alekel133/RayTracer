/***************************************************************************************
Definitions for flex parsing
***************************************************************************************/

%option yylineno
%option noyywrap

%{
#include "lexer.h"
%}

%%
"//".*
"/*".*"*/"
[\n\t\r ]+
-?[[:digit:]]*[.][[:digit:]]*     { return TOK_FLOAT; }
-?[[:digit:]]*                    { return TOK_INT; }
["]([^"\\\n]|\\(.|\n))*["]        { return TOK_STRING; }
[']([^'\\\n]|\\(.|\n))*[']        { return TOK_STRING; }
"NONE"                            { return TOK_NONE; }
"Width"                           { return TOK_WIDTH; }
"Height"                          { return TOK_HEIGHT; }
"Ambient"                         { return TOK_AMB; }
"Camera"                          { return TOK_CAMERA; }
"Sphere"                          { return TOK_SPHERE; }
"Plane"                           { return TOK_PLANE; }
"Mesh"                            { return TOK_MESH; }
"Point"                           { return TOK_PL; }
"Direction"                       { return TOK_DL; }
"FOV"                             { return TOK_FOV; }
"origin"                          { return TOK_ORIGIN; }
"normal"                          { return TOK_NORMAL; }
"radius"                          { return TOK_RADIUS; }
"label"                           { return TOK_LABEL; }
"material"                        { return TOK_MAT; }
"parent"                          { return TOK_PARENT; }
"diffuse"                         { return TOK_DIFF; }
"specular"                        { return TOK_SPEC; }
"shine"                           { return TOK_SHINE; }
"color"                           { return TOK_COLOR; }
"intensity"                       { return TOK_INTEN; }
"transform"                       { return TOK_TRANS; }
"vertices"                        { return TOK_VLIST; }
"faces"                           { return TOK_FLIST; }
"v"                               { return TOK_VERTEX; }
"f"                               { return TOK_FACE; }
"RX"                              { return TOK_RX; }
"RY"                              { return TOK_RY; }
"RZ"                              { return TOK_RZ; }
"TX"                              { return TOK_TX; }
"TY"                              { return TOK_TY; }
"TZ"                              { return TOK_TZ; }
"SC"                              { return TOK_SC; }
"="                               { return TOK_EQUAL; }
"("                               { return TOK_OPENPAREN; }
")"                               { return TOK_CLOSEPAREN; }
"{"                               { return TOK_OPENBRACK; }
"}"                               { return TOK_CLOSEBRACK; }
","                               { return TOK_COMMA; }
":"                               { return TOK_COLON; }
";"                               { return TOK_SEMI; }
.                                 { return TOK_UNKNOWN; } 
<<EOF>>                           { return TOK_EOF; }
