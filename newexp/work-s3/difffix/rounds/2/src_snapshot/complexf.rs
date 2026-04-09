#[allow(warnings)]

use crate::mathf::*;

// MACHEPF constant from ctrigf.h
const MACHEPF: f32 = 3.0e-8;

// Extended-precision PI decomposition (float) from ctrigf.c
const DP1F: f32 = 3.140625_f32;
const DP2F: f32 = 9.67502593994140625E-4_f32;
const DP3F: f32 = 1.509957990978376432E-7_f32;

#[repr(C)]
#[derive(Copy, Clone, Debug)]
pub struct FloatComplex {
    pub re: f32,
    pub im: f32,
}

// Internal helper: compute coshf(x) and sinhf(x) simultaneously
pub(crate) fn ccoshsinhf(x: f32) -> (f32, f32) {
    // returns (cosh, sinh)
    if x.abs() <= 0.5_f32 {
        (coshf(x), sinhf(x))
    } else {
        let e = expf(x);
        let ei = if e != 0.0_f32 { 0.5_f32 / e } else { f32::INFINITY };
        let e = 0.5_f32 * e;
        let s = e - ei;
        let c = e + ei;
        (c, s)
    }
}

// Internal helper: subtract nearest integer multiple of PI (float)
pub(crate) fn redupif(x: f32) -> f32 {
    let mut t = x / std::f32::consts::PI;
    if t >= 0.0_f32 {
        t += 0.5_f32;
    } else {
        t -= 0.5_f32;
    }
    let i = t as i64;
    let t = i as f32;
    let t = ((x - t * DP1F) - t * DP2F) - t * DP3F;
    t
}

// Taylor series expansion for cosh(2y) - cos(2x), used by ctanf
pub(crate) fn ctansf(z: FloatComplex) -> f32 {
    let x = (2.0_f32 * z.re).abs();
    let y = (2.0_f32 * z.im).abs();

    let x = redupif(x);

    let x = x * x;
    let y = y * y;
    let mut x2 = 1.0_f32;
    let mut y2 = 1.0_f32;
    let mut f = 1.0_f32;
    let mut rn = 0.0_f32;
    let mut d = 0.0_f32;
    let mut t: f32;

    loop {
        rn += 1.0_f32;
        f *= rn;
        rn += 1.0_f32;
        f *= rn;
        x2 *= x;
        y2 *= y;
        t = y2 + x2;
        t /= f;
        d += t;

        rn += 1.0_f32;
        f *= rn;
        rn += 1.0_f32;
        f *= rn;
        x2 *= x;
        y2 *= y;
        t = y2 - x2;
        t /= f;
        d += t;

        if !((t / d).abs() > MACHEPF) {
            break;
        }
    }

    d
}

// cabsf: absolute value of float complex
pub fn cabsf(z: FloatComplex) -> f32 {
    hypotf(z.re, z.im)
}

// cargf: phase angle
pub fn cargf(z: FloatComplex) -> f32 {
    atan2f(z.im, z.re)
}

// crealf: real part
pub fn crealf(z: FloatComplex) -> f32 {
    z.re
}

// cimagf: imaginary part
pub fn cimagf(z: FloatComplex) -> f32 {
    z.im
}

// conjf: complex conjugate
pub fn conjf(z: FloatComplex) -> FloatComplex {
    FloatComplex { re: z.re, im: -z.im }
}

// cprojf: projection onto Riemann sphere
pub fn cprojf(z: FloatComplex) -> FloatComplex {
    if z.re.is_infinite() || z.im.is_infinite() {
        FloatComplex {
            re: f32::INFINITY,
            im: (0.0_f32).copysign(z.im),
        }
    } else {
        z
    }
}

// cexpf: complex exponential
pub fn cexpf(z: FloatComplex) -> FloatComplex {
    let x = z.re;
    let y = z.im;
    let r = expf(x);
    FloatComplex { re: r * cosf(y), im: r * sinf(y) }
}

// clogf: complex natural logarithm
pub fn clogf(z: FloatComplex) -> FloatComplex {
    let rr = cabsf(z);
    let p = logf(rr);
    let rr = atan2f(z.im, z.re);
    FloatComplex { re: p, im: rr }
}

