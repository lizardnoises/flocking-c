#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
#include "entities.h"
#include "raymath.h"

void update_position(struct component_manager *com_man, struct entity_manager *ent_man) {
    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        if (ent_man->flags[i].position && ent_man->flags[i].move) {
            com_man->position[i].position = Vector2Add(com_man->position[i].position, com_man->move[i].velocity);
        }
    }
}

#endif