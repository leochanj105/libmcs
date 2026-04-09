#[allow(warnings)]

use crate::mathd::{
    expd, logd, sqrtd, cosd, sind, coshd, sinhd, atan2d, hypotd, powd,
};

// MACHEP constant from ctrigd.h
const MACHEP: f64 = 1.1e-16;

// Extended-precision PI decomposition from ctrigd.c
const DP1: f64 = 3.14159265160560607910E0;
const DP2: f64 = 1.98418714791870343106E-9;
const DP3: f64 = 1.14423774522196636802E-17;

#[repr(C)]
#[derive(Copy, Clone, Debug)]
pub struct DoubleComplex {
    pub re: f64,
    pub im: f64,
}

// Internal helper: compute cosh(x) and sinh(x) simultaneously
pub(crate) fn ccoshsinh(x: f64) -> (f64, f64) {
    // returns (cosh, sinh)
    if x.abs() <= 0.5 {
        (coshd(x), sinhd(x))
    } else {
        let e = expd(x);
        let ei = if e != 0.0 { 0.5 / e } else { f64::INFINITY };
        let e = 0.5 * e;
        let s = e - ei;
        let c = e + ei;
        (c, s)
    }
}

// Internal helper: subtract nearest integer multiple of PI
pub(crate) fn redupi(x: f64) -> f64 {
    let mut t = x / std::f64::consts::PI;
    if t >= 0.0 {
        t += 0.5;
    } else {
        t -= 0.5;
    }
    let i = t as i64;
    let t = i as f64;
    let t = ((x - t * DP1) - t * DP2) - t * DP3;
    t
}

// Taylor series expansion for cosh(2y) - cos(2x), used by ctand
pub(crate) fn ctans(z: DoubleComplex) -> f64 {
    let x = (2.0 * z.re).abs();
    let y = (2.0 * z.im).abs();

    let x = redupi(x);

    let x = x * x;
    let y = y * y;
    let mut x2 = 1.0_f64;
    let mut y2 = 1.0_f64;
    let mut f = 1.0_f64;
    let mut rn = 0.0_f64;
    let mut d = 0.0_f64;
    let mut t: f64;

    loop {
        rn += 1.0;
        f *= rn;
        rn += 1.0;
        f *= rn;
        x2 *= x;
        y2 *= y;
        t = y2 + x2;
        t /= f;
        d += t;

        rn += 1.0;
        f *= rn;
        rn += 1.0;
        f *= rn;
        x2 *= x;
        y2 *= y;
        t = y2 - x2;
        t /= f;
        d += t;

        if (t / d).abs() <= MACHEP {
            break;
        }
    }

    d
}

// cabs: absolute value of complex
pub fn cabsd(z: DoubleComplex) -> f64 {
    hypotd(z.re, z.im)
}

// carg: phase angle
pub fn cargd(z: DoubleComplex) -> f64 {
    atan2d(z.im, z.re)
}

// creal: real part
pub fn creald(z: DoubleComplex) -> f64 {
    z.re
}

// cimag: imaginary part
pub fn cimagd(z: DoubleComplex) -> f64 {
    z.im
}

// conj: complex conjugate
pub fn conjd(z: DoubleComplex) -> DoubleComplex {
    DoubleComplex { re: z.re, im: -z.im }
}

// cproj: projection onto Riemann sphere
pub fn cprojd(z: DoubleComplex) -> DoubleComplex {
    if z.re.is_infinite() || z.im.is_infinite() {
        DoubleComplex {
            re: f64::INFINITY,
            im: (0.0_f64).copysign(z.im),
        }
    } else {
        z
    }
}

// cexp: complex exponential
pub fn cexpd(z: DoubleComplex) -> DoubleComplex {
    let x = z.re;
    let y = z.im;
    let r = expd(x);
    DoubleComplex { re: r * cosd(y), im: r * sind(y) }
}

