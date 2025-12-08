#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Ingreso {
private:
    // Atributos privados: Solo esta clase puede modificarlos directamente.
    float montoBruto;
    int tasaImpuesto;
    float montoNeto;

public:
    // Constructor: Inicializa los valores y calcula el neto automáticamente al crear el objeto.
    Ingreso(float monto, int tasa) {
        this->montoBruto = monto;
        this->tasaImpuesto = tasa;
        calcularNeto();
    }
    
    // Función para descontar los impuestos del monto bruto.
    void calcularNeto() {
        float impuesto = montoBruto * (tasaImpuesto / 100.0f);
        montoNeto = montoBruto - impuesto;
    }

    // Setters: Si cambia el monto bruto, recalcula el neto automáticamente.
    void setMontoBruto(float monto) {
        montoBruto = monto;
        calcularNeto(); 
    }

    // Getters: Para obtener el valor final ya libre de impuestos.
    float getMontoNeto() {
        return montoNeto;
    }
    
    // muestra la informacion incluida en este objeto
    void mostrarInfo() {
        cout << "--- INGRESO ---" << endl;
        cout << "Bruto: $" << montoBruto << " Tasa: " << tasaImpuesto << "% Neto: $" << montoNeto << endl;
    }
};


// Clase Padre. Define la estructura básica de cualquier gasto.
class Gasto {
protected:
    // 'protected' permite que las clases hijas (Deducible/NoDeducible) accedan a estas variables.
    // esto es necesario enn vez de private siempre que tenga clases hijas para que hereden 
    float monto;
    string nombre;

public:
    Gasto(string nom, float m) : nombre(nom), monto(m) {}
    
    // Destructor virtual: borra correctamente la memoria de las clases hijas.
    // Creo que esto no lo vimos en clase pero tuve que ver un tutorial: https://www.youtube.com/watch?v=KcYNw7oO12w
    virtual ~Gasto() {}
    //getters y setters
    float getMonto() const { return monto; }
    void setMonto(float m) { monto = m; }
    string getNombre() const { return nombre; }

    // Obliga a las clases hijas a definir su propia forma de procesar el gasto.
    // gracias a esto no se pueden crear objetos 'Gasto' por sí solos
    virtual void procesarGasto(float &saldoActual) = 0;
};


// Clase Hija: Gastos que pueden deducirse como impuestos si cumplen los requisitos.
class GastoDeducible : public Gasto {
private:
    string tipo;
    bool tieneFactura;

public:
    // Constructor que usa al constructor del padre e inicializa sus propios atributos.
    GastoDeducible(string nom, float m, string t, bool fac) 
        : Gasto(nom, m), tipo(t), tieneFactura(fac) {}

    // Permite cambiar el estado de la factura en caso de que inicialemnte no tenga factura pero despues se facture.
    void setFactura(bool fac) { tieneFactura = fac; }
    string getTipo() { return tipo; }

    // Implementación específica: Solo resta dinero si es un tipo válido Y tiene factura.
    void procesarGasto(float &saldoActual) override {
        // Validacion de requisitos del SAT
        if ((tipo == "comida" || tipo == "mercancia" || tipo == "gasolina") && tieneFactura) {
            cout << "[DEDUCIBLE] " << nombre << ": Gasto aplicado. Se resta $" << monto << " del saldo." << endl;
            saldoActual -= monto; 
        } else {
            // Si no cumple los requisitos, no afecta el saldo.
            cout << "[ERROR] " << nombre << ": No es deducible (Falta factura o tipo invalido)." << endl;
        }
    }
};


// Clase Hija: Gastos personales o sin factura.
class GastoNoDeducible : public Gasto {
private:
    string motivo; 

public:
    GastoNoDeducible(string nom, float m, string mot) 
        : Gasto(nom, m), motivo(mot) {}

    void setMotivo(string m) { motivo = m; }
    string getMotivo() { return motivo; }

    // Implementación: Resta el dinero pero avisa al usuario que no hay beneficio fiscal.
    void procesarGasto(float &saldoActual) override {
        cout << "[NO DEDUCIBLE] " << nombre << " (" << motivo << "): Se resta $" << monto << " del saldo (Sin beneficios fiscales)." << endl;
        saldoActual -= monto;
    }
};

// Clase Gestor: Controla todo
class GestorFinanzas {
private:
    Ingreso* miIngreso;
    // almacenará objetos 'GastoDeducible' o 'GastoNoDeducible'.
    vector<Gasto*> listaGastos; 
    float saldoFinal;

public:
    GestorFinanzas() : miIngreso(nullptr), saldoFinal(0.0) {}

    // Destructor: Limpia la memoria de la lista de gastos al finalizar el programa.
    ~GestorFinanzas() {
        for (Gasto* g : listaGastos) {
            delete g;
        }
        listaGastos.clear();
    }

    // Recibe el objeto Ingreso del main.
    void setIngreso(Ingreso* ing) {
        miIngreso = ing;
        if(miIngreso) saldoFinal = ing->getMontoNeto();
    }

    // Solo lo guarda en la lista para procesarlo.
    void agregarGastoPorAgregacion(Gasto* g) {
        listaGastos.push_back(g);
        cout << ">> Agregacion: Se registro el gasto externo '" << g->getNombre() << "'" << endl;
    }
    // crea un gasto por composicion
    void crearGastoPorComposicion(string nombre, float monto, string motivo) {
        GastoNoDeducible* nuevoGasto = new GastoNoDeducible(nombre, monto, motivo);
        listaGastos.push_back(nuevoGasto);
        cout << ">> Composicion: Se creo internamente el gasto '" << nombre << "'" << endl;
    }

    // Recorre todos los gastos (sean deducibles o no) y actualiza el saldo.
    void calcularBalance() {
        if (!miIngreso) {
            cout << "No se ha definido un ingreso inicial." << endl;
            return;
        }
        
        // Reiniciamos el saldo base desde el ingreso neto
        saldoFinal = miIngreso->getMontoNeto();

        miIngreso->mostrarInfo();
        cout << "\nPROCESANDO LISTA DE GASTOS" << endl;

        // No importa si es Deducible o NoDeducible, se llama a su version correcta de 'procesarGasto'.
        for (Gasto* g : listaGastos) {
            g->procesarGasto(saldoFinal);
        }

        cout << "SALDO FINAL DISPONIBLE: $" << saldoFinal << endl;
    }
};