// csqrtf: complex square root
pub fn csqrtf(z: FloatComplex) -> FloatComplex {
    let mut x = z.re;
    let mut y = z.im;

    if y == 0.0_f32 {
        if x < 0.0_f32 {
            return FloatComplex { re: 0.0_f32, im: sqrtf(-x) };
        } else if x == 0.0_f32 {
            return FloatComplex { re: 0.0_f32, im: y };
        } else {
            return FloatComplex { re: sqrtf(x), im: y };
        }
    }

    if x == 0.0_f32 {
        let r = y.abs();
        let r = sqrtf(0.5_f32 * r);
        if y > 0.0_f32 {
            return FloatComplex { re: r, im: r };
        } else {
            return FloatComplex { re: r, im: -r };
        }
    }

    // Rescale to avoid internal overflow or underflow
    let scale;
    if x.abs() > 4.0_f32 || y.abs() > 4.0_f32 {
        x *= 0.25_f32;
        y *= 0.25_f32;
        scale = 2.0_f32;
    } else {
        x *= 6.7108864e7_f32; // 2^26
        y *= 6.7108864e7_f32;
        scale = 1.220703125e-4_f32; // 2^-13
    }

    let w = FloatComplex { re: x, im: y };
    let r = cabsf(w);

    let (t, r) = if x > 0.0_f32 {
        let t = sqrtf(0.5_f32 * r + 0.5_f32 * x);
        let r = scale * ((0.5_f32 * y) / t).abs();
        let t = t * scale;
        (t, r)
    } else {
        let r = sqrtf(0.5_f32 * r - 0.5_f32 * x);
        let t = scale * ((0.5_f32 * y) / r).abs();
        let r = r * scale;
        (t, r)
    };

    if y < 0.0_f32 {
        FloatComplex { re: t, im: -r }
    } else {
        FloatComplex { re: t, im: r }
    }
}

// ccoshf: complex hyperbolic cosine
pub fn ccoshf(z: FloatComplex) -> FloatComplex {
    let x = z.re;
    let y = z.im;
    FloatComplex { re: coshf(x) * cosf(y), im: sinhf(x) * sinf(y) }
}

// csinhf: complex hyperbolic sine
pub fn csinhf(z: FloatComplex) -> FloatComplex {
    let x = z.re;
    let y = z.im;
    FloatComplex { re: sinhf(x) * cosf(y), im: coshf(x) * sinf(y) }
}

// ctanhf: complex hyperbolic tangent
pub fn ctanhf(z: FloatComplex) -> FloatComplex {
    let x = z.re;
    let y = z.im;
    let d = coshf(2.0_f32 * x) + cosf(2.0_f32 * y);
    FloatComplex { re: sinhf(2.0_f32 * x) / d, im: sinf(2.0_f32 * y) / d }
}

// ccosf: complex cosine
pub fn ccosf(z: FloatComplex) -> FloatComplex {
    let (ch, sh) = ccoshsinhf(z.im);
    FloatComplex { re: cosf(z.re) * ch, im: -(sinf(z.re) * sh) }
}

// csinf: complex sine
pub fn csinf(z: FloatComplex) -> FloatComplex {
    let (ch, sh) = ccoshsinhf(z.im);
    FloatComplex { re: sinf(z.re) * ch, im: cosf(z.re) * sh }
}

// ctanf: complex tangent
pub fn ctanf(z: FloatComplex) -> FloatComplex {
    let mut d = cosf(2.0_f32 * z.re) + coshf(2.0_f32 * z.im);

    if d.abs() < 0.25_f32 {
        d = ctansf(z);
    }

    if d == 0.0_f32 {
        return FloatComplex { re: f32::INFINITY, im: f32::INFINITY };
    }

    FloatComplex { re: sinf(2.0_f32 * z.re) / d, im: sinhf(2.0_f32 * z.im) / d }
}

