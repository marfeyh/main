/*
 * path_structure.h
 *
 * Authors: Jon Fridéhn Eric Britsman Shan Huang
 */
#ifndef NAV_INDOORSTRUCTURE_H
#define NAV_INDOORSTRUCTURE_H

#include <stdint.h>
#include <sys/time.h>
#include <math.h>

#define MAP_Y 12
#define MAP_X 10
#define NUM_ADJACENT 8
#define CENTIMETRES_PER_TILE 108
#define TILE_CENTER (CENTIMETRES_PER_TILE/2)
#define TRUE_NORTH 10 + 90
#define AVOID_DISTANCE 100

typedef struct {
    double lon;
    double lat;
    double angle;
    double distance;
} roomPosition;
typedef struct progressiveNode {
    roomPosition p;
    struct progressiveNode *prev;
    struct progressiveNode *next;
} progressiveNode;
typedef struct {
    int32_t x;
    int32_t y;
} tile;
typedef struct node {
    tile pos;
    int32_t totalCost, heuristic;
    tile previous;
}node;
typedef struct {
    node *list;
    int32_t count;
}nodeList;
typedef struct {
    roomPosition *list;
    int32_t num;
}positionList;

positionList indoorDijkstra(const tile *start, const tile *end);
positionList indoorAstar(const tile *start, const tile *end);
void initIndoorNavigation(void);
void initPath(tile *start, tile *end);
void stopIndoorNavigation(void);
void collisionAvoided(int32_t direction);
roomPosition getCurrentPosition(void);
tile * getDestinationTile(void);
int8_t getRunning();

#endif /* NAV_INDOORSTRUCTURE_H */