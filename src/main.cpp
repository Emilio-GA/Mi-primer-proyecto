/**
 * @file main.cpp
 * @author EMILIO GUILLÉN ÁLVAREZ
 */
#include <iostream>
#include <cstring>
#include <string>
#include "MPTools.h"
#include "Byte.h"
#include "Image.h"
#include "Histogram.h"

using namespace std;

static const int ERROR_ARGUMENTS = 100;

/**
 * @brief It waits until the key [INTRO] [RETURN] is pressed
 */
void pressReturnToContinue();

/**
 * @brief it shows help about the syntax of the command line
 */
void showHelp();

/**
 * @brief It breaks the program due to some error and shows a message
 * @param errorcode The type of error as declared in Image.h
 * @param errordata A message trying to describe the error
 */
void errorBreak(int errorcode, const string & errordata);

bool comprobarcantarg(int nargs);

int main(int nargs, char *args[]) {
    //He ajustado el showInWindow y el inspect
    string input = "", copy = "", output = "", zoom, from, texto;
    Image im_input, im_output, im_copyfrom, im_bin, im_cut, im_histogram, im_collection[10], im_zoom, result, im_from;
    int res, n, x, max = (Image::IMAGE_MAX_SIZE/8)-1, y, w, h, q, t, k, cont = 0;
    bool comp;
    char txt[max];
    if (comprobarcantarg(nargs)) {
        cout << "Faltan argumentos" << endl;
        return 2;
    }

    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-i") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -i" << endl;
                return 2;
            }
            cout << "...Reading image from" << args[q + 1] << endl;
            cont++;
            input = args[q + 1];
            x = 0;
            res = im_input.readFromFile(input.c_str());
            if (res != 0) {
                errorBreak(res, input);
            };

            im_output = im_input;

            cout << "[ " << "im_input" << "]" << im_input.inspect() << endl;
            im_input.showInWindow("input");

        }
    }

    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-c") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -c" << endl;
                return 2;

            }
            cout << "...Reading image from" << args[q + 1] << endl;
            copy = args[q + 1];
            res = im_copyfrom.readFromFile(copy.c_str());
            if (res) {
                errorBreak(res, copy);
            }


            im_copyfrom.showInWindow("copyfrom");
            cout << "[ " << "im_copyfrom" << "]" << im_copyfrom.inspect() << endl;

            w = im_copyfrom.width() + 5;
            h = im_copyfrom.height() + 5;
            im_bin = im_copyfrom.threshold();
            im_bin.showInWindow("threshold");
            cout << "[ " << "im_bin" << "]" << im_bin.inspect() << endl;


            im_output.pasteArea(x, 0, im_copyfrom);
            im_copyfrom.extractObjects(im_collection, n, 3); //cambiar a que coja los blancos
            im_cut = im_collection[0];
            im_collection[0].showInWindow("segmented");
            cout << "[ " << "im_collection[0]" << "]" << im_collection[0].inspect() << endl;


            x = x + w;
            im_output.pasteArea(x, 0, im_cut);
            im_output.pasteArea(x, h, im_bin);
            x = x + w;
            im_output.pasteArea(x, 0, im_cut, 64);
            im_output.pasteArea(x, h, im_bin, 64);
            x = x + w;
            im_output.pasteArea(x, 0, im_cut, 64, 50);
            im_output.pasteArea(x, h, im_bin, 64, 50);

        }

    }



    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-p") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -p" << endl;
                return 2;
            }
            string aux2 = args[q + 1];
            k = stoi(aux2);
            cout << "...Se ha cogido el plano "<< k << endl;
        }
    }

    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-ht") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -ht" << endl;
                return 2;
            }
            cout << "...Cogiendo el texto del archivo" << args[q+1] << endl;
            readFromFileT(args[q+1], texto);
            cout << "...Escondiendo el texto del archivo en el plano " << k << endl;
            comp = im_output.hideText(texto.c_str(),  k);
            if (comp == false) {
                cout << "El texto NO se ha encriptado correctamente" << endl;
            }
        }
    }

    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-st") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -st" << endl;
                return 2;
            }
            cout << "...Mostrando texto oculto del plano "<< k << endl;
           comp = im_output.showText(txt, max, k);
            if (comp == false) {
                cout << "El texto NO se ha desencriptado correctamente o no hay ningún texto inscriptado" << endl;
            } else {
                for (int l = 0; txt[l] != '\0' ; l++) {
                    cout << txt[l];
                }
                cout << endl;
            }
        }
    }
    

    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-hi") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -hi" << endl;
                return 2;
            }
            cout << "...Cogiendo la imagen del archivo" << args[q+1] << endl;
            from = args[q + 1];
            res = im_from.readFromFile(from.c_str());
            if (res != 0) {
                errorBreak(res, input);
            };
            cout << "...Escondiendo la imagen del archivo en el plano " << k << endl;
            comp = im_output.hideImage(k, im_from);
            if (comp == false) {
                cout << "La imagen NO se ha encriptado correctamente" << endl;
            }
        }
    }

    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-si") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -si" << endl;
                return 2;
            }
            cout << "...Mostrando imagen oculto del plano "<< k << endl;
            comp = im_output.showImage(k, result);
            if (comp == false) {
                cout << "La imagen NO se ha desencriptado correctamente o no hay ningún texto inscriptado" << endl;
            } else {
                result.showInWindow("result");
            }
        }
    }


    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-z") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -z" << endl;
                return 2;

            }
            aux = (args[q + 1]);
            if (aux == "-1") {
                cout << "...Zoom Out " << args[q + 1] << endl;
                im_zoom = im_input.zoomOut();

                im_zoom.showInWindow("zoom");
                cout << "[ " << "im_input" << "] " << im_zoom.inspect() << endl;

            }
            if (aux == "1") {
                cout << "...Zoom In " << args[q + 1] << endl;
                im_zoom = im_input.zoomIn();
                im_zoom.showInWindow("zoom");
                cout << "[ " << "im_input" << "] " << im_zoom.inspect() << endl;
            }
        }
    }





    for (q = 0; q < nargs; q++) {
        string aux(args[q]);
        if (aux == "-o") {
            if (q + 1 >= nargs) {
                cout << "Faltan un argumentos detrás de -o" << endl;
                return 2;
            }
            cout << "...Saving image into" << args[q + 1] << endl;

            im_output.saveToFile(args[q + 1]);
        }

    }
    if (cont == 0) {
        cout << "Falta un argumento obligatorio" << endl;
        return 2;
    }

    im_output.showInWindow("output");
    cout << "[ " << "Im_output" << "]" << im_output.inspect() << endl;


    pressReturnToContinue();
    return 0;
}

