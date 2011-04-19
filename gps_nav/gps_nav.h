#ifndef GPS_NAV
#define GPS_NAV

#include <stdio.h>
#include "dijk.h"

#include "serial.h"
#include "parser.h"


static int ON_OFF = 1; 

struct point curr;	/* current position, this data will be modified by gps device reader */ 

void setup_gps(char *dev,int baud);

void gps_navigation(struct point Destination);

void get_startp(struct point *pt);

struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link *lk);

struct trac* outdoor_nav(struct point *pts,struct point destination);

int get_direction(struct point currp,struct point dest,struct point *pts,struct trac *next_Node);

#endif
