#include <iostream>
#include <list>

using namespace std;

class IngresosDespuesDeImpuestos{
    public:
        float ingresos;
        int tasa_de_interes;
        float interes;
        float ingresos_netos;

        float ingresos_sin_impuestos(float ingresos, int tasa_de_interes){
            interes = (100 - tasa_de_interes) * 0.01;
            ingresos_netos = (ingresos * (100 - interes));
            return ingresos_netos;
        }
};

class SonGastosDeducibles{
    public:
        float gasto;
        float gasto_acumulado = 0.0;
        string tipo;
        string factura;
        float ingresos_netos;
        float total;


        bool es_deducible(float gasto, string tipo, string factura, float ingresos_netos){
            if(tipo == "comida" || tipo == "adquisicion de mercancias" || tipo == "gastos generales" || tipo == "gasolina"){
                if(factura == "Si"){
                    cout <<"El gasto es deducible" << endl;
                    total = ingresos_netos + gasto;
                    return total;
                }
                else if(factura == "No"){
                    cout <<"Para incluir este gasto, es necesario facturar"<< endl;
                }
            }
            else{
                cout <<"El tipo de gasto no es apto para su deduccion";
                total = ingresos_netos - gasto;
                return total;
            }    
        };
};
