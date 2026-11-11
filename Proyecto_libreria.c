#include <stdio.h>
#include <stdlib.h>


// quien es el 1?


























































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

//Carlos
void registrarLibro(void)
{
    Libro l;
    FILE *f;
    char resp[LEN];

    encabezado("REGISTRAR LIBRO")
    memset(&l, 0, sizeof(Libro));

    leerCadena("Titulo: ", l.titulo, LEN);
    if (l.titulo[0] == '\0')
    {
        printf("El Titulo no puede estar vacio.\n");
        pausar();
        return;
    }
    leerCadena("Autor: ", l.autor, LEN);
    leerCadena("Categoria (Ej. Ciencia, Novela, Historia)", l.categoria, LEN);
    if (l.categoria[0]== '\0')
        strcpy(l.categoria, "GENERAL");
    l.id= siguienteId(ARCH_LIBROS, sizeof(Libro));
    l.disponible=1;
    l.vecesPrestado=0;
    l.activo=1;

    f=fopen(ARCH_LIBROS, "ab");
    if (f == NULL)
    {
        printf ("Error: No se puede abrir el archivo de libroa.\n");
        pausar();
        return;
    }

    fwrite(&l sizeof(Libro), l, f);
    fclose (f);

    printf("\n Libro registrado con ID unico L-%04d\n", l.id);
    if (generarQR('L', l.id));
    {
        leerCadena("Desea abrir la imagen del QR para imprimirla ? (s/n)", resp, LEN);
        if (resp[0]== 's' || resp[0]== 'S')
        mostrarQr('L', l.id);
    }

    pausar();
        
}

void modificarLibro(void)
{
    Libro 1;
    long pos;
    int id;
    chr tmp [LEN];
    FILE *f;

    encabezado ("MODIFICAR LIBRO");
    id = leerCodigo("Escanee el QR del libro (o ingrese su ID): ",'L' );
    if (id<0 || !buscarLibroPorId(id, &l, &pos))
    {
        printf("Libro no encontrado");
        pausar();
        return;
    }
    printf("(Deje vacio y presione ENTER para conservar el dato actual.)\n\n");
    
    printf("Titulo actual: %s\n", l.titulo);
    leerCadena("Nuevo titulo: ", tmp, LEN);
    if (tmp[0] != '\0') strcpy (l.titulo, tmp);

    printf("Autor actual: %s\n", l.titulo);
    leerCadena("Nuevo autor: ", tmp, LEN);
    if (tmp[0] != '\0') strcpy (l.autor, tmp);

    printf("Categoria actual: %s\n", l.titulo);
    leerCadena("Nueva categoria : ", tmp, LEN);
    if (tmp[0] != '\0') strcpy (l.categoria, tmp);

    f = fopen (ARCH_LIBROS, "r+b");
    if (f == NULL)
    {
        printf ("Error al abrir el archivo\n");
        pausar();
        return;
    }
    fseek(f, pos * (long)sizeof(Libro), SEEK_SET);
    fwrite(&l, sizeof(Libro), 1, f);
    fclose(f);
    printf("Libro actualizado.\n");
    pausar();
}

void eliminarLibro(void)
{
    Libro l;
    long pos;
    int id;
    char resp [LEN];
    FILE *f;

    encabezado("ELIMINAR LIBRO");
    id = leerCodigo ("Escanee el QR (o escriba su ID): ", 'L' );
    if (id<0 || !buscarLibroporId(id, &l, &pos))
    {
      printf("Libro no encontrado.\n");
        pausar();
        return;
    }

    if (!l.disponible)
    {
        printf("No se puede eliminar: El libro esta prestado actualmente");
        pausar ();
        return;
    }
    printf("Libro: %s (L-%04d)\n", l.titulo, l.id);
    leerCadena("Confirmar que desea borrarlo? (s/n): ", resp, LEN);
    if (resp[0] != 's' || resp[0] != 'S')
    {
        printf("Operacion cancelada\n");
        pausar();
        return;
    }

    l.activo=0;
    f=fopen(ARCH_LIBROS, "r+b");
    if (f == NULL)
    {
        printf("Error al abrir el archivo.\n");
        pausar();
        return;
    }

    fseek(f, pos * (long)sizeof(Libro), SEEK_SET);
    fwrite(&l, sizeof(Libro), 1, f);
    fclose(f);
    printf("Libro eliminado.\n");
    pausar();
}

