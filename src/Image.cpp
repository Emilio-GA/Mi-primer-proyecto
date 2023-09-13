/**
 * @file Image.cpp
 * @note To be implemented by students 
 * @author MP-DGIM, MP-IADE, MP-II (grupo B)
 * @author Emilio Guillén Álvarez:
 */
#include <iostream>
#include <istream>
#include <fstream>
#include <cstring>
#include <string>
#include "MPTools.h"
#include "Image.h"

using namespace std;

Byte ** reservarM(int tam) {
    Byte ** q = nullptr;
    if (tam > 0) {
        q = new Byte * [tam];
    }
    return q;
}

Byte * reservarm(int tam) {
    Byte * q = nullptr;
    if (tam > 0) {
        q = new Byte [tam];
    }
    return q;
}

void Image::apuntarpunt(int width, int height){
    _height = height;
    _width = width;
   _data = reservarM(_height); 
   _data[0] = reservarm(_height * _width );
   for ( int i = 1; i < _height ; i++ ){
     
      _data[i] = &(_data[0][i * _width ]);
}
}

Image::Image() {
    _height = 0;
    _width = 0;
    _data = nullptr;
}

Image::Image(int width, int height) {
    apuntarpunt( width, height);
   

}

int Image::height() const {
    return _height;
}

int Image::width() const {
    return _width;
}

void Image::setPixel(int x, int y, const Byte & v) {
    if ((x >= 0) && (y >= 0) && (x <= _width) && (y <= _height)) {
        _data[y][x] = v;
    }


}

int Image::getPixel(int x, int y) const {
    if ((x >= 0) && (y >= 0) && (x <= _width) && (y <= _height)) {
        Byte c(_data[y][x]);
        int n = c.getValue();
        return n;
    } else {
        int n = -1;
        return n;
    }

}



void Image::flatten(const Byte &b) {
    for (int y = 0; y < _height; y++) {
        for (int x = 0 ; x < _width ; x++){
        _data[y][x] = b;
        }   
    }

}
void Image::showInWindow(string title) const {
    string tempname = "data" + SLASH + ".hidden_" + title + ".pgm";


    mpSavePGMImage(tempname, (const unsigned char*) _data[0], _width, _height);
    mpDisplayImage(tempname, title);

}

string Image::inspect() const {
    string result = "";
    result = std::to_string(_width) + "x" + std::to_string(_height) + " " + std::to_string(mphash((const unsigned char*) _data[0], _height * _width));
    return result;
}

int Image::readFromFile(const char filename[]) {
    char a, b;
    int tope, dato, i;
    ifstream fentrada;
    fentrada.open(filename);
    if (fentrada) {
        fentrada >> a;
        if (!fentrada) {
            return IMAGE_ERROR_FORMAT;
        }
        if (a != 'P') {
            return IMAGE_ERROR_FORMAT; // menos de tresciento mil
        }

        fentrada >> b;
        if (!fentrada) {
            return IMAGE_ERROR_FORMAT;
        }
        if (b != '2') {
            return IMAGE_ERROR_FORMAT;
        }

        fentrada >> _width;
        if (!fentrada) {
            return IMAGE_ERROR_FORMAT;
        }
        fentrada >> _height;
        if (!fentrada) {
            return IMAGE_ERROR_FORMAT;
        };

        if (_height * _width > IMAGE_MAX_SIZE) {
            return IMAGE_TOO_LARGE;
        }

        fentrada >> tope;
        if (!fentrada) {
            return IMAGE_ERROR_FORMAT;
        }
        apuntarpunt(_width,  _height);
         

        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                fentrada >> dato;
                _data[y][x].setValue(dato);

                if (!fentrada) {
                    return IMAGE_ERROR_DATA;
                }

                if (dato > tope) {
                    return IMAGE_ERROR_FORMAT;
                }
            }
        }
        if ((i == _height * _width) && (fentrada >> dato)) {
            return IMAGE_ERROR_DATA;
        }


    } else {
        return IMAGE_ERROR_OPEN;
    }
    fentrada.close();
    return IMAGE_DISK_OK;
}

int readFromFileT(const char filename[], string & linea) {
    char dato;
    ifstream fentrada;
    fentrada.open(filename);
    if (fentrada) {
        while (fentrada.get(dato)) {
            linea.push_back(dato);
        }
    } else {
        return 1;
    }
    fentrada.close();
    return 0;
}





