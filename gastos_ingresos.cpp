#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Ingreso {
private:
    float montoBruto;
    int tasaImpuesto;
    float montoNeto;

public:
    Ingreso(float monto, int tasa) {
        this->montoBruto = monto;
        this->tasaImpuesto = tasa;
        calcularNeto();
    }
    
    void calcularNeto() {
        float impuesto = montoBruto * (tasaImpuesto / 100.0f);
        montoNeto = montoBruto - impuesto;
    }

    void setMontoBruto(float monto) {
        montoBruto = monto;
        calcularNeto(); 
    }

    float getMontoNeto() {
        return montoNeto;
    }

    void mostrarInfo() {
        cout << "--- INGRESO ---" << endl;
        cout << "Bruto: $" << montoBruto << " Tasa: " << tasaImpuesto << "% Neto: $" << montoNeto << endl;
    }
};


class Gasto {
protected:
    float monto;
    string nombre;

public:
    Gasto(string nom, float m) : nombre(nom), monto(m) {}
    virtual ~Gasto() {}

    float getMonto() const { return monto; }
    void setMonto(float m) { monto = m; }
    string getNombre() const { return nombre; }

    virtual void procesarGasto(float &saldoActual) = 0;
};


class GastoDeducible : public Gasto {
private:
    string tipo;
    bool tieneFactura;

public:
    GastoDeducible(string nom, float m, string t, bool fac) 
        : Gasto(nom, m), tipo(t), tieneFactura(fac) {}

    void setFactura(bool fac) { tieneFactura = fac; }
    string getTipo() { return tipo; }

    void procesarGasto(float &saldoActual) override {
        if ((tipo == "comida" || tipo == "mercancia" || tipo == "gasolina") && tieneFactura) {
            cout << "[DEDUCIBLE] " << nombre << ": Gasto aplicado. Se resta $" << monto << " del saldo." << endl;
            saldoActual -= monto; 
        } else {
            cout << "[ERROR] " << nombre << ": No es deducible (Falta factura o tipo invalido)." << endl;
        }
    }
};


class GastoNoDeducible : public Gasto {
private:
    string motivo; 

public:
    GastoNoDeducible(string nom, float m, string mot) 
        : Gasto(nom, m), motivo(mot) {}

    void setMotivo(string m) { motivo = m; }
    string getMotivo() { return motivo; }

    void procesarGasto(float &saldoActual) override {
        cout << "[NO DEDUCIBLE] " << nombre << " (" << motivo << "): Se resta $" << monto << " del saldo (Sin beneficios fiscales)." << endl;
        saldoActual -= monto;
    }
};

class GestorFinanzas {
private:
    Ingreso* miIngreso;
    vector<Gasto*> listaGastos; 
    float saldoFinal;

public:
    GestorFinanzas() : miIngreso(nullptr), saldoFinal(0.0) {}

    ~GestorFinanzas() {
        for (Gasto* g : listaGastos) {
            delete g;
        }
        listaGastos.clear();
    }

    void setIngreso(Ingreso* ing) {
        miIngreso = ing;
        if(miIngreso) saldoFinal = ing->getMontoNeto();
    }

    void agregarGastoPorAgregacion(Gasto* g) {
        listaGastos.push_back(g);
        cout << ">> Agregacion: Se registro el gasto externo '" << g->getNombre() << "'" << endl;
    }

    void crearGastoPorComposicion(string nombre, float monto, string motivo) {
        GastoNoDeducible* nuevoGasto = new GastoNoDeducible(nombre, monto, motivo);
        listaGastos.push_back(nuevoGasto);
        cout << ">> Composicion: Se creo internamente el gasto '" << nombre << "'" << endl;
    }

    void calcularBalance() {
        if (!miIngreso) {
            cout << "No se ha definido un ingreso inicial." << endl;
            return;
        }
        
        saldoFinal = miIngreso->getMontoNeto();

        miIngreso->mostrarInfo();
        cout << "\nPROCESANDO LISTA DE GASTOS" << endl;

        for (Gasto* g : listaGastos) {
            g->procesarGasto(saldoFinal);
        }

        cout << "SALDO FINAL DISPONIBLE: $" << saldoFinal << endl;
    }
};