#include "actors.h"
#include <stdlib.h>
#include "raylib.h"
#include <stdio.h>
#include <math.h>


CircleNode* createCircle(float radius, Vector2 parentPosition, float lineLength, float angularSpeed, Color color) {
    CircleNode *newCircle = malloc(sizeof(CircleNode));
    if (newCircle) {
        newCircle->radius = radius;
        newCircle->angle = GetRandomValue(0, 2*PI);
        newCircle->position = (Vector2){parentPosition.x + lineLength*cos(newCircle->angle), parentPosition.y + lineLength*sin(newCircle->angle)};
        newCircle->lineLength = lineLength;
        newCircle->angularSpeed = angularSpeed;
        newCircle->color = color;
        newCircle->next = NULL;
        newCircle->prev = NULL;
    }
    printf("createCircle Success\n");
    return newCircle;
}

void addCircle(List *list, CircleNode *circle) {
    if (list->head == NULL) {
        list->head = circle;
        list->tail = circle;
    } else {
        list->tail->next = circle;
        circle->prev = list->tail;
        list->tail = circle;
    }
    printf("addCircle Success\n");
}

//Remove from head (skipping the dummy node) 
void removeCircle(List *list) {
    if (list->head->next == NULL){
    return;
    }
    CircleNode *temp = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free(temp);
    printf("removeCircle Success\n");
}


