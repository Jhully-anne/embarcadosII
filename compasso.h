#ifndef COMPASSO_H
#define COMPASSO_H

    void Compasso_Init(void);
    char* ProximoEstado(void);
    char* AnteriorEstado(void);

    // ------------Estado do Compaso----------------------
    void EstadoCompasso_Reset(void);
    char* ProximoEstadoCompasso(void);
    char* AnteriorEstadoCompasso(void);

#endif

