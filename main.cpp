#include <iostream>
#include "gastos_ingresos.cpp" 

using namespace std;

int main() {
    cout << "=== SISTEMA DE GASTOS FISCALES (OOP) ===" << endl;

    // Creamos el objeto principal 'contabilidad'. 
    GestorFinanzas contabilidad;
    
    // Se asigna un salario de 20,000 con una tasa de IVA del 16%.
    // Se puede modificar para probar nuevos valores
    Ingreso* salario = new Ingreso(20000.0, 16); 
 
    // ocupamos la funcion de setIngreso para ingresarle la variable salario de 20,000 y ese IVA
    contabilidad.setIngreso(salario);

    cout << "\n--- FASE 1: AGREGACION (Objetos externos) ---" << endl;
    
    // Creamos los objetos de gastos.
    // gastoGasolina tiene si tiene factura, por lo que si será deducible ante el SAT.
    // Se pueden modificar estos valores para hacer nuevas pruebas
    GastoDeducible* gastoGasolina = new GastoDeducible("Gasolina Marzo", 1500.0, "gasolina", true);
    
    // gastoMateria no tiene factura inicialmente, por lo que NO será deducible aún, pero se solicitara la factura.
    GastoDeducible* gastoMateria = new GastoDeducible("Materia Prima", 800.0, "comida", false); 

    //Agregamos lso gastos ya con la validacion al objeto principal de contabilidad
    contabilidad.agregarGastoPorAgregacion(gastoGasolina);
    contabilidad.agregarGastoPorAgregacion(gastoMateria);

    cout << "\n--- COMPOSICION (Objetos internos) ---" << endl;
    
    // A adiferencia del paso anterior aqui creamos el gasto directo desde la funcion del objeto principal contabilidad
    // Estos gastos dependen del objeto padre a diferencia de los pasados.
    contabilidad.crearGastoPorComposicion("Comision Bancaria", 50.0, "Cargo automatico del banco");
    contabilidad.crearGastoPorComposicion("Cafe de la oficina", 120.0, "Antojo");

    cout << "\n--- CALCULO INICIAL ---" << endl;
    //  Se recorre la lista de gastos, suma los deducibles y calcula impuestos
    // basándose en el ingreso y los gastos válidos hasta el momento.
    contabilidad.calcularBalance();

    cout << "\nConsiguiendo factura para Materia Prima..." << endl;
    
    //Cambiar 'false' a 'true' mediante el setter, el gasto ahora es deducible.
    gastoMateria->setFactura(true); 
    
    // Volvemos a calcular. El resultado debería cambiar porque ahora hay más gastos deducibles
    contabilidad.calcularBalance();

    // Limpiamos las instancias de la memoria para ejecutar el proceso la proxima vez
    delete salario;

    return 0;
}
