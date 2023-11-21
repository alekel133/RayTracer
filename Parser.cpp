#include "Parser.h"

void getTransform(int &token, Primitive* prim){
  if(token != TOK_TRANS) {
    cout << "Error, expect transform data in definition." << endl;
    exit(EXIT_FAILURE);
  }


  token = yylex();
  if(token != TOK_COLON) {
    cout << "Error, expected ':' after 'transform'." << endl;
    exit(EXIT_FAILURE);
  }

  int cont = 1; 
  token = yylex();
  while(token == TOK_TX || token == TOK_TY || token == TOK_TZ || token == TOK_RX || token == TOK_RY || token == TOK_RZ || token == TOK_SC) {
    if(!cont) break;
    switch(token) {
        case TOK_TX: {
          token = yylex();
          if(token != TOK_COLON) {
            cout << "Error, no colon after TX." << endl;
            exit(EXIT_FAILURE);
          }
          
          token = yylex();
          if(token != TOK_FLOAT && token != TOK_INT) {
            cout << "Error, invalid translationn format: "<< yytext << "." << endl;
            exit(EXIT_FAILURE);
          }
          
          prim->mat = translateX(stod(yytext)) * prim->mat;

          token = yylex();
          if(token != TOK_COMMA) {
            if(token == TOK_SEMI) {
              cont = 0;
            }
            else {
              cout << "Error, expecte ',' or ';' in transformation list." << endl;
              exit(EXIT_FAILURE);
            }
          }
          break;
        }

        case TOK_TY: {
          token = yylex();
          if(token != TOK_COLON) {
            cout << "Error, no colon after TY." << endl;
            exit(EXIT_FAILURE);
          }
          
          token = yylex();
          if(token != TOK_FLOAT && token != TOK_INT) {
            cout << "Error, invalid translationn format: " << yytext << "." << endl;
            exit(EXIT_FAILURE);
          }
          
          prim->mat = translateY(stod(yytext)) * prim->mat;

          token = yylex();
          if(token != TOK_COMMA) {
            if(token == TOK_SEMI) {
              cont = 0;
            }
            else {
              cout << "Error, expecte ',' or ';' in transformation list." << endl;
              exit(EXIT_FAILURE);
            }
          }
          break;
        }

        case TOK_TZ: {
          token = yylex();
          if(token != TOK_COLON) {
            cout << "Error, no colon after TZ." << endl;
            exit(EXIT_FAILURE);
          }
          
          token = yylex();
          if(token != TOK_FLOAT && token != TOK_INT) {
            cout << "Error, invalid translationn format: "<< yytext << "." << endl;
            exit(EXIT_FAILURE);
          }
          
          prim->mat = translateZ(stod(yytext))*prim->mat;

          token = yylex();
          if(token != TOK_COMMA) {
            if(token == TOK_SEMI) {
              cont = 0;
            }
            else {
              cout << "Error, expecte ',' or ';' in transformation list." << endl;
              exit(EXIT_FAILURE);
            }
          }
          break;
        }

        case TOK_RX: {
          token = yylex();
          if(token != TOK_COLON) {
            cout << "Error, no colon after RX." << endl;
            exit(EXIT_FAILURE);
          }
          
          token = yylex();
          if(token != TOK_FLOAT && token != TOK_INT) {
            cout << "Error, invalid rotation format: " << yytext << "." << endl;
            exit(EXIT_FAILURE);
          }
          
          prim->mat = rotateX(stod(yytext))*prim->mat;

          token = yylex();
          if(token != TOK_COMMA) {
            if(token == TOK_SEMI) {
              cont = 0;
            }
            else {
              cout << "Error, expecte ',' or ';' in transformation list." << endl;
              exit(EXIT_FAILURE);
            }
          }
          break;
        }

        case TOK_RY: {
          token = yylex();
          if(token != TOK_COLON) {
            cout << "Error, no colon after RY." << endl;
            exit(EXIT_FAILURE);
          }
          
          token = yylex();
          if(token != TOK_FLOAT && token != TOK_INT) {
            cout << "Error, invalid translationn format: " << yytext << "." << endl;
            exit(EXIT_FAILURE);
          }
          
          prim->mat = rotateY(stod(yytext))*prim->mat;

          token = yylex();
          if(token != TOK_COMMA) {
            if(token == TOK_SEMI) {
              cont = 0;
            }
            else {
              cout << "Error, expecte ',' or ';' in transformation list." << endl;
              exit(EXIT_FAILURE);
            }
          }
          break;
        }

        case TOK_RZ: {
          token = yylex();
          if(token != TOK_COLON) {
            cout << "Error, no colon after RZ." << endl;
            exit(EXIT_FAILURE);
          }
          
          token = yylex();
          if(token != TOK_FLOAT && token != TOK_INT) {
            cout << "Error, invalid translationn format: " << yytext << "." << endl;
            exit(EXIT_FAILURE);
          }
          
          prim->mat = rotateZ(stod(yytext))*prim->mat;

          token = yylex();
          if(token != TOK_COMMA) {
            if(token == TOK_SEMI) {
              cont = 0;
            }
            else {
              cout << "Error, expecte ',' or ';' in transformation list." << endl;
              exit(EXIT_FAILURE);
            }
          }
          break;
        }

        case TOK_SC: {
        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, no colon after RZ." << endl;
          exit(EXIT_FAILURE);
        }
        
        token = yylex();
        if(token != TOK_FLOAT && token != TOK_INT) {
          cout << "Error, invalid translationn format: " << yytext << "." << endl;
          exit(EXIT_FAILURE);
        }
        
        prim->mat = scale(stod(yytext))*prim->mat;

        token = yylex();
        if(token != TOK_COMMA) {
          if(token == TOK_SEMI) {
            cont = 0;
          }
          else {
            cout << "Error, expecte ',' or ';' in transformation list." << endl;
            exit(EXIT_FAILURE);
          }
        }
        break;
      }
      default: {
        cout << "Error, invalid transform." << endl;
        exit(EXIT_FAILURE);
      }
    }
    if(cont) token = yylex();
  }
}