int Image::saveToFile(const char filename[]) const {
    char a = 'P', b = '2';
    int c = 255;
    ofstream fsalida;
    fsalida.open(filename);
    if (fsalida) {
        fsalida << a << b << endl;
        fsalida << _height << " " << _width << endl;
        fsalida << c << endl;
        for (int y = 0; y < _height; y++) {
        for (int x = 0 ; x < _width ; x++){
            fsalida << _data[y][x].getValue() << " ";
        }}
        fsalida.close();
    } else {
        return IMAGE_ERROR_OPEN;
    }
    return IMAGE_DISK_OK;
}

//int Image::saveToFileT(const char filename[],) const {
//    char a = 'P', b = '2';
//    int c = 255;
//    ofstream fsalida;
//    fsalida.open(filename);
//    if (fsalida) {
//        fsalida << a << b << endl;
//        fsalida << _height << " " << _width << endl;
//        fsalida << c << endl;
//        for (int y = 0; y < _height; y++) {
//        for (int x = 0 ; x < _width ; x++){
//            fsalida << _data[y][x].getValue() << " ";
//        }}
//        fsalida.close();
//    } else {
//        return IMAGE_ERROR_OPEN;
//    }
//    return IMAGE_DISK_OK;
//}

Histogram Image::getHistogram() const {
    int cont = 0;
    Histogram h;
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            h.setLevel(_data[y][x], h.getLevel(_data[y][x]) + 1);
        }
    }
    return h;
}



//Image Image::depictsHistogram() const {
//    Image result;
//
//    Histogram h = getHistogram();
//
//    result._height = 160;
//    result._width = 256;
//    //Imagen blanca
//    result._data = reservarM(result._height * result._width);
//    for (int n = 0; n < (result._height * result._width); n++) {
//
//        result._data[n] = 255;
//    }
//
//    //la escala de grises
//    for (int fila = 159; fila > (159 - 8); fila--) {
//
//        for (int i = 0; i <= 255; i++) {
//            result._data[fila * _width + i] = i;
//        }
//
//    }
//    
//
//    //los bordes en blanco
//    for (int columna = 0; columna <= 255; columna++) {
//
//        result._data[151 * _width + columna] = 255;
//        result._data[150 * _width + columna] = 0;
//        result._data[0 * _width + columna] = 255;
//    }
//
//
//    // pasa el histograma a una grafica de barritas
//    double max = 0;
//    for (int i = 0; i <= 255; i++) {
//        if (h.getLevel(Byte(i)) > max) {
//            max = h.getLevel(Byte(i));
//        }
//    }
//    for (int columna = 0; columna <= 255; columna++) {
//        double escala = h.getLevel(Byte(columna)) / max;
//        for (int fila = 150; fila > (149 - (escala * 149)); fila--) {
//            result._data[fila * _width + columna] = 0;
//        }
//    }
//    return result;
//};
//


void Image::extractObjects(Image set [], int &nimages, int maximages, double tolerance) {
    Histogram h = getHistogram();
    int cont = 0, pico[(maximages * 2) - 1], n = -1;
    nimages = 0;
    double tolreal = tolerance * h.getMaxLevel();
    for (int i = 0; i < h.size(); i++) {
        if (h.getLevel(Byte(i)) >= tolreal) {
            cont++;
            // [0, 1, 2 , 0, 2]
            if ((i + 1) == h.size() || h.getLevel(Byte(i + 1)) < tolreal) {
                pico[++n] = i - (cont - 1);
                pico[++n] = i;
                nimages++;
                cont = 0;
            }
        }
    }
    int f = nimages;
    Image result;
    result._height = _height;
    result._width = _width;
    result.apuntarpunt(result._width,result._height);// preguntar
    //    for (int r = 0; r < nimages; r++) { 
    for (int pos = 0; pos < (nimages * 2) - 1; pos += 2) {

        for (int n = 0; n < (result._height * result._width); n++) {
            result._data[0][n] = 0;
        }

        for (int i = 0; i < (result._height * result._width); i++) {
            for (int g = pico[pos]; g <= pico[pos + 1]; g++) {
                if (g == _data[0][i].getValue()) {
                    result._data[0][i].setValue(g);
                }
            }
        }
        set[--f] = result;
    }
}



         /**
      * It returns a binarization of the original image. All pixels  strictly greater than the value @a t
      * are set to 11111111 and the others to 00000000. Query method.
      * @param t The threshold. This value must be within [0,255]. In the case 
      * that the threshold is not within these bounds, an automatic threshold is chosen,
      * that is, the first level that leaves, at least the half of points less that
      * or equal to it. Input parameter, default value is set to -1.
      * @return A copy of the original image
      */
     Image Image::threshold(int t) const {
         if( t > 255 || t < 0) {
             Histogram h = getHistogram();
             t = h.getBalancedLevel();
             t++;// para q salga como en el pdf
         }
         Image result;
         result._height = _height;
         result._width = _width;
         result.apuntarpunt(result._width,result._height);// preguntar
         for(int i = 0; i < _height * _width; i++){
             result._data[0][i] = _data[0][i]; 
         }
         for (int j=0; j < _width * _height; j++){
             if  (result._data[0][j].getValue() <= t){
                 result._data[0][j] = 0;}
             else{
                 result._data[0][j] = 255;}
             }
         return result;
         };
