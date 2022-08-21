#include <stdio.h>
#include <stdlib.h>

#if !defined(Funciones)
#define Funciones

typedef struct estado
{
    double x;
    double y;
    double z;
} estado;

typedef struct constantesK
{
    double k1;
    double k2;
    double k3;
    double k4;
} RK4ks;

estado osciladorPrima(estado actual);

void obtenerKs(RK4ks* constK, estado actual, double paso);

estado siguienteEstado(RK4ks* constK, estado actual, double paso);

estado* RK4Oscilador(estado inicial, double paso, double t_max, int* num_estados);

void exportarEstados(const char* ruta_archivo, estado* estados, int num_estados);

#endif