void getLabelData(int token, Primitive* prim, vector<Primitive*> &prims) {
  if(token != TOK_LABEL) {
    cout << "Error, expected 'label'." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_COLON) {
    cout << "Error, expected ':' after 'label'." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_STRING) {
    cout << "Error, expected string literal leading qutoe." << endl;
    exit(EXIT_FAILURE);
  }

  string tmp = yytext;
  tmp.erase(
    std::remove(tmp.begin(), tmp.end(), '\"'), 
    tmp.end());

  prim->name = tmp;

  token = yylex();
  if(token != TOK_SEMI) {
    cout << "Error, no terminating semicolon." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_PARENT) {
    cout << "Error, expected parent data to follow label." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_COLON) {
    cout << "Error, expected ':' to follow 'parent'." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token == TOK_NONE) {
    prim->parent = nullptr;

    token = yylex();
    if(token != TOK_SEMI) {
      cout << "Error, no terminating semicolon." << endl;
      exit(EXIT_FAILURE);
    }
    return;
  }

  if(token != TOK_STRING) {
    cout << "Error, invalid sring data after leading quote." << endl;
    exit(EXIT_FAILURE);
  }

  string tmp2 = yytext;
  tmp2.erase(
    std::remove(tmp2.begin(), tmp2.end(), '\"'), 
    tmp2.end());


  int check = 0;
  for(int i = 0; i < prims.size(); ++i) {
    if(prims[i]->name == tmp2){
      prim->parent = prims[i];
      check = 1;
    }
  }
  if(!check){
    cout << "Error, parent doesn't exist." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_SEMI) {
    cout << "Error, no terminating semicolon." << endl;
    exit(EXIT_FAILURE);
  }
}


