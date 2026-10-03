#include <stdio.h>
#include <stdlib.h>

int main(){

    int opcMenu;
    int opcUsuarios;
    int opcLibros;
    int opcPrestamos;
    int opcDevoluciones;
    int salir;
    salir = 0;

    while (salir == 0)
    {
        system("cls");
        printf("==============================================\n");
        printf("              SMARTLIBRARY QR                 \n");
        printf("==============================================\n");
        printf("1. Usuarios\n");
        printf("2. Libros\n");
        printf("3. Prestamos\n");
        printf("4. Devoluciones\n");
        printf("0. Salir\n");
        printf("----------------------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcMenu);

        switch (opcMenu){

        case 1:
            salir = 0;
            opcUsuarios = -1;
            while (opcUsuarios != 0){
                system("cls");
                printf("==============================================\n");
                printf("             GESTION DE USUARIOS\n");
                printf("==============================================\n");
                printf("1. Crear usuario\n");
                printf("2. Borrar usuario\n");
                printf("3. Administrar usuario\n");
                printf("0. Regresar al menu principal\n");
                printf("----------------------------------------------\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &opcUsuarios);
                    
                switch (opcUsuarios){
                    case 1:
                        system("cls");
                        printf("==============================================\n");
                        printf("             CREAR USUARIO\n");
                        printf("==============================================\n");
                        printf("aqui se crea el usuario\n");
                        printf("no tenemos aun la generacion qr ai que por ahora solo es un menu y ya\n");
                        printf("precione enter para continuar\n");
                        getchar();
                        getchar();
                        break;
                    case 2:
                        system("cls");
                        printf("==============================================\n");
                        printf("             BORRAR USUARIO\n");
                        printf("==============================================\n");
                        printf("aqui se borra el usuario\n");
                        printf("no tenemos aun la generacion qr ai que por ahora solo es un menu y ya\n");
                        printf("precione enter para continuar\n");
                        getchar();
                        getchar();
                        break;
                    case 3:
                        system("cls");
                        printf("==============================================\n");
                        printf("             ADMINISTRAR USUARIO\n");
                        printf("==============================================\n");
                            printf("1. Editar datos\n");
                            printf("2. Consultar historial\n");
                            printf("0. Regresar\n");
                            printf("seleccione una opcion: ");
                            scanf("%d", &opcUsuarios);

                            switch (opcUsuarios)
                            {
                            case 1:
                                printf("==============================================\n");
                                printf("             EDITAR DATOS\n");
                                printf("==============================================\n");
                                printf("aqui se editan los datos del usuario\n");
                                printf("no tenemos aun la generacion qr ai que por ahora solo es un menu y ya\n");
                                printf("precione enter para continuar\n");
                                getchar();
                                getchar();
                                opcUsuarios = -1;
                                break;
                            case 2:
                                printf("==============================================\n");
                                printf("             CONSULTAR HISTORIAL\n");
                                printf("==============================================\n");
                                printf("aqui se consulta el historial del usuario\n");
                                printf("no tenemos aun la generacion qr ai que por ahora solo es un menu y ya\n");
                                printf("precione enter para continuar\n");
                                getchar();
                                getchar();
                                opcUsuarios = -1;
                                break;
                            case 0:
                                opcUsuarios = -1;
                                break;
                            default:
                                system("cls");
                                printf("Opción no válida.\n");
                                printf("Precione enter para continuar\n");
                                getchar();
                                getchar();
                                opcUsuarios = -1;
                                break;
                            }
                        break;
                    case 0:
                        salir = 1;
                        break;
                    default:
                        printf("Opción no válida.\n");
                        printf("Precione enter para continuar\n");
                        getchar();
                        getchar();
                        opcUsuarios = -1;
                        break;
                    }
                }
            break;
        case 2:
            opcLibros = -1;

            while (opcLibros != 0){

                system("cls");

                printf("==============================================\n");
                printf("             GESTION DE LIBROS\n");
                printf("==============================================\n");
                printf("1. Registrar libro\n");
                printf("2. Modificar libro\n");
                printf("3. Eliminar libro\n");
                printf("4. Buscar libro\n");
                printf("5. Consultar disponibilidad\n");
                printf("0. Regresar al menu principal\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &opcLibros);
            }
            
            break;
        case 3:
            opcPrestamos = -1;
            while (opcPrestamos != 0){

            system("cls");

            printf("==============================================\n");
            printf("             GESTION DE PRESTAMOS\n");
            printf("==============================================\n");
            printf("1. Registrar prestamo\n");
            printf("2. Consultar prestamos\n");
            printf("0. Regresar al menu principal\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &opcPrestamos);
            break;
            }
        case 4:
            opcDevoluciones = -1;
            while (opcDevoluciones != 0){
                system("cls");
                printf("==============================================\n");
                printf("             GESTION DE DEVOLUCIONES\n");
                printf("==============================================\n");
                printf("1. Registrar devolucion\n");
                printf("2. Consultar devoluciones\n");
                printf("0. Regresar al menu principal\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &opcDevoluciones);
            }
            break;
        case 0:
            salir = 1;
            break;
        default:
            printf("Opción no válida.\n");
            printf("Precione enter para continuar\n");
            getchar();
            getchar();
            break;
        }
    }

}