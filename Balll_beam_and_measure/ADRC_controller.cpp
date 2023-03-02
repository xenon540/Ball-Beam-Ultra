// #include "ADRC_controller.h"

// void ESO(){
//     fe = fal(e, 0.5, h);
//     fe1 = fal(e, 0.25, h);
//     z1 = z1 + h*z2 - b0(1)*e;
//     z2 = z2 + h*(z3 + b0*u) - b0(2)*fe;
//     z3 = z2 - b0(3)*fe1;
// }

// void TD() {
//     fv = fhan(v1 - v, v2, r0, h);
//     v1 = v1 + h*v2;
//     v2 = v2 + h*fv;
// }

// void NLWS() {

// }

// void fhan(v1, v2, r0, h0) {
//     d = h0*(r0^2);
//     a0 = h0*v2;
//     y = v1 + a0;
//     a1 = sqrt(d*(d+8*abs(y));
//     a2 = a0 + sign(y)*(a1-d)/2;
//     sy = (sign(y+d) - sign(y-d))/2;
//     a = (a0 + y - a2)*sy + a2;
//     sa = (sign(a+d) - sign(a-d))/2;
//     y = -r0*(a/d-sign(a))*sa - r0*sign(a);
// }

// void fal(e, alpha, delta) {
//     if abs(x) <= delta :
//         y = e/(delta^(1-alpha));
//     else
//         y = abs(e)^alpha*sign(e);
// }