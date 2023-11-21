//******************************************************
// List of tokens for SDF file parser.
//******************************************************

//************** List of Token Codes *******************

// Image Data Constructs
#define TOK_HEIGHT       1000
#define TOK_WIDTH        1001
#define TOK_FOV          1002
#define TOK_AMB          1003


// Scene Ovject Constructs
#define TOK_CAMERA       1004
#define TOK_SPHERE       1005
#define TOK_PLANE        1006
#define TOK_MESH         1007
#define TOK_PL           1008
#define TOK_DL           1009

// Object Data
#define TOK_ORIGIN       2000
#define TOK_RADIUS       2001
#define TOK_NORMAL       2002
#define TOK_LABEL        2003
#define TOK_PARENT       2004
#define TOK_DIFF         2005
#define TOK_SPEC         2006
#define TOK_SHINE        2007
#define TOK_COLOR        2008
#define TOK_INTEN        2009
#define TOK_TRANS        2010
#define TOK_VLIST        2011
#define TOK_FLIST        2012
#define TOK_VERTEX       2013
#define TOK_FACE         2014
#define TOK_MAT          2015

// Operators
#define TOK_EQUAL        3000
#define TOK_OPENPAREN    3001
#define TOK_CLOSEPAREN   3002
#define TOK_OPENBRACK    3003
#define TOK_CLOSEBRACK   3004
#define TOK_COMMA        3005
#define TOK_COLON        3006
#define TOK_SEMI         3007

// Literals
#define TOK_INT          4000
#define TOK_FLOAT        4001
#define TOK_STRING       4002
#define TOK_EOF          4003
#define TOK_UNKNOWN      4004
#define TOK_NONE         4005

// Transforms
#define TOK_RX           5000
#define TOK_RY           5001
#define TOK_RZ           5002
#define TOK_TX           5003
#define TOK_TY           5004
#define TOK_TZ           5005
#define TOK_SC           5006

