#include "entities.h"
#include "components.h"
#include "stdarg.h"

void init_entity_manager(struct entity_manager *manager) {
    memset(manager->flags, 0, sizeof(manager->flags));
}