void getMaterialData(int token, Primitive* prim) {
  if(token != TOK_MAT) {
    cout << "Error, expected material data." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_COLON) {
    cout << "Error, expected ':' to follow 'material'." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_DIFF) {
    cout << "Error, expected diffuse color in material description." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_COLON) {
    cout << "Error, expected ':' to follow 'diffuse'." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_OPENPAREN)  {
    cout << "Error, expected diffuse color." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  int i = 0;
  prim->material.diffuse = (int*) malloc(3*sizeof(int));
  prim->material.specular = (int*) malloc(3*sizeof(int));
  while(token == TOK_INT) {
    prim->material.diffuse[i] = stoi(yytext);

    token = yylex();
    if(token == TOK_COMMA) {
      token = yylex();
      ++i;
      continue;
    }

    if(token != TOK_CLOSEPAREN) {
      cout << "Error, unterminated color list." << endl;
      exit(EXIT_FAILURE);
    }
    
    token = yylex();
    if(token != TOK_SEMI) {
      cout << "Error, no terminating semicolon" << endl;
      exit(EXIT_FAILURE);
    }
  }

  token = yylex();
  if(token != TOK_SPEC) {
    cout << "Error, expected diffuse color in material description." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_COLON) {
    cout << "Error, expected ':' to follow 'diffuse'." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_OPENPAREN)  {
    cout << "Error, expected specular color." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  i = 0;
  while(token == TOK_INT) {
    prim->material.specular[i] = stoi(yytext);

    token = yylex();
    if(token == TOK_COMMA) {
      token = yylex();
      ++i;
      continue;
    }

    if(token != TOK_CLOSEPAREN) {
      cout << "Error, unterminated color list." << endl;
      exit(EXIT_FAILURE);
    }
    
    token = yylex();
    if(token != TOK_SEMI) {
      cout << "Error, no terminating semicolon" << endl;
      exit(EXIT_FAILURE);
    }
  }

  token = yylex();
  if(token != TOK_SHINE) {
    cout << "Error, expected diffuse color in material description." << endl;
    exit(EXIT_FAILURE);
  }

  token = yylex();
  if(token != TOK_COLON) {
    cout << "Error, expected ':' to follow 'diffuse'." << endl;
    exit(EXIT_FAILURE);
  }
  token = yylex();
  if(token != TOK_FLOAT) {
    cout << "Error, expected float." << endl;
    exit(EXIT_FAILURE);
  }

  prim->material.shine = stod(yytext);

  token = yylex();
  if(token != TOK_SEMI) {
    cout << "Error, no terminating smeicolon." << endl;
    exit(EXIT_FAILURE);
  }
}


int parseFile(char* filename, ParseData &data ) {
  int token;
  int cont = 1;

  srand(time(NULL));
  
  yyin = fopen(filename, "r");

  yyout = stdout;

  token = yylex();
  while(true) {
    if(token == TOK_EOF) {
      break;
    }

    // Parse based on token values
    switch(token){

      // Get Height Data, make sure input file matches expected pattern;
      case TOK_HEIGHT:{
        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, no height specified." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_INT) {
          cout << "Error, invalid height format" << endl;
          exit(EXIT_FAILURE);
        }

        data.height = stoi(yytext);
        
        token = yylex();
        if(token != TOK_SEMI) {
            cout << "Error, expected ';' after assignement.";
            exit(EXIT_FAILURE);
        }
        break;
      }

      // Get Width Data
      case TOK_WIDTH:{
        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, no width specified." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_INT) {
          cout << "Error, invalid width format" << endl;
          exit(EXIT_FAILURE);
        }

        data.width = stoi(yytext);
        
        token = yylex();
        if(token != TOK_SEMI) {
            cout << "Error, expected ';' after assignement.";
            exit(EXIT_FAILURE);
        }
        break;
      }

      // Get FOV data
      case TOK_FOV:{
        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, no fov specified." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_INT) {
          cout << "Error, invalid fov format" << endl;
          exit(EXIT_FAILURE);
        }

        data.FOV = stoi(yytext);
        
        token = yylex();
        if(token != TOK_SEMI) {
            cout << "Error, expected ';' after assignement.";
            exit(EXIT_FAILURE);
        }
        break;
      }

      case TOK_AMB:{
        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, no fov specified." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_FLOAT) {
          cout << "Error, invalid fov format" << endl;
          exit(EXIT_FAILURE);
        }

        data.ambient = stod(yytext);
        
        token = yylex();
        if(token != TOK_SEMI) {
            cout << "Error, expected ';' after assignement.";
            exit(EXIT_FAILURE);
        }
        break;
      }

      case TOK_PL: {
        PointLight *p = new PointLight();
        
        token = yylex();
        if(token != TOK_OPENBRACK) {
          cout << "Error, invalid light data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        getLabelData(token, p, data.prims);

        token = yylex();
        if(token != TOK_INTEN) {
          cout << "Error, expected intensity.";
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, expeceted ':' after 'intensity'.";
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_FLOAT && token != TOK_INT) {
          cout << "Error, invalid intesity."  << endl;
          exit(EXIT_FAILURE);
        }

        p->intensity = stod(yytext);

        token = yylex();
        if(token != TOK_SEMI) {
          cout << "Error, no terminating semicolon." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_COLOR) {
          cout << "Error, expected color data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, expected color data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_OPENPAREN) {
          cout << "Error, expected color data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        int i = 0;
        p->color = (int*) malloc(3*sizeof(int));
        while(token == TOK_INT) {
          p->color[i] = stoi(yytext);
          
          token = yylex();
          if(token == TOK_COMMA) {
            token = yylex();
            ++i;
            continue;
          }

          if(token != TOK_CLOSEPAREN) {
            cout << "Error, unterminated color list." << endl;
            exit(EXIT_FAILURE);
          }

          token =  yylex();
          if(token != TOK_SEMI) {
            cout << "Error, no terminating semicolon." << endl;
            exit(EXIT_FAILURE);
          }
          break;
        }

        token = yylex();
        getTransform(token, p);

        token = yylex();
        if(token != TOK_CLOSEBRACK) {
          cout << "Error, no terminating bracket." << endl;
          exit(EXIT_FAILURE);
        }
        data.lights.push_back(p);
        break;
      }

      case TOK_DL: {
        DirectionalLight *d = new DirectionalLight();
        
        token = yylex();
        if(token != TOK_OPENBRACK) {
          cout << "Error, invalid light data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        getLabelData(token, d, data.prims);

        token = yylex();
        if(token != TOK_INTEN) {
          cout << "Error, expected intensity.";
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, expeceted ':' after 'intensity'.";
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_FLOAT && token != TOK_INT) {
          cout << "Error, invalid intesity."  << endl;
          exit(EXIT_FAILURE);
        }

        d->intensity = stod(yytext);

        token = yylex();
        if(token != TOK_SEMI) {
          cout << "Error, no terminating semicolon." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_COLOR) {
          cout << "Error, expected color data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, expected color data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_OPENPAREN) {
          cout << "Error, expected color data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        int i = 0;
        d->color = (int*) malloc(3*sizeof(int));
        while(token == TOK_INT) {
          d->color[i] = stoi(yytext);
          token = yylex();
          if(token == TOK_COMMA) {
            token = yylex();
            ++i;
            continue;
          }

          if(token != TOK_CLOSEPAREN) {
            cout << "Error, unterminated color list." << endl;
            exit(EXIT_FAILURE);
          }

          token =  yylex();
          if(token != TOK_SEMI) {
            cout << "Error, no terminating semicolon." << endl;
            exit(EXIT_FAILURE);
          }
          break;
        }

        token = yylex();
        getTransform(token, d);

        token = yylex();
        if(token != TOK_CLOSEBRACK) {
          cout << "Error, no terminating bracket." << endl;
          exit(EXIT_FAILURE);
        }
        data.lights.push_back(d);
        break;
      }

      case TOK_CAMERA: {
        data.camera = new Camera();

        token = yylex();
        if(token == TOK_SEMI) {
          continue;
        }
        
        if(token != TOK_OPENBRACK) {
          cout << "Error, expected ';' or transform data after 'Camera'." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        getTransform(token, data.camera);
        
        token = yylex();
        if(token != TOK_CLOSEBRACK) {
          cout << "Error, no closing bracket." << endl;
          exit(EXIT_FAILURE);
        }
        break;
      }

      case TOK_SPHERE: {
        Sphere *sphere = new Sphere();

        token = yylex();
        if(token != TOK_OPENBRACK) {
          cout << "Error, invalid sphere data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        getLabelData(token, sphere, data.prims);

        token = yylex();
        getMaterialData(token, sphere);

        token = yylex();
        getTransform(token, sphere);

        token = yylex();
        if(token != TOK_CLOSEBRACK) {
          cout << "Error, no closing bracket." << endl;
          exit(EXIT_FAILURE);
        }
        
        data.prims.push_back(sphere);
        break;
      }

      case TOK_PLANE: {
        Plane *plane = new Plane();

        token = yylex();
        if(token != TOK_OPENBRACK) {
          cout << "Error, invalid sphere data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        getLabelData(token, plane, data.prims);
        
        token = yylex();
        getMaterialData(token, plane);

        token = yylex();
        getTransform(token, plane);

        token = yylex();
        if(token != TOK_CLOSEBRACK) {
          cout << "Error, no closing bracket." << endl;
          exit(EXIT_FAILURE);
        }
        data.prims.push_back(plane);
        break;
      }
      case TOK_MESH: {
        Mesh *mesh = new Mesh();
        Vertex *vertex;
        Face* face;

        token = yylex();
        if(token != TOK_OPENBRACK) {
          cout << "Error, invalid sphere data." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        getLabelData(token, mesh, data.prims);

        token = yylex();
        getMaterialData(token, mesh);

        token = yylex();
        if(token != TOK_VLIST)  {
          cout << "Error, expected vertex list." << endl;
        }

        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, expecte 'vertices:'." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        while(token == TOK_VERTEX) {
          vertex = new Vertex; 
          
          token = yylex();
          vertex->coord[0] = stod(yytext);
          token = yylex();
          vertex->coord[1] = stod(yytext);
          token = yylex();
          vertex->coord[2] = stod(yytext);
          mesh->vertices.push_back(*vertex);
          token = yylex();
        }

        if(token != TOK_FLIST) {
          cout << "Error, expected face list." << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        if(token != TOK_COLON) {
          cout << "Error, expected 'faces:'. " << endl;
          exit(EXIT_FAILURE);
        }

        token = yylex();
        while(token == TOK_FACE) {
          face = new Face;
          
          token = yylex();
          face->vertices[0] = stoi(yytext)-1;
          token = yylex();
          face->vertices[1] = stoi(yytext)-1;
          token = yylex();
          face->vertices[2] = stoi(yytext)-1;

          mesh->faces.push_back(*face);
          token = yylex();
        }

        getTransform(token, mesh);

        token = yylex();
        if(token != TOK_CLOSEBRACK) {
          cout << "Error, no closing bracket." << endl;
          exit(EXIT_FAILURE);
        }
        data.prims.push_back(mesh);
        break;
      }
    }
    token = yylex();
  }
  return 0;
}
