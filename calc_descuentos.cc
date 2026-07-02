#include <iostream>
#include <stdexcept>

const int MAX_PRODUCTOS = 50;

enum TipoDescuento {
    POR_PORCENTAJE,
    POR_CANTIDAD_FIJA
};

struct Producto {
    double precio_original;
    double descuento_aplicado;
    double precio_final;
    double porcentaje;
    TipoDescuento tipo;
};

Producto historial[MAX_PRODUCTOS];
int total_registros = 0;

void imprimir_double(double valor) {
    if (valor < 0.0) {
        std::cout << '-';
        valor = -valor;
    }

  
    long long entero = static_cast<long long>(valor);

   
    long long centavos = static_cast<long long>((valor - entero) * 100.0 + 0.5);

    // Si el redondeo sube los centavos a 100, ajustamos
    if (centavos >= 100) {
        entero++;
        centavos -= 100;
    }

    std::cout << entero << '.';
    if (centavos < 10) std::cout << '0';
    std::cout << centavos;
}

bool es_precio_valido(double precio) {
    return precio > 0.0;
}
bool es_porcentaje_valido(double porcentaje) {
    return porcentaje >= 0.0 && porcentaje <= 100.0;
}

bool es_descuento_fijo_valido(double precio, double descuento) {
    return descuento > 0.0 && descuento < precio;
}

// Limpia el estado de error de cin y descarta lo que haya quedado
// en el buffer, para que la siguiente lectura no se rompa.
void limpiar_entrada() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void calcular_por_porcentaje(Producto& p) {
    p.descuento_aplicado = (p.precio_original * p.porcentaje) / 100.0;
    p.precio_final       = p.precio_original - p.descuento_aplicado;
}

void calcular_por_cantidad_fija(Producto& p) {
    p.precio_final = p.precio_original - p.descuento_aplicado;
    p.porcentaje   = (p.descuento_aplicado / p.precio_original) * 100.0;
}



int leer_cantidad_productos() {
    int cantidad;
    while (true) {
        try {
            std::cout << "Cuántos productos desea calcular? ";
            std::cin >> cantidad;
            if (std::cin.fail()) {
                throw std::runtime_error("Debe ingresar un número entero.");
            }
            if (cantidad <= 0) {
                throw std::runtime_error("La cantidad debe ser mayor que 0.");
            }
            return cantidad;
        } catch (const std::exception& e) {
            std::cout << "\n[Error] " << e.what() << "\n";
            limpiar_entrada();
        }
    }
}


void leer_datos_porcentaje(Producto& p, int i, int total) {
    std::cout << "\n--- Producto " << i << " de " << total << " ---\n";

    std::cout << "Precio original del producto: $";
    std::cin >> p.precio_original;
    if (std::cin.fail()) {
        limpiar_entrada();
        throw std::runtime_error("El precio ingresado no es un número válido.");
    }

    std::cout << "Porcentaje de descuento (%): ";
    std::cin >> p.porcentaje;
    if (std::cin.fail()) {
        limpiar_entrada();
        throw std::runtime_error("El porcentaje ingresado no es un número válido.");
    }

    p.tipo = POR_PORCENTAJE;
}


void leer_datos_cantidad_fija(Producto& p, int i, int total) {
    std::cout << "\n--- Producto " << i << " de " << total << " ---\n";

    std::cout << "Precio original del producto: $";
    std::cin >> p.precio_original;
    if (std::cin.fail()) {
        limpiar_entrada();
        throw std::runtime_error("El precio ingresado no es un número válido.");
    }

    std::cout << "Cantidad de descuento a aplicar: $";
    std::cin >> p.descuento_aplicado;
    if (std::cin.fail()) {
        limpiar_entrada();
        throw std::runtime_error("El descuento ingresado no es un número válido.");
    }

    p.tipo = POR_CANTIDAD_FIJA;
}


void mostrar_resultado_porcentaje(const Producto& p) {
    std::cout << "\n--- Resultado ---\n";
    std::cout << "Descuento aplicado : $"; imprimir_double(p.descuento_aplicado); std::cout << "\n";
    std::cout << "Precio final       : $"; imprimir_double(p.precio_final);       std::cout << "\n";
}


