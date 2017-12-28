#include "BoundBox.h"


BoundBox::~BoundBox()
{
}

BoundBox::BoundBox(const vec3 & min, const vec3 & max)
{
	this->minim = min;
	this->maxim = max;
	this->extent = max - min;
}

BoundBox::BoundBox(const vec3 & p)
{
	this->minim = p;
	this->maxim = p;
	this->extent = maxim - minim;
}

#define loadps(mem)		_mm_load_ps((const float * const)(mem))
#define storess(ss,mem)		_mm_store_ss((float * const)(mem),(ss))
#define minss			_mm_min_ss
#define maxss			_mm_max_ss
#define minps			_mm_min_ps
#define maxps			_mm_max_ps
#define mulps			_mm_mul_ps
#define subps			_mm_sub_ps
#define rotatelps(ps)		_mm_shuffle_ps((ps),(ps), 0x39)	
#define muxhps(low,high)	_mm_movehl_ps((low),(high))	
static const float flt_plus_inf = -logf(0);	
const __m128 ps_cst_plus_inf[4] = { flt_plus_inf,  flt_plus_inf,  flt_plus_inf,  flt_plus_inf },
ps_cst_minus_inf[4] = { -flt_plus_inf, -flt_plus_inf, -flt_plus_inf, -flt_plus_inf };

bool BoundBox::intersect(const Ray & r, float * tnear, float * tfar) const
{
	const __m128
		plus_inf = loadps(ps_cst_plus_inf),
		minus_inf = loadps(ps_cst_minus_inf);

	__m128 m128;
	const __m128
		box_min = loadps(&minim),
		box_max = loadps(&maxim),
		pos = loadps(&r.orig),
		// I changed the brackets to &r.dir which stopped the error, but not sure if it actually makes it work
		inv_dir = loadps(&r.dir);

	const __m128 l1 = mulps(subps(box_min, pos), inv_dir);
	const __m128 l2 = mulps(subps(box_max, pos), inv_dir);

	const __m128 filtered_l1a = minps(l1, plus_inf);
	const __m128 filtered_l2a = minps(l2, plus_inf);

	const __m128 filtered_l1b = maxps(l1, minus_inf);
	const __m128 filtered_l2b = maxps(l2, minus_inf);

	__m128 lmax = maxps(filtered_l1a, filtered_l2a);
	__m128 lmin = minps(filtered_l1b, filtered_l2b);

	const __m128 lmax0 = rotatelps(lmax);
	const __m128 lmin0 = rotatelps(lmin);
	lmax = minss(lmax, lmax0);
	lmin = maxss(lmin, lmin0);

	const __m128 lmax1 = muxhps(lmax, lmax);
	const __m128 lmin1 = muxhps(lmin, lmin);
	lmax = minss(lmax, lmax1);
	lmin = maxss(lmin, lmin1);

	const bool ret = _mm_comige_ss(lmax, _mm_setzero_ps()) & _mm_comige_ss(lmax, lmin);

	storess(lmin, tnear);
	storess(lmax, tfar);

	return  ret;
}

void BoundBox::expand(const vec3 & p)
{
	if (this->minim.length < p.length)
		this->minim = minim;
	else
		this->minim = p;

	if (this->maxim.length > p.length)
		this->maxim = maxim;
	else
		this->maxim = p;

	this->extent = maxim - minim;
}

void BoundBox::expand(const BoundBox & b)
{
	if (this->minim.length < b.minim.length)
		this->minim = minim;
	else
		this->minim = b.minim;

	if (this->maxim.length > b.maxim.length)
		this->maxim = maxim;
	else
		this->maxim = b.maxim;

	this->extent = maxim - minim;
}

uint BoundBox::maxDim() const
{
	uint result = 0;

	if (extent.y > extent.x)
		result = 1;
	if (extent.z > extent.y)
		result = 2;

	return result;
}

float BoundBox::surface() const
{	
	return 2.0f * (extent.x * extent.z + extent.x*extent.y + extent.y * extent.z);
}
