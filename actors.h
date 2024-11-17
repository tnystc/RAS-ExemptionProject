#ifndef ACTORS_H
#define ACTORS_H

#include "raylib.h"


typedef struct CircleNode {
    float radius;
    Vector2 position;
    float lineLength;
    float angularSpeed;
    float angle;
    Color color;
    struct CircleNode *next;
    struct CircleNode *prev;
} CircleNode;

typedef struct List {
    CircleNode *head;
    CircleNode *tail;
} List;

CircleNode* createCircle(float radius, Vector2 parentPosition, float lineLength, float angularSpeed, Color color);
void addCircle(List *list, CircleNode *node);
void removeCircle(List *list);


#endif