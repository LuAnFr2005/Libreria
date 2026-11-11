#include <stdio.h>
#include <stdlib.h>





























































void limpiarPantalla(void){
    system(CMD_LIMPIAR)
}
void encabezado(const char *titulo)
{
   limpiarPantalla();
    printf("=======================\n");
    printf("%s\n"titulo);
    printf("=======================\n");
}

void limpiarBuffer(void)
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
void pausar(void)
{
    char tmp [LEN];
    printf("\npresione enter para continuar....");
    fgets(tmp, sizeof(tmp), stdin);
}

void leerCadena(const char *mensaje, char *destino,int tam)
{
    printf("%s", mensaje);
    if(fgets(destino, tam, stdin ) == NULL){
        destino[0] = '\0';
        return;
}
    destino[strcspn(destino, "\r\r")] = '\0';
}
int leerEntero(const char *mensaje)
{
char buffer[LEN];
    char *fin;
    char valor;

leerCadena(mensaje, buffer, sizeof(buffer));
    if (buffer [0] == '\0') 
    return -1;

    valor = strtol(buffer, &fin, 10);
    while (*fin == '')
        fin++;
if (*fin != '\0')
    return -1;
    return (int)valor;
}
void obtenerFecha(char *destino, int tam)
{
    time_t t = time (NULL);
    struct tm *info = localtime(&t);
    strftime(destino, tam, "%Y-%m-%d %H:%M", info);
}
int siguienteId(const char *archivo, size_t tamRegistro)
{
FILE *f = fopen(archivo,"rb");
long bytes;

if (f == NULL)
 return 1;
    fseek(f, 0,SEEK_END);
bytes = ftell(f);
  fclose(f);
    return (int)(bytes / (long)tamRegistro) + 1;
}
int contieneTexto(const char *texto, const char *buscado)
{
char a[LEN * 2], b [LEN * 2];
int i;
if (buscando[0] == '\0')
return 0;
    for (i = 0; texto[i] != '\0' && i < (LEN * 2) - 1; i++)
a[i] = (char)tolower((unsigned char)texto[i]);
    a[i] = '\0';
    for (i = 0; buscado[i] != '\0' && i < (LEN * 2) - 1; i++)
        b[i] = (char)tolower((unsigned char)buscado[i]);
    b[i] = '\0';
    return strstr(a, b) != NULL;
}

int leerCodigo(const char *mensaje, char prefijo)
{

    char buffer[LEN];
    char *p;
    char *fin;
    long valor ;

leerCadena(mensaje, buffer, sizeof(buffer));
    p = buffer;
    while (*p == '' )
    p++;
    if (*p == '\0')
        return -1;
if (isalpha((unsigned char)*p)) {
    if (toupper((unsigned char)*p) != prefijo)
        return -1;
    p++;
    if (*p == '-')
        p++;
}
  valor = strtol(p, &fin, 10);
    while (*fin == '')
        fin++;
if (fin == p || *fin != '\0' || valor <= 0)
return -1;
    return (int)valor;  
}
int generarQR(char prefijo, int id)
{
    char comando [256];
    
    #ifdef _WIN32
    system("if not exist " CARPETA_QR " mkdir " CARPETA_QR);
#else
    system("mkdir -p " CARPETA_QR);
#endif

    sprintf(comando,
            "qrencode -o %s/%c_%04d.png -s 10 -m 2 \"%c-%04d\"",
            CARPETA_QR, prefijo, id, prefijo, id);

    if (system(comando) != 0) {
        printf("\n[!] No se pudo generar el QR. Verifique que 'qrencode'\n");
        printf("    este instalado y agregado al PATH.\n");
        return 0;
    }
    printf("\nQR generado: %s/%c_%04d.png  (contenido: %c-%04d)\n",
           CARPETA_QR, prefijo, id, prefijo, id);
    return 1;
}
void mostrarQR(char prefijo, int id)
{
    char comando[256];

#ifdef _WIN32
    sprintf(comando, "start \"\" \"%s\\%c_%04d.png\"", CARPETA_QR, prefijo, id);
#else
    sprintf(comando, "xdg-open \"%s/%c_%04d.png\" >/dev/null 2>&1", CARPETA_QR, prefijo, id);
#endif
    system(comando);
}

int buscarUsuarioPorId(int id, usuario *u, long *pos)
{
FILE *f = fopen(ARCH_USUARIOS, "rb");
Usuario tmp;
long i = 0;

    if (f == NULL)
    return 0;
while (fread(&tmp, sizeof()Usuarios), 1, f) == 1) {
    if (tmp.id == id &&tmp.activo){
        if (u != NULL)
            *u = tmp ;
        if (pos != NULL)
            *pos = i;
    }
    i++;
}
fclose(f);
    return 0;
}
int buscarLibroPorId(int id, Libro *l, long *pos)
{
    FILE *f = fopen(ARCH_LIBROS, "rb");
    Libro tmp;
    long i = 0;

    if (f == NULL)
        return 0;
    while (fread(&tmp, sizeof(Libro), 1, f) == 1) {
        if (tmp.id == id && tmp.activo) {
            if (l != NULL)
                *l = tmp;
            if (pos != NULL)
                *pos = i;
            fclose(f);
            return 1;
        }
        i++;
    }
    fclose(f);
    return 0;
}