// clog: complex natural logarithm
pub fn clogd(z: DoubleComplex) -> DoubleComplex {
    let rr = cabsd(z);
    let p = logd(rr);
    let rr = atan2d(z.im, z.re);
    DoubleComplex { re: p, im: rr }
}

// csqrt: complex square root
pub fn csqrtd(z: DoubleComplex) -> DoubleComplex {
    let mut x = z.re;
    let mut y = z.im;

    if y == 0.0 {
        if x == 0.0 {
            return DoubleComplex { re: 0.0, im: y };
        } else {
            let r = x.abs();
            let r = sqrtd(r);
            if x < 0.0 {
                return DoubleComplex { re: 0.0, im: r };
            } else {
                return DoubleComplex { re: r, im: y };
            }
        }
    }

    if x == 0.0 {
        let r = y.abs();
        let r = sqrtd(0.5 * r);
        if y > 0.0 {
            return DoubleComplex { re: r, im: r };
        } else {
            return DoubleComplex { re: r, im: -r };
        }
    }

    // Rescale to avoid internal overflow or underflow
    let scale;
    if x.abs() > 4.0 || y.abs() > 4.0 {
        x *= 0.25;
        y *= 0.25;
        scale = 2.0;
    } else {
        x *= 1.8014398509481984e16; // 2^54
        y *= 1.8014398509481984e16;
        scale = 7.450580596923828125e-9; // 2^-27
    }

    let w = DoubleComplex { re: x, im: y };
    let r = cabsd(w);

    let (t, r) = if x > 0.0 {
        let t = sqrtd(0.5 * r + 0.5 * x);
        let r = scale * ((0.5 * y) / t).abs();
        let t = t * scale;
        (t, r)
    } else {
        let r = sqrtd(0.5 * r - 0.5 * x);
        let t = scale * ((0.5 * y) / r).abs();
        let r = r * scale;
        (t, r)
    };

    if y < 0.0 {
        DoubleComplex { re: t, im: -r }
    } else {
        DoubleComplex { re: t, im: r }
    }
}

// ccosh: complex hyperbolic cosine
pub fn ccoshd(z: DoubleComplex) -> DoubleComplex {
    let x = z.re;
    let y = z.im;
    DoubleComplex { re: coshd(x) * cosd(y), im: sinhd(x) * sind(y) }
}

// csinh: complex hyperbolic sine
pub fn csinhd(z: DoubleComplex) -> DoubleComplex {
    let x = z.re;
    let y = z.im;
    DoubleComplex { re: sinhd(x) * cosd(y), im: coshd(x) * sind(y) }
}

// ctanh: complex hyperbolic tangent
pub fn ctanhd(z: DoubleComplex) -> DoubleComplex {
    let x = z.re;
    let y = z.im;
    let d = coshd(2.0 * x) + cosd(2.0 * y);
    DoubleComplex { re: sinhd(2.0 * x) / d, im: sind(2.0 * y) / d }
}

// ccos: complex cosine
pub fn ccosd(z: DoubleComplex) -> DoubleComplex {
    let (ch, sh) = ccoshsinh(z.im);
    DoubleComplex { re: cosd(z.re) * ch, im: -(sind(z.re) * sh) }
}

// csin: complex sine
pub fn csind(z: DoubleComplex) -> DoubleComplex {
    let (ch, sh) = ccoshsinh(z.im);
    DoubleComplex { re: sind(z.re) * ch, im: cosd(z.re) * sh }
}

// ctan: complex tangent
pub fn ctand(z: DoubleComplex) -> DoubleComplex {
    let mut d = cosd(2.0 * z.re) + coshd(2.0 * z.im);

    if d.abs() < 0.25 {
        d = ctans(z);
    }

    if d == 0.0 {
        return DoubleComplex { re: f64::INFINITY, im: f64::INFINITY };
    }

    DoubleComplex { re: sind(2.0 * z.re) / d, im: sinhd(2.0 * z.im) / d }
}

