#include <iostream>
#include <iomanip>

// ============================================================
//  ESTRUCTURAS DE DATOS ESTÁTICAS
// ============================================================

// Máximo de productos permitidos por sesión (arreglo estático)
const int MAX_PRODUCTOS = 50;

// Enumeración para distinguir el tipo de cálculo realizado
enum TipoDescuento {
    POR_PORCENTAJE,
    POR_CANTIDAD_FIJA
};

// Struct que agrupa todos los datos de un producto calculado
struct Producto {
    double precio_original;
    double descuento_aplicado;
    double precio_final;
    double porcentaje;
    TipoDescuento tipo;
};

// Arreglo estático global que actúa como historial de la sesión
Producto historial[MAX_PRODUCTOS];
int total_registros = 0;     // Cuántos productos se han procesado


// ============================================================
//  FUNCIONES AUXILIARES
// ============================================================

// Guarda un producto en el historial (si hay espacio)
void guardar_en_historial(Producto p) {
    if (total_registros < MAX_PRODUCTOS) {
        historial[total_registros] = p;
        total_registros++;
    } else {
        std::cout << "\n[Advertencia] Se alcanzó el límite de "
                  << MAX_PRODUCTOS << " productos en el historial.\n";
    }
}

// Muestra el resumen completo de la sesión usando el arreglo estático
void mostrar_historial() {
    if (total_registros == 0) {
        std::cout << "\nNo hay productos registrados en esta sesión.\n";
        return;
    }

    std::cout << "\n\n";
    std::cout << "============================================================\n";
    std::cout << "             HISTORIAL DE LA SESIÓN\n";
    std::cout << "============================================================\n";
    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < total_registros; i++) {
        Producto& p = historial[i];
        std::cout << "\n  [" << (i + 1) << "] "
                  << (p.tipo == POR_PORCENTAJE
                      ? "Descuento por porcentaje"
                      : "Descuento por cantidad fija") << "\n";
        std::cout << "      Precio original : $" << p.precio_original    << "\n";
        std::cout << "      Descuento        : $" << p.descuento_aplicado << "\n";
        std::cout << "      Porcentaje       : "  << p.porcentaje         << "%\n";
        std::cout << "      Precio final     : $" << p.precio_final       << "\n";
    }

    std::cout << "\n------------------------------------------------------------\n";
    std::cout << "  Total de productos calculados: " << total_registros << "\n";
    std::cout << "============================================================\n";
}


// ============================================================
//  FLUJOGRAMA 1 — Descuento por porcentaje
// ============================================================
void flujograma1() {
    int cantidad;

    std::cout << "\n========================================\n";
    std::cout << "  FLUJOGRAMA 1: Descuento por porcentaje\n";
    std::cout << "========================================\n";

    std::cout << "¿Cuántos productos desea calcular? ";
    std::cin >> cantidad;

    for (int i = 1; i <= cantidad; i++) {
        std::cout << "\n--- Producto " << i << " de " << cantidad << " ---\n";

        // Usamos un struct para capturar los datos de entrada
        Producto p;
        p.tipo = POR_PORCENTAJE;

        std::cout << "Precio original del producto: $";
        std::cin >> p.precio_original;
        std::cout << "Porcentaje de descuento (%): ";
        std::cin >> p.porcentaje;

        // Decisión: validar datos
        if (p.precio_original > 0 && p.porcentaje >= 0 && p.porcentaje <= 100) {

            // Proceso: calcular y completar el struct
            p.descuento_aplicado = (p.precio_original * p.porcentaje) / 100.0;
            p.precio_final       = p.precio_original - p.descuento_aplicado;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "\n--- Resultado ---\n";
            std::cout << "Descuento aplicado : $" << p.descuento_aplicado << "\n";
            std::cout << "Precio final       : $" << p.precio_final       << "\n";

            // Guardar el struct completo en el arreglo estático
            guardar_en_historial(p);

        } else {
            std::cout << "\nDatos inválidos. Precio debe ser > 0 y descuento entre 0 y 100.\n";
            i--;    // Repetir este intento
        }
    }
}


// ============================================================
//  FLUJOGRAMA 2 — Descuento por cantidad fija
// ============================================================
void flujograma2() {
    int cantidad;

    std::cout << "\n==========================================\n";
    std::cout << "  FLUJOGRAMA 2: Descuento de cantidad fija\n";
    std::cout << "==========================================\n";

    std::cout << "¿Cuántos productos desea calcular? ";
    std::cin >> cantidad;

    for (int i = 1; i <= cantidad; i++) {
        std::cout << "\n--- Producto " << i << " de " << cantidad << " ---\n";

        // Usamos un struct para capturar los datos de entrada
        Producto p;
        p.tipo = POR_CANTIDAD_FIJA;

        std::cout << "Precio original del producto: $";
        std::cin >> p.precio_original;
        std::cout << "Cantidad de descuento a aplicar: $";
        std::cin >> p.descuento_aplicado;

        // Proceso: calcular precio final
        p.precio_final = p.precio_original - p.descuento_aplicado;

        // Decisión: precio final debe ser positivo
        if (p.precio_final > 0 && p.precio_original > 0) {

            p.porcentaje = (p.descuento_aplicado / p.precio_original) * 100.0;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "\n--- Resultado ---\n";
            std::cout << "Precio a pagar    : $" << p.precio_final       << "\n";
            std::cout << "Porcentaje ahorrado: " << p.porcentaje         << "%\n";

            // Guardar el struct completo en el arreglo estático
            guardar_en_historial(p);

        } else {
            std::cout << "\nDatos inválidos. El descuento no puede ser mayor o igual al precio.\n";
            i--;    // Repetir este intento
        }
    }
}


// ============================================================
//  PROGRAMA PRINCIPAL
// ============================================================
int main() {
    int opcion;

    std::cout << "=== Sistema de Cálculo de Descuentos ===\n";

    do {
        std::cout << "\n1. Flujograma 1 (descuento por porcentaje)\n";
        std::cout << "2. Flujograma 2 (descuento por cantidad fija)\n";
        std::cout << "3. Ver historial de la sesión\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: flujograma1();       break;
            case 2: flujograma2();       break;
            case 3: mostrar_historial(); break;
            case 0:
                mostrar_historial();
                std::cout << "\nFin del programa.\n";
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}