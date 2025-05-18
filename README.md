# Tiny ESP32 KNN Vector Database

That project demonstrates the integration and usage of the **knn-esp32-vector** component as a *tiny vector database* for ESP32, using the ESP-IDF framework. Add vectors to a small database and query the nearest vector using the KNN (K-Nearest Neighbor) algorithm.

---

## 📋 Description

The **knn-esp32-vector** is a minimalist vector database for ESP32 microcontrollers. It allows storing fixed-dimension vectors (`VECT_DIM`) in RAM and efficiently performing vector queries based on Euclidean distance.

---

## ⚙️ Importing

To use the component via ESP-IDF dependency management, add the following to your project's `idf_component.yml` file:

```yaml
dependencies:
  knn-esp32-vector:
    git: "https://github.com/nodestark/knn-esp32-vector.git"
    version: "main"
````

Then, reconfigure the project:

```bash
idf.py reconfigure
```

---

## 🛠️ Functionality

The component provides the following functions in `knn_esp32_vector.h`:

* `void add_vector(int id, const float *vector);`

  * Adds a vector to the database, associating it with a unique identifier.

* `vector_entry_t *query_nn(const float *query);`

  * Executes a KNN query (with K = 1), returning a pointer to the structure with the ID and distance of the nearest vector.

The `vector_entry_t` structure contains:

```c
typedef struct {
    int    id;        // ID of the stored vector
    float  distance;  // Distance to the query vector
} vector_entry_t;
```

---

## 🚀 Usage Example / Test

File: `teste_knn.c`

```c
#include <stdio.h>
#include "knn_esp32_vector.h"

void app_main(void) {

    // Database with 5 vectors of dimension VECT_DIM (4)
    float db[5][VECT_DIM] = {
            {1.1, 2.2, 3.3, 4.4},
            {5.5, 6.6, 7.7, 8.8},
            {9.9, 10.1, 11.1, 12.2},
            {13.3, 14.4, 15.5, 16.6},
            {17.7, 18.8, 19.9, 20.0}
    };

    // Add vectors to the database
    for (int i = 0; i < 5; i++) {
        add_vector(i, db[i]);
    }

    // Query vector
    float query[] = {8.9, 40.6, 1.1, 2.2};

    // KNN query (K = 1)
    vector_entry_t *result = query_nn((float *)&query);

    // Print the ID of the nearest vector
    printf(">_ Nearest ID: %d\n", result->id);
}
```

### CMakeLists.txt (main)

```cmake
idf_component_register(
    SRCS "teste_knn.c"
    INCLUDE_DIRS "."
    REQUIRES knn-esp32-vector
)
```

### idf\_component.yml (project root)

```yaml
dependencies:
  knn-esp32-vector:
    git: "https://github.com/nodestark/knn-esp32-vector.git"
    version: "main"
```

```
```