/**
 * @brief It returns a subimage of the original image given by the parameters.
 * If the parameters exceed  the dimensions of the original image, then 
 * the cut image should not exceed those limits. Query method.
 * @param x x-coordinate of the top left corner.
 * @param y y-coordinate of the topt left corner
 * @param w width of the subimage
 * @param h height of the subimage. x,y,w, are input parameters.
 * @return The subimage cut
 */
Image Image::copyArea(int x, int y, int w, int h) const {// Actualizar los valores de y e x, los limites
        int tx, ty, tfx, tfy, tw, th;
    tx = std::min(std::max(x, 0), width());
    ty = std::min(std::max(y, 0), height());
    tfx = std::min(std::max(x + w, 0), width());
    tfy = std::min(std::max(y + h, 0), height());
    tw = tfx - tx;
    th = tfy - ty;
    Image aux(tw, th);
    aux.flatten(0);
    for (int y = 0; y < aux.height(); y++) {
        for (int x = 0; x < aux.width(); x++) {
            Byte b = getPixel(tx + x, ty + y);
            aux.setPixel(x, y, b);
        }
    }
    return aux;

    
    
    
    
//    int i = 0, xaux = x, yaux = y;
//    //copiar imagen
//    Image result;
//    result._height=h;
//    result._width=w;
//    
//    result._data = reservarM((w * h));// preguntar
//    if (x > _width || y > _height) {
//        return result;
//    } else {
//        if (y < 0) {
//            y = 0;
//        }
//        while (y < h + yaux && y <_height) {
//            if (x < 0) {
//                x = 0;
//            }
//            while (x < w+xaux && x <  _width) {
//                result._data[i] = _data[y * _width + x];
//                x++;
//                i++;
//            }
//            x = xaux;
//            y++;
//        }
//        return result;
//    }
}

/**
 * @brief It pastes a secondary image into the original image, at the given position,
 * into the same original image, which results modified. 
 * This operation should maintain the limits of the original image
 * @param x x-coordinate of the top left corner. input param
 * @param y y-coordinate of the topt left corner. input param
 * @param from The second image. input param
 * @param toneup value. input param
 * @param merge value for the combination of the 2 images. input param
 */

void Image::pasteArea(int x, int y, const Image &from, int toneup, int merge) {//si no le dan valor va con el agenciado
    int i = 0, xaux = x, yaux = y, cont = 0;
    if (x < _width && y < _height) {
        if (y < 0) {
            y = 0;
        }
        while (y < from._height + yaux && y < _height) {
            if (x < 0) {
                x = 0;
            }
            while (x < from._width + xaux && x < _width) {
                if (from._data[0][i].getValue() > toneup) {
                    _data[y][x].mergeByte(from._data[0][i], merge);
                }
                cont++;
                x++;
                i++;
            }
            if (x == _width) {
                i += (from._width - cont);
            }
            cont = 0;
            x = xaux;
            y++;
        }
    }
}


void Image::mergeByte(Byte &nuevo, Byte base, int merge) {
    nuevo.setValue( (nuevo.getValue() * (100 - merge) + base.getValue() * merge) / 100);
    
}

Image::~Image(){

//    _height = 0;
//    _width = 0;
    if (_data != nullptr) {
     if (_data[0] != nullptr) {
        delete[] _data[0];
    }      
        delete[] _data;
    }

}

