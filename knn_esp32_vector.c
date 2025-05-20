// gcc main.c -o main -lm && ./main

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "knn_esp32_vector.h"

vector_entry_t *vector_entry_db = (void*) 0;

float cosine_distance( float *vctA, float *vctB ){

	float mag_a = 0.00, mag_b = 0.00, dot = 0.00;

	for(int x= 0; x < VECT_DIM; x++){

		dot  += vctA[x] * vctB[x];

		mag_a += vctA[x] * vctA[x];
		mag_b += vctB[x] * vctB[x];
	}

	return dot / (sqrt(mag_a)*sqrt(mag_b));
}

float euclidean_distance( float *vctA, float *vctB ){

	float soma = 0.00;

	for(int x = 0; x < VECT_DIM; x++){
		float diff = vctA[x] - vctB[x];

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
