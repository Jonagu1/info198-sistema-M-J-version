#include "../include/args.h"
#include "../include/dotenv.h"
#include "../include/util.h"
#include "../include/conteo.h"
#include "../include/calcula_funcion.h"
#include "../include/palindrome.h"
#include <cstring>
#include <string>
#include <cstring>
using namespace std;

int autenticarUsuario(vector<usuario>& usuarios, string usuarioIngresado, string passwordIngresada);
int solicitarOpcion(char* perfil);
void interfazIndice(string path);


int main(int argc, char* argv[]) {
    args::ArgumentParser parser("Programa principal del sistema creado para INFO198.");
    args::HelpFlag help(parser, "help", "Muestra este menú de ayuda", {'h', "help"});
    args::Group obligatorio(parser, "ARGUMENTOS OBLIGATORIOS:", args::Group::Validators::All);
    args::ValueFlag<string> usuarioIngresado(obligatorio, "user", "El nombre de usuario", {'u', "user"});
    args::ValueFlag<string> passwordIngresada(obligatorio, "user", "La contraseña del usuario", {'p', "password"});
    args::ValueFlag<string> rutaArchivoIngresada(obligatorio, "file", "El archivo a analizar", {'f', "file"});
    string librosPath = env.get("BOOKS_FOLDER");
    string indicePath = env.get("CREATE_INDEX");

    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help) {
        std::cout << parser;
        return 0;
    } catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    } catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    dotenv env(".env");
    vector<usuario> usuarios;
    string archivoUsuarios = env.get("USER_FILE");

    cargarUsuarios(usuarios, archivoUsuarios);
    int indiceUsuario = autenticarUsuario(usuarios, args::get(usuarioIngresado), args::get(passwordIngresada));

    if (indiceUsuario == -1) {
        cout << "(ERROR) Usuario o contraseña incorrectos." << endl;
        return 1;
    }

    usuario u = usuarios[indiceUsuario];

    while (true) {
        cout << endl;
        cout << "---= SISTEMA DE USUARIOS =---" << endl;
        cout << "Usuario: " << args::get(usuarioIngresado) << endl;
        cout << endl;
        cout << "0) Salir" << endl;
        cout << "1) Administrador de usuarios" << endl;
        cout << "2) Multiplicación de matrices cuadradas" << endl;
        cout << "3) Juego" << endl;
        cout << "4) ¿Es palíndromo?" << endl;
        cout << "5) Calcula f(x) = x² + 2x + 8" << endl;
        cout << "6) Conteo sobre texto" << endl;
        cout << "7) Crea índice invertido" << endl;
        cout << endl;

        int opcionInt = solicitarOpcion(u.perfil);
        cout << endl;

        switch (opcionInt) {
            case 1:
                cout << "(ERROR) Opción en construcción." << endl;
                esperarTecla();
                break;
            case 2:
                cout << "(ERROR) Opción en construcción." << endl;
                esperarTecla();
                break;
            case 3:
                cout << "(ERROR) Opción en construcción." << endl;
                esperarTecla();
                break;
            case 4:
                menuPalindromo();
                break;
            case 5:
                calcularFuncion();
                break;
            case 6:
                imprimirConteo(args::get(rutaArchivoIngresada));
                break;
            case 7:
                interfazIndice(librosPath);
                break;    
            case 0:
                cout << endl;
                cout << "¡Hasta pronto!" << endl;
                return 0;
            default:
                cout << "(ERROR) ¡Opción inválida!" << endl;
                esperarTecla();
                break;
        }
    }

    return 0;
}

int autenticarUsuario(vector<usuario>& usuarios, string usuarioIngresado, string passwordIngresada) {
    for (int i = 0; i < usuarios.size(); i++) {
        usuario u = usuarios[i];

        if (strcmp(u.username, usuarioIngresado.c_str()) == 0 && strcmp(u.password, passwordIngresada.c_str()) == 0) {
            return i;
        }
    }

    return -1;
}

int solicitarOpcion(char* perfil) {
    string opcion = "0";

    while (true) {
        cout << "Ingrese opción (debe ser número): ";
        cin >> opcion;

        if (esEntero(opcion)) {
            if (std::stoi(opcion) == 1 && strcmp(perfil, "GENERAL") == 0) {
                cout << "(ERROR) Usted no tiene permisos para usar esta opción. Intente con otra." << endl;
                continue;
            }

            break;
        }

        cout << "(ERROR) Opción inválida. Intente nuevamente." << endl;
    }

    return std::stoi(opcion);
}
void interfazIndice(string path){
    string librosPath = path;
    string nombreIndice;
    while (true) {
        cout << endl;
        cout << "---= CREA INDICE INVERTIDO =---" << endl;
        cout << "1) Ingresar nombre del archivo a crear" << endl;
        cout << "2) Ingresar path de los libros" << endl;
        cout << "   --Path actual:" <<  librosPath << endl;
        cout << "3) Ejecutar creacipon de index" << endl;
    int opcion = solicitarOpcion();

    switch (opcion) {
        case 1:{
            cout << endl;
            cout << "---= NOMBRE DEL ARCHIVO A CREAR =---" << endl;
            while(true){
                cout << "Ingresar nombre: '...'.idx";
                cin >> nombreIndice;
                cout << endl;
                if (nombreIndice.length() < 41) {
                    cout << "Confirma el nombre: " << nombreIndice << "?" <<endl;
                    cout << "1) Sí"<< endl;
                    cout << "2) No , volver" << endl;
                    int opcion2 = solicitarOpcion();
                    if (opcion2 == 1) {
                            cout << endl;
                            break;
                    }
                    else if (opcion2 == 2){
                        cout << "Volver a ingresar nombre (OBLIGATORIO)" << endl;
                    }
                    else{
                        cout << "(ERROR) ¡Opción inválida! NOMBRE BORRADO" << endl;
                    }
                    
                }
                else {
                    cout << "(ERROR) Nombre sobre los 40 caracteres. Intente nuevamente." << endl;
                }
            }
            string nombre_salida(nombreIndice  + ".idx");
            ofstream salida(nombre_salida);
            
            break;}    
        case 2:
            cout << endl;
            while(true){
            
                cout << "---= INGRESAR PATH A LA CARPETA LIBROS =---" << endl;
                cin >> librosPath;
                cout << "Confirma el path: " << librosPath << "?" <<endl;
                cout << "1) Sí"<< endl;
                cout << "2) No , volver" << endl;
                int opcion2 = solicitarOpcion();
                if (opcion2 == 1) {
                        cout << endl;
                        break;
                }
                else if (opcion2 == 2){
                    cout << "Volver a ingresar path (OBLIGATORIO)" << endl;
                }
                else{
                    cout << "(ERROR) ¡Opción inválida! PATH POR DEFAULT" << endl;
                }
        }
            cout << endl;
            break;
        case 3:
            cout << "Creando index..." << endl;
            indice(string pathCarpeta);
            return;
        default:
            cout << "(ERROR) ¡Opción inválida!" << endl;
            break;
        }
    }
}