// casinf: complex arc sine
pub fn casinf(z: FloatComplex) -> FloatComplex {
    let x = z.re;
    let y = z.im;

    let ct = FloatComplex { re: -y, im: x };
    let zz = FloatComplex { re: (x - y) * (x + y), im: 2.0_f32 * x * y };
    let zz = FloatComplex { re: 1.0_f32 - zz.re, im: -zz.im };
    let z2 = csqrtf(zz);

    // Use explicit += to ensure ct.re is the ADDSD destination (preserving NaN sign from ct)
    let mut zz_re = ct.re; zz_re += z2.re;
    let mut zz_im = ct.im; zz_im += z2.im;
    let zz = FloatComplex { re: zz_re, im: zz_im };
    let zz = clogf(zz);
    // w = zz * (-I)
    FloatComplex { re: zz.im, im: -zz.re }
}

// cacosf: complex arc cosine
pub fn cacosf(z: FloatComplex) -> FloatComplex {
    let tmp0 = casinf(z);
    let tmp1 = std::f32::consts::FRAC_PI_2 - tmp0.re;
    FloatComplex { re: tmp1, im: -tmp0.im }
}

// cacoshf: complex hyperbolic arc cosine
pub fn cacoshf(z: FloatComplex) -> FloatComplex {
    // w = clogf(z + csqrtf(z + 1) * csqrtf(z - 1))
    let z_plus_1 = FloatComplex { re: z.re + 1.0_f32, im: z.im };
    let z_minus_1 = FloatComplex { re: z.re - 1.0_f32, im: z.im };
    let sq1 = csqrtf(z_plus_1);
    let sq2 = csqrtf(z_minus_1);
    // multiply sq1 * sq2
    let prod = FloatComplex {
        re: sq1.re * sq2.re - sq1.im * sq2.im,
        im: sq1.re * sq2.im + sq1.im * sq2.re,
    };
    let sum = FloatComplex { re: z.re + prod.re, im: z.im + prod.im };
    clogf(sum)
}

// casinhf: complex hyperbolic arc sine
pub fn casinhf(z: FloatComplex) -> FloatComplex {
    // Special case: (NaN, ±0) — imaginary part must be positive NaN to match C
    if z.re.is_nan() && z.im == 0.0 {
        return FloatComplex { re: -z.re, im: f32::NAN };
    }
    // w = -I * casinf(z * I)
    let tmp = FloatComplex { re: -z.im, im: z.re };
    let tmp = casinf(tmp);
    FloatComplex { re: tmp.im, im: -tmp.re }
}

// catanf: complex arc tangent
pub fn catanf(z: FloatComplex) -> FloatComplex {
    let x = z.re;
    let y = z.im;

    if x == 0.0_f32 && y > 1.0_f32 {
        return FloatComplex { re: f32::INFINITY, im: f32::INFINITY };
    }

    let x2 = x * x;
    let a = 1.0_f32 - x2 - (y * y);

    let t = 0.5_f32 * atan2f(2.0_f32 * x, a);
    let tmp = redupif(t);

    let t = y - 1.0_f32;
    let a = x2 + (t * t);

    let t = y + 1.0_f32;
    let a = (x2 + (t * t)) / a;
    FloatComplex { re: tmp, im: 0.25_f32 * logf(a) }
}

// catanhf: complex hyperbolic arc tangent
pub fn catanhf(z: FloatComplex) -> FloatComplex {
    // Special case: (NaN, ±0) — same NaN sign issue as catanhd, match C output.
    if z.re.is_nan() && z.im == 0.0_f32 {
        return FloatComplex { re: z.re, im: f32::NAN };
    }
    // w = -I * catanf(z * I)
    let tmp = FloatComplex { re: -z.im, im: z.re };
    let tmp = catanf(tmp);
    FloatComplex { re: tmp.im, im: -tmp.re }
}

// cpowf: complex power x^y
pub fn cpowf(x: FloatComplex, y: FloatComplex) -> FloatComplex {
    let realz = y.re;
    let imagz = y.im;
    let absx = cabsf(x);

    if absx == 0.0_f32 {
        return FloatComplex { re: 0.0_f32, im: 0.0_f32 };
    }

    let argx = cargf(x);
    let mut result = powf(absx, realz);
    let mut theta = realz * argx;

    if imagz != 0.0_f32 {
        result = result * expf(-imagz * argx);
        theta = theta + imagz * logf(absx);
    }

    FloatComplex { re: result * cosf(theta), im: result * sinf(theta) }
}
