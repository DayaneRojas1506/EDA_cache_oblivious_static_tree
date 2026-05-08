# EDA_cache_oblivious_static_tree
- Rojas Brigitte
- Miranda Yoselyn

## Descripción

Este proyecto implementa y compara:

- Binary Search Tree (BST) basado en punteros
- Cache-Oblivious Static Tree usando layout tipo van Emde Boas (vEB)

El objetivo es evaluar el impacto de la localidad de memoria en el rendimiento.

---

## Configuración del experimento

- Número de elementos: 1,000,000
- Número de consultas: 1,000,000
- Tipo de dato: enteros de 32 bits
- Distribución: aleatoria uniforme

---

## Metodología

1. Generar N enteros aleatorios
2. Ordenar los datos
3. Construir:
   - BST (inserción secuencial)
   - vEB tree (layout cache-oblivious)
4. Generar Q consultas aleatorias
5. Medir tiempo de búsqueda para ambos árboles
6. Repetir T veces y promediar

---

# Resultados Experimentales

Parámetros del experimento:

- Número de elementos: 1,000,000
- Número de consultas: 1,000,000
- Número de experimentos: 5
- Tipo de dato: enteros de 32 bits

## Resultados

| Experimento | BST (s) | vEB Tree (s) | Speedup |
|---|---:|---:|---:|
| 1 | 0.947421 | 0.456572 | 2.075x |
| 2 | 0.961711 | 0.520459 | 1.848x |
| 3 | 0.969290 | 0.456134 | 2.125x |
| 4 | 0.942815 | 0.470535 | 2.004x |
| 5 | 0.972997 | 0.480469 | 2.025x |
| **Promedio** | **0.958847** | **0.476834** | **2.011x** |

## Observaciones

El árbol cache-oblivious con layout van Emde Boas (vEB) obtuvo aproximadamente un speedup de 2x respecto al BST implementado con punteros.

La mejora se debe principalmente a una mejor localidad de memoria y menor cantidad de fallos de caché durante las búsquedas
