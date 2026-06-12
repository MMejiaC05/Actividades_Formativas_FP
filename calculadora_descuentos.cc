#include <iostream>

void flujograma1() {
    double numero_1, numero_2;
    int cantidad;

    std::cout << "\n========================================\n";
    std::cout << "  FLUJOGRAMA 1: Descuento por porcentaje\n";
    std::cout << "========================================\n";

    std::cout << "¿Cuantos productos desea calcular? ";
    std::cin >> cantidad;

    for (int i = 1; i <= cantidad; i++) {
        std::cout << "\n--- Producto " << i << " de " << cantidad << " ---\n";

        std::cout << "Ingrese el precio original del producto: $";
        std::cin >> numero_1;
        std::cout << "Ingrese el porcentaje de descuento (%): ";
        std::cin >> numero_2;

        // Decision: ¿El precio y el descuento son validos?
        if (numero_1 > 0 && numero_2 >= 0 && numero_2 <= 100) {
            // Proceso: multiplicar precio x porcentaje / 100
            double descuento = (numero_1 * numero_2) / 100;
            double precio_final = numero_1 - descuento;

            std::cout << "\n--- Resultado ---\n";
            std::cout << "Descuento aplicado: $" << descuento << "\n";
            std::cout << "Precio final:       $" << precio_final << "\n";
        } else {
            std::cout << "\nEl precio y el descuento no son validos.\n";
            i--; // No contar este intento si los datos son invalidos
        }
    }
}

void flujograma2() {
    double numero_1, descuento;
    int cantidad;

    std::cout << "\n========================================\n";
    std::cout << "  FLUJOGRAMA 2: Descuento de cantidad fija\n";
    std::cout << "========================================\n";

    std::cout << "¿Cuantos productos desea calcular? ";
    std::cin >> cantidad;

    for (int i = 1; i <= cantidad; i++) {
        std::cout << "\n--- Producto " << i << " de " << cantidad << " ---\n";

        std::cout << "Ingrese el precio original del producto: $";
        std::cin >> numero_1;
        std::cout << "Ingrese la cantidad de descuento a aplicar: $";
        std::cin >> descuento;

        // Proceso: precio original - descuento
        double precio_a_pagar = numero_1 - descuento;

        // Decision: ¿Precio a pagar es valido?
        if (precio_a_pagar > 0) {
            double porcentaje = (descuento / numero_1) * 100;

            std::cout << "\n--- Resultado ---\n";
            std::cout << "Precio a pagar despues del descuento: $" << precio_a_pagar << "\n";
            std::cout << "Porcentaje de descuento del precio original: "
                      << porcentaje << "%\n";
        } else {
            std::cout << "\nLo sentimos, no pudimos completar su pedido.\n";
            i--; // No contar este intento si los datos son invalidos
        }
    }
}

int main() {
    int opcion;

    std::cout << "=== Sistema de Calculo de Descuentos ===\n";

    do {
        std::cout << "\n1. Flujograma 1 (descuento por porcentaje)\n";
        std::cout << "2. Flujograma 2 (descuento por cantidad fija)\n";
        std::cout << "0. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: flujograma1(); break;
            case 2: flujograma2(); break;
            case 0: std::cout << "\nFin del programa.\n"; break;
            default: std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}