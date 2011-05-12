/*

	@file: nav_gps_nav.c

	@author: Qiushi Wang

	@date: May 10th, 2011

	@detail: internal integration of the GPS Navigation System, give interface to Nav-Corelogic. 

	to do:
		1. when could not receive good data in a long period, stop the GPS IO loop. 
		2. send movement command.
*/
#include "nav_gps_nav.h"


void setup_gps(char *dev,int baud)
{
	good_data = 0;

	GPSLocation *curr_position_UI = NULL;

	currentOutdoorPosition.latitude = 0;
	currentOutdoorPosition.longitude = 0;

	int32_t fd = 0;
	char buf [256];

	fd = dev_init(dev,baud);

	if(fd == -1)
	{
	printf("can not init device\n");
	return;
	}

	usleep(1000*1000);

	while(GPSIO_ON_OFF){

	    	serial_read(fd,buf,10);

		if (strncmp(buf, "$GPRMC",6) == 0)
		{

			if(check_gps_output(buf))
			{			
		    		printf("%s",buf);
				
				struct point *position = parser(buf);

				currentOutdoorPosition.latitude = curr.lat = in_degree(position->lat);
				currentOutdoorPosition.longitude = curr.lon = in_degree(position->lon);

				free(position);
		
				if(currentOutdoorPosition.latitude != 0)
				{
					good_data = 1;
					/*
					// send current position to UI
					
					curr_position_UI = malloc(sizeof(GPSLocation));	

					curr_position_UI->latitude = curr.lat;
					curr_position_UI->longitude = curr.lon;				

					nav_sendCurrentOutdoorPositionToGui(curr_position_UI);

					*/
				}
				else
				{
					good_data = 0;
				}
	
				printf("lat: %f ",currentOutdoorPosition.latitude);
				printf("lon: %f\n",currentOutdoorPosition.longitude);
			}	
		}
	}
}




void gps_navigation(GPSLocation* Destination)
{
	struct point destination = {-2,Destination->latitude,Destination->longitude};

	struct point *pts = init_map(); 			

	struct trac *path = calc_path(pts,destination); 	

	GPSLocation **path_UI = path_for_UI(path,pts);	// Path to UI 

/*	printf("UI:  %f,%f\n",path_UI[0]->latitude,path_UI[0]->longitude);
	printf("UI:  %f,%f\n",path_UI[1]->latitude,path_UI[1]->longitude);
	printf("UI:  %f,%f\n",path_UI[2]->latitude,path_UI[2]->longitude);
	printf("UI:  %f,%f\n",path_UI[3]->latitude,path_UI[3]->longitude);
	printf("UI:  %f,%f\n",path_UI[4]->latitude,path_UI[4]->longitude);
	printf("UI:  %f,%f\n",path_UI[5]->latitude,path_UI[5]->longitude);
	printf("UI:  %f,%f\n",path_UI[6]->latitude,path_UI[6]->longitude);
	printf("UI:  %f,%f\n",path_UI[7]->latitude,path_UI[7]->longitude);
*/

	/* 
	//send UI the path 

	nav_sendOutdoorPathToGui(GPSLocation path_UI);
	*/
	
	struct trac *next_Node = path;

	int32_t angle = 0;

	int32_t distance_to_nextNode = 0; 

	while(GPSNAV_ON_OFF)
	{
		next_Node = update_path(curr,destination,pts,next_Node);

		angle = give_angle(curr,destination,pts,next_Node);

		distance_to_nextNode = give_distance(curr,destination,pts,next_Node);

		printf("angle : %d  distance : %d\n",angle,distance_to_nextNode);

	/*
        send movement command here.

	if(sendMovement == 1){

	if( angle == -2 )
	{                                 // sendautomovementcommand(char order , int height, int distance, int yaw)	
		sendautomovementcommand(1,2,1,0);  // auto, landing, 1m, 0 degree.	
	}
	else if( angle == -1)
	{
		sendautomovementcommand(1,0,0,0);  // auto, hovering, 0m, 0 degree.
	}
	else
	{
		sendautomovementcommand(1,1,distance_to_nextNode,angle);
	}


	set_MovementCommand_False();

	}//sendMovement=1
	*/
	
	sleep(1);
}

	/* dealloc */
	free(pts);
	deallocate_trac(path);
}


/*
        -2: arrive the destination
	-1: waiting
     0-359: moveing there	
*/
int give_angle(struct point currp,struct point dest,struct point *pts,struct trac *next_Node)
{
	struct point next_Point = {0,0,0};

	int32_t angle = -1;
			
	if(next_Node->p == -2)
	{	
		next_Point = dest;

		angle = (int)calc_angle(currp,next_Point);

		if(calc_dist(currp,next_Point)<10)
		{
			angle = -2;
		}
	}
	else
	{
		next_Point = pts [next_Node->p - 1];
		angle = (int)calc_angle(currp,next_Point);			
	}	
	return angle;		
}





int give_distance(struct point currp,struct point dest,struct point *pts,struct trac *next_Node)
{
	struct point next_Point = {0,0,0};

	int32_t distance = 11;

	if(next_Node->p = -2)
	{
		next_Point = dest;
		distance = calc_dist(currp,next_Point);
	}
	else
	{
		next_Point = pts [next_Node->p - 1];		
		distance = calc_dist(currp,next_Point);
	}
	return distance;
}





