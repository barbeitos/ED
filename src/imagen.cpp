#include "imagen.h"

int Imagen::num_filas() const{
  return nf;
}
//--------------------------------------------------------------------------

int Imagen::num_cols() const{
  return nc;
}
//--------------------------------------------------------------------------

void Imagen::Borrar(){
  for(int i=0; i<nf; i++){
    delete [] data[i];
  }
  
  delete [] data;
  
  nf = 0;
  nc = 0;
}
//--------------------------------------------------------------------------

void Imagen::Copiar(const Imagen & I){
  nf = I.nf;
  nc = I.nc;
  
  for(int i=0; i<nf; i++){
    for(int j=0; j<nc; j++){
      this->Set(i,j,I.Get(i,j));
    }
  }
}
//--------------------------------------------------------------------------

void Imagen::Reservar(int filas, int columnas){
  data = new Pixel *[filas];
  
  for(int i=0; i<filas; i++){
    data[i] = new Pixel[columnas];
  }
  
  for(int i=0; i<filas; i++){
    for(int j=0; j<columnas; j++){
      data[i][j].r = 0;
      data[i][j].g = 0;
      data[i][j].b = 0;
      data[i][j].transparencia = 0;
    }
  }
  
  nf = filas;
  nc = columnas;
}


//Constructores
Imagen::Imagen(){
  data = new Pixel*[TAM_DEF];
  
  for (int i=0; i<TAM_DEF; i++){
    data[i] = new Pixel[TAM_DEF];
  }
  
  nf = TAM_DEF;
  nc = TAM_DEF;
  
  
  for(int i=0; i<nf; i++){
    for(int j=0; j<nc; j++){
      data[i][j].r = 0;
      data[i][j].g = 0;
      data[i][j].b = 0;
      data[i][j].transparencia = 0;
    }
  }
}
//--------------------------------------------------------------------------

Imagen::Imagen(int filas, int columnas){
  Reservar(filas, columnas);
}
//--------------------------------------------------------------------------

Imagen::Imagen(const Imagen &I){
  Reservar(I.nf, I.nc);
  Copiar(I);
}
//--------------------------------------------------------------------------

//Destructor
Imagen::~Imagen(){
  Borrar();
}
//--------------------------------------------------------------------------

Pixel & Imagen::operator()(int i, int j){
  return data[i][j];
}
//--------------------------------------------------------------------------

Pixel & Imagen::operator()(int i, int j) const{
  return data[i][j];
}
//--------------------------------------------------------------------------

Imagen & Imagen::operator= (const Imagen &I){
  if(this!=&I){
    Borrar();
    Reservar(I.nf, I.nc);
    Copiar(I); 
  }
  
  return *this;
}
//--------------------------------------------------------------------------

void Imagen::Set(int f, int c, Pixel v){
  data[f][c] = v;
}
//--------------------------------------------------------------------------

Pixel Imagen::Get(int f, int c) const{
  return data[f][c];
}
//--------------------------------------------------------------------------

bool Imagen::EscribirImagen(const char file[]) const{
  int filas = this->nf, columnas = this->nc;
  unsigned char buffer[filas*columnas*3];
  int pos = 0;
  
  for(int i=0; i<filas; i++){
    for(int j=0; j<columnas; j++){
      Pixel aux = Get(i,j);
      
      buffer[pos] = aux.r;
      pos++;
      buffer[pos] = aux.g;
      pos++;
      buffer[pos] = aux.b;
      pos++;
    }
  }
  
  if(EscribirImagenPPM(file, buffer, filas, columnas)){
    return true;
  }
  
  return false;
}
//--------------------------------------------------------------------------

bool Imagen::LeerImagen(const char file[], string nombre_mascara){
  int filas, columnas, pos=0, filasPGM, columnasPGM;
  const char *mascara;
  mascara = nombre_mascara.c_str();
  
  TipoImagen tipo = LeerTipoImagen(file, filas, columnas);
  LeerTipoImagen(mascara, filasPGM, columnasPGM);
  
  unsigned char bufferPPM[filas*columnas*3];
  unsigned char bufferPGM[filasPGM*columnasPGM];
 
  LeerImagenPGM(mascara, filasPGM, columnasPGM, bufferPGM);
  
  this->Reservar(filas, columnas);
  
  if(tipo == IMG_PPM){
    if(LeerImagenPPM(file, filas, columnas, bufferPPM)){
      for(int i=0; i<filas; i++){
	for(int j=0; j<columnas; j++){
	  Pixel aux;
	  
	  aux.r = bufferPPM[pos];
	  pos++;
	  aux.g = bufferPPM[pos];
	  pos++;
	  aux.b = bufferPPM[pos];
	  pos++;
	  
	  aux.transparencia = bufferPGM[i*columnasPGM+j];
	  
	  this->Set(i,j,aux);
	}
      }
      
      return true;
    }else{
      cerr << "Error al abrir la imagen" << endl;
      return false;
    }
  }else{
    cerr << "No se puede abrir este tipo de imagen" << endl;
    return false;
  }
  
  return false;
}
//--------------------------------------------------------------------------

void Imagen::PutImagen(int i, int j, Imagen &Ip, Tipo_Pegado tp){
  int filas = Ip.num_filas(), columnas = Ip.num_cols();
  
  if((num_filas()-i) < filas){
    filas = num_filas()-i;
  }
  
  if((num_cols()-j) < columnas){
    columnas = num_cols()-j;
  }
  
  if(tp == OPACO || tp == BLENDING){
    for(int x=i, q=0; q<filas; x++, q++){
      for(int y=j, w=0; w<columnas; y++, w++){
	if(tp == OPACO && Ip(q,w).transparencia == 255){
	  data[x][y] = Ip(q,w);
	}else if(tp == BLENDING && Ip(q,w).transparencia == 255){
	  Pixel aux;
	  
	  aux.r = (this->Get(x,y).r + Ip(q,w).r) / 2;
	  aux.g = (this->Get(x,y).g + Ip(q,w).g) / 2;
	  aux.b = (this->Get(x,y).b + Ip(q,w).b) / 2;
	  
	  data[x][y] = aux;
	}
      }
    }
  }else{
    cerr << "No se conoce ese tipo de pegado" << endl;
  }
}
//--------------------------------------------------------------------------
