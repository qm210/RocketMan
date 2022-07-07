int triangle_modulo(int x, int scale) {
    int double_scale = 2 * scale;
    int x_ = x % double_scale;
    return x_ < scale ? x_ : (double_scale - x_ - 1);
}