// casin: complex arc sine
pub fn casind(z: DoubleComplex) -> DoubleComplex {
    let x = z.re;
    let y = z.im;

    let ct = DoubleComplex { re: -y, im: x };
    let zz = DoubleComplex { re: (x - y) * (x + y), im: 2.0 * x * y };
    let zz = DoubleComplex { re: 1.0 - zz.re, im: -zz.im };
    let z2 = csqrtd(zz);

    let zz = DoubleComplex { re: ct.re + z2.re, im: ct.im + z2.im };
    let zz = clogd(zz);
    // w = zz * (-I)
    DoubleComplex { re: zz.im, im: -zz.re }
}

// cacos: complex arc cosine
pub fn cacosd(z: DoubleComplex) -> DoubleComplex {
    let tmp0 = casind(z);
    let tmp1 = std::f64::consts::FRAC_PI_2 - tmp0.re;
    DoubleComplex { re: tmp1, im: -tmp0.im }
}

// cacosh: complex hyperbolic arc cosine
pub fn cacoshd(z: DoubleComplex) -> DoubleComplex {
    // w = clog(z + csqrt(z + 1) * csqrt(z - 1))
    let z_plus_1 = DoubleComplex { re: z.re + 1.0, im: z.im };
    let z_minus_1 = DoubleComplex { re: z.re - 1.0, im: z.im };
    let sq1 = csqrtd(z_plus_1);
    let sq2 = csqrtd(z_minus_1);
    // multiply sq1 * sq2
    let prod = DoubleComplex {
        re: sq1.re * sq2.re - sq1.im * sq2.im,
        im: sq1.re * sq2.im + sq1.im * sq2.re,
    };
    let sum = DoubleComplex { re: z.re + prod.re, im: z.im + prod.im };
    clogd(sum)
}

// casinh: complex hyperbolic arc sine
pub fn casinhd(z: DoubleComplex) -> DoubleComplex {
    // w = -I * casin(z * I)
    let tmp = DoubleComplex { re: -z.im, im: z.re };
    let tmp = casind(tmp);
    DoubleComplex { re: tmp.im, im: -tmp.re }
}

// catan: complex arc tangent
pub fn catand(z: DoubleComplex) -> DoubleComplex {
    let x = z.re;
    let y = z.im;

    if x == 0.0 && y > 1.0 {
        return DoubleComplex { re: f64::INFINITY, im: f64::INFINITY };
    }

    let x2 = x * x;
    let a = 1.0 - x2 - (y * y);

    let t = 0.5 * atan2d(2.0 * x, a);
    let tmp = redupi(t);

    let t = y - 1.0;
    let a = x2 + (t * t);

    let t = y + 1.0;
    let a = (x2 + (t * t)) / a;
    DoubleComplex { re: tmp, im: 0.25 * logd(a) }
}

// catanh: complex hyperbolic arc tangent
pub fn catanhd(z: DoubleComplex) -> DoubleComplex {
    // w = -I * catan(z * I)
    let tmp = DoubleComplex { re: -z.im, im: z.re };
    let tmp = catand(tmp);
    DoubleComplex { re: tmp.im, im: -tmp.re }
}

// cpow: complex power x^y
pub fn cpowd(x: DoubleComplex, y: DoubleComplex) -> DoubleComplex {
    let realz = y.re;
    let imagz = y.im;
    let absx = cabsd(x);

    if absx == 0.0 {
        return DoubleComplex { re: 0.0, im: 0.0 };
    }

    let argx = cargd(x);
    let mut result = powd(absx, realz);
    let mut theta = realz * argx;

    if imagz != 0.0 {
        result = result * expd(-imagz * argx);
        theta = theta + imagz * logd(absx);
    }

    DoubleComplex { re: result * cosd(theta), im: result * sind(theta) }
}