void buscarLibro(void)
{
    FILE *f;
    Libro l;
    char texto[LEN];
    int encontrados = 0;
    int idBuscado;

    encabezado("BUSCAR LIBRO");
    leerCadena("Titulo, autor, categoria o codigo (L-0001): ", texto, LEN);
    idBuscado = (texto[0] != '\0' && (isdigit((unsigned char)texto[0]) ||
                 toupper((unsigned char)texto[0]) == 'L') &&
                 (strchr(texto, '-') != NULL || isdigit((unsigned char)texto[0])))
                 ? atoi(strchr(texto, '-') ? strchr(texto, '-') + 1 : texto) : -1;

    f = fopen(ARCH_LIBROS, "rb");
    if (f == NULL) {
        printf("No hay libros registrados.\n");
        pausar();
        return;
    }
    printf("\n%-8s %-28s %-18s %-12s %-10s\n", "ID", "TITULO", "AUTOR", "CATEGORIA", "ESTADO");
    printf("--------------------------------------------------------------------------------\n");
    while (fread(&l, sizeof(Libro), 1, f) == 1) {
        if (!l.activo)
            continue;
        if (contieneTexto(l.titulo, texto) || contieneTexto(l.autor, texto) ||
            contieneTexto(l.categoria, texto) || (idBuscado > 0 && l.id == idBuscado)) {
            printf("L-%04d  %-28s %-18s %-12s %-10s\n", l.id, l.titulo, l.autor,
                   l.categoria, l.disponible ? "Disponible" : "Prestado");
            encontrados++;
        }
    }
    fclose(f);
    if (encontrados == 0)
        printf("Sin resultados.\n");
    pausar();
}

void consultarDisponibilidad(void)
{
    Libro l;
    Prestamo p;
    Usuario u;
    int id;

    encabezado("CONSULTAR DISPONIBILIDAD");
    id = leerCodigo("Escanee el QR del libro (o escriba su ID): ", 'L');
    if (id < 0 || !buscarLibroPorId(id, &l, NULL)) {
        printf("Libro no encontrado.\n");
        pausar();
        return;
    }
    printf("\nLibro:     %s (L-%04d)\n", l.titulo, l.id);
    printf("Autor:     %s\n", l.autor);
    printf("Categoria: %s\n", l.categoria);
    printf("Estado:    %s\n", l.disponible ? "DISPONIBLE" : "PRESTADO");
    if (!l.disponible && libroPrestadoActivo(id, &p, NULL)) {
        if (buscarUsuarioPorId(p.idUsuario, &u, NULL))
            printf("Prestado a: %s desde %s\n", u.nombre, p.fechaPrestamo);
    }
    pausar();
}

void clasificarLibrosPorCategoria(void)
{
    FILE *f;
    Libro lista[MAX_LIBROS];
    Libro tmp;
    int n = 0, i, j, yaVista;

    encabezado("LIBROS POR CATEGORIA");
    f = fopen(ARCH_LIBROS, "rb");
    if (f == NULL) {
        printf("No hay libros registrados.\n");
        pausar();
        return;
    }
    while (n < MAX_LIBROS && fread(&tmp, sizeof(Libro), 1, f) == 1) {
        if (tmp.activo) {
            lista[n] = tmp;
            n++;
        }
    }
    fclose(f);

    if (n == 0) {
        printf("No hay libros registrados.\n");
        pausar();
        return;
    }
    for (i = 0; i < n; i++) {

        yaVista = 0;
        for (j = 0; j < i; j++)
            if (strcmp(lista[j].categoria, lista[i].categoria) == 0)
                yaVista = 1;
        if (yaVista)
            continue;

        printf("\n[ %s ]\n", lista[i].categoria);
        for (j = 0; j < n; j++)
            if (strcmp(lista[j].categoria, lista[i].categoria) == 0)
                printf("   L-%04d  %-30s %-18s %s\n", lista[j].id, lista[j].titulo,
                       lista[j].autor, lista[j].disponible ? "Disponible" : "Prestado");
    }
    pausar();
}

//amet parte 3
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

