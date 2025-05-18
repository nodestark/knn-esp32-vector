#ifndef KNN_ESP32_VECTOR_H
#define KNN_ESP32_VECTOR_H

#define VECT_DIM 	4

typedef struct {
	int id;
    float data[VECT_DIM];
    float distance;
    void *next;
} vector_entry_t;

void add_vector(int id, float *vct);
vector_entry_t* query_nn(float *vct);

#endif
