#pragma once
#include "JSONError.h"

class JSONObject
{

public:
	/* Constructores de JSONObject */
	/* El constructor por defecto inicializa un JSONObject vacío
	* Si se desea luego agregar un JSON a parsear se pueden usar las
	* funciones
	* parseString() definidas más abajo
	*/
	JSONObject();
	/* Permiten crear un JSONObject con el string s (en el segundo caso NULL
	* terminated)
	* recibido como parámetro.
	* En caso de surgir un error en el análisis del JSON (por ejemplo el
	* string recibido no es un JSON
	* o no cumple con las reglas de formato encontradas en www.json.org)
	* la clase JSONObject debe guardar el error en su interior
	* y se le informará al usuario cuando este invoque a getError mediante
	* el objeto JSONError
	*/
	JSONObject(string& s);
	JSONObject(const char * s);

	/* Devuelve en su nombre la cantidad de campos que contiene el
	* JSONObject */
	unsigned int getFieldCount(void);


	/* Devuelve en su nombre el tipo de campo de f. Los posibles tipos son
	* (todos en minúscula):
	* "object" si el campo f contiene un objeto JSON.
	* "array" si el campo f contiene un array.
	* "string" si el campo f contiene un string.
	* "number" si el campo f contiene un número.
	* "bool" si el campo f contiene "true" o "false"
	* "invalid" si el campo f no pertenece al JSONObject. En este último
	* caso genera un error que almacena internamente
	*/
	const char * getFieldType(const char * f);

	/* Devuelve en su nombre el tipo de elemento del array f (f es un campo
	* dentro del JSONObject de tipo array).
	* Los posibles tipos son (todos en minúscula):
	* "object" si el array f contiene un objeto JSON.
	* "array" si el array f contiene un array.
	* "string" si el array f contiene un string.
	* "number" si el array f contiene un número.
	* "bool" si el array f contiene "true" o "false"
	* "invalid" si el array f no pertenece al JSONObject. En este último
	* caso genera un error que almacena internamente
	* Nota: en el caso de que se encuentren elementos null dentro del
	* array, los vamos a tomar como objetos JSON vacíos
	* por lo que ante un null vamos a tomar que su "tipo" es object.
	*/
	const char * getArrayType(const char * f);

	/* Devuelve en su nombre el tamaño del campo f, donde por tamaño se
	* entiende:
	* si f es de tipo "object" la cantidad de campos que tiene el objeto
	* (pensar si en este caso conviene generar un JSONObject temporal) con
	* el contenido del campo f y devolver getFieldCount de dicho objeto).
	* si f es de tipo "array" devuelve la cantidad de elementos en el
	* arreglo.
	* si f es de tipo "string" devuelve la cantidad de caracteres en el
	* string.
	* si f es de tipo "number" devuelve sizeof(double).
	* si f es de tipo "bool" devuelve sizeof(bool).
	* si f es no pertenece al objeto devuelve 0. En este último caso genera
	* un error que almacena internamente
	*/
	unsigned int getFieldSize(const char * f);

	/* Devuelve true si el campo f se encuentra dentro del JSONObject
	* (primera iteración).
	* No tiene que iterar por todos los objetos JSON contenidos dentro del
	* actual. En otras palabras,
	* si el objeto actual tiene diversos campos que son a su vez objetos
	* JSON no debe analizarlos,
	* sino que se limita a analizar los campos del JSON actual. Si dentro
	* del objeto actual encuentra
	* el campo f devuelve true. De lo contrario false.
	* Esta función no genera errores que se almacenen internamente.
	*/
	bool isFieldPresent(const char * f);

	/* Devuelven en su nombre una variable creada en el heap con las
	* siguientes característias:
	* si f es de tipo "object" crea en el heap un JSONObject lo inicializa
	* con el objeto contenido en f y lo devuelve en su nombre
	* si f es de tipo "array" crea en el heap un arreglo de elementos tipo
	* getArrayType() y cantidad getFieldSize()
	* copia en dicho arreglo el arreglo contenido en f y lo devuelve en su
	* nombre.
	* si f es de tipo "string" crea en el heap un string, copia el string
	* contenido en f y lo devuelve en su nombre.
	* si f es de tipo "number" crea en el h
	* en su nombre.
	* si los elementos del arreglo son de tipo "number" crea en el heap un
	* double, lo inicializa con el elemento pos del arreglo y lo devuelve
	* en su nombre.
	* si los elementos del arreglo son de tipo "bool" crea en el heap un
	* bool, lo inicializa con true o false según el elemento pos del
	* arreglo y lo devuelve en su nombre.
	* si f no pertenece al JSONObject o la función encuentra un error
	* devuelve NULL en su nombre y genera un error que almacena
	* internamente.
	* pos es cero-based, por lo que pos=0 refiere al primer elemento del
	* arreglo, pos=1 al segundo y así sucesivamente. Siempre pos
	* getFieldSize().
	*/
	void * copyArrayValue(const char * f, unsigned int pos);

	/*
	* imprime uno a uno los campos del JSONObject y su tipo.
	* Por ejemplo, dado el JSON
	* {
	* "title": "example glossary",
	* "GlossDiv": {
	* "title": "S",
	* "GlossList": { (...) }
	* }
	*}
	* Imprimiría:
	*
	* Start of JSON Object:
	*
	* FIELD : TYPE
	* ---------------
	* title : string
	* GlossDiv: object
	*
	* End of JSON Object
	* un campo por línea.
	*/
	void print(void);

	/* Devuelve en su nombre un JSONError según se explica en JSONError.h*/
	JSONError getError(void);

	/*
	* En caso de generar un objeto JSON por defecto
	* con esta funciones se le puede pasar un buffer a analizar
	* si el análisis fuera correcto devuelven true.
	* caso contrario devuelve false y genera un error que almacena
	* internamente.
	* Si el objeto se creao con los constructores que reciben un buffer
	* con estas funciones podemos cambiar el JSON parseado por otro.
	*/
	bool parseString(const char * s);
	bool parseString(string& s);

	/*
	* Devuelve en su nombre true si el objeto JSON está vacío, o false en caso
	* contrario.
	*/
	bool isEmpty(void);


	/*
	* Nota: en el caso de recibir un JSON vacío (Ej: {}), se creará un objeto
	* tipo JSONObject donde la función getFieldCount() devuelve 0 (ya que dicho
	* objeto no tiene campos, y la función isEmpty() devuelve true.
	* En todo los otros casos isEmpty() devuelve false. A su vez, existe un
	* caso en donde el objeto JSON puede solamente contener un arreglo
	* (Ej: {[item1, item2, item3, etc]}. En este caso, el arreglo contenido por
	* el objeto JSON no está asociado a ningún campo, sin embargo el JSONObject
	* no está vacío por lo que isEmpty() devuelve false. A se vez,
	* getFieldCount() devuelve 0. Nos vamos a referir a este arreglo como el
	* “field” NULL, por lo tanto, si llamamos a getFieldType(NULL) en este caso
	* la función devuelve “array” en su nombre y si llamamos a
	* getArrayType(NULL), esta función devuelve el tipo de itemN en su nombre y
	* así sucesivamente para el resto de las funciones. Noten que este es el
	* único caso en que un objeto JSON puede tener valores sin estar asociados
	* a una campo.
	*/
};