struct trac* update_path(struct point currp,struct point dest,struct point *pts,struct trac *next_Node)
{
	struct point next_Point = {0,0,0};

	if(next_Node->p == -1)
	{	
		return next_Node->last;
	}
	else if( next_Node->p == -2 )
	{
		return next_Node;
	}
	else
	{
		next_Point = pts [next_Node->p - 1];

		if(calc_dist(currp,next_Point) <= 10)
		{
			if(next_Point.name != -2)
			{
			return next_Node->last;		
			}
			else{
			return next_Node;}			
		}
		else
		{
			return next_Node;
		}

	}
}





void get_startp(struct point *pt)
{
	pt->name = -1;
	pt->lat = currentOutdoorPosition.latitude;
	pt->lon = currentOutdoorPosition.longitude;
}




struct link* connect_nodes(struct dist *st1,struct dist *st2,struct dist *end1,struct dist *end2,struct point *pts,struct link* lk)
{
	if(st1->name == end1->name && st1->name == 0)
	{
		printf("go there straight\n");
		lk = add_link(-1,-2,0.0000,lk);			
	}
	else if(st2->name == end2->name && st2->name == 0)
	{
		printf("go there straight\n");
		lk = add_link(-1,-2,0.0000,lk);
	}
	else
	{
	if(st1->name != 0)
	lk = add_link(-1,st1->name,st1->distance,lk);
	
	if(st2->name != 0)	
	lk = add_link(-1,st2->name,st1->distance,lk);

	if(end1->name != 0)
	lk = add_link(end1->name,-2,end1->distance,lk);
	
	if(end2->name != 0)	
	lk = add_link(end2->name,-2,end2->distance,lk);
	
	lk = init_link(lk,pts);
	}

	return lk;
}





struct trac *calc_path(struct point *pts,struct point destination)
{
	struct link *lk = NULL;
	struct dist *st_1, *st_2, *end_1, *end_2;	/* options of */
	struct trac *path;

	struct point startp;
	get_startp(&startp);

	struct point endp;
	endp.name = -2;
	endp.lat = destination.lat;
	endp.lon = destination.lon;

	st_1 = pnode(startp,endp,pts,0);
							//printf("st1 %d\n", st_1->name);	
	st_2 = pnode(startp,endp,pts,1);
							//printf("st2 %d\n", st_2->name);
	end_1 = pnode(endp,startp,pts,0);
							//printf("end1 %d\n", end_1->name);
	end_2 = pnode(endp,startp,pts,1);
							//printf("end2 %d\n", end_2->name);

	lk = connect_nodes(st_1,st_2,end_1,end_2,pts,lk);

	if(lk->last == NULL)				/*you can go there straight, no necessary to run dijkstra*/
	{
		struct trac *head;
	
		path = malloc(sizeof(struct trac));
		path->p = -2;
		path->last = NULL;

		head = path;

		path = malloc(sizeof(struct trac));
		path->p = -1;
		path->last = head;
	}
	else
	{
		path = calculate(startp.name,endp.name,lk);
	}

		struct trac *head;
		head = path;	

	while(head != NULL){
		printf("%d + ",head->p);
		int element = head->p;
		struct point m;
		switch(element) {
		
		case -1: printf("start latitude:%f,longitude:%f\n", startp.lat,startp.lon);
			break;		
		case -2: printf("end latitude:%f, longitude: %f \n", endp.lat,endp.lon);
			break;
		default: m = pts [element-1];
			printf("latitude:%f,longitude:%f\n",m.lat,m.lon);
			break;
		}	
		head = head->last;
	}

/*---- deallocate memory ----*/
	free(st_1);
	free(st_2);
	free(end_1);
	free(end_2);
	deallocate_link(lk);

return path;
}



/* check that the output of gps is available */
int32_t check_gps_output(char buf [])
{
	int32_t i = 0;
	int32_t num = 0;

	while(buf [i] != 10)
	{
		if(buf [i] == 44)
		num++;
	i++;
	}	
	
	if( num == 12)
	return 1;
	else
	return 0;
}



int32_t get_goodData()
{
	return good_data;
}




/* generate the path what's gonna be sent to UI */
GPSLocation **path_for_UI(struct trac* path,struct point* pts)
{
	struct trac *currp = path;

	GPSLocation **Route = NULL;

	GPSLocation *node = NULL;

	int32_t i = 0;

	Route = malloc(sizeof(GPSLocation*));

	while(currp != NULL)
	{
		if(i != 0)
		Route = realloc(Route,(i+1)*sizeof(GPSLocation*));

		node = malloc(sizeof(GPSLocation));

		if(i == 0)
		{
		node->latitude = curr.lat;
		node->longitude = curr.lon;		
		}
		else
		{
		node->latitude = pts[currp->p - 1].lat;
		node->longitude = pts[currp->p - 1].lon;
		}

		printf("%d index \n",i);
		Route [i] = node;

		currp = currp->last;
		i++;		
	}
	
	return Route;
}