Image::Image(const Image &from) {// preguntar 
    copy( from );  
}


Image & Image::operator=(const Image & rhs) {
    if (this != &rhs) {
        copy(rhs);
    }
    return *this;
}

Image Image::zoomIn() const {
    //coger la imagen
    //nueva imagen con el doble de columnas y filas
    Image zoom(2 * _width, 2 * _height);
    // colar por pares(uno si uno no)
    
    for (int i = 0; i < zoom._width; i++) {
        for (int j = 0; j < zoom._height; j++) {
            if ((i % 2 == 0) || (j % 2 == 0)){
                zoom.setPixel(i,j,getPixel(i/2,j/2));

                }
            }
    }


    for (int i = 0; i < zoom._width; i++) {
        for (int j = 0; j < zoom._height; j++) {
            if ((i % 2 != 0) && (j % 2 != 0)) {
                Image aux = copyArea((i / 2) - 1, (j / 2) - 1, 3, 3);
//                int nivel;
              int nivel = aux.getHistogram().getBalancedLevel();
               // nivel = 255;
                zoom.setPixel(i,j,nivel );
              //  zoom._data[j * zoom._width + i] = 
            }

        }
    }
    return zoom;
}
 
    
 Image Image::zoomOut() const {

    //coger la imagen

    // creas la mitad de columnas y filas
    Image zoom(_width / 2, _height / 2);
    for (int i = 0; i < zoom._width; i++) {
        for (int j = 0; j < zoom._height; j++) {

            zoom._data[j][i] = this->copyArea(i*2-1, j*2-1, 3, 3).getHistogram().getBalancedLevel();
        }
    }
//    // 
    return zoom;
    
 }
   
      void Image::clear() {
    if (_data != nullptr) {

        delete[] _data[0];

        delete[] _data;
        _data = nullptr;
    }
    _height = 0;
    _width = 0;
}

void Image::copy(const Image &rhs) {
    setSize(rhs._height, rhs._width);
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            _data[y][x] = rhs._data[y][x];
        }
    }
}

void Image::setSize(int newheight , int newwidth ){
    if ( newheight * newwidth != _height * _width){
        clear();
        
        apuntarpunt(newwidth,newheight );
                
        
        }
    _height = newheight;
    _width = newwidth;
}

bool Image::showImage(int k, Image &result) {
    //comprobar IMG
    int pos = 0;
    string cadena = "IMG";
    for (int p = 0; p < cadena.size(); p++) {
        Byte b(cadena[p]);        
        for (int cont = 0; cont < 8; pos++, cont++) {
            if (b.getBit(cont) != _data[0][pos].getBit(k)) {
                return false;
            }
        }
    }
    

    // W H
    for (int p = 0; p < 2; p++) {
        Byte b;
        for (int cont = 0; cont < 8; pos++, cont++) {

            if (_data[0][pos].getBit(k) == 1) {
                b.onBit(cont);
            } else {
                b.offBit(cont);
                
            }
        }
        if (p == 0) {
            result._width = b.getValue();
        }
        if (p == 1) {
            result._height = b.getValue();
        }
    }
    //sabemos que result._height y result._width  se repite la asignación
    result.apuntarpunt(result._width, result._height);
    //sacar los pixeles
    for (int y = 0; y < result._height; y++) {
        for (int x = 0; x < result._width; x++) {
            Byte b;
            //Byte b solo sustituye valores de 1 y 0 segun obtenga
            for (int cont = 0; cont < 8; pos++, cont++) {

                if (_data[0][pos].getBit(k) == 1) {
                    b.onBit(cont);
                } else {
                    b.offBit(cont);
                }
            }
            result._data[y][x] = b;

        }

    }
    return true;
}

/**
 * @brief It hides the image @a from by encoding the sequence of values of its pixels
 * into the bits of plane @a k. In order to do that, it first hides the cookieImage constant
 * to identify this plane as containing an image. Then it hides the width and the height. Then
 * all the bytes from left to right and top down. The self image is modified. Modifier method.
 * @param k The plane. input param
 * @param from The image to hide. input param
 * @return  It return true if the process is successful, false otherwise. 
 */