void mostrar_resultado_cantidad_fija(const Producto& p) {
    std::cout << "\n--- Resultado ---\n";
    std::cout << "Precio a pagar     : $"; imprimir_double(p.precio_final); std::cout << "\n";
    std::cout << "Porcentaje ahorrado: ";  imprimir_double(p.porcentaje);   std::cout << "%\n";
}
void mostrar_fila_historial(const Producto& p, int indice) {
    std::cout << "\n  [" << indice << "] "
              << (p.tipo == POR_PORCENTAJE
                  ? "Descuento por porcentaje"
                  : "Descuento por cantidad fija") << "\n";
    std::cout << "      Precio original : $"; imprimir_double(p.precio_original);    std::cout << "\n";
    std::cout << "      Descuento        : $"; imprimir_double(p.descuento_aplicado); std::cout << "\n";
    std::cout << "      Porcentaje       : ";  imprimir_double(p.porcentaje);         std::cout << "%\n";
    std::cout << "      Precio final     : $"; imprimir_double(p.precio_final);       std::cout << "\n";
}


void mostrar_historial() {
    if (total_registros == 0) {
        std::cout << "\nNo hay productos registrados en esta sesión.\n";
        return;
    }

    std::cout << "             HISTORIAL DE LA SESIÓN\n";
    for (int i = 0; i < total_registros; i++) {
        mostrar_fila_historial(historial[i], i + 1);
    }
    std::cout << "  Total de productos calculados: " << total_registros << "\n";
   
}



void guardar_en_historial(Producto p) {
    if (total_registros < MAX_PRODUCTOS) {
        historial[total_registros] = p;
        total_registros++;
    } else {
        std::cout << "\n[Advertencia] Se alcanzó el límite de "
                  << MAX_PRODUCTOS << " productos en el historial.\n";
    }
}



void flujograma1() {
    std::cout << "  FLUJOGRAMA 1: Descuento por porcentaje\n";

    int cantidad = leer_cantidad_productos();

    for (int i = 1; i <= cantidad; i++) {
        Producto p;

        try {
            leer_datos_porcentaje(p, i, cantidad);

            if (!es_precio_valido(p.precio_original) ||
                !es_porcentaje_valido(p.porcentaje)) {
                std::cout << "\nDatos inválidos. Precio debe ser > 0 "
                             "y descuento entre 0 y 100.\n";
                i--;
                continue;
            }

            calcular_por_porcentaje(p);
            mostrar_resultado_porcentaje(p);
            guardar_en_historial(p);

        } catch (const std::exception& e) {
            std::cout << "\n[Error] " << e.what() << "\n";
            i--;
        }
    }
}

void flujograma2() {
    std::cout << "  FLUJOGRAMA 2: Descuento de cantidad fija\n";

    int cantidad = leer_cantidad_productos();

    for (int i = 1; i <= cantidad; i++) {
        Producto p;

        try {
            leer_datos_cantidad_fija(p, i, cantidad);

            if (!es_precio_valido(p.precio_original) ||
                !es_descuento_fijo_valido(p.precio_original, p.descuento_aplicado)) {
                std::cout << "\nDatos inválidos. El descuento no puede "
                             "ser mayor o igual al precio.\n";
                i--;
                continue;
            }

            calcular_por_cantidad_fija(p);
            mostrar_resultado_cantidad_fija(p);
            guardar_en_historial(p);

        } catch (const std::exception& e) {
            std::cout << "\n[Error] " << e.what() << "\n";
            i--;
        }
    }
}

int mostrar_menu() {
    int opcion;
    std::cout << "\n1. Flujograma 1 (descuento por porcentaje)\n";
    std::cout << "2. Flujograma 2 (descuento por cantidad fija)\n";
    std::cout << "3. Ver historial de la sesion\n";
    std::cout << "0. Salir\n";
    std::cout << "Opcion: ";

    try {
        std::cin >> opcion;
        if (std::cin.fail()) {
            throw std::runtime_error("Debe ingresar un número.");
        }
    } catch (const std::exception& e) {
        std::cout << "\n[Error] " << e.what() << "\n";
        limpiar_entrada();
        opcion = -1; // cae en el "default" del switch en main()
    }

    return opcion;
}
int main() {
    std::cout << "=== Sistema de Cálculo de Descuentos ===\n";

    int opcion;
    do {
        opcion = mostrar_menu();

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