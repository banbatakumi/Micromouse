#ifndef __MYMATH__
#define __MYMATH__

#ifdef __cplusplus

#include <cstdio>

extern "C" {

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352
#define SQRT3 1.73205080757f
#define SQRT2 1.41421356237f
#define PI_3 1.0471975512f
#define CW true
#define CCW false

#define abs(x) ((x) > 0 ? (x) : -(x))
#define Range(a, x, b) ((a) <= (x) && (x) <= (b))
#define Constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define Round(x) ((x) >= 0 ? (long)((x) + 0.5) : (long)((x) - 0.5))
#define Radians(deg) ((deg) * DEG_TO_RAD)
#define Degrees(rad) ((rad) * RAD_TO_DEG)

#define SIN0 0
#define SIN1 0.0174524064372835
#define SIN2 0.034899496702501
#define SIN3 0.0523359562429438
#define SIN4 0.0697564737441253
#define SIN5 0.0871557427476582
#define SIN6 0.104528463267653
#define SIN7 0.121869343405147
#define SIN8 0.139173100960065
#define SIN9 0.156434465040231
#define SIN10 0.17364817766693
#define SIN11 0.190808995376545
#define SIN12 0.207911690817759
#define SIN13 0.224951054343865
#define SIN14 0.241921895599668
#define SIN15 0.258819045102521
#define SIN16 0.275637355816999
#define SIN17 0.292371704722737
#define SIN18 0.309016994374947
#define SIN19 0.325568154457157
#define SIN20 0.342020143325669
#define SIN21 0.3583679495453
#define SIN22 0.374606593415912
#define SIN23 0.390731128489274
#define SIN24 0.4067366430758
#define SIN25 0.422618261740699
#define SIN26 0.438371146789077
#define SIN27 0.453990499739547
#define SIN28 0.469471562785891
#define SIN29 0.484809620246337
#define SIN30 0.5
#define SIN31 0.515038074910054
#define SIN32 0.529919264233205
#define SIN33 0.544639035015027
#define SIN34 0.559192903470747
#define SIN35 0.573576436351046
#define SIN36 0.587785252292473
#define SIN37 0.601815023152048
#define SIN38 0.615661475325658
#define SIN39 0.629320391049838
#define SIN40 0.642787609686539
#define SIN41 0.656059028990507
#define SIN42 0.669130606358858
#define SIN43 0.681998360062498
#define SIN44 0.694658370458997
#define SIN45 0.707106781186547
#define SIN46 0.719339800338651
#define SIN47 0.73135370161917
#define SIN48 0.743144825477394
#define SIN49 0.754709580222772
#define SIN50 0.766044443118978
#define SIN51 0.777145961456971
#define SIN52 0.788010753606722
#define SIN53 0.798635510047293
#define SIN54 0.809016994374947
#define SIN55 0.819152044288992
#define SIN56 0.829037572555042
#define SIN57 0.838670567945424
#define SIN58 0.848048096156426
#define SIN59 0.857167300702112
#define SIN60 0.866025403784439
#define SIN61 0.874619707139396
#define SIN62 0.882947592858927
#define SIN63 0.891006524188368
#define SIN64 0.898794046299167
#define SIN65 0.90630778703665
#define SIN66 0.913545457642601
#define SIN67 0.92050485345244
#define SIN68 0.927183854566787
#define SIN69 0.933580426497202
#define SIN70 0.939692620785908
#define SIN71 0.945518575599317
#define SIN72 0.951056516295154
#define SIN73 0.956304755963035
#define SIN74 0.961261695938319
#define SIN75 0.965925826289068
#define SIN76 0.970295726275996
#define SIN77 0.974370064785235
#define SIN78 0.978147600733806
#define SIN79 0.981627183447664
#define SIN80 0.984807753012208
#define SIN81 0.987688340595138
#define SIN82 0.99026806874157
#define SIN83 0.992546151641322
#define SIN84 0.994521895368273
#define SIN85 0.996194698091746
#define SIN86 0.997564050259824
#define SIN87 0.998629534754574
#define SIN88 0.999390827019096
#define SIN89 0.999847695156391
#define SIN90 1

namespace MyMath {
float sinDeg(int deg);
float cosDeg(int deg);
float tanDeg(int deg);
float sin(float rad);
float cos(float rad);
float tan(float rad);
int atan2(int _y, int _x);

int normalizeDegrees(int theta);
float normalizeRadians(float theta);
int gapDegrees180(int deg1, int deg2);
int gapDegrees(int deg1, int deg2);
float gapRadians180(float rad1, float rad2);
float gapRadians(float rad1, float rad2);
float sqrt(float x);
void printBit(char c);
} // namespace MyMath
}
#endif
#endif