int prestamosActivosDeUsuario(int idUsuario)
{
    FILE *f = fopen(ARCH_PRESTAMOS, "rb");
    Prestamo p;
    int total = 0;

    if (f == NULL)
        return 0;
    while (fread(&p, sizeof(Prestamo), 1, f) == 1)
        if (p.activo && p.idUsuario == idUsuario)
            total++;
    fclose(f);
    return total;
}

int libroPrestadoActivo(int idLibro, Prestamo *p, long *pos)
{
    FILE *f = fopen(ARCH_PRESTAMOS, "rb");
    Prestamo tmp;
    long i = 0;

    if (f == NULL)
        return 0;
    while (fread(&tmp, sizeof(Prestamo), 1, f) == 1) {
        if (tmp.activo && tmp.idLibro == idLibro) {
            if (p != NULL)
                *p = tmp;
            if (pos != NULL)
                *pos = i;
            fclose(f);
            return 1;
        }
        i++;
    }
    fclose(f);
    return 0;
}

void registrarMovimiento(int tipo, int idUsuario, int idLibro)
{
    FILE *f = fopen(ARCH_MOVIMIENTOS, "ab");
    Movimiento m;

    if (f == NULL) {
        printf("Error: no se pudo abrir el historial.\n");
        return;
    }
    m.tipo = tipo;
    m.idUsuario = idUsuario;
    m.idLibro = idLibro;
    obtenerFecha(m.fecha, sizeof(m.fecha));
    fwrite(&m, sizeof(Movimiento), 1, f);
    fclose(f);
}

//amet parte 3(yo)
void reporteLibrosDisponibles(void)
{
FILE *f;
Libro l;
int total=0;

encabezado("REPORTE: LUBROS DISPONIBLES");
f= fopen(ARCH_LIBROS, "rb");
if (f== NULL){
printf("No hay libros registrados.\n");
pausar();
return;
}
printf("%-8s %-30s %-20s %-12s\n", "ID", "TITULO", "AUTOR", "CATEGORIA");
printf("-----------------------------------------------------------------------\n");
while (fread(&l, sizeof(Libro), 1, f)==1){
if(l.activo && l.disponible){
printf("L-%04d %-30s %-20s %-12s\n", l.id, l.titulo, l.autor, l.categoria);
total++;
}
}
fclose(f);
printf("\nTotal: %d libro(s) disponible(s)\n", total);
pausar();
}

void reporteLibrosPretados(void)
{
FILE *f;
Libro l;
Prestamo p;
Usuario u;
int total=0;

encabezado ("REPORTE: LIBROS PRESTADOS");
f = fopen(ARCH_LIBROS, "rb");
if (f == NULL){
printf("No hay libros registrados.\n");
pausar ();
return;
}
printf("%-8s %-28s %-22s %-17s\n", "ID", "TITULO", "PRESTADO A", "DESDE");
printf("-------------------------------------------------------------------------\n");
while (fread (&l, sizeof(Libro),1,f)==1){
if(l.activo && !l.disponible){
strcpy(u.nombre, "(desconocido)");
strcpy(p.fechaPrestamo, "-");
if (libroPrestadoActivo(l.id,&p, NULL))
    if (!buscarUsuarioPorId(p.idUsuario,&u,NULL))
        strcpy(u.nombre,"(eliminado)");
printf("L-%04d %-28s %-22s %-17s\n", l.id,l.titulo, u.nombre,p.fechaPrestamo);
total++;
}
}
fclose(f);
printf("\nTotal: %d libros(s) prestado(s) \n", total);
pausar();
}

void reporteUsuariosRegistrados(void)
{
consultarUsuarios();
}

void reporteHistorialPrestamos(void)
{
FILE *f;
Movimiento m;
Usuario u;
Libro l;
int total= 0;

encabezado("REPORTE: HISTORIAL DE PRESTAMOS");
f = fopen(ARCH_MOVIMIENTOS, "rb");
if (f == NULL){
printf("aun no hay movimientos.\n");
pausar()
    return;
}
printf("%-17s %-22s %-28s\n", "FECHA", "USUARIO", "LIBRO");
printf("-------------------------------------------------------------------\n");
while(fread(&m, sizeof(Movimiento), 1, f)==1){
if(m.tipo != MOV_PRESTAMO)
    continue;
if (!buscarUsuarioPorId(m.idUsuario, &u, NULL))
    strcpy(u.nombre, "(eliminado)");
if(!buscarLibroPorId(m.idLibro, &l, NULL))
    strcpy(l.titulo,"(eliminado)");
printf("%-17s %-22s %-28s\n", m.fecha, u.nombre, l.titulo);
total++;
}
    fclose(f);
    printf("\nTotal: %d prestamo(s) registrados(s)\n", total);
    pausar();
}

void

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
