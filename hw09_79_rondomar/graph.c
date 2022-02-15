#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "graph.h"

#define BASE_CAP 100
#define FROM 0
#define TO 1
#define COST 2

graph_t* allocate_graph(){
	graph_t *graph = (graph_t*)malloc(sizeof(graph_t));
	graph->count_of_edges = 0;
	graph->data = (int**)malloc(BASE_CAP*sizeof(int*));
	for(int i = 0; i < BASE_CAP; ++i){
		graph->data[i] = (int*)malloc(3*sizeof(int));
	}
	graph->capacity = BASE_CAP;
	return graph;
}


void free_graph(graph_t **graph){
	for(int i = 0; i < (*graph)->capacity; ++i){
		free((*graph)->data[i]);
	}
	free((*graph)->data);
	free(*graph);
}


void load_txt(const char *fname, graph_t *graph){
	FILE *f = fopen(fname, "r");
	/*if(f == NULL){
		fputs("Error: Couldn't open file!\n", stderr);
	}*/
	while(!feof(f)){
		if(fscanf(f,"%d %d %d\n", &graph->data[graph->count_of_edges][FROM], &graph->data[graph->count_of_edges][TO], &graph->data[graph->count_of_edges][COST])){
			++graph->count_of_edges;
			if(graph->count_of_edges == graph->capacity){
				int old_cap = graph->capacity;
				graph->capacity *= 5;
				graph->data = (int**)realloc(graph->data, graph->capacity * sizeof(int*));
				for(int i = old_cap; i < graph->capacity; ++i){
					graph->data[i] = (int*)malloc(3 * sizeof(int));
				}
			}
		}
	}
	fclose(f);
}


void load_bin(const char *fname, graph_t *graph){
	FILE *f = fopen(fname, "rb");
	/*if(f == NULL){
		fputs("Error: Couldn't open file!\n", stderr);
	}*/
	int from, to, cost;
	while(fread(&from, sizeof(int), 1, f)){
		if(!fread(&to, sizeof(int), 1, f)) break;
		if(!fread(&cost, sizeof(int), 1, f)) break;
		graph->data[graph->count_of_edges][FROM] = from;
		graph->data[graph->count_of_edges][TO] = to;
		graph->data[graph->count_of_edges][COST] = cost;
		++graph->count_of_edges;
		if(graph->count_of_edges == graph->capacity){
			int old_cap = graph->capacity;
			graph->capacity *= 5;
			graph->data = (int**)realloc(graph->data, graph->capacity*sizeof(int*));
			for(int i = old_cap; i < graph->capacity; ++i){
				graph->data[i] = (int*)malloc(3*sizeof(int));
			}
		}
	}
	fclose(f);
}

void save_txt(const graph_t * const graph, const char *fname){
	FILE *f = fopen(fname, "w");
	for(int i = 0; i < graph->count_of_edges; ++i){
		fprintf(f,"%d %d %d\n", graph->data[i][FROM], graph->data[i][TO], graph->data[i][COST]);
	}
	fclose(f);
}

void save_bin(const graph_t * const graph, const char *fname){
	FILE *f = fopen(fname, "wb");
	for(int i = 0; i < graph->count_of_edges; ++i){
		fwrite(&graph->data[i][FROM], sizeof(int), 1, f);
		fwrite(&graph->data[i][TO], sizeof(int), 1, f);
		fwrite(&graph->data[i][COST], sizeof(int), 1, f);
	}
	fclose(f);
}

