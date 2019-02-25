#ifndef V2_H
#define V2_H

struct v2 {
    float x;
    float y;
};

float rand_normalized();
float v2_length(struct v2 v);
struct v2 v2_normalized(struct v2 v);
struct v2 v2_rand_normalized();
struct v2 v2_truncated(struct v2 v, float max);
struct v2 v2_add(struct v2 a, struct v2 b);
struct v2 v2_sub(struct v2 a, struct v2 b);
struct v2 v2_dot(struct v2 a, struct v2 b);
struct v2 v2_mult_scalar(struct v2 v, float c);
struct v2 v2_div_scalar(struct v2 v, float c);

#endif