#include <iostream>
#include "gastos_ingresos.cpp"
using namespace std;

int main() {
    cout << "=== SISTEMA DE GASTOS FISCALES ===" << endl;

    // 1. Crear el Objeto
    GestorFinanzas contabilidad;

    // 2. Definir Ingresos usando Getters/Setters y Constructor
    Ingreso* salario = new Ingreso(20000.0, 16); // 20,000 con 16% de impuesto (IVA)
    contabilidad.setIngreso(salario);

    // 3. Crear Gastos Deducibles de impuestos(Clase original modificada)
    GastoDeducible* gasto1 = new GastoDeducible("Gasolina Marzo", 1500.0, "gasolina", true);
    GastoDeducible* gasto2 = new GastoDeducible("Compra de Materia prima", 800.0, "comida", false); // No se facturo, no deberia ser deducible

    // 4. Crear Gastos No Deducibles de impuestos (Nueva clase)
    GastoNoDeducible* gasto3 = new GastoNoDeducible("Coca y Fritos", 400.0, "antojito de media noche");

    // 5. Agregar al gestor
    contabilidad.agregarGastoPorAgregacion(gasto1);
    contabilidad.agregarGastoPorAgregacion(gasto2);
    contabilidad.agregarGastoPorAgregacion(gasto3);

    // 6. Ejecutar cálculo
    contabilidad.calcularBalance();


    cout << "\nConsiguiendo factura para coca y fritos..." << endl;
    gasto2->setFactura(true); 
    
    contabilidad.setIngreso(salario); 
    contabilidad.calcularBalance();

    return 0;
}