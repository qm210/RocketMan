
int triangle_modulo(int x, uint16_t scale) {
    uint16_t double_scale = 2 * scale;
    int x_ = x % double_scale;
    return x_ < scale ? x_ : (double_scale - x_ - 1);
}


// #define ARRAY_SIZE(A) (sizeof(A)/sizeof(A[0]))
