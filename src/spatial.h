/**
 * Using the Barnes-Hut algorithm (http://arborjs.org/docs/barnes-hut).
 */

#ifndef SPATIAL_H
#define SPATIAL_H

struct bh_tree {
    struct bh_tree *children[4];
};

#endif