/**
	\file Mlem2d.h
	\brief Archivo que contiene la definición de la clase Mlem2d. 
	Clase derivada de Mlem, que define el algoritmo Mlem para los sinogramas2d genérico. Que
	supone un fov circular.

	\todo
	\bug
	\warning
	\author Martín Belzunce (martin.a.belzunce@gmail.com)
	\date 2010.11.11
	\version 1.1.0
*/
#ifndef _MLEM2D_H_
#define _MLEM2D_H_

#include <Mlem.h>
#include <Sinogram2D.h>
#include <Logger.h>

using namespace::std;


// DLL export/import declaration: visibility of objects
#ifndef LINK_STATIC
	#ifdef WIN32               // Win32 build
		#ifdef DLL_BUILD    // this applies to DLL building
			#define DLLEXPORT __declspec(dllexport)
		#else                   // this applies to DLL clients/users
			#define DLLEXPORT __declspec(dllimport)
		#endif
		#define DLLLOCAL        // not explicitly export-marked objects are local by default on Win32
	#else
		#ifdef HAVE_GCCVISIBILITYPATCH   // GCC 4.x and patched GCC 3.4 under Linux
			#define DLLEXPORT __attribute__ ((visibility("default")))
			#define DLLLOCAL __attribute__ ((visibility("hidden")))
		#else
			#define DLLEXPORT
			#define DLLLOCAL
		#endif
	#endif
#else                         // static linking
	#define DLLEXPORT
	#define DLLLOCAL
#endif



/**
    \brief Clase abstracta del método de reconstrucción MLEM.
    Esta clase abstracta define de forma general una reconstrucción del tipo MLEM. Las clases derivadas
	omplementarán los distintos tipos de reconstrucción, sea 2D, 3D, o con cualquier otra particularidad.Los
	parámetros de reconstrucción son seteados a través de las distintas propiedades de la clase. 
	
    \todo 
*/
#ifdef __cplusplus
//extern "C"
#endif
class DLLEXPORT Mlem2d : public Mlem
{  
    /// Proyección a reconstruir.
    /* Objeto del tipo Projection que será la entrada al algoritmo de reconstrucción,
    puede ser alguno de los distintos tipos de proyección: sinograma 2D, sinograma 3D, etc. */
    Sinogram2D* inputProjection;
    
    /// Sinograma con factores multiplicativos en el modelo de proyección.
    /** Objeto del tipo Sinogram2D con el factor multiplicativo en el proyector, o sea debe 
      * incluir factores de atenuación y de normalización entre otros. 
      */
    Sinogram2D* multiplicativeProjection;
    
    /// Sinograma con el factor aditivo en el modelo de proyección.
    /** Objeto del tipo Sinogram2D que será el factor aditivo en la proyección.
      * Este sinograma es un termino aditivo en la proyección por lo que debe incluir corrección por
      * randoms y scatter. El término aditivo debe estar dividido por el multiplicative factor, 
      * ya que este se aplica solo en la sensitivity image.  
    */
    Sinogram2D* additiveProjection;
    
    /// Método que calcula la imagen de sensibilidad.
    /* Método que hace la backprojection de una imagen cosntante para obtener
    la imagen de sensibilidad necesaria para la reconstrucción. */
    bool computeSensitivity(Image*);
    
  public:
    /// Constructores de la clase.
    /* Constructor que carga los parámetros base de una reconstrucción MLEM 2d para el tgs. */
    Mlem2d(Sinogram2D* cInputProjection, Image* cInitialEstimate, string cPathSalida, string cOutputPrefix, int cNumIterations, int cSaveIterationInterval, bool cSaveIntermediate, bool cSensitivityImageFromFile, Projector* cForwardprojector, Projector* cBackprojector);
    
    /// Constructores de la clase a partir de un archivo de configuración.
    /* Constructor que carga los parámetros base de una reconstrucción MLEM
    a partir de un archivo de configuración con cierto formato dado. */
    Mlem2d(string configFilename);
    
    /// Método que carga desde un archivo interfile el factor multiplicativo del modelo de proyección.
    /**  Este método habilita el factor multiplicativo en el forward model de la proyección.
    */
    bool setMultiplicativeProjection(string acfFilename);
    
    /// Método que carga un sinograma desde un archivo interfile con el término aditivo en el modelo de la proyección.
    /**  Este método habilita el termino aditivo en el forward model del proyector. El término aditivo
    * debe estar dividido por el multiplicative factor, ya que este se aplica solo en la sensitivity image.
    */
    bool setAdditiveProjection(string acfFilename);
    
    /// Sobrecarga de setMultiplicativeProjection que carga un sinograma para el factor multiplicativo desde otro sinograma.
    /**  Este método habilita el factor multiplicativo y carga un sinograma para ello.
    */
    bool setMultiplicativeProjection(Sinogram2D* multiplicative);
    
    /// Sobrecarga de setAdditiveProjection que carga un sinograma para el factor aditivo desde otro sinograma.
    /**  Este método habilita el factor aditivo y carga un sinograma para ello.
    */
    bool setAdditiveProjection(Sinogram2D* additive);
    
    /// Método que realiza la reconstrucción de las proyecciones. 
    bool Reconstruct();
		
};

#endif