void reporteHistorialDevoluciones(void)
{
    FILE *f;
    Movimiento m;
    Usuario u;
    Libro l;
    int total = 0;

    encabezado("REPORTE: HISTOTRIAL DE DEVOLUCIONES");
    f= fopen(ARCH_MOVIMIENTOS, "rb");
    if(f =0 NULL){
        printf("Aun no hay movimientos.\n");
        pausar();
        return;
    }
        printf("%-17s %-22s %-28s\n", "FECHA", "USUARIO", "LIBRO");
        printf("----------------------------------------------------------\n");
        while (fread(&m, sizeof(Movimiento), 1, f)== 1);
        if(m-tipo != MOV_DEVOLUCION)
            continue;
        if(!buscarUsuariosPorId(m.idUsuario, &u, NULL))
            strcpy(u.nombre, "(eliminado)");
        if(!buscarLibroPorId(m.idLibro, &l, NULL))
            strcpy(l.titulo, "(eliminado)");
        printf("%-17s %-22s %-28s\n", m.fecha, u.nombre, l.titulo);
        total++;
}
fclose(f);
printf("\nTotal: %d devolucion(es) registrada(s)\n", total);
pausar();
}

void reporteLibrosMasPrestados(void)
{
    FILE *f;
    Libro tmp;
    Libro lista[MAX_LIBROS];
    int n = 0, i, j, limite;
    encabezado("REPORTE: LIBRO MAS PRESTADOS");
    f = fopen(ARCH_LIBROS, "rb");
    if (f == NULL){
        printf("NO hay libros registrados.\n");
        pausar()
        return;
    }
    while(n < MAX_LIBROS && fread(&tmp, sizeof(Libro), 1, f) == 1){
        if (tmp.activo) {
            lista[n] = tmp;
            n++;
        }
    }
    fclose(f);

    if (n == 0){
        printf("NO hay libros registrados.\n");
        pausar();
        return;
    }
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - 1; j++){
            if(lista[j].vecesPrestado < lista[j + 1].vecesPrestado){
                tmp = lista[j];
                lista[j] = lista[j + 1];
                lista[j +1] = tmp;
            }
        }
    }
    limite = (n < 10) ? n : 10;

    printf("%-s %-8s %-30s %-10s\n", "TOP", "ID", "TITULO", "PRESTAMOS");
    printf("-------------------------------------------------------------------\n");
    for (i = 0; i < limite; i++)
        printf("%-5d L-%04d %-30s %-10d\n", i+1, lista[i].id, lista[i].titulo, lista[i].vecesPrestado);
    pausar();
}

void reporteUsuariosPrestamosActivos(void)
{
    FILE *f;
    Usuario u;
    int activos, total = 0;

    encabezado("REPORTE: USUARIOS CON PRESTAMOS ACTIVOS");
    f = fopen(ARCH_USUARIOS, "rb");
    if (f == NULL){
        printf("No hay usuarios registrados.\n");
        pausar();
        return;
    }
    printf("%-8s %-28s %-10s\n", "ID", "NOMBRE", "ACTIVOS");
    printf("--------------------------------------------------\n");
    while (fread(&u, sizeof(Usuario), 1, f)== 1){
        if(!u.activo)
            continue;
        activos = prestamosActivosDeUsuario(u.id);
        if(activos > 0){
            printf("U-%04d %-28s %-10d\n", u.id, u.nombre, activos);
            total++;
        }
    }
    fclose(f);
    if (total == 0)
        printf ("Ningun usuario tiene prestamos activos.\n");
    pausar();
}

void menuReportes(void)
{
    int op = -1;

    while (op != 0){
        encabezado("REPORTES");
        printf("1.- Libros disponibles\n");
        printf("2.- Libros prestados\n");
        printf("3.- Usuarios registrados\n");
        printf("4.- Historial de prestamos\n");
        printf("5.- Historial de devoluciones\n");
        printf("6.- Libros con mayor numero de prestamos\n");
        printf("7.- Usuarios con prestamos activos\n");
        printf("--------------------------------------------------\n");
        op = leerEntero("Seleccione una opcion: ");
        switch (op){
            case 1: reporteLibrosDisponibles(); break;
            case 2: reporteLibrosPrestados(); break;
            case 3: reporteUsuariosRegistrados(); break;
            case 4: reporteHistorialPrestamos(); break;
            case 5: reporteHIstorialDevoluciones() break;
            case 6: reporteLibrosMasPrestados() break;
            case 7: reporteUsuariosPrestamosActivos(); break;
            case 0; break;
            default: printf("Opcion no valida.\n"); pausar(); break;
        }
    }
}
void consultarDevoluciones(void)
{
    reporteHistorialDevoluciones();
}
//hasta aca mi trabajo yo amet uwu
    
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
