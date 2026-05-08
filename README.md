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

# Resultados de Experimentos

| Experimento | BST (s) | vEB (s) | Hits BST | Hits vEB |
|---|---:|---:|---:|---:|
| 1 | 0.971584 | 0.471755 | 1000000 | 1000000 |
| 2 | 0.979670 | 0.360066 | 1000000 | 1000000 |
| 3 | 0.975111 | 0.465507 | 1000000 | 1000000 |
| 4 | 1.003750 | 0.461009 | 1000000 | 1000000 |
| 5 | 1.010250 | 0.457245 | 1000000 | 1000000 |

# Resultados Promedio

| Estructura | Tiempo promedio |
|---|---:|
| BST | 0.988073 s |
| vEB | 0.443116 s |
