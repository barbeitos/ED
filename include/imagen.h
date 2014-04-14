/**
  * @file imagen.h
  * @brief Fichero para tratar las imagenes en blanco y negro
  *
*/

#ifndef IMAGEN_H_
#define IMAGEN_H_

#include<iostream>
#include<string>
#include "imagenES.h"

using namespace std;

/**
 * @brief Pixel
 * 
 * Constante de tipo unsigned char
 */
//#define Pixel unsigned char

/**
 * @brief TAM_DEF
 * 
 * Constante con tamaño 1000 para crear imagenes con un tamño estandar
 */
#define TAM_DEF 10000

enum Tipo_Pegado {
  OPACO = 0,
  BLENDING = 1
};

struct Pixel{
  unsigned char r,g,b;
  unsigned char transparencia;
};

class Imagen{
private:
  /**
   * @brief Matriz de punteros que contiene los datos de la imagen
   */
  Pixel **data;
  
  /**
   * @brief Tamaño de filas y columnas, para saber el ancho y alto de la imagen.
   * @param nf número de filas
   * @param nc número de columnas
   */
  int nf, nc;
  
  /**
   * @brief Borra los datos de la imagen que lo invoca
   * @pre Una vez que es invocado el método ya no se podrá acceder a los datos de la imagen.
   */
  void Borrar();
  
  /**
   * @brief Realiza una copia de una imagen dada
   * @param I Imagen que va a ser copiada
   */
  void Copiar(const Imagen & I);
  
  /**
   * @brief Reserva de memoria para crear una imagen
   * @param filas cantidad de filas que se va a reservar para la memoria de la imagen
   * @param columnas cantidad de columnas que se va a reservar para la memoria de la imagen
   */
  void Reservar(int filas, int columnas);
  
public:
  /**
   * @brief Constructor por defecto
   */
  Imagen();
  
  /**
   * @brief Constructor para reservar memoria
   * @param filas cantidad de filas que se va a reservar
   * @param columnas cantidad de columnas que se va a reservar
   */
  Imagen(int filas, int columnas);
  
  /**
   * @brief Constructor de copia
   * @param I imagen que se va a copiar en la nueva imagen
   */
  Imagen(const Imagen &I);
  
  /**
   * @brief Destructor de Imagenes
   */
  ~Imagen();
  
  /**
   * @brief Devuelve un pixel
   * @param i fila del pixel que vamos a devolver
   * @param j columna del pixel que vamos a devolver
   * @retval Pixel devuelve el pixel de la posición @a i y @a j
   */
  Pixel & operator()(int i, int j);
  
  /**
   * @brief Devuelve un pixel que no se puede modificar (constante)
   * @param i fila del pixel que vamos a devolver
   * @param j columna del pixel que vamos a devolver
   * @retval Pixel devuelve el pixel de la posición @a i y @a j
   */
  Pixel & operator()(int i, int j) const;
  
  /**
   * @brief Copia una imagen, si es la misma no hace nada pero si es destinta borra
   * su memoria, reserva la memoria de la que se pasa por referencia y luego se copia.
   * @param I imagen que va a ser copiada en la asignación
   */
  Imagen & operator=(const Imagen &I);
  
  /**
   * @brief Modifica un pixel en una posición
   * @param f fila donde se encuentra el pixel que va a ser modificado
   * @param c columnas donde se encuentra el pixel que va a ser modificado
   * @param v pixel que va a modificar el pixel actual
   */
  void Set(int f, int c, Pixel v);
  
  /**
   * @brief Obtiene un pixel en una posición
   * @param f fila donde se encuentra el pixel que va a ser devuelto
   * @param c columna donde se encuentra el pixel que va a ser devuelto
   */
  Pixel Get(int f, int c) const ;
  
  /**
   * @brief Escribe una imagen en disco
   * @param file contiene los datos de la imagen para ser guardada
   * @retval true se ha escrito la imagen con éxito
   * @retval false ha habido un error y no se ha podido escribir correctamente la
   * imagen en disco.
   */
  bool EscribirImagen(const char file[]) const;
  
  /**
   * @brief Lee una imagen del disco
   * @param file carga todos los datos en este buffer para tener la imagen
   * @retval true la imagen ha sido leida correctamente y esta en memoria
   * @retval false la imagen no ha sido leida correctamente. Ha habido un error.
   */
  bool LeerImagen(const char file[], string nombre_mascara="");
  
  /**
   * @brief Devuelve la cantidad de filas de pixeles que hay en la imagen
   */
  int num_filas() const;
  
  /**
   * @brief Devuelve la cantidad de columnas de pixeles que hay en la imagen
   */
  int num_cols() const;
  
  
  /**
   * @brief Devuelve una Imagen la cual se le ha pegado otra.
   * @param i fila donde empezar el pegado de la imagen
   * @param j columnas donde empezar el pegado de la imagen
   * @param Ip Imagen que se va a pegar en la imagen base
   * @param tp Tipo de pegado que se va a realizar de @a Ip en la imagen base
   */
  void PutImagen(int i, int j, Imagen &Ip, Tipo_Pegado tp);
};

#endif