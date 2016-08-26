#define FIXED_SHIFT	        7
#define FIXED_SCALE		(1 << FIXED_SHIFT)
#define i2fp(a)			((a) << FIXED_SHIFT)
#define fp2i(a)			((a) >> FIXED_SHIFT)
#define fp_add(a, b)	((a) + (b))
#define fp_sub(a, b)	((a) - (b))
#define FP_FRACMASK 0x00007FFF ; // ! Only valid with FIXED_SHIFT=15
#define fp_mul(x,y)		((long)(((long)(x) * (long)(y)) >> FIXED_SHIFT))
#define fp_div(x,y)		((((x)<<2)/((y)>>8))<<10)
#define fp_mulint(x,y)	fp_mul(x,y)
#define FP_ONE		(1 << FIXED_SHIFT)
#define FPONE		FP_ONE

inline int fl2fp(float val) {
	return (long)(val * FIXED_SCALE);
}
inline float fp2fl(long val) {
	return ((float)val) / FIXED_SCALE;
}
