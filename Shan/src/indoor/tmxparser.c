/*
* @author: Jarryd Hall
* Purpose: An XML Parser to parse a tilemap
* Note: The TMX file has been converted to an xml file before hand
* CommandLine usage: gcc source.c -I/usr/include/libxml2 -lxml2 -o output
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "tilemap.h"

xmlXPathObjectPtr retrieveXmlnodeset (xmlDocPtr doc, xmlChar *xpath)
{
	xmlXPathContextPtr context;
	xmlXPathObjectPtr object;

	context = xmlXPathNewContext(doc);
	if (context == NULL) 
	{
		printf("xmlXPathNewContext error\n");
		return NULL;
	}
	object = xmlXPathEvalExpression(xpath, context);
	xmlXPathFreeContext(context);
	
	if (object == NULL) 
	{
		printf("xmlXPathEvalExpression error\n");
		return NULL;
	}
	if (xmlXPathNodeSetIsEmpty(object->nodesetval))
	{
		xmlXPathFreeObject(object);
		printf("xmlXPathObject couldnt be created\n");
		return NULL;
	}
	return object;
}

void getMapDetails (xmlDocPtr doc, xmlNodePtr cur, ThreeDWorld *world)
{
	xmlChar *mapWidth;
	xmlChar *mapHeight;
	xmlChar *tileWidth;
	xmlChar *tileHeight;
	
	if((!xmlStrcmp(cur->name, (const xmlChar *)"map")))
	{
		mapWidth = xmlGetProp(cur, "width");
		int mw = atoi(mapWidth);
		world->mapWidth = mw;
		
		mapHeight = xmlGetProp(cur, "height");
		int mh = atoi(mapHeight);
		world->mapHeight = mh;
		
		tileWidth = xmlGetProp(cur, "tilewidth");
		int tw = atoi(tileWidth);
		world->tileWidth = tw;
		
		tileHeight = xmlGetProp(cur, "tileheight");
		int th = atoi(tileHeight);
		world->tileHeight = th;
	}
	
	int mapH = atoi(mapHeight);
	int mapW = atoi(mapWidth);
	world->representation = malloc(sizeof(int *) * mapH);
	int i;
	for (i = 0; i < mapH; i++ )
	{
		world->representation[i] = malloc(sizeof(int) * mapW);
	}
}

void createTwoDArray(ThreeDWorld *world, int w, int h, int array[])
{
	int one;
	int two;
	int arrayCounter = 0;
	
	for(one = 0; one < h; one++)
	{
		for(two = 0; two < w; two++)
		{
			//printf("Value in tile array is %d\n", array[one + two]);
			world->representation[one][two] = array[arrayCounter];
            printf("  %d", world->representation[one][two]);
			if(two == 9)
				printf("\n");	
			arrayCounter++;
		}
	}
}

/* A function to return all the tiles and their type. 
* e.g. background tiles and collision tiles
* purpose: Outputs the list of tiles and their types which will be used 
* to create a 2dimensional array representation
* TODO: add code to create the 2d array representation on the fly
*/
void getTileDetails (xmlDocPtr doc, xmlNodePtr cur, ThreeDWorld *world)
{
	xmlChar *xpath = (xmlChar*) "//layer[@name=\"collision\"]/data/tile/@gid";
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;

	xmlChar *keyword;

	int width = world->mapWidth;
	int height = world->mapHeight;
	int i;
	int numMovableTiles = 0;
	int numCollisionTiles = 0;
	int totalTiles = 0;
	int tileValuesArray [width * height]; 
	int arrayCounter = 0;
	
	result = retrieveXmlnodeset (doc, xpath);
	if (result) 
	{
		nodeset = result->nodesetval;
		for (i=0; i < nodeset->nodeNr; i++) 
		{
			keyword = xmlNodeListGetString(doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);
		
			int id = atoi(keyword);
			int index = i;
			
			if (id == 0)
			{
				tileValuesArray[arrayCounter] = 0;
				arrayCounter++;
				numMovableTiles += 1;
			}
			if (id != 0)
			{
				tileValuesArray[arrayCounter] = 1;
				arrayCounter++;
				numCollisionTiles += 1;
			}
			 		
			xmlFree(keyword);
		}
		xmlXPathFreeObject (result);
	}
	
	totalTiles = numMovableTiles + numCollisionTiles;
	
	printf("number of collision tiles : %d\n", numCollisionTiles);
	printf("number of movable tiles : %d\n", numMovableTiles);
	printf("Total tiles : %d\n", totalTiles);
	world->numberOfTilesInMap = totalTiles;
	
	createTwoDArray(world, width, height, tileValuesArray);
	//world->height = 
}

/* Helper function to retrieve a the value for the specfied attribute at a specified node */
char* getAttributeValueForNode (xmlDocPtr doc, xmlNodePtr cur, char *node, char *attribute)
{
	xmlChar *attributeValue;
	cur = cur->xmlChildrenNode;
	
	while (cur != NULL)
	{
		if((!xmlStrcmp(cur->name, (const xmlChar *) node)))
		{
			attributeValue = xmlGetProp(cur, attribute);
			printf("node: %s value: %s\n", node, attributeValue);
		}
		cur = cur->next;
	}
	//xmlFree(attributeValue);
	return (char *)attributeValue;
}




/* TODO: Add functions to return all the data in a struct. */
void parseDoc(char *docname, ThreeDWorld *world) 
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);
	
	if (doc == NULL) 
	{
		fprintf(stderr,"Parsing was unsuccesful \n");
		return;
	}
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) 
	{
		fprintf(stderr,"No XML Data\n");
		xmlFreeDoc(doc);
		return;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "map"))
	{
		fprintf(stderr,"Root node != map, not a tmx file\n");
		xmlFreeDoc(doc);
		return;
	}
	
	getMapDetails(doc, cur, world);
	getTileDetails(doc, cur, world);

	xmlFreeDoc(doc);
	return;
}

void fill_map(ThreeDWorld * world) {
	char *doc = "/Users/E0/Desktop/linkthis/src/indoor/secondYearSquare.xml";
	parseDoc(doc, world);
}
