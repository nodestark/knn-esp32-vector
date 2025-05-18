// gcc main.c -o main -lm && ./main

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define VECT_DIM 	4

typedef struct {
	int id;
    float data[VECT_DIM];
    float distance;
    void *next;
} vector_entry_t;

vector_entry_t *vector_entry_db = (void*) 0;

float euclidean_distance( float *a, float *b ){

	float soma = 0.00;

	for(int x = 0; x < VECT_DIM; x++){
		float diff = a[x] - b[x];

		soma += (diff * diff);
	}

	return sqrt(soma);
}

void add_vector(int id, float *vct){

	vector_entry_t *vector_entry = (vector_entry_t*) malloc( sizeof(vector_entry_t) );
	vector_entry->id = id;

	memcpy(vector_entry->data, vct, VECT_DIM * sizeof(float));

	vector_entry->next = vector_entry_db;

	vector_entry_db = vector_entry;
}

vector_entry_t* query_nn(float *vct){

	vector_entry_t *vector_entry = vector_entry_db;
	while(vector_entry){

		vector_entry->distance = euclidean_distance(vct, vector_entry->data);

		vector_entry = vector_entry->next;
	}

	vector_entry_t *vector_entry_ = vector_entry = vector_entry_db;
	while(vector_entry){

		if(vector_entry->distance < vector_entry_->distance)
			vector_entry_ = vector_entry;

		vector_entry = vector_entry->next;
	}

	return vector_entry_;
}

int main() {

	float db[5][4] = {
	        {1.1, 2.2, 3.3, 4.4},
	        {5.5, 6.6, 7.7, 8.8},
	        {9.9, 10.1, 11.1, 12.2},
	        {13.3, 14.4, 15.5, 16.6},
	        {17.7, 18.8, 19.9, 20.0}};

	add_vector(0, db[0]);
	add_vector(1, db[1]);
	add_vector(2, db[2]);
	add_vector(3, db[3]);
	add_vector(4, db[4]);

	float query[] = {8.9, 40.6, 1.1, 2.2};

	vector_entry_t *vector_entry = query_nn((float*) &query);

	printf(">_ %d\n", vector_entry->id);

	return 0;
}