bool comprobarcantarg(int nargs) {
    bool i;
    if (nargs < 3) {
        return i = true;
    };
    return i = false;
}

void pressReturnToContinue() {
    char aux[10];
    cout << "Press [RETURN] to continue ...";
    cin.getline(aux, 1, '\n');
}

void showHelp() {
    cout << "Please use: -i <input> [-c <copyfrom> -z <zoom> -o <output>]" << endl;
    cout << "\n-i <input>\n\tInput image from <input>";
    cout << "\n-c <copyfrom>\n\tCopy clip from <copyfrom>";
    cout << "\n-z <zoom>\n\t+-1 zoom to the input image";
    cout << "\n-o <output>\n\tOutput image to <output>" << endl;
}

void errorBreak(int errorcode, const string & errordata) {
    switch (errorcode) {
        case ERROR_ARGUMENTS:
            cout << endl << "Error in call: " << errordata << endl;
            showHelp();
            break;
        case Image::IMAGE_ERROR_OPEN:
            cout << endl << "Error opening file " << errordata << endl;
            break;
        case Image::IMAGE_ERROR_DATA:
            cout << endl << "Data error in file " << errordata << endl;
            break;
        case Image::IMAGE_ERROR_FORMAT:
            cout << endl << "Unrecognized format in file " << errordata << endl;
            break;
        case Image::IMAGE_TOO_LARGE:
            cout << endl << "The image is too large and does not fit into memory" << errordata << endl;
            break;
    }
    std::exit(1);
}
