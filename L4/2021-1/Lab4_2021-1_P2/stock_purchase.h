/*
 Definición de StockPurchase
*/
#ifndef BATCH_H
#define BATCH_H

typedef struct StockPurchase  {
    char datetime[15];
    char doc_number[9];
    int stock_number;
    double amount;
    char status;
} ElementoArbol;


#endif
