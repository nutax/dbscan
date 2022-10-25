#ifndef __RANDOM_H__
#define __RANDOM_H__

#define FAST_RAND_MAX 32767
static unsigned int g_seed = 0;

inline void rand_seed(unsigned int seed)
{
    g_seed = seed;
}

inline int fast_rand(void)
{
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

#endif