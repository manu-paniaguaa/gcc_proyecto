#include <iostream>
#include "gastos_ingresos.cpp" 

using namespace std;

int main() {
    cout << "=== SISTEMA DE GASTOS FISCALES (OOP) ===" << endl;

    // 1. Instancia del Gestor
    GestorFinanzas contabilidad;
    
    Ingreso* salario = new Ingreso(20000.0, 16); // 20,000 con 16% IVA
    contabilidad.setIngreso(salario);

    cout << "\n--- FASE 1: AGREGACION (Objetos externos) ---" << endl;
    GastoDeducible* gastoGasolina = new GastoDeducible("Gasolina Marzo", 1500.0, "gasolina", true);
    GastoDeducible* gastoMateria = new GastoDeducible("Materia Prima", 800.0, "comida", false); // Sin factura

    contabilidad.agregarGastoPorAgregacion(gastoGasolina);
    contabilidad.agregarGastoPorAgregacion(gastoMateria);
    cout << "\n--- COMPOSICION (Objetos internos) ---" << endl;
    contabilidad.crearGastoPorComposicion("Comision Bancaria", 50.0, "Cargo automatico del banco");
    contabilidad.crearGastoPorComposicion("Café de la oficina", 120.0, "Antojo");

    cout << "\n--- CALCULO INICIAL ---" << endl;
    contabilidad.calcularBalance();

    cout << "\nConsiguiendo factura para Materia Prima..." << endl;
    gastoMateria->setFactura(true); 
    contabilidad.calcularBalance();
    delete salario;

    return 0;
}
