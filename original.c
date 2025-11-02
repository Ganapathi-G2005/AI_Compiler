#include <stdio.h>

int main() {

    int arr[100];  // Array allocation
    int *t22, *t23, *t25, *t26, *t32, *t33, *t38, *t39, *t57, *t58;
    int *t65, *t66;

    int a, b, c, d, e, f, g, h, i, j;
    int k, l, m, n, o, p, q, r, s, t;
    int t0, t1, t10, t11, t12, t13, t14, t15, t16, t17;
    int t18, t19, t2, t20, t21, t24, t27, t28, t29, t3;
    int t30, t31, t34, t35, t36, t37, t4, t40, t41, t42;
    int t43, t44, t45, t46, t47, t48, t49, t5, t50, t51;
    int t52, t53, t54, t55, t56, t59, t6, t60, t61, t62;
    int t63, t64, t67, t7, t8, t9, u, v, w, x;
    int y, z;

    a = 100;
    b = 10;
    c = 50;
    d = 5;
    i = 0;
    L0:
    if (!(i < 100)) {
        goto L1;
    }
    t0 = a + b;
    x = t0;
    t1 = c - d;
    y = t1;
    t2 = x + y;
    z = t2;
    t3 = a + b;
    w = t3;
    t4 = c - d;
    v = t4;
    t5 = w - v;
    u = t5;
    t6 = a + b;
    t = t6;
    t7 = c - d;
    s = t7;
    t8 = t * s;
    r = t8;
    t9 = a + b;
    q = t9;
    t10 = c - d;
    p = t10;
    t11 = q / p;
    o = t11;
    t12 = a + b;
    n = t12;
    t13 = c - d;
    m = t13;
    // t14 = n % m
    l = t14;
    t15 = i * 4;
    k = t15;
    t16 = z + u;
    t17 = t16 + r;
    t18 = t17 + o;
    t19 = t18 + l;
    t20 = t19 + k;
    t21 = i * 4;
    t22 = arr;  // Array name decays to pointer to first element
    t23 = t22 + t21;
    *t23 = t20;
    t24 = i * 4;
    t25 = arr;  // Array name decays to pointer to first element
    t26 = t25 + t24;
    // t27 = *t26
    if (t27 > 100) {
        goto L2;
    } else {
        goto L3;
    }
    L2:
    t28 = a + b;
    j = t28;
    t29 = c - d;
    h = t29;
    t30 = j - h;
    g = t30;
    t31 = i * 4;
    t32 = arr;  // Array name decays to pointer to first element
    t33 = t32 + t31;
    *t33 = g;
    goto L4;
    L3:
    t34 = a + b;
    f = t34;
    t35 = c - d;
    e = t35;
    t36 = f + e;
    t37 = i * 4;
    t38 = arr;  // Array name decays to pointer to first element
    t39 = t38 + t37;
    *t39 = t36;
    L4:
    t40 = a + b;
    x = t40;
    t41 = c - d;
    y = t41;
    t42 = x + y;
    z = t42;
    t43 = a + b;
    w = t43;
    t44 = c - d;
    v = t44;
    t45 = w - v;
    u = t45;
    t46 = a + b;
    t = t46;
    t47 = c - d;
    s = t47;
    t48 = t * s;
    r = t48;
    t49 = a + b;
    q = t49;
    t50 = c - d;
    p = t50;
    t51 = q / p;
    o = t51;
    t52 = a + b;
    n = t52;
    t53 = c - d;
    m = t53;
    // t54 = n % m
    l = t54;
    t56 = i * 4;
    t57 = arr;  // Array name decays to pointer to first element
    t58 = t57 + t56;
    // t59 = *t58
    t55 = t59 + z;
    t60 = t55 + u;
    t61 = t60 + r;
    t62 = t61 + o;
    t63 = t62 + l;
    t64 = i * 4;
    t65 = arr;  // Array name decays to pointer to first element
    t66 = t65 + t64;
    *t66 = t63;
    t67 = i + 1;
    i = t67;
    goto L0;
    L1:
    return 0;
}