bool Image::hideImage(int k, const Image &from) {

    //condiciones
    if (from._height * from._width > 255 * 255) {
        cout << "La imagen a esconder es demasiado grande " << endl;
        return false;
    }
    if (_height * _width < (from.width() * from.height() + 5) - 8) {
        cout << "La imagen input no tiene los suficiemtes pixeles " << endl;
        return false;
    }
   

    int pos = 0;
    string cadena = "IMG";
    cadena +=  from._width;
    cadena +=  from._height;
  
    // IMG w h
    for (int p = 0; p < cadena.size(); p++) {
        Byte b(cadena[p]);
        for (int cont = 0; cont < 8; pos++, cont++) {

            if (b.getBit(cont) == 1) {
                _data[0][pos].onBit(k);
            } else {
                _data[0][pos].offBit(k);
            }
        }
    }
    //meter los pixeles
    for (int y = 0; y < from._height; y++) {
        for (int x = 0; x < from._width; x++) {

            for (int cont = 0; cont < 8; pos++, cont++) {

                if (from._data[y][x].getBit(cont) == 1) {
                    _data[0][pos].onBit(k);
                } else {
                    _data[0][pos].offBit(k);
                }
            }
        }

    }
    return true;
}

/**
 * @brief Steganography process.
 * It hides the cstring given within the k-plane especified. If no
 * plane is specified, the 0-plane is considered. If the cstring is too
 * large given the size of the original image, it must return false. Otherwise
 * the image hides the cstring and it returns true. In order to do that, it first
 * hides the cookieText constant, then the content of the cstring and finally,
 * the \0 delimiter converted in 00000000 encoded into the image. Modifier method.
 * @param the cstring to hide. input param
 * @param k the k-plane. input param
 * @return true if it has been possible, false otherwise
 */

bool Image::hideText(const char source [], int k) {

    //condiciones
    if (_height * _width >= (strlen(source) + 1)*8) {
        cout << "El texto a esconder es demasiado grande " << endl;
        return false;
    }

    

    int pos = 0;
    string cadena = "TXT";
    //    char c = _width;
    //    cadena.push_back(c);
    //    c = _height;
    //    cadena.push_back(c);

    // TXT
    for (int p = 0; p < cadena.size(); p++) {
        Byte b(cadena[p]);


        for (int cont = 0; cont < 8; pos++, cont++) {

            if (b.getBit(cont) == 1) {
                _data[0][pos].onBit(k);
            } else {
                _data[0][pos].offBit(k);
            }
        }
    }


    //meter las letras
    for (int n = 0; n < strlen(source) && pos < (_height * _width)-8 ; n++) {
        Byte b(source[n]);
        for (int cont = 0; cont < 8; pos++, cont++) {

            if (b.getBit(cont) == 1) {
                _data[0][pos].onBit(k);
            } else {
                _data[0][pos].offBit(k);
            }
        }
    }

    // mete /0
    Byte b('\0');
    for (int cont = 0; cont < 8; pos++, cont++) {

            if (b.getBit(cont) == 1) {
                _data[0][pos].onBit(k);
            } else {
                _data[0][pos].offBit(k);
            }
    }
    
    return true;
}

/**
 * @brief It checks that the k-plane contains a cstring if the first bytes 
 * of the image contains the cookieText constant. Afterwards, all the bytes
 * encided in plane k are extracted and the final one must be the \0 delimiter
 * @param hidden cstring to return the hidden string, if any
 * @param max size of the cstring, without including the \0 delimiter
 * @param k The plane
 * @return True if success, false otherwise.
 */
bool Image::showText(char hidden [], int max, int k) const {
    bool fin = false;

    //comprobar IMG
    int pos = 0;
    string cadena = "TXT";
    for (int p = 0; p < cadena.size(); p++) {
        Byte b(cadena[p]);
        for (int cont = 0; cont < 8; pos++, cont++) {
            if (b.getBit(cont) != _data[0][pos].getBit(k)) {
                return false;
            }
        }
    }



    //sacar las letras
    for (int l = 0; l <= max && fin == false; l++) {

        Byte b;
        for (int cont = 0; cont < 8; pos++, cont++) {

            if (_data[0][pos].getBit(k) == 1) {
                b.onBit(cont);
            } else {
                b.offBit(cont);
            }
        }

        hidden[l] = b.getValue();
        if ((l == max) && (b.getValue() != '\0')) {
            return false;
        }
        if ((b.getValue() == '\0')) {
            fin = true;
        }     
    }

    return true;
}






















