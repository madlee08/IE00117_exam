#include "examen.h"

estado osciladorPrima(estado actual)
{
    double a = 10;
    double b = 4.85;
    double c = 10;

    // Derivadas para cada estado respectivo
    // de acuerdo con ecuaciones en (1)
    estado actualPrima;
    actualPrima.x = a*(b*(actual.y) - actual.x);
    actualPrima.y = c*(actual.x) - (actual.x)*(actual.z);
    actualPrima.z = (actual.x)*(actual.y) - b*(actual.z);

    return actualPrima;
}

void obtenerKs(RK4ks* constK, estado actual, double paso)
{
    // Calculo de la constante k_1
    estado v1 = actual;

    estado k1 = osciladorPrima(v1);


    // Calculo de la constante k_2
    estado v2;
    v2.x = v1.x + 0.5*k1.x*paso;
    v2.y = v1.y + 0.5*k1.y*paso;
    v2.z = v1.z + 0.5*k1.z*paso;

    estado k2 = osciladorPrima(v2);


    // Calculo de la constante k_3
    estado v3;
    v3.x = v1.x + 0.5*k2.x*paso;
    v3.y = v1.y + 0.5*k2.y*paso;
    v3.z = v1.z + 0.5*k2.z*paso;

    estado k3 = osciladorPrima(v3);


    // Calculo de la constante k_4
    estado v4;
    v4.x = v1.x + k3.x*paso;
    v4.y = v1.y + k3.y*paso;
    v4.z = v1.z + k3.z*paso;

    estado k4 = osciladorPrima(v4);


    // Asignacion de las constantes al bloque de memoria de [0] k_x, [1] k_y y [2] k_z
    constK[0].k1 = k1.x;
    constK[0].k2 = k2.x;
    constK[0].k3 = k3.x;
    constK[0].k4 = k4.x;

    constK[1].k1 = k1.y;
    constK[1].k2 = k2.y;
    constK[1].k3 = k3.y;
    constK[1].k4 = k4.y;
    
    constK[2].k1 = k1.z;
    constK[2].k2 = k2.z;
    constK[2].k3 = k3.z;
    constK[2].k4 = k4.z;
}

estado siguienteEstado(RK4ks* constK, estado actual, double paso)
{
    double frac = 1.0/6.0;

    // Calculo del siguiente estado de acuerdo con la ecuacion (5)
    estado estado_siguiente;
    estado_siguiente.x = actual.x + (frac)*(constK[0].k1 + 2*constK[0].k2 + 2*constK[0].k3 + constK[0].k4)*paso;
    estado_siguiente.y = actual.y + (frac)*(constK[1].k1 + 2*constK[1].k2 + 2*constK[1].k3 + constK[1].k4)*paso;
    estado_siguiente.z = actual.z + (frac)*(constK[2].k1 + 2*constK[2].k2 + 2*constK[2].k3 + constK[2].k4)*paso;
    
    return estado_siguiente;
}

estado* RK4Oscilador(estado inicial, double paso, double t_max, int* num_estados)
{
    // Reservar memoria para el
    // bloque de constantes [0] k_x,
    // [1] k_y y [2] k_z
    RK4ks* constK = malloc(sizeof(RK4ks)*3);


    // Determinar el numero de
    // estados que se va a calcular
    // y reservar memoria para
    // todo esos estados.
    *num_estados = t_max/paso;

    estado* estados = malloc(sizeof(estado)*(*num_estados));


    // Condiciones iniciales t = 0
    estados[0].x = inicial.x;
    estados[0].y = inicial.y;
    estados[0].z = inicial.z;

    // Condiciones para 0 < t <= t_max
    for (int i = 1; i < *num_estados; i++)
    {
        obtenerKs(constK, estados[i-1], paso);

        estados[i] = siguienteEstado(constK, estados[i-1], paso);
    }

    free(constK);

    return estados;
}

void exportarEstados(const char* ruta_archivo, estado* estados, int num_estados)
{
    FILE* arx_out = fopen(("%s", ruta_archivo), "w");

    for (int i = 0; i < num_estados; i++)
    {   
        fprintf(arx_out, "%.4f, %.4f, %.4f\n", estados[i].x, estados[i].y, estados[i].z);
    }

    fclose(arx_out);
}