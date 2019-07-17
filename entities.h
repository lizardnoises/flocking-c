#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdint.h>
#include <string.h>

#define MAX_ENTITIES 256

struct entity_manager {
    struct component_flags flags[MAX_ENTITIES];
};

void init_entity_manager(struct entity_manager *manager);

#endif