# EDA_cache_oblivious_static_tree
----
# Cache-Oblivious Static Tree vs BST

## 📌 Descripción

Este proyecto implementa y compara:

- Binary Search Tree (BST) basado en punteros
- Cache-Oblivious Static Tree usando layout tipo van Emde Boas (vEB)

El objetivo es evaluar el impacto de la localidad de memoria en el rendimiento.

---

## ⚙️ Configuración del experimento

- Número de elementos: 1,000,000
- Número de consultas: 1,000,000
- Tipo de dato: enteros de 32 bits
- Distribución: aleatoria uniforme

---

## 🧪 Metodología

1. Generar N enteros aleatorios
2. Ordenar los datos
3. Construir:
   - BST (inserción secuencial)
   - vEB tree (layout cache-oblivious)
4. Generar Q consultas aleatorias
5. Medir tiempo de búsqueda para ambos árboles
6. Repetir T veces y promediar

---

## ⏱️ Métrica

Tiempo total de ejecución de Q búsquedas:
