#[allow(clippy::all, warnings)]

use std::cell::Cell;

// ---------------------------------------------------------------------------
// Thread-local for lgammaf sign (mirrors C global __signgam)
// ---------------------------------------------------------------------------
thread_local! {
    pub static SIGNGAM: Cell<i32> = Cell::new(1);
}

// ---------------------------------------------------------------------------
// Primitive helpers (mirror the C macros from tools.h)
// ---------------------------------------------------------------------------
#[inline(always)]
fn get_float_word(f: f32) -> u32 {
    f.to_bits()
}

#[inline(always)]
fn set_float_word(i: u32) -> f32 {
    f32::from_bits(i)
}

// FLT_UWORD macros from internal_config.h (non-DAZ build, with subnormals)
#[inline(always)]
fn flt_uword_is_zero(x: u32) -> bool { x == 0 }
#[inline(always)]
fn flt_uword_is_subnormal(x: u32) -> bool { x < 0x00800000 }
#[inline(always)]
fn flt_uword_is_finite(x: u32) -> bool { x < 0x7f800000 }
#[inline(always)]
fn flt_uword_is_infinite(x: u32) -> bool { x == 0x7f800000 }
#[inline(always)]
fn flt_uword_is_nan(x: u32) -> bool { x > 0x7f800000 }

// Constants from internal_config.h
const FLT_UWORD_MAX: u32 = 0x7f7fffff;
const FLT_UWORD_EXP_MAX: u32 = 0x43000000;
const FLT_UWORD_EXP_MIN: u32 = 0x43160000;
const FLT_UWORD_LOG_MAX: u32 = 0x42b17217;
const FLT_UWORD_LOG_2MAX: u32 = 0x42b2d4fc;
const FLT_UWORD_HALF_MAX: u32 = FLT_UWORD_MAX - (1 << 23);
const FLT_LARGEST_EXP: u32 = FLT_UWORD_MAX >> 23; // = 0xfe
const FLT_SMALLEST_EXP: i32 = -22;

// FP_ILOGB constants (from math.h)
const FP_ILOGB0: i32 = -2147483647; // FP_ILOGB0 = -INT_MAX = 0x80000001
const FP_ILOGBNAN: i32 = i32::MAX;

// __issignalingf: checks if a float is a signaling NaN
#[inline(always)]
fn issignalingf(x: f32) -> i32 {
    let ix = get_float_word(x);
    if flt_uword_is_nan(ix & 0x7fffffff) && (ix & 0x00400000) == 0 {
        1
    } else {
        0
    }
}

// Exception-raising helpers (no actual signal; just return the IEEE result)
#[inline(always)]
fn raise_invalidf() -> f32 { f32::NAN }
#[inline(always)]
fn raise_div_by_zerof(x: f32) -> f32 {
    if x.is_sign_negative() { f32::NEG_INFINITY } else { f32::INFINITY }
}
#[inline(always)]
fn raise_overflowf(x: f32) -> f32 {
    if x.is_sign_negative() { f32::NEG_INFINITY } else { f32::INFINITY }
}
#[inline(always)]
fn raise_underflowf(x: f32) -> f32 {
    if x < 0.0f32 { -0.0f32 } else { 0.0f32 }
}
#[inline(always)]
fn raise_inexactf(x: f32) -> f32 { x }

// ---------------------------------------------------------------------------
// Internal trig helpers  (from mathf/internal/trigf.c)
// ---------------------------------------------------------------------------

static PIO2_ARR: [f32; 11] = [
    1.5703125000e+00f32, // 0x3fc90000
    4.5776367188e-04f32, // 0x39f00000
    2.5987625122e-05f32, // 0x37da0000
    7.5437128544e-08f32, // 0x33a20000
    6.0026650317e-11f32, // 0x2e840000
    7.3896444519e-13f32, // 0x2b500000
    5.3845816694e-15f32, // 0x27c20000
    5.6378512969e-18f32, // 0x22d00000
    8.3009228831e-20f32, // 0x1fc40000
    3.2756352257e-22f32, // 0x1bc60000
    6.3331015649e-25f32, // 0x17440000
];

static IPIO2: [i32; 66] = [
    0xA2, 0xF9, 0x83, 0x6E, 0x4E, 0x44, 0x15, 0x29, 0xFC,
    0x27, 0x57, 0xD1, 0xF5, 0x34, 0xDD, 0xC0, 0xDB, 0x62,
    0x95, 0x99, 0x3C, 0x43, 0x90, 0x41, 0xFE, 0x51, 0x63,
    0xAB, 0xDE, 0xBB, 0xC5, 0x61, 0xB7, 0x24, 0x6E, 0x3A,
    0x42, 0x4D, 0xD2, 0xE0, 0x06, 0x49, 0x2E, 0xEA, 0x09,
    0xD1, 0x92, 0x1C, 0xFE, 0x1D, 0xEB, 0x1C, 0xB1, 0x29,
    0xA7, 0x3E, 0xE8, 0x82, 0x35, 0xF5, 0x2E, 0xBB, 0x44,
    0x84, 0xE9, 0x9C,
];

pub(crate) fn rem_pio2f_internal(x: &[f32; 3], y: &mut [f32; 2], e0: i32, nx: i32) -> i32 {
    let jk: i32 = 7;
    let jp: i32 = jk;

    let mut q: [f32; 20] = [0.0f32; 20];
    let mut iq: [i32; 20] = [0i32; 20];
    let mut f: [f32; 20] = [0.0f32; 20];
    let mut fq: [f32; 20] = [0.0f32; 20];

    let jx = nx - 1;
    let jv = (e0 - 3) / 8;
    let mut q0 = e0 - 8 * (jv + 1);

    // set up f[0] to f[jx+jk]
    let j_start = jv - jx;
    let m = jx + jk;
    for i in 0..=m as usize {
        let j = j_start + i as i32;
        f[i] = if j < 0 { 0.0f32 } else { IPIO2[j as usize] as f32 };
    }

    // compute q[0]..q[jk]
    for i in 0..=jk as usize {
        let mut fw = 0.0f32;
        for j in 0..=jx as usize {
            fw += x[j] * f[jx as usize + i - j];
        }
        q[i] = fw;
    }

    let mut jz = jk;

    // Variables that persist out of the loop
    let mut z_out: f32 = 0.0f32;
    let mut n_out: i32 = 0;
    let mut ih_out: i32 = 0;

    loop {
        let mut recompute = false;
        let mut exhausted = false;

        // distill lower part of q[] into iq[], leave higher in z
        let mut z = q[jz as usize];
        let mut i_idx = 0usize;
        let mut j_idx = jz as usize;
        while j_idx > 0 {
            let fw = ((3.90625e-3f32 * z) as i32) as f32; // twon8 = 2^-8 = 3.90625e-3
            iq[i_idx] = (z - 256.0f32 * fw) as i32;
            z = q[j_idx - 1] + fw;
            i_idx += 1;
            j_idx -= 1;
        }

        // compute n
        z = scalbnf_inner(z, q0);
        z -= 8.0f32 * floorf_inner(z * 0.125f32);
        let mut n = z as i32;
        z -= n as f32;
        let mut ih: i32 = 0;

        if q0 > 0 {
            let i2 = (iq[(jz - 1) as usize] >> (8 - q0)) as i32;
            n += i2;
            iq[(jz - 1) as usize] -= i2 << (8 - q0);
            ih = iq[(jz - 1) as usize] >> (7 - q0);
        } else if q0 == 0 {
            ih = iq[(jz - 1) as usize] >> 7;
        } else if z >= 0.5f32 {
            ih = 2;
        }

        if ih > 0 {
            n += 1;
            let mut carry: i32 = 0;
            for i2 in 0..(jz as usize) {
                let j2 = iq[i2];
                if carry == 0 {
                    if j2 != 0 {
                        carry = 1;
                        iq[i2] = 0x100 - j2;
                    }
                } else {
                    iq[i2] = 0xff - j2;
                }
            }
            if q0 > 0 {
                if q0 == 1 {
                    iq[(jz - 1) as usize] &= 0x7f;
                } else if q0 == 2 {
                    iq[(jz - 1) as usize] &= 0x3f;
                }
            }
            if ih == 2 {
                z = 1.0f32 - z;
                if carry != 0 {
                    z -= scalbnf_inner(1.0f32, q0);
                }
            }
        }

        // save for post-loop use
        z_out = z;
        n_out = n;
        ih_out = ih;

        // check if recomputation needed
        if z == 0.0f32 {
            let mut j2: i32 = 0;
            for i2 in (jk as usize..jz as usize).rev() {
                j2 |= iq[i2];
            }
            if j2 == 0 {
                let mut k: i32 = 1;
                while (jk - k) >= 0 && iq[(jk - k) as usize] == 0 {
                    k += 1;
                }
                for i2 in (jz as usize + 1)..=(jz + k) as usize {
                    if (jv + i2 as i32) < 66 && (jx + i2 as i32) < 20 {
                        f[jx as usize + i2] = IPIO2[(jv + i2 as i32) as usize] as f32;
                    } else {
                        exhausted = true;
                    }
                    let mut fw2 = 0.0f32;
                    for j2 in 0..=jx as usize {
                        fw2 += x[j2] * f[jx as usize + i2 - j2];
                    }
                    q[i2] = fw2;
                }
                jz += k;
                recompute = true;
            }
        }

        if !recompute || exhausted {
            break;
        }
    }

    let mut z = z_out;
    let n_final = n_out;
    let ih = ih_out;

    // chop off zero terms
    if z == 0.0f32 {
        q0 -= 8;
        let mut jz2 = jz - 1;
        while jz2 >= 0 {
            if iq[jz2 as usize] != 0 {
                break;
            }
            q0 -= 8;
            jz2 -= 1;
        }
        jz = jz2;
    } else {
        z = scalbnf_inner(z, -q0);
        iq[jz as usize] = z as i32;
    }

    // convert integer bit chunks to floating-point
    let mut fw = scalbnf_inner(1.0f32, q0);
    for i in (0..=jz as usize).rev() {
        q[i] = fw * iq[i] as f32;
        fw *= 3.90625e-3f32; // twon8
    }

    // compute PIo2[0,...,jp]*q[jz,...,0]
    for i in (0..=jz as usize).rev() {
        let mut fw2 = 0.0f32;
        let mut k = 0usize;
        while k <= jp as usize && k <= jz as usize - i {
            fw2 += PIO2_ARR[k] * q[i + k];
            k += 1;
        }
        fq[jz as usize - i] = fw2;
    }

    // compress fq[] into y[]
    let mut fw = 0.0f32;
    for i in (0..=jz as usize).rev() {
        fw += fq[i];
    }
    y[0] = if ih == 0 { fw } else { -fw };
    fw = fq[0] - fw;
    for i in 1..=jz as usize {
        fw += fq[i];
    }
    y[1] = if ih == 0 { fw } else { -fw };

    n_final & 7
}

// scalbnf / floorf used internally in rem_pio2f (avoid recursion through pub versions)
fn scalbnf_inner(x: f32, n: i32) -> f32 {
    // simple but correct scalbn for internal use
    let mut x = x;
    let mut n = n;
    if n > 127 {
        x *= f32::from_bits(0x7f000000); // 2^127
        n -= 127;
        if n > 127 {
            x *= f32::from_bits(0x7f000000);
            n -= 127;
            if n > 127 { n = 127; }
        }
    } else if n < -127 {
        x *= f32::from_bits(0x00800000); // 2^-126
        n += 126;
        if n < -127 {
            x *= f32::from_bits(0x00800000);
            n += 126;
            if n < -127 { n = -127; }
        }
    }
    x * f32::from_bits(((127 + n) as u32) << 23)
}

fn floorf_inner(x: f32) -> f32 {
    let i0 = get_float_word(x) as i32;
    let ix = (i0 & 0x7fffffff) as u32;
    let j0 = (ix >> 23) as i32 - 0x7f;
    if j0 < 23 {
        if j0 < 0 {
            if flt_uword_is_zero(ix) { return x; }
            // round toward -inf
            let mut i0m = i0;
            if i0 >= 0 {
                i0m = 0;
            } else {
                i0m = 0xbf800000u32 as i32;
            }
            return set_float_word(i0m as u32);
        } else {
            let mask = 0x007fffffu32 >> j0;
            if (i0 as u32 & mask) == 0 { return x; }
            let mut i0m = i0;
            if i0 < 0 {
                i0m += (0x00800000i32) >> j0;
            }
            i0m &= !(mask as i32);
            return set_float_word(i0m as u32);
        }
    } else {
        if !flt_uword_is_finite(ix) { return x + x; }
        return x;
    }
}

// The main rem_pio2f
pub(crate) fn rem_pio2f_fn(x: f32, y: &mut [f32; 2]) -> i32 {
    const HALF: f32 = 5.0000000000e-01f32;
    const INVPIO2: f32 = 6.3661980629e-01f32; // 0x3f22f984
    const PIO2_1: f32 = 1.5707855225e+00f32;  // 0x3fc90f80
    const PIO2_1T: f32 = 1.0804334124e-05f32; // 0x37354443
    const PIO2_2: f32 = 1.0804273188e-05f32;  // 0x37354400
    const PIO2_2T: f32 = 6.0770999344e-11f32; // 0x2e85a308
    const PIO2_3: f32 = 6.0770943833e-11f32;  // 0x2e85a300
    const PIO2_3T: f32 = 6.1232342629e-17f32; // 0x248d3132

    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;

    if ix <= 0x3f490fd8 {
        y[0] = x;
        y[1] = 0.0f32;
        return 0;
    }

    if ix < 0x4016cbe4 {
        if hx > 0 {
            let mut z = x - PIO2_1;
            if (ix as u32 & 0xfffe0000u32) != 0x3fc80000 {
                y[0] = z - PIO2_1T;
                y[1] = (z - y[0]) - PIO2_1T;
            } else {
                z -= PIO2_2;
                y[0] = z - PIO2_2T;
                y[1] = (z - y[0]) - PIO2_2T;
            }
            return 1;
        } else {
            let mut z = x + PIO2_1;
            if (ix as u32 & 0xfffe0000u32) != 0x3fc80000 {
                y[0] = z + PIO2_1T;
                y[1] = (z - y[0]) + PIO2_1T;
            } else {
                z += PIO2_2;
                y[0] = z + PIO2_2T;
                y[1] = (z - y[0]) + PIO2_2T;
            }
            return -1;
        }
    }

    if ix <= 0x43490f80 {
        let t = fabsf_fn(x);
        let n = (t * INVPIO2 + HALF) as i32;
        let fn_ = n as f32;
        let mut r = t - fn_ * PIO2_1;
        let mut w = fn_ * PIO2_1T;
        {
            let j = ix >> 23;
            y[0] = r - w;
            let high = get_float_word(y[0]);
            let i = j - (((high >> 23) & 0xff) as i32);
            if i > 8 {
                let t2 = r;
                w = fn_ * PIO2_2;
                r = t2 - w;
                w = fn_ * PIO2_2T - ((t2 - r) - w);
                y[0] = r - w;
                let high2 = get_float_word(y[0]);
                let i2 = j - (((high2 >> 23) & 0xff) as i32);
                if i2 > 25 {
                    let t3 = r;
                    w = fn_ * PIO2_3;
                    r = t3 - w;
                    w = fn_ * PIO2_3T - ((t3 - r) - w);
                    y[0] = r - w;
                }
            }
        }
        y[1] = (r - y[0]) - w;
        if hx < 0 {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        } else {
            return n;
        }
    }

    // large arguments
    if !flt_uword_is_finite(ix as u32) {
        if x.is_nan() {
            y[1] = x - x;
            y[0] = y[1];
        } else {
            y[1] = raise_invalidf();
            y[0] = y[1];
        }
        return 0;
    }

    let e0 = (ix >> 23) as i32 - 134;
    let z = set_float_word((ix as i32 - (e0 << 23)) as u32);
    let mut tx = [0.0f32; 3];
    let mut z2 = z;
    for i in 0..2usize {
        tx[i] = (z2 as i32) as f32;
        z2 = (z2 - tx[i]) * 256.0f32;
    }
    tx[2] = z2;

    let mut nx = 3i32;
    while nx > 1 && tx[(nx - 1) as usize] == 0.0f32 {
        nx -= 1;
    }

    let n = rem_pio2f_internal(&tx, y, e0, nx);

    if hx < 0 {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }
    n
}

// __cosf internal
pub(crate) fn cosf_kern(x: f32, y: f32) -> f32 {
    // C1 =  0xaaaaa5.0p-28f = 0x3D2AAAAA => 4.16666455e-2
    // C2 = -0xb60615.0p-33f = 0xBAB60615 => -1.38873106e-3
    // C3 =  0xccf47d.0p-39f = 0x37CCF47C => 2.44325429e-5
    let c1 = f32::from_bits(0x3D2AAAA5);  // ~0.04166664556
    let c2 = f32::from_bits(0xBAB60615);  // ~-0.001388731063
    let c3 = f32::from_bits(0x37CCF47C);  // ~0.00002443254289
    let z = x * x;
    let r = z * (c1 + z * (c2 + z * c3));
    let hz = 0.5f32 * z;
    let w = 1.0f32 - hz;
    w + (((1.0f32 - w) - hz) + (z * r - x * y))
}

pub(crate) fn sinf_kern(x: f32, y: f32, iy: i32) -> f32 {
    // S1 = -0xaaaaab.0p-26 = 0xBE2AAAAB => -0.16666667
    // S2 =  0x8888bb.0p-30 = 0x3C0888BB => 0.008333380334
    // S3 = -0xd02de1.0p-36 = 0xB9502DE1 => -0.0001985352
    // S4 =  0xbe6dbe.0p-42 = 0x363E6DBE => 0.000002837608
    let s1 = f32::from_bits(0xBE2AAAAB);
    let s2 = f32::from_bits(0x3C0888BB);
    let s3 = f32::from_bits(0xB9502DE1);
    let s4 = f32::from_bits(0x363E6DBE);
    let half = 0.5f32;
    let z = x * x;
    let v = z * x;
    let r = s2 + z * (s3 + z * s4);
    if iy == 0 {
        x + v * (s1 + z * r)
    } else {
        x - ((z * (half * y - v * r) - y) - v * s1)
    }
}

// ---------------------------------------------------------------------------
// Internal gamma helpers  (from mathf/internal/gammaf.c)
// ---------------------------------------------------------------------------

pub(crate) fn sin_pif(x: f32) -> f32 {
    const PI_G: f32 = 3.1415927410e+00f32;
    const TWO23_G: f32 = 8.3886080000e+06f32;
    let ix = (get_float_word(x) as i32) & 0x7fffffff;

    if ix < 0x3e800000 {
        return sinf_kern(PI_G * x, 0.0f32, 0);
    }

    let mut y = -x;
    let z = floorf_inner(y);
    let mut n: i32;
    let mut y2: f32;

    if z != y {
        y2 = y * 0.5f32;
        y2 = 2.0f32 * (y2 - floorf_inner(y2));
        n = (y2 * 4.0f32) as i32;
    } else {
        let zt = y + TWO23_G;
        let mut nz = get_float_word(zt) as i32;
        nz &= 1;
        y2 = nz as f32;
        n = nz << 2;
    }

    let result = match n {
        0 => sinf_kern(PI_G * y2, 0.0f32, 0),
        1 | 2 => cosf_kern(PI_G * (0.5f32 - y2), 0.0f32),
        3 | 4 => sinf_kern(PI_G * (1.0f32 - y2), 0.0f32, 0),
        5 | 6 => -cosf_kern(PI_G * (y2 - 1.5f32), 0.0f32),
        _ => sinf_kern(PI_G * (y2 - 2.0f32), 0.0f32, 0),
    };
    -result
}

pub(crate) fn lgammaf_r(x: f32, signgamp: &mut i32) -> f32 {
    // Constants from gammaf.c
    const TWO23: f32 = 8.3886080000e+06f32;
    const HALF_G: f32 = 5.0000000000e-01f32;
    const ONE_G: f32 = 1.0000000000e+00f32;
    const PI_G: f32 = 3.1415927410e+00f32;
    const A0: f32 = 7.7215664089e-02f32;
    const A1: f32 = 3.2246702909e-01f32;
    const A2: f32 = 6.7352302372e-02f32;
    const A3: f32 = 2.0580807701e-02f32;
    const A4: f32 = 7.3855509982e-03f32;
    const A5: f32 = 2.8905137442e-03f32;
    const A6: f32 = 1.1927076848e-03f32;
    const A7: f32 = 5.1006977446e-04f32;
    const A8: f32 = 2.2086278477e-04f32;
    const A9: f32 = 1.0801156895e-04f32;
    const A10: f32 = 2.5214456400e-05f32;
    const A11: f32 = 4.4864096708e-05f32;
    const TC: f32 = 1.4616321325e+00f32;
    const TF: f32 = -1.2148628384e-01f32;
    const TT: f32 = 6.6971006518e-09f32;
    const T0: f32 = 4.8383611441e-01f32;
    const T1: f32 = -1.4758771658e-01f32;
    const T2: f32 = 6.4624942839e-02f32;
    const T3: f32 = -3.2788541168e-02f32;
    const T4: f32 = 1.7970675603e-02f32;
    const T5: f32 = -1.0314224288e-02f32;
    const T6: f32 = 6.1005386524e-03f32;
    const T7: f32 = -3.6845202558e-03f32;
    const T8: f32 = 2.2596477065e-03f32;
    const T9: f32 = -1.4034647029e-03f32;
    const T10: f32 = 8.8108185446e-04f32;
    const T11: f32 = -5.3859531181e-04f32;
    const T12: f32 = 3.1563205994e-04f32;
    const T13: f32 = -3.1275415677e-04f32;
    const T14: f32 = 3.3552918467e-04f32;
    const U0: f32 = -7.7215664089e-02f32;
    const U1: f32 = 6.3282704353e-01f32;
    const U2: f32 = 1.4549225569e+00f32;
    const U3: f32 = 9.7771751881e-01f32;
    const U4: f32 = 2.2896373272e-01f32;
    const U5: f32 = 1.3381091878e-02f32;
    const V1: f32 = 2.4559779167e+00f32;
    const V2: f32 = 2.1284897327e+00f32;
    const V3: f32 = 7.6928514242e-01f32;
    const V4: f32 = 1.0422264785e-01f32;
    const V5: f32 = 3.2170924824e-03f32;
    const S0: f32 = -7.7215664089e-02f32;
    const S1: f32 = 2.1498242021e-01f32;
    const S2: f32 = 3.2577878237e-01f32;
    const S3: f32 = 1.4635047317e-01f32;
    const S4: f32 = 2.6642270386e-02f32;
    const S5: f32 = 1.8402845599e-03f32;
    const S6: f32 = 3.1947532989e-05f32;
    const R1: f32 = 1.3920053244e+00f32;
    const R2: f32 = 7.2193557024e-01f32;
    const R3: f32 = 1.7193385959e-01f32;
    const R4: f32 = 1.8645919859e-02f32;
    const R5: f32 = 7.7794247773e-04f32;
    const R6: f32 = 7.3266842264e-06f32;
    const W0: f32 = 4.1893854737e-01f32;
    const W1: f32 = 8.3333335817e-02f32;
    const W2: f32 = -2.7777778450e-03f32;
    const W3: f32 = 7.9365057172e-04f32;
    const W4: f32 = -5.9518753551e-04f32;
    const W5: f32 = 8.3633989561e-04f32;
    const W6: f32 = -1.6309292987e-03f32;

    let mut x = x;
    let hx = get_float_word(x) as i32;
    *signgamp = 1;
    let ix = hx & 0x7fffffff;

    if ix >= 0x7f800000 {
        return x * x;
    }

    if ix == 0 {
        if hx < 0 { *signgamp = -1; }
        return raise_div_by_zerof(0.0f32);
    }

    if ix < 0x30800000 {
        if hx < 0 {
            *signgamp = -1;
            return -logf_fn(-x);
        } else {
            return -logf_fn(x);
        }
    }

    let mut nadj = 0.0f32;

    if hx < 0 {
        if ix >= 0x4b000000 {
            return raise_div_by_zerof(0.0f32);
        }
        let t2 = sin_pif(x);
        if t2 == 0.0f32 {
            return raise_div_by_zerof(0.0f32);
        }
        nadj = logf_fn(PI_G / fabsf_fn(t2 * x));
        if t2 < 0.0f32 {
            *signgamp = -1;
        }
        x = -x;
    }

    let hx2 = get_float_word(x) as i32;
    let ix2 = hx2 & 0x7fffffff;

    let r: f32;

    if ix2 == 0x3f800000 || ix2 == 0x40000000 {
        r = 0.0f32;
    } else if ix2 < 0x40000000 {
        let mut r2 = 0.0f32;
        let (y2, i2) = if ix2 <= 0x3f666666 {
            r2 = -logf_fn(x);
            if ix2 >= 0x3f3b4a20 {
                (ONE_G - x, 0i32)
            } else if ix2 >= 0x3e6d3308 {
                (x - (TC - ONE_G), 1i32)
            } else {
                (x, 2i32)
            }
        } else {
            if ix2 >= 0x3fdda618 {
                (2.0f32 - x, 0i32)
            } else if ix2 >= 0x3F9da620 {
                (x - TC, 1i32)
            } else {
                (x - ONE_G, 2i32)
            }
        };
        let p2: f32;
        let p1: f32;
        let p: f32;
        match i2 {
            0 => {
                let z = y2 * y2;
                p1 = A0 + z * (A2 + z * (A4 + z * (A6 + z * (A8 + z * A10))));
                p2 = z * (A1 + z * (A3 + z * (A5 + z * (A7 + z * (A9 + z * A11)))));
                p = y2 * p1 + p2;
                r2 += p - 0.5f32 * y2;
            }
            1 => {
                let z = y2 * y2;
                let w2 = z * y2;
                p1 = T0 + w2 * (T3 + w2 * (T6 + w2 * (T9 + w2 * T12)));
                p2 = T1 + w2 * (T4 + w2 * (T7 + w2 * (T10 + w2 * T13)));
                let p3 = T2 + w2 * (T5 + w2 * (T8 + w2 * (T11 + w2 * T14)));
                p = z * p1 - (TT - w2 * (p2 + y2 * p3));
                r2 += TF + p;
            }
            _ => {
                p1 = y2 * (U0 + y2 * (U1 + y2 * (U2 + y2 * (U3 + y2 * (U4 + y2 * U5)))));
                p2 = ONE_G + y2 * (V1 + y2 * (V2 + y2 * (V3 + y2 * (V4 + y2 * V5))));
                r2 += -0.5f32 * y2 + p1 / p2;
            }
        }
        r = r2;
    } else if ix2 < 0x41000000 {
        let i2 = x as i32;
        let y2 = x - i2 as f32;
        let p = y2 * (S0 + y2 * (S1 + y2 * (S2 + y2 * (S3 + y2 * (S4 + y2 * (S5 + y2 * S6))))));
        let q = ONE_G + y2 * (R1 + y2 * (R2 + y2 * (R3 + y2 * (R4 + y2 * (R5 + y2 * R6)))));
        let mut r2 = HALF_G * y2 + p / q;
        let mut z = ONE_G;
        let mut ii = i2;
        if ii == 7 { z *= y2 + 6.0f32; ii = 6; }
        if ii == 6 { z *= y2 + 5.0f32; ii = 5; }
        if ii == 5 { z *= y2 + 4.0f32; ii = 4; }
        if ii == 4 { z *= y2 + 3.0f32; ii = 3; }
        if ii == 3 { z *= y2 + 2.0f32; }
        r2 += logf_fn(z);
        r = r2;
    } else if ix2 < 0x5c800000 {
        let t2 = logf_fn(x);
        let z = ONE_G / x;
        let y2 = z * z;
        let w2 = W0 + z * (W1 + y2 * (W2 + y2 * (W3 + y2 * (W4 + y2 * (W5 + y2 * W6)))));
        r = (x - HALF_G) * (t2 - ONE_G) + w2;
    } else {
        r = x * (logf_fn(x) - ONE_G);
    }

    if hx < 0 {
        nadj - r
    } else {
        r
    }
}

// Internal logf, used by lgamma
fn logf_fn(x: f32) -> f32 {
    logf(x)
}

fn fabsf_fn(x: f32) -> f32 {
    fabsf(x)
}

// ---------------------------------------------------------------------------
// Internal error-function helpers  (from errorfunctionf.h)
// ---------------------------------------------------------------------------

fn erff_y(x: f32) -> f32 {
    const PP0: f32 = 1.28379166e-01f32;
    const PP1: f32 = -3.36030394e-01f32;
    const PP2: f32 = -1.86261395e-03f32;
    const QQ1: f32 = 3.12324315e-01f32;
    const QQ2: f32 = 2.16070414e-02f32;
    const QQ3: f32 = -1.98859372e-03f32;
    let z = x * x;
    let r = PP0 + z * (PP1 + z * PP2);
    let s = 1.0f32 + z * (QQ1 + z * (QQ2 + z * QQ3));
    r / s
}

fn erff_p(s: f32) -> f32 {
    const PA0: f32 = 3.65041046e-06f32;
    const PA1: f32 = 4.15109307e-01f32;
    const PA2: f32 = -2.09395722e-01f32;
    const PA3: f32 = 8.67677554e-02f32;
    PA0 + s * (PA1 + s * (PA2 + s * PA3))
}

fn erff_q(s: f32) -> f32 {
    const QA1: f32 = 4.95560974e-01f32;
    const QA2: f32 = 3.71248513e-01f32;
    const QA3: f32 = 3.92478965e-02f32;
    1.0f32 + s * (QA1 + s * (QA2 + s * QA3))
}

fn erff_ra(s: f32) -> f32 {
    const RA0: f32 = -9.88156721e-03f32;
    const RA1: f32 = -5.43658376e-01f32;
    const RA2: f32 = -1.66828310e+00f32;
    const RA3: f32 = -6.91554189e-01f32;
    RA0 + s * (RA1 + s * (RA2 + s * RA3))
}

fn erff_sa(s: f32) -> f32 {
    const SA1: f32 = 4.48581553e+00f32;
    const SA2: f32 = 4.10799170e+00f32;
    const SA3: f32 = 5.53855181e-01f32;
    1.0f32 + s * (SA1 + s * (SA2 + s * SA3))
}

fn erff_rb(s: f32) -> f32 {
    const RB0: f32 = -9.86496918e-03f32;
    const RB1: f32 = -5.48049808e-01f32;
    const RB2: f32 = -1.84115684e+00f32;
    RB0 + s * (RB1 + s * RB2)
}

fn erff_sb(s: f32) -> f32 {
    const SB1: f32 = 4.87132740e+00f32;
    const SB2: f32 = 3.04982710e+00f32;
    const SB3: f32 = -7.61900663e-01f32;
    1.0f32 + s * (SB1 + s * (SB2 + s * SB3))
}

// Internal log1pmff helper  (from log1pmff.h)
fn log1pmff(f: f32) -> f32 {
    const LG1: f32 = f32::from_bits(0x3F2AAAAA); // 0xaaaaaa.0p-24
    const LG2: f32 = f32::from_bits(0x3ECCCE13); // 0xccce13.0p-25
    const LG3: f32 = f32::from_bits(0x3E91E9EE); // 0x91e9ee.0p-25
    const LG4: f32 = f32::from_bits(0x3E789E26); // 0xf89e26.0p-26
    let s = f / (2.0f32 + f);
    let z = s * s;
    let w = z * z;
    let t1 = w * (LG2 + w * LG4);
    let t2 = z * (LG1 + w * LG3);
    let r = t2 + t1;
    let hfsq = 0.5f32 * f * f;
    s * (hfsq + r)
}

// Internal tanf helper
pub(crate) fn tanf_kern(x: f32, y: f32, iy: i32) -> f32 {
    const PIO4: f32 = 7.8539812565e-01f32;
    const PIO4LO: f32 = 3.7748947079e-08f32;
    const T: [f32; 13] = [
        3.3333334327e-01f32,
        1.3333334029e-01f32,
        5.3968254477e-02f32,
        2.1869488060e-02f32,
        8.8632395491e-03f32,
        3.5920790397e-03f32,
        1.4562094584e-03f32,
        5.8804126456e-04f32,
        2.4646313977e-04f32,
        7.8179444245e-05f32,
        7.1407252108e-05f32,
        -1.8558637748e-05f32,
        2.5907305826e-05f32,
    ];

    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;
    let mut x2 = x;
    let mut y2 = y;

    if ix >= 0x3f2ca140 {
        if hx < 0 {
            x2 = -x2;
            y2 = -y2;
        }
        let z = PIO4 - x2;
        let w = PIO4LO - y2;
        x2 = z + w;
        y2 = 0.0f32;
    }

    let z = x2 * x2;
    let w = z * z;
    let r = T[1] + w * (T[3] + w * (T[5] + w * (T[7] + w * (T[9] + w * T[11]))));
    let v = z * (T[2] + w * (T[4] + w * (T[6] + w * (T[8] + w * (T[10] + w * T[12])))));
    let s = z * x2;
    let mut r2 = y2 + z * (s * (r + v) + y2);
    r2 += T[0] * s;
    let w2 = x2 + r2;

    if ix >= 0x3f2ca140 {
        let v2 = iy as f32;
        return (1 - ((hx >> 30) & 2)) as f32 * (v2 - 2.0f32 * (x2 - (w2 * w2 / (w2 + v2) - r2)));
    }

    if iy == 1 {
        return w2;
    } else {
        let a: f32;
        let mut t: f32;
        let s2: f32;
        let mut zz = w2;
        let mut i = get_float_word(zz) as i32;
        zz = set_float_word((i as u32) & 0xfffff000u32);
        let v3 = r2 - (zz - x2);
        t = -1.0f32 / w2;
        a = t;
        i = get_float_word(t) as i32;
        t = set_float_word((i as u32) & 0xfffff000u32);
        s2 = 1.0f32 + t * zz;
        return t + a * (s2 + t * v3);
    }
}

// ---------------------------------------------------------------------------
// Public math functions
// ---------------------------------------------------------------------------

pub fn acosf(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    const PI: f32 = 3.1415925026e+00f32;
    const PIO2_HI: f32 = 1.5707962513e+00f32;
    const PIO2_LO: f32 = 7.5497894159e-08f32;
    const PS0: f32 = 1.6666667163e-01f32;
    const PS1: f32 = -3.2556581497e-01f32;
    const PS2: f32 = 2.0121252537e-01f32;
    const PS3: f32 = -4.0055535734e-02f32;
    const PS4: f32 = 7.9153501429e-04f32;
    const PS5: f32 = 3.4793309169e-05f32;
    const QS1: f32 = -2.4033949375e+00f32;
    const QS2: f32 = 2.0209457874e+00f32;
    const QS3: f32 = -6.8828397989e-01f32;
    const QS4: f32 = 7.7038154006e-02f32;

    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;

    if ix == 0x3f800000 {
        if hx > 0 {
            return 0.0f32;
        } else {
            return PI + 2.0f32 * PIO2_LO;
        }
    } else if ix > 0x3f800000 {
        if x.is_nan() { return x + x; }
        return raise_invalidf();
    }

    if ix < 0x3f000000 {
        if ix <= 0x23000000 {
            return PIO2_HI + PIO2_LO;
        }
        let z = x * x;
        let p = z * (PS0 + z * (PS1 + z * (PS2 + z * (PS3 + z * (PS4 + z * PS5)))));
        let q = ONE + z * (QS1 + z * (QS2 + z * (QS3 + z * QS4)));
        let r = p / q;
        return PIO2_HI - (x - (PIO2_LO - x * r));
    } else if hx < 0 {
        let z = (ONE + x) * 0.5f32;
        let p = z * (PS0 + z * (PS1 + z * (PS2 + z * (PS3 + z * (PS4 + z * PS5)))));
        let q = ONE + z * (QS1 + z * (QS2 + z * (QS3 + z * QS4)));
        let s = sqrtf(z);
        let r = p / q;
        let w = r * s - PIO2_LO;
        return PI - 2.0f32 * (s + w);
    } else {
        let z = (ONE - x) * 0.5f32;
        let s = sqrtf(z);
        let mut df = s;
        let idf = get_float_word(df) as i32;
        df = set_float_word((idf as u32) & 0xfffff000u32);
        let c = (z - df * df) / (s + df);
        let p = z * (PS0 + z * (PS1 + z * (PS2 + z * (PS3 + z * (PS4 + z * PS5)))));
        let q = ONE + z * (QS1 + z * (QS2 + z * (QS3 + z * QS4)));
        let r = p / q;
        let w = r * s + c;
        return 2.0f32 * (df + w);
    }
}

pub fn acoshf(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    const LN2: f32 = 6.9314718246e-01f32;
    let hx = get_float_word(x) as i32;

    if hx < 0x3f800000 {
        if x.is_nan() { return x + x; }
        return raise_invalidf();
    } else if hx >= 0x4d800000 {
        if !flt_uword_is_finite(hx as u32) { return x + x; }
        return logf(x) + LN2;
    } else if hx == 0x3f800000 {
        return 0.0f32;
    } else if hx > 0x40000000 {
        let t = x * x;
        return logf(2.0f32 * x - ONE / (x + sqrtf(t - ONE)));
    } else {
        let t = x - ONE;
        return log1pf(t + sqrtf(2.0f32 * t + t * t));
    }
}

pub fn asinf(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    const PIO2_HI: f32 = 1.57079637050628662109375f32;
    const PIO2_LO: f32 = -4.37113900018624283e-8f32;
    const PIO4_HI: f32 = 0.785398185253143310546875f32;
    const PS0: f32 = 1.6666667163e-01f32;
    const PS1: f32 = -3.2556581497e-01f32;
    const PS2: f32 = 2.0121252537e-01f32;
    const PS3: f32 = -4.0055535734e-02f32;
    const PS4: f32 = 7.9153501429e-04f32;
    const PS5: f32 = 3.4793309169e-05f32;
    const QS1: f32 = -2.4033949375e+00f32;
    const QS2: f32 = 2.0209457874e+00f32;
    const QS3: f32 = -6.8828397989e-01f32;
    const QS4: f32 = 7.7038154006e-02f32;

    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;

    if ix == 0x3f800000 {
        return x * PIO2_HI + x * PIO2_LO;
    } else if ix > 0x3f800000 {
        if x.is_nan() { return x + x; }
        return raise_invalidf();
    } else if ix < 0x3f000000 {
        if ix < 0x32000000 {
            if flt_uword_is_zero(ix as u32) { return x; }
            return raise_inexactf(x);
        }
        let t = x * x;
        let p = t * (PS0 + t * (PS1 + t * (PS2 + t * (PS3 + t * (PS4 + t * PS5)))));
        let q = ONE + t * (QS1 + t * (QS2 + t * (QS3 + t * QS4)));
        let w = p / q;
        return x + x * w;
    }

    let w = ONE - fabsf(x);
    let t = w * 0.5f32;
    let p = t * (PS0 + t * (PS1 + t * (PS2 + t * (PS3 + t * (PS4 + t * PS5)))));
    let q = ONE + t * (QS1 + t * (QS2 + t * (QS3 + t * QS4)));
    let s = sqrtf(t);
    let t2: f32;

    if ix >= 0x3F79999A {
        let w2 = p / q;
        t2 = PIO2_HI - (2.0f32 * (s + s * w2) - PIO2_LO);
    } else {
        let mut w2 = s;
        let iw = get_float_word(w2) as i32;
        w2 = set_float_word((iw as u32) & 0xfffff000u32);
        let c = (t - w2 * w2) / (s + w2);
        let r = p / q;
        let p2 = 2.0f32 * s * r - (PIO2_LO - 2.0f32 * c);
        let q2 = PIO4_HI - 2.0f32 * w2;
        t2 = PIO4_HI - (p2 - q2);
    }

    if hx > 0 { t2 } else { -t2 }
}

pub fn asinhf(x: f32) -> f32 {
    const ONE: f32 = 1.0000000000e+00f32;
    const LN2: f32 = 6.9314718246e-01f32;
    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;

    if !flt_uword_is_finite(ix as u32) {
        return x + x;
    }

    if ix < 0x31800000 {
        if flt_uword_is_zero(ix as u32) { return x; }
        return raise_inexactf(x);
    }

    let w: f32;
    if ix > 0x4d800000 {
        w = logf(fabsf(x)) + LN2;
    } else if ix > 0x40000000 {
        let t = fabsf(x);
        w = logf(2.0f32 * t + ONE / (sqrtf(x * x + ONE) + t));
    } else {
        let t = x * x;
        w = log1pf(fabsf(x) + t / (ONE + sqrtf(ONE + t)));
    }

    if hx > 0 { w } else { -w }
}

pub fn atanf(x: f32) -> f32 {
    const ATANHI: [f32; 4] = [
        4.6364760399e-01f32,
        7.8539812565e-01f32,
        9.8279368877e-01f32,
        1.5707962513e+00f32,
    ];
    const ATANLO: [f32; 4] = [
        5.0121582440e-09f32,
        3.7748947079e-08f32,
        3.4473217170e-08f32,
        7.5497894159e-08f32,
    ];
    const AT: [f32; 11] = [
        3.3333334327e-01f32,
        -2.0000000298e-01f32,
        1.4285714924e-01f32,
        -1.1111110449e-01f32,
        9.0908870101e-02f32,
        -7.6918758452e-02f32,
        6.6610731184e-02f32,
        -5.8335702866e-02f32,
        4.9768779427e-02f32,
        -3.6531571299e-02f32,
        1.6285819933e-02f32,
    ];
    const ONE: f32 = 1.0f32;

    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;

    if ix >= 0x50800000 {
        if flt_uword_is_nan(ix as u32) { return x + x; }
        if hx > 0 { return ATANHI[3] + ATANLO[3]; }
        return -ATANHI[3] - ATANLO[3];
    }

    let id: i32;
    let mut x2 = x;

    if ix < 0x3ee00000 {
        if ix < 0x31000000 {
            if flt_uword_is_zero(ix as u32) { return x; }
            return raise_inexactf(x);
        }
        id = -1;
    } else {
        x2 = fabsf(x2);
        if ix < 0x3f980000 {
            if ix < 0x3f300000 {
                id = 0;
                x2 = (2.0f32 * x2 - ONE) / (2.0f32 + x2);
            } else {
                id = 1;
                x2 = (x2 - ONE) / (x2 + ONE);
            }
        } else {
            if ix < 0x401c0000 {
                id = 2;
                x2 = (x2 - 1.5f32) / (ONE + 1.5f32 * x2);
            } else {
                id = 3;
                x2 = -1.0f32 / x2;
            }
        }
    }

    let z = x2 * x2;
    let w = z * z;
    let s1 = z * (AT[0] + w * (AT[2] + w * (AT[4] + w * (AT[6] + w * (AT[8] + w * AT[10])))));
    let s2 = w * (AT[1] + w * (AT[3] + w * (AT[5] + w * (AT[7] + w * AT[9]))));

    if id < 0 {
        x2 - x2 * (s1 + s2)
    } else {
        let z2 = ATANHI[id as usize] - ((x2 * (s1 + s2) - ATANLO[id as usize]) - x2);
        if hx < 0 { -z2 } else { z2 }
    }
}

pub fn atan2f(y: f32, x: f32) -> f32 {
    const PI_O_4: f32 = 7.8539818525e-01f32;
    const PI_O_2: f32 = 1.5707963705e+00f32;
    const PI: f32 = 3.1415927410e+00f32;
    const PI_LO: f32 = -8.7422776573e-08f32;

    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;
    let hy = get_float_word(y) as i32;
    let iy = hy & 0x7fffffff;

    if flt_uword_is_nan(ix as u32) || flt_uword_is_nan(iy as u32) {
        return x + y;
    }

    if hx == 0x3f800000 {
        return atanf(y);
    }

    let m = ((hy >> 31) & 1) | ((hx >> 30) & 2);

    if flt_uword_is_zero(iy as u32) {
        return match m {
            0 | 1 => y,
            2 => raise_inexactf(PI),
            3 => -raise_inexactf(PI),
            _ => y,
        };
    }

    if flt_uword_is_zero(ix as u32) {
        return if hy < 0 { -raise_inexactf(PI_O_2) } else { raise_inexactf(PI_O_2) };
    }

    if flt_uword_is_infinite(ix as u32) {
        if flt_uword_is_infinite(iy as u32) {
            return match m {
                0 => raise_inexactf(PI_O_4),
                1 => -raise_inexactf(PI_O_4),
                2 => raise_inexactf(3.0f32 * PI_O_4),
                3 => -raise_inexactf(3.0f32 * PI_O_4),
                _ => raise_inexactf(PI_O_4),
            };
        } else {
            return match m {
                0 => 0.0f32,
                1 => -0.0f32,
                2 => raise_inexactf(PI),
                3 => -raise_inexactf(PI),
                _ => 0.0f32,
            };
        }
    }

    if flt_uword_is_infinite(iy as u32) {
        return if hy < 0 { -raise_inexactf(PI_O_2) } else { raise_inexactf(PI_O_2) };
    }

    let k = (iy - ix) >> 23;
    let z: f32;
    let mut m2 = m;

    if k > 26 {
        z = raise_inexactf(PI_O_2);
        m2 &= 1;
    } else if hx < 0 && k < -26 {
        z = 0.0f32;
    } else {
        z = atanf(fabsf(y / x));
    }

    match m2 {
        0 => z,
        1 => -z,
        2 => PI - (z - PI_LO),
        _ => (z - PI_LO) - PI,
    }
}

pub fn atanhf(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;

    if ix > 0x3f800000 {
        if x.is_nan() { return x + x; }
        return raise_invalidf();
    }
    if ix == 0x3f800000 {
        return raise_div_by_zerof(x);
    }
    if ix < 0x31800000 {
        if flt_uword_is_zero(ix as u32) { return x; }
        return raise_inexactf(x);
    }

    let mut x2 = set_float_word(ix as u32);

    let t: f32;
    if ix < 0x3f000000 {
        let t2 = x2 + x2;
        t = 0.5f32 * log1pf(t2 + t2 * x2 / (ONE - x2));
    } else {
        t = 0.5f32 * log1pf((x2 + x2) / (ONE - x2));
    }

    if hx >= 0 { t } else { -t }
}

pub fn cbrtf(x: f32) -> f32 {
    const B1: u32 = 709958130;
    const B2: u32 = 642849266;
    const C: f32 = 5.4285717010e-01f32;
    const D: f32 = -7.0530611277e-01f32;
    const E: f32 = 1.4142856598e+00f32;
    const F: f32 = 1.6071428061e+00f32;
    const G: f32 = 3.5714286566e-01f32;

    let hx = get_float_word(x) as i32;
    let sign = (hx as u32) & 0x80000000u32;
    let hx2 = hx ^ sign as i32;

    if !flt_uword_is_finite(hx2 as u32) { return x + x; }
    if flt_uword_is_zero(hx2 as u32) { return x; }

    let mut x2 = set_float_word(hx2 as u32);

    let t: f32;
    if flt_uword_is_subnormal(hx2 as u32) {
        let t2 = set_float_word(0x4b800000u32);
        let t3 = t2 * x2;
        let high = get_float_word(t3);
        t = set_float_word(high / 3 + B2);
    } else {
        t = set_float_word((hx2 as u32) / 3 + B1);
    }

    let r = t * t / x2;
    let s = C + r * t;
    let t2 = t * (G + F / (s + E + D / s));

    let high = get_float_word(t2);
    set_float_word(high | sign)
}

pub fn ceilf(x: f32) -> f32 {
    let mut i0 = get_float_word(x) as i32;
    let ix = (i0 & 0x7fffffff) as u32;
    let j0 = (ix >> 23) as i32 - 0x7f;

    if j0 < 23 {
        if j0 < 0 {
            if flt_uword_is_zero(ix) { return x; }
            let _ = raise_inexactf(x);
            if i0 < 0 {
                i0 = 0x80000000u32 as i32;
            } else {
                i0 = 0x3f800000i32;
            }
        } else {
            let mask = 0x007fffffu32 >> j0;
            if ((i0 as u32) & mask) == 0 { return x; }
            let _ = raise_inexactf(x);
            if i0 > 0 {
                i0 = i0.wrapping_add((0x00800000i32) >> j0);
            }
            i0 &= !(mask as i32);
        }
    } else {
        if !flt_uword_is_finite(ix) { return x + x; }
        return x;
    }

    set_float_word(i0 as u32)
}

pub fn copysignf(x: f32, y: f32) -> f32 {
    let ix = get_float_word(x);
    let iy = get_float_word(y);
    set_float_word((ix & 0x7fffffffu32) | (iy & 0x80000000u32))
}

pub fn cosf(x: f32) -> f32 {
    let mut y = [0.0f32; 2];
    let z = 0.0f32;
    let ix = (get_float_word(x) as i32) & 0x7fffffff;

    if ix <= 0x3f490fd8 {
        if ix < 0x39800000 {
            if x == 0.0f32 { return 1.0f32; }
            return raise_inexactf(1.0f32);
        }
        return cosf_kern(x, z);
    } else if !flt_uword_is_finite(ix as u32) {
        if x.is_nan() { return x + x; }
        return raise_invalidf();
    } else {
        let n = rem_pio2f_fn(x, &mut y);
        match n & 3 {
            0 => cosf_kern(y[0], y[1]),
            1 => -sinf_kern(y[0], y[1], 1),
            2 => -cosf_kern(y[0], y[1]),
            _ => sinf_kern(y[0], y[1], 1),
        }
    }
}

pub fn coshf(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    const HALF: f32 = 0.5f32;
    let ix = (get_float_word(x) as i32) & 0x7fffffff;

    if !flt_uword_is_finite(ix as u32) { return x * x; }

    if ix < 0x3eb17218 {
        let t = expm1f(fabsf(x));
        let w = ONE + t;
        if ix < 0x24000000 { return w; }
        return ONE + (t * t) / (w + w);
    }

    if ix < 0x41b00000 {
        let t = expf(fabsf(x));
        return HALF * t + HALF / t;
    }

    if ix <= FLT_UWORD_LOG_MAX as i32 {
        return HALF * expf(fabsf(x));
    }

    if ix <= FLT_UWORD_LOG_2MAX as i32 {
        let w = expf(HALF * fabsf(x));
        let t = HALF * w;
        return t * w;
    }

    raise_overflowf(1.0f32)
}

pub fn erfcf(x: f32) -> f32 {
    const HALF: f32 = 5.0000000000e-01f32;
    const TWO: f32 = 2.0000000000e+00f32;
    const ERX: f32 = 8.42697144e-01f32;
    const ONE: f32 = 1.0f32;

    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;

    if !flt_uword_is_finite(ix as u32) {
        if x.is_nan() { return x + x; }
        if hx > 0 { return 0.0f32; }
        return TWO;
    }

    if ix < 0x3f580000 {
        if ix < 0x33800000 { return raise_inexactf(ONE); }
        let y = erff_y(x);
        if hx < 0x3e800000 {
            return ONE - (x + x * y);
        } else {
            let r = x * y;
            let r2 = r + (x - HALF);
            return HALF - r2;
        }
    }

    if ix < 0x3fa00000 {
        let s = fabsf(x) - ONE;
        let p = erff_p(s);
        let q = erff_q(s);
        if hx >= 0 {
            let z = ONE - ERX;
            return z - p / q;
        } else {
            let z = ERX + p / q;
            return ONE + z;
        }
    }

    if ix < 0x41220000 {
        let mut x2 = fabsf(x);
        let s = ONE / (x2 * x2);
        let r: f32;
        let ss: f32;
        if ix < 0x4036DB6D {
            r = erff_ra(s);
            ss = erff_sa(s);
        } else {
            if hx < 0 && ix >= 0x40c00000 {
                return raise_inexactf(TWO);
            }
            r = erff_rb(s);
            ss = erff_sb(s);
        }
        let ix2 = get_float_word(x2) as i32;
        let z = set_float_word((ix2 as u32) & 0xffffc000u32);
        let rv = expf(-z * z - 0.5625f32) * expf((z - x2) * (z + x2) + r / ss);
        if hx > 0 { rv / x2 } else { TWO - rv / x2 }
    } else {
        if hx > 0 {
            raise_underflowf(0.0f32)
        } else {
            raise_inexactf(TWO)
        }
    }
}

pub fn erff(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    const ERX: f32 = 8.42697144e-01f32;
    const EFX: f32 = 1.2837916613e-01f32;
    const EFX8: f32 = 1.0270333290e+00f32;

    let hx = get_float_word(x) as i32;
    let ix = hx & 0x7fffffff;

    if !flt_uword_is_finite(ix as u32) {
        if x.is_nan() { return x + x; }
        if hx > 0 { return 1.0f32; }
        return -1.0f32;
    }

    if ix < 0x3f580000 {
        if ix < 0x38800000 {
            if ix < 0x04000000 {
                return 0.125f32 * (8.0f32 * x + EFX8 * x);
            }
            return x + EFX * x;
        }
        return x + x * erff_y(x);
    }

    if ix < 0x3fa00000 {
        let s = fabsf(x) - ONE;
        let p = erff_p(s);
        let q = erff_q(s);
        if hx >= 0 { return ERX + p / q; }
        return -ERX - p / q;
    }

    if ix >= 0x40800000 {
        if hx >= 0 { return raise_inexactf(ONE); }
        return -raise_inexactf(ONE);
    }

    let x2 = fabsf(x);
    let s = ONE / (x2 * x2);
    let r: f32;
    let ss: f32;
    if ix < 0x4036DB8C {
        r = erff_ra(s);
        ss = erff_sa(s);
    } else {
        r = erff_rb(s);
        ss = erff_sb(s);
    }
    let ix2 = get_float_word(x2) as i32;
    let z = set_float_word((ix2 as u32) & 0xffffc000u32);
    let rv = expf(-z * z - 0.5625f32) * expf((z - x2) * (z + x2) + r / ss);

    if hx >= 0 { ONE - rv / x2 } else { rv / x2 - ONE }
}

pub fn exp2f(x: f32) -> f32 {
    powf(2.0f32, x)
}

pub fn expf(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    const ZERO: f32 = 0.0f32;
    const HALF_F: [f32; 2] = [0.5f32, -0.5f32];
    const TWOM100: f32 = 7.8886090522e-31f32;
    const LN2HI: [f32; 2] = [6.9314575195e-01f32, -6.9314575195e-01f32];
    const LN2LO: [f32; 2] = [1.4286067653e-06f32, -1.4286067653e-06f32];
    const INVLN2: f32 = 1.4426950216e+00f32;
    const P1: f32 = 1.6666667163e-01f32;
    const P2: f32 = -2.7777778450e-03f32;
    const P3: f32 = 6.6137559770e-05f32;
    const P4: f32 = -1.6533901999e-06f32;
    const P5: f32 = 4.1381369442e-08f32;

    let sx = get_float_word(x) as i32;
    let xsb = ((sx >> 31) & 1) as usize;
    let hx = (sx as u32) & 0x7fffffff;

    if flt_uword_is_nan(hx) { return x + x; }
    if flt_uword_is_infinite(hx) {
        return if xsb == 0 { x } else { ZERO };
    }
    if sx > FLT_UWORD_LOG_MAX as i32 {
        return raise_overflowf(ONE);
    }
    if sx < 0 && hx > 0x42cff1b5 {  // FLT_UWORD_LOG_MIN non-DAZ
        return raise_underflowf(ZERO);
    }

    let mut hi = 0.0f32;
    let mut lo = 0.0f32;
    let mut k: i32 = 0;

    if hx > 0x3eb17218 {
        if hx < 0x3F851592 {
            hi = x - LN2HI[xsb];
            lo = LN2LO[xsb];
            k = 1 - (xsb as i32) - (xsb as i32);
        } else {
            k = (INVLN2 * x + HALF_F[xsb]) as i32;
            let t = k as f32;
            hi = x - t * LN2HI[0];
            lo = t * LN2LO[0];
        }
        let x2 = hi - lo;
        // use x2 from here
        let t = x2 * x2;
        let c = x2 - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
        if k == 0 {
            return ONE - ((x2 * c) / (c - 2.0f32) - x2);
        }
        let y = ONE - ((lo - (x2 * c) / (2.0f32 - c)) - hi);
        if k >= -125 {
            let hy = get_float_word(y);
            return set_float_word(hy.wrapping_add(((k as u32) << 23)));
        } else {
            let hy = get_float_word(y);
            let y2 = set_float_word(hy.wrapping_add(((k as u32 + 100u32) << 23)));
            return y2 * TWOM100;
        }
    } else if hx < 0x34000000 {
        if x == 0.0f32 { return ONE; }
        return raise_inexactf(ONE + x);
    }

    let t = x * x;
    let c = x - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
    if k == 0 {
        ONE - ((x * c) / (c - 2.0f32) - x)
    } else {
        let y = ONE - ((lo - (x * c) / (2.0f32 - c)) - hi);
        if k >= -125 {
            let hy = get_float_word(y);
            set_float_word(hy.wrapping_add(((k as u32) << 23)))
        } else {
            let hy = get_float_word(y);
            let y2 = set_float_word(hy.wrapping_add(((k as u32 + 100u32) << 23)));
            y2 * TWOM100
        }
    }
}

pub fn expm1f(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    const LN2_HI: f32 = 6.9313812256e-01f32;
    const LN2_LO: f32 = 9.0580006145e-06f32;
    const INVLN2: f32 = 1.4426950216e+00f32;
    const Q1: f32 = -3.3333335072e-02f32;
    const Q2: f32 = 1.5873016091e-03f32;
    const Q3: f32 = -7.9365076090e-05f32;
    const Q4: f32 = 4.0082177293e-06f32;
    const Q5: f32 = -2.0109921195e-07f32;

    let mut hx = get_float_word(x) as u32;
    let xsb = hx & 0x80000000u32;
    hx &= 0x7fffffffu32;

    let mut c = f32::NAN;

    if hx >= 0x4195b844 {
        if flt_uword_is_nan(hx) { return x + x; }
        if flt_uword_is_infinite(hx) {
            return if xsb == 0 { x } else { -ONE };
        }
        if xsb == 0 && hx > FLT_UWORD_LOG_MAX {
            return raise_overflowf(ONE);
        }
        if xsb != 0 {
            return -raise_inexactf(ONE);
        }
    }

    let mut k: i32 = 0;
    let mut x2 = x;

    if hx > 0x3eb17218 {
        if hx < 0x3F851592 {
            if xsb == 0 {
                k = 1;
                let hi = x2 - LN2_HI;
                let lo = LN2_LO;
                x2 = hi - lo;
                c = (hi - x2) - lo;
            } else {
                k = -1;
                let hi = x2 + LN2_HI;
                let lo = -LN2_LO;
                x2 = hi - lo;
                c = (hi - x2) - lo;
            }
        } else {
            k = (INVLN2 * x2 + if xsb == 0 { 0.5f32 } else { -0.5f32 }) as i32;
            let t = k as f32;
            let hi = x2 - t * LN2_HI;
            let lo = t * LN2_LO;
            x2 = hi - lo;
            c = (hi - x2) - lo;
        }
    } else if hx < 0x33000000 {
        if x2 == 0.0f32 { return x2; }
        return raise_inexactf(x2);
    } else {
        k = 0;
    }

    let hfx = 0.5f32 * x2;
    let hxs = x2 * hfx;
    let r1 = ONE + hxs * (Q1 + hxs * (Q2 + hxs * (Q3 + hxs * (Q4 + hxs * Q5))));
    let t = 3.0f32 - r1 * hfx;
    let e = hxs * ((r1 - t) / (6.0f32 - x2 * t));

    if k == 0 {
        return x2 - (x2 * e - hxs);
    }

    let e2 = x2 * (e - c) - c;
    let e3 = e2 - hxs;

    if k == -1 {
        return 0.5f32 * (x2 - e3) - 0.5f32;
    }
    if k == 1 {
        if x2 < -0.25f32 {
            return -2.0f32 * (e3 - (x2 + 0.5f32));
        } else {
            return ONE + 2.0f32 * (x2 - e3);
        }
    }

    if k <= -2 || k > 56 {
        let mut y2 = ONE - (e3 - x2);
        let i = get_float_word(y2) as i32;
        let y3 = set_float_word((i as u32).wrapping_add((k as u32) << 23));
        return y3 - ONE;
    }

    let mut t2 = ONE;
    if k < 23 {
        t2 = set_float_word(0x3f800000u32 - (0x1000000u32 >> k as u32));
        let mut y2 = t2 - (e3 - x2);
        let i = get_float_word(y2) as i32;
        set_float_word((i as u32).wrapping_add((k as u32) << 23))
    } else {
        t2 = set_float_word(((0x7f - k) as u32) << 23);
        let y2 = x2 - (e3 + t2);
        let y3 = y2 + ONE;
        let i = get_float_word(y3) as i32;
        set_float_word((i as u32).wrapping_add((k as u32) << 23))
    }
}

pub fn fabsf(x: f32) -> f32 {
    let ix = get_float_word(x);
    set_float_word(ix & 0x7fffffffu32)
}

pub fn fdimf(x: f32, y: f32) -> f32 {
    if x.is_nan() || y.is_nan() { return x * y; }
    if x > y { x - y } else { 0.0f32 }
}

pub fn floorf(x: f32) -> f32 {
    let mut i0 = get_float_word(x) as i32;
    let ix = (i0 & 0x7fffffff) as u32;
    let j0 = (ix >> 23) as i32 - 0x7f;

    if j0 < 23 {
        if j0 < 0 {
            if flt_uword_is_zero(ix) { return x; }
            let _ = raise_inexactf(x);
            if i0 >= 0 {
                i0 = 0;
            } else {
                i0 = 0xbf800000u32 as i32;
            }
        } else {
            let mask = 0x007fffffu32 >> j0;
            if ((i0 as u32) & mask) == 0 { return x; }
            let _ = raise_inexactf(x);
            if i0 < 0 {
                i0 = i0.wrapping_add((0x00800000i32) >> j0);
            }
            i0 &= !(mask as i32);
        }
    } else {
        if !flt_uword_is_finite(ix) { return x + x; }
        return x;
    }

    set_float_word(i0 as u32)
}

pub fn fmaf(x: f32, y: f32, z: f32) -> f32 {
    x * y + z
}

pub fn fmaxf(x: f32, y: f32) -> f32 {
    if x.is_nan() {
        if issignalingf(x) != 0 || issignalingf(y) != 0 { return x * y; }
        return y;
    }
    if y.is_nan() {
        if issignalingf(y) != 0 { return x * y; }
        return x;
    }
    if x > y { x } else { y }
}

pub fn fminf(x: f32, y: f32) -> f32 {
    if x.is_nan() {
        if issignalingf(x) != 0 || issignalingf(y) != 0 { return x * y; }
        return y;
    }
    if y.is_nan() {
        if issignalingf(y) != 0 { return x * y; }
        return x;
    }
    if x < y { x } else { y }
}

pub fn fmodf(x: f32, y: f32) -> f32 {
    const ZERO: [f32; 2] = [0.0f32, -0.0f32];

    let hx = get_float_word(x) as i32;
    let hy = get_float_word(y) as i32;
    let sx = (hx as u32) & 0x80000000u32;
    let mut hx2 = hx ^ sx as i32;
    let mut hy2 = hy & 0x7fffffff;

    if !flt_uword_is_finite(hx2 as u32) || !flt_uword_is_finite(hy2 as u32) {
        if flt_uword_is_infinite(hx2 as u32) { return raise_invalidf(); }
        if flt_uword_is_nan(hx2 as u32) || flt_uword_is_nan(hy2 as u32) { return x + y; }
    } else if flt_uword_is_zero(hy2 as u32) {
        return raise_invalidf();
    }

    if hx2 < hy2 { return x; }
    if hx2 == hy2 { return ZERO[(sx >> 31) as usize]; }

    let mut ix: i32;
    let mut iy: i32;
    let mut i: i32;

    if flt_uword_is_subnormal(hx2 as u32) {
        ix = -126;
        i = hx2 << 8;
        while i > 0 { ix -= 1; i <<= 1; }
    } else {
        ix = (hx2 >> 23) - 127;
    }

    if flt_uword_is_subnormal(hy2 as u32) {
        iy = -126;
        i = hy2 << 8;
        while i >= 0 { iy -= 1; i <<= 1; }
    } else {
        iy = (hy2 >> 23) - 127;
    }

    if ix >= -126 {
        hx2 = 0x00800000 | (0x007fffff & hx2);
    } else {
        let n = -126 - ix;
        hx2 = hx2 << n;
    }

    if iy >= -126 {
        hy2 = 0x00800000 | (0x007fffff & hy2);
    } else {
        let n = -126 - iy;
        hy2 = hy2 << n;
    }

    let mut n = ix - iy;
    while n > 0 {
        n -= 1;
        let hz = hx2 - hy2;
        if hz < 0 {
            hx2 = hx2 + hx2;
        } else {
            if hz == 0 { return ZERO[(sx >> 31) as usize]; }
            hx2 = hz + hz;
        }
    }

    let hz = hx2 - hy2;
    if hz >= 0 { hx2 = hz; }

    if hx2 == 0 { return ZERO[(sx >> 31) as usize]; }

    while hx2 < 0x00800000 {
        hx2 = hx2 + hx2;
        iy -= 1;
    }

    let mut x2 = x;
    if iy >= -126 {
        hx2 = ((hx2 - 0x00800000) | ((iy + 127) << 23));
        x2 = set_float_word((hx2 as u32) | sx);
    } else {
        let n = -126 - iy;
        hx2 >>= n;
        x2 = set_float_word((hx2 as u32) | sx);
    }

    x2
}

pub fn frexpf(x: f32, exp: &mut i32) -> f32 {
    const TWO25: f32 = 3.3554432000e+07f32;
    let hx = get_float_word(x) as i32;
    let ix = 0x7fffffff & hx;
    *exp = 0;

    if !flt_uword_is_finite(ix as u32) || flt_uword_is_zero(ix as u32) {
        return x + x;
    }

    let mut hx2 = hx;
    let mut ix2 = ix;

    if flt_uword_is_subnormal(ix as u32) {
        let x2 = x * TWO25;
        hx2 = get_float_word(x2) as i32;
        ix2 = hx2 & 0x7fffffff;
        *exp = -25;
    }

    *exp += (ix2 >> 23) - 126;
    hx2 = (hx2 & 0x807fffffu32 as i32) | 0x3f000000i32;
    set_float_word(hx2 as u32)
}

pub fn hypotf(x: f32, y: f32) -> f32 {
    let mut a = x;
    let mut b = y;
    let mut ha = get_float_word(x) as i32;
    ha &= 0x7fffffff;
    let mut hb = get_float_word(y) as i32;
    hb &= 0x7fffffff;

    if hb > ha {
        let j = ha; ha = hb; hb = j;
    }

    a = set_float_word(ha as u32);
    b = set_float_word(hb as u32);

    if (ha - hb) > 0xf000000 { return a + b; }

    let mut k = 0i32;

    if ha > 0x58800000 {
        if !flt_uword_is_finite(ha as u32) {
            let mut w = a + b;
            if flt_uword_is_infinite(ha as u32) { w = a; }
            if flt_uword_is_infinite(hb as u32) { w = b; }
            return w;
        }
        ha -= 0x22000000;
        hb -= 0x22000000;
        k += 68;
        a = set_float_word(ha as u32);
        b = set_float_word(hb as u32);
    }

    if hb < 0x26800000 {
        if flt_uword_is_zero(hb as u32) { return a; }
        if flt_uword_is_subnormal(hb as u32) {
            let t1 = set_float_word(0x7e800000u32);
            b *= t1;
            a *= t1;
            k -= 126;
        } else {
            ha += 0x28000000;
            hb += 0x28000000;
            k -= 80;
            a = set_float_word(ha as u32);
            b = set_float_word(hb as u32);
        }
    }

    let w = a - b;
    let w2: f32;
    if w > b {
        let t1 = set_float_word((ha as u32) & 0xfffff000u32);
        let t2 = a - t1;
        w2 = sqrtf(t1 * t1 - (b * (-b) - t2 * (a + t1)));
    } else {
        let a2 = a + a;
        let y1 = set_float_word((hb as u32) & 0xfffff000u32);
        let y2 = b - y1;
        let t1 = set_float_word(((ha as u32 + 0x00800000u32) & 0xfffff000u32));
        let t2 = a2 - t1;
        w2 = sqrtf(t1 * y1 - (w * (-w) - (t1 * y2 + t2 * b)));
    }

    if k != 0 {
        let t1 = set_float_word(((0x7f + k) as u32) << 23);
        t1 * w2
    } else {
        w2
    }
}

pub fn ilogbf(x: f32) -> i32 {
    let mut hx = get_float_word(x) as i32;
    hx &= 0x7fffffff;

    if flt_uword_is_zero(hx as u32) {
        let _ = raise_invalidf();
        return FP_ILOGB0;
    } else if flt_uword_is_subnormal(hx as u32) {
        let mut ix = -126i32;
        hx <<= 8;
        while hx > 0 { ix -= 1; hx <<= 1; }
        return ix;
    } else if flt_uword_is_finite(hx as u32) {
        return (hx >> 23) - 127;
    } else if flt_uword_is_nan(hx as u32) {
        let _ = raise_invalidf();
        return FP_ILOGBNAN;
    } else {
        let _ = raise_invalidf();
        return i32::MAX;
    }
}

pub fn ldexpf(x: f32, exp: i32) -> f32 {
    if !x.is_finite() || x == 0.0f32 { return x + x; }
    scalbnf(x, exp)
}

pub fn lgammaf(x: f32) -> f32 {
    let mut signgamp = 1i32;
    let result = lgammaf_r(x, &mut signgamp);
    SIGNGAM.with(|s| s.set(signgamp));
    result
}

pub fn llrintf(x: f32) -> i64 {
    const TWO23: [f32; 2] = [8.3886080000e+06f32, -8.3886080000e+06f32];

    let mut i0 = get_float_word(x) as u32;
    let sx = (i0 >> 31) as usize;
    let j0 = (((i0 & 0x7f800000) >> 23) as i32) - 127;

    if j0 < (i64::BITS as i32) - 1 {
        if j0 < -1 { return 0; }
        if j0 >= 23 {
            let result = ((i0 & 0x7fffff) | 0x800000) as i64;
            return if sx != 0 { -(result << (j0 - 23)) } else { result << (j0 - 23) };
        }
        // round
        let w: f32 = TWO23[sx] + x;
        let t = w - TWO23[sx];
        i0 = get_float_word(t) as u32;
        if (i0 & !(1u32 << 31)) == 0 { return 0; }
        let j02 = (((i0 >> 23) & 0xff) as i32) - 0x7f;
        i0 &= 0x7fffff;
        i0 |= 0x800000;
        let result = (i0 >> (23 - j02)) as i64;
        if sx != 0 { -result } else { result }
    } else {
        let _ = raise_invalidf();
        if sx != 0 { i64::MIN } else { i64::MAX }
    }
}

pub fn llroundf(x: f32) -> i64 {
    let mut w = get_float_word(x) as u32;
    let exp = ((w & 0x7f800000) >> 23) as i32 - 127;
    let sign: i64 = if (w & 0x80000000u32) != 0 { -1 } else { 1 };
    w &= 0x7fffff;
    w |= 0x800000;

    if exp < (i64::BITS as i32) - 1 {
        if exp < 0 {
            return if exp < -1 { 0 } else { sign };
        } else if exp >= 23 {
            return sign * (w as i64) << (exp - 23);
        } else {
            w = w.wrapping_add(0x400000u32 >> exp as u32);
            return sign * (w >> (23 - exp as u32)) as i64;
        }
    } else {
        let _ = raise_invalidf();
        if sign == -1 { i64::MIN } else { i64::MAX }
    }
}

pub fn log10f(x: f32) -> f32 {
    const TWO25: f32 = 3.3554432000e+07f32;
    const IVLN10HI: f32 = 4.3432617188e-01f32;
    const IVLN10LO: f32 = -3.1689971365e-05f32;
    const LOG10_2HI: f32 = 3.0102920532e-01f32;
    const LOG10_2LO: f32 = 7.9034151668e-07f32;

    let mut hx = get_float_word(x) as i32;
    let mut k = 0i32;

    if flt_uword_is_zero((hx & 0x7fffffff) as u32) {
        return raise_div_by_zerof(-1.0f32);
    }
    if flt_uword_is_nan((hx & 0x7fffffff) as u32) { return x + x; }
    if hx < 0 { return raise_invalidf(); }
    if flt_uword_is_infinite(hx as u32) { return x + x; }

    let mut x2 = x;
    if flt_uword_is_subnormal(hx as u32) {
        k -= 25;
        x2 *= TWO25;
        hx = get_float_word(x2) as i32;
    }

    if hx == 0x3f800000 { return 0.0f32; }

    k += (hx >> 23) - 127;
    hx &= 0x007fffff;
    let i = (hx + 0x4afb0d) & 0x800000;
    x2 = set_float_word((hx as u32) | ((i as u32) ^ 0x3f800000u32));
    k += i >> 23;
    let y = k as f32;
    let f = x2 - 1.0f32;
    let hfsq = 0.5f32 * f * f;
    let r = log1pmff(f);
    let mut hi = f - hfsq;
    let hx2 = get_float_word(hi) as i32;
    hi = set_float_word((hx2 as u32) & 0xfffff000u32);
    let lo = (f - hi) - hfsq + r;
    y * LOG10_2LO + (lo + hi) * IVLN10LO + lo * IVLN10HI + hi * IVLN10HI + y * LOG10_2HI
}

pub fn log1pf(x: f32) -> f32 {
    const LN2_HI: f32 = 6.9313812256e-01f32;
    const LN2_LO: f32 = 9.0580006145e-06f32;

    let hx = get_float_word(x) as i32;
    let ax = hx & 0x7fffffff;

    let mut k = 1i32;
    let mut c = f32::NAN;
    let mut f = f32::NAN;
    let mut hu = i32::MAX;

    if !flt_uword_is_finite(ax as u32) { return x + x; }

    if hx < 0x3ed413d7 {
        if ax >= 0x3f800000 {
            if flt_uword_is_nan(ax as u32) { return x + x; }
            if x == -1.0f32 { return raise_div_by_zerof(-1.0f32); }
            return raise_invalidf();
        }
        if ax < 0x31000000 {
            if ax < 0x24800000 { return raise_inexactf(x); }
            return raise_inexactf(x - x * x * 0.5f32);
        }
        if hx > 0 || hx <= 0xbe95f61fu32 as i32 {
            k = 0;
            f = x;
            hu = 1;
        }
    }

    let mut u: f32 = 0.0f32;

    if k != 0 {
        if hx < 0x5a000000 {
            u = 1.0f32 + x;
            hu = get_float_word(u) as i32;
            k = (hu >> 23) - 127;
            c = if k > 0 { 1.0f32 - (u - x) } else { x - (u - 1.0f32) };
            c /= u;
        } else {
            u = x;
            hu = get_float_word(u) as i32;
            k = (hu >> 23) - 127;
            c = 0.0f32;
        }

        hu &= 0x007fffff;
        if hu < 0x3504f7 {
            u = set_float_word((hu as u32) | 0x3f800000u32);
        } else {
            k += 1;
            u = set_float_word((hu as u32) | 0x3f000000u32);
            hu = (0x00800000 - hu) >> 2;
        }
        f = u - 1.0f32;
    }

    let hfsq = 0.5f32 * f * f;

    if hu == 0 {
        if f == 0.0f32 {
            let c2 = c + k as f32 * LN2_LO;
            return k as f32 * LN2_HI + c2;
        }
        let r = hfsq * (1.0f32 - 0.66666666666666666f32 * f);
        return k as f32 * LN2_HI - ((r - (k as f32 * LN2_LO + c)) - f);
    }

    let r = log1pmff(f);
    if k == 0 {
        f - (hfsq - r)
    } else {
        k as f32 * LN2_HI - ((hfsq - (r + (k as f32 * LN2_LO + c))) - f)
    }
}

pub fn log2f(x: f32) -> f32 {
    const TWO25: f32 = 3.3554432000e+07f32;
    const IVLN2HI: f32 = 1.4428710938e+00f32;
    const IVLN2LO: f32 = -1.7605285393e-04f32;

    let mut hx = get_float_word(x) as i32;
    let mut k = 0i32;

    if flt_uword_is_zero((hx & 0x7fffffff) as u32) { return raise_div_by_zerof(-1.0f32); }
    if flt_uword_is_nan((hx & 0x7fffffff) as u32) { return x + x; }
    if hx < 0 { return raise_invalidf(); }
    if flt_uword_is_infinite(hx as u32) { return x + x; }

    let mut x2 = x;
    if flt_uword_is_subnormal(hx as u32) {
        k -= 25;
        x2 *= TWO25;
        hx = get_float_word(x2) as i32;
    }

    if hx == 0x3f800000 { return 0.0f32; }

    k += (hx >> 23) - 127;
    hx &= 0x007fffff;
    let i = (hx + 0x4afb0d) & 0x800000;
    x2 = set_float_word((hx as u32) | ((i as u32) ^ 0x3f800000u32));
    k += i >> 23;
    let y = k as f32;
    let f = x2 - 1.0f32;
    let hfsq = 0.5f32 * f * f;
    let r = log1pmff(f);
    let mut hi = f - hfsq;
    let hx2 = get_float_word(hi) as i32;
    hi = set_float_word((hx2 as u32) & 0xfffff000u32);
    let lo = (f - hi) - hfsq + r;
    (lo + hi) * IVLN2LO + lo * IVLN2HI + hi * IVLN2HI + y
}

pub fn logbf(x: f32) -> f32 {
    let mut hx = get_float_word(x) as i32;
    hx &= 0x7fffffff;

    if flt_uword_is_zero(hx as u32) { return raise_div_by_zerof(-1.0f32); }

    if flt_uword_is_subnormal(hx as u32) {
        let mut ix = -126i32;
        hx <<= 8;
        while hx > 0 { ix -= 1; hx <<= 1; }
        return ix as f32;
    } else if !flt_uword_is_finite(hx as u32) {
        return x * x;
    } else {
        return ((hx >> 23) - 127) as f32;
    }
}

pub fn logf(x: f32) -> f32 {
    const LN2_HI: f32 = 6.9313812256e-01f32;
    const LN2_LO: f32 = 9.0580006145e-06f32;
    const TWO25: f32 = 3.355443200e+07f32;
    const LG1: f32 = 6.6666668653e-01f32;
    const LG2: f32 = 4.0000000596e-01f32;
    const LG3: f32 = 2.8571429849e-01f32;
    const LG4: f32 = 2.2222198546e-01f32;
    const LG5: f32 = 1.8183572590e-01f32;
    const LG6: f32 = 1.5313838422e-01f32;
    const LG7: f32 = 1.4798198640e-01f32;

    let mut ix = get_float_word(x) as i32;
    let mut k = 0i32;

    if flt_uword_is_zero((ix & 0x7fffffff) as u32) {
        return raise_div_by_zerof(-1.0f32);
    }
    if flt_uword_is_nan((ix & 0x7fffffff) as u32) { return x + x; }
    if ix < 0 { return raise_invalidf(); }
    if flt_uword_is_infinite(ix as u32) { return x + x; }

    let mut x2 = x;
    if flt_uword_is_subnormal(ix as u32) {
        k -= 25;
        x2 *= TWO25;
        ix = get_float_word(x2) as i32;
    }

    k += (ix >> 23) - 127;
    ix &= 0x007fffff;
    let i = (ix + (0x95f64 << 3)) & 0x800000;
    x2 = set_float_word((ix as u32) | ((i as u32) ^ 0x3f800000u32));
    k += i >> 23;
    let f = x2 - 1.0f32;

    if (0x007fffff & (15 + ix)) < 16 {
        if f == 0.0f32 {
            if k == 0 { return 0.0f32; }
            let dk = k as f32;
            return dk * LN2_HI + dk * LN2_LO;
        }
        let r = f * f * (0.5f32 - 0.33333333333333333f32 * f);
        if k == 0 {
            return f - r;
        }
        let dk = k as f32;
        return dk * LN2_HI - ((r - dk * LN2_LO) - f);
    }

    let s = f / (2.0f32 + f);
    let dk = k as f32;
    let z = s * s;
    let i2 = ix - (0x6147a << 3);
    let w = z * z;
    let j = (0x6b851 << 3) - ix;
    let t1 = w * (LG2 + w * (LG4 + w * LG6));
    let t2 = z * (LG1 + w * (LG3 + w * (LG5 + w * LG7)));
    let ii = i2 | j;
    let r = t2 + t1;

    if ii > 0 {
        let hfsq = 0.5f32 * f * f;
        if k == 0 {
            f - (hfsq - s * (hfsq + r))
        } else {
            dk * LN2_HI - ((hfsq - (s * (hfsq + r) + dk * LN2_LO)) - f)
        }
    } else {
        if k == 0 {
            f - s * (f - r)
        } else {
            dk * LN2_HI - ((s * (f - r) - dk * LN2_LO) - f)
        }
    }
}

pub fn lrintf(x: f32) -> i64 {
    // C uses long int; on 64-bit linux that's 64 bits
    const TWO23: [f32; 2] = [8.3886080000e+06f32, -8.3886080000e+06f32];

    let mut i0 = get_float_word(x) as u32;
    let sx = (i0 >> 31) as usize;
    let j0 = (((i0 & 0x7f800000) >> 23) as i32) - 127;

    if j0 < (i64::BITS as i32) - 1 {
        if j0 < -1 { return 0; }
        if j0 >= 23 {
            let result = ((i0 & 0x7fffff) | 0x800000) as i64;
            return if sx != 0 { -(result << (j0 - 23)) } else { result << (j0 - 23) };
        }
        let w: f32 = TWO23[sx] + x;
        let t = w - TWO23[sx];
        i0 = get_float_word(t) as u32;
        if (i0 & 0x7fffffffu32) == 0 { return 0; }
        let j02 = (((i0 >> 23) & 0xff) as i32) - 0x7f;
        i0 &= 0x7fffff;
        i0 |= 0x800000;
        let result = (i0 >> (23 - j02 as u32)) as i64;
        if sx != 0 { -result } else { result }
    } else {
        let _ = raise_invalidf();
        if sx != 0 { i64::MIN } else { i64::MAX }
    }
}

pub fn lroundf(x: f32) -> i64 {
    let mut w = get_float_word(x) as u32;
    let exp = ((w & 0x7f800000) >> 23) as i32 - 127;
    let sign: i64 = if (w & 0x80000000u32) != 0 { -1 } else { 1 };
    w &= 0x7fffff;
    w |= 0x800000;

    if exp < (i64::BITS as i32) - 1 {
        if exp < 0 {
            return if exp < -1 { 0 } else { sign };
        } else if exp >= 23 {
            return sign * (w as i64) << (exp - 23);
        } else {
            w = w.wrapping_add(0x400000u32 >> exp as u32);
            return sign * (w >> (23 - exp as u32)) as i64;
        }
    } else {
        let _ = raise_invalidf();
        if sign == -1 { i64::MIN } else { i64::MAX }
    }
}

pub fn modff(x: f32, iptr: &mut f32) -> f32 {
    let i0 = get_float_word(x) as i32;
    let j0 = ((i0 >> 23) & 0xff) - 0x7f;

    if j0 < 23 {
        if j0 < 0 {
            *iptr = set_float_word((i0 as u32) & 0x80000000u32);
            return x;
        } else {
            let mask = 0x007fffffu32 >> j0;
            if ((i0 as u32) & mask) == 0 {
                *iptr = x;
                let x2 = set_float_word((i0 as u32) & 0x80000000u32);
                return x2;
            } else {
                *iptr = set_float_word((i0 as u32) & (!mask));
                return x - *iptr;
            }
        }
    } else {
        *iptr = x;
        if x.is_nan() {
            *iptr = x + x;
            return *iptr;
        }
        let x2 = set_float_word((i0 as u32) & 0x80000000u32);
        return x2;
    }
}

pub fn nanf(_tagp: *const i8) -> f32 {
    set_float_word(0x7FCF067Du32)
}

pub fn nearbyintf(x: f32) -> f32 {
    rintf(x)
}

pub fn nextafterf(x: f32, y: f32) -> f32 {
    let mut hx = get_float_word(x) as i32;
    let hy = get_float_word(y) as i32;
    let ix = hx & 0x7fffffff;
    let iy = hy & 0x7fffffff;

    if flt_uword_is_nan(ix as u32) || flt_uword_is_nan(iy as u32) {
        return x + y;
    }
    if hx == hy { return y; }
    if ix == 0 {
        if ix == iy { return y; }
        // return +-minsubnormal
        hx = ((hy as u32) & 0x80000000u32) as i32 | 1i32;
        let x2 = set_float_word(hx as u32);
        let _ = raise_underflowf(x2);
        return x2;
    }

    if hx >= 0 {
        if hx > hy { hx -= 1; } else { hx += 1; }
    } else {
        if hy >= 0 || hx > hy { hx -= 1; } else { hx += 1; }
    }

    let hy2 = hx & 0x7f800000;
    if hy2 > FLT_UWORD_MAX as i32 {
        return raise_overflowf(x);
    }
    if hy2 < 0x00800000 {
        let _ = raise_underflowf(x);
    }

    set_float_word(hx as u32)
}

pub fn nexttowardf(x: f32, y: f64) -> f32 {
    // Only implemented for long-double-is-64bits case (which is typical on linux x86-64)
    if x.is_nan() || y.is_nan() { return x + y as f32; }
    if x as f64 == y { return y as f32; }

    let mut bits = get_float_word(x);

    if x == 0.0f32 {
        bits = 1u32;
        if y.is_sign_negative() { bits |= 0x80000000u32; }
    } else if (x as f64) < y {
        if x.is_sign_negative() { bits -= 1; } else { bits += 1; }
    } else {
        if x.is_sign_negative() { bits += 1; } else { bits -= 1; }
    }

    let e = bits & 0x7f800000u32;
    if e == 0x7f800000u32 {
        return raise_overflowf(x);
    }
    if e == 0 {
        let _ = raise_underflowf(x);
    }

    set_float_word(bits)
}

pub fn powf(x: f32, y: f32) -> f32 {
    const BP: [f32; 2] = [1.0f32, 1.5f32];
    const DP_H: [f32; 2] = [0.0f32, 5.84960938e-01f32];
    const DP_L: [f32; 2] = [0.0f32, 1.56322085e-06f32];
    const ZERO: f32 = 0.0f32;
    const ONE: f32 = 1.0f32;
    const TWO: f32 = 2.0f32;
    const TWO24: f32 = 16777216.0f32;
    const L1: f32 = 6.0000002384e-01f32;
    const L2: f32 = 4.2857143283e-01f32;
    const L3: f32 = 3.3333334327e-01f32;
    const L4: f32 = 2.7272811532e-01f32;
    const L5: f32 = 2.3066075146e-01f32;
    const L6: f32 = 2.0697501302e-01f32;
    const P1: f32 = 1.6666667163e-01f32;
    const P2: f32 = -2.7777778450e-03f32;
    const P3: f32 = 6.6137559770e-05f32;
    const P4: f32 = -1.6533901999e-06f32;
    const P5: f32 = 4.1381369442e-08f32;
    const LG2: f32 = 6.9314718246e-01f32;
    const LG2_H: f32 = 6.93145752e-01f32;
    const LG2_L: f32 = 1.42860654e-06f32;
    const OVT: f32 = 4.2995665694e-08f32;
    const CP: f32 = 9.6179670095e-01f32;
    const CP_H: f32 = 9.6191406250e-01f32;
    const CP_L: f32 = -1.1736857402e-04f32;
    const IVLN2: f32 = 1.4426950216e+00f32;
    const IVLN2_H: f32 = 1.4426879883e+00f32;
    const IVLN2_L: f32 = 7.0526075433e-06f32;

    let hx = get_float_word(x) as i32;
    let hy = get_float_word(y) as i32;
    let mut ix = hx & 0x7fffffff;
    let iy = hy & 0x7fffffff;

    if flt_uword_is_zero(iy as u32) {
        if issignalingf(x) != 0 { return x + y; }
        return ONE;
    }

    if flt_uword_is_nan(ix as u32) || flt_uword_is_nan(iy as u32) {
        if hx == 0x3f800000 && issignalingf(y) == 0 { return ONE; }
        return x + y;
    }

    let mut yisint = 0i32;
    if hx < 0 {
        if iy >= 0x4b800000 {
            yisint = 2;
        } else if iy >= 0x3f800000 {
            let k = (iy >> 23) - 0x7f;
            let j = iy >> (23 - k);
            if (j << (23 - k)) == iy {
                yisint = 2 - (j & 1);
            }
        }
    }

    if flt_uword_is_infinite(iy as u32) {
        if ix == 0x3f800000 { return ONE; }
        if ix > 0x3f800000 {
            return if hy >= 0 { y } else { ZERO };
        }
        return if hy < 0 { -y } else { ZERO };
    }

    if iy == 0x3f800000 {
        return if hy < 0 { ONE / x } else { x };
    }
    if hy == 0x40000000 { return x * x; }
    if hy == 0x3f000000 && hx >= 0 { return sqrtf(x); }

    let ax = fabsf(x);

    if flt_uword_is_infinite(ix as u32) || flt_uword_is_zero(ix as u32) || ix == 0x3f800000 {
        let mut z = ax;
        if hy < 0 {
            if flt_uword_is_infinite(ix as u32) { z = ZERO; }
            else if flt_uword_is_zero(ix as u32) { z = raise_div_by_zerof(z); }
        }
        if hx < 0 {
            if ((ix - 0x3f800000) | yisint) == 0 {
                z = raise_invalidf();
            } else if yisint == 1 {
                z = -z;
            }
        }
        return z;
    }

    if ((((hx as u32) >> 31u32) - 1u32) | (yisint as u32)) == 0 {
        return raise_invalidf();
    }

    let t1: f32;
    let t2: f32;

    if iy > 0x4d000000 {
        if ix < 0x3f7ffff4 {
            return if hy < 0 { raise_overflowf(ONE) } else { raise_underflowf(ONE) };
        }
        if ix > 0x3f800007 {
            return if hy > 0 { raise_overflowf(ONE) } else { raise_underflowf(ONE) };
        }
        let t = ax - ONE;
        let w2 = (t * t) * (0.5f32 - t * (0.333333333333f32 - t * 0.25f32));
        let u = IVLN2_H * t;
        let v = t * IVLN2_L - w2 * IVLN2;
        t1 = u + v;
        let is = get_float_word(t1) as i32;
        let t1b = set_float_word((is as u32) & 0xfffff000u32);
        t2 = v - (t1b - u);
        // use t1b from here
        // but we need to reassign for the final computation
        let t1f = t1b;
        let t2f = t2;

        // fall through to final pow computation
        return pow_finish(x, y, hx, hy, t1f, t2f, yisint,
            &BP, &DP_H, &DP_L, ONE, TWO, P1, P2, P3, P4, P5,
            LG2, LG2_H, LG2_L, OVT, CP, CP_H, CP_L, IVLN2, IVLN2_H, IVLN2_L,
            ZERO);
    }

    let mut n = 0i32;
    let mut ax2 = ax;
    if flt_uword_is_subnormal(ix as u32) {
        ax2 *= TWO24;
        n -= 24;
        ix = get_float_word(ax2) as i32;
    }

    n += ((ix) >> 23) - 0x7f;
    let j = ix & 0x007fffff;
    ix = j | 0x3f800000;

    let k: i32;
    if j <= 0x1cc471 { k = 0; }
    else if j < 0x5db3d7 { k = 1; }
    else { k = 0; n += 1; ix -= 0x00800000; }

    ax2 = set_float_word(ix as u32);

    let u = ax2 - BP[k as usize];
    let v = ONE / (ax2 + BP[k as usize]);
    let s = u * v;
    let mut s_h = s;
    let is = get_float_word(s_h) as i32;
    s_h = set_float_word((is as u32) & 0xfffff000u32);
    let is2 = ((ix >> 1) & 0xfffff000u32 as i32) as u32 | 0x20000000u32;
    let t_h = set_float_word(is2 + 0x00400000u32 + ((k as u32) << 21));
    let t_l = ax2 - (t_h - BP[k as usize]);
    let s_l = v * ((u - s_h * t_h) - s_h * t_l);
    let s2 = s * s;
    let r = s2 * s2 * (L1 + s2 * (L2 + s2 * (L3 + s2 * (L4 + s2 * (L5 + s2 * L6)))));
    let r2 = r + s_l * (s_h + s);
    let s2b = s_h * s_h;
    let mut t_h2 = 3.0f32 + s2b + r2;
    let is3 = get_float_word(t_h2) as i32;
    t_h2 = set_float_word((is3 as u32) & 0xfffff000u32);
    let t_l2 = r2 - ((t_h2 - 3.0f32) - s2b);
    let u2 = s_h * t_h2;
    let v2 = s_l * t_h2 + t_l2 * s;
    let mut p_h = u2 + v2;
    let is4 = get_float_word(p_h) as i32;
    p_h = set_float_word((is4 as u32) & 0xfffff000u32);
    let p_l = v2 - (p_h - u2);
    let z_h = CP_H * p_h;
    let z_l = CP_L * p_h + p_l * CP + DP_L[k as usize];
    let t_val = n as f32;
    let mut t1f = (((z_h + z_l) + DP_H[k as usize]) + t_val);
    let is5 = get_float_word(t1f) as i32;
    t1f = set_float_word((is5 as u32) & 0xfffff000u32);
    let t2f = z_l - (((t1f - t_val) - DP_H[k as usize]) - z_h);

    pow_finish(x, y, hx, hy, t1f, t2f, yisint,
        &BP, &DP_H, &DP_L, ONE, TWO, P1, P2, P3, P4, P5,
        LG2, LG2_H, LG2_L, OVT, CP, CP_H, CP_L, IVLN2, IVLN2_H, IVLN2_L,
        ZERO)
}

fn pow_finish(
    x: f32, y: f32, hx: i32, hy: i32, t1: f32, t2: f32, yisint: i32,
    bp: &[f32; 2], dp_h: &[f32; 2], dp_l: &[f32; 2],
    one: f32, two: f32, p1: f32, p2: f32, p3: f32, p4: f32, p5: f32,
    lg2: f32, lg2_h: f32, lg2_l: f32, ovt: f32,
    cp: f32, cp_h: f32, cp_l: f32, ivln2: f32, ivln2_h: f32, ivln2_l: f32,
    zero: f32,
) -> f32 {
    const FLT_UWORD_EXP_MAX_: u32 = 0x43000000;
    const FLT_UWORD_EXP_MIN_: u32 = 0x43160000;

    let mut s = one;
    if ((((hx as u32) >> 31u32) - 1u32) | ((yisint - 1) as u32)) == 0 {
        s = -one;
    }

    let is = get_float_word(y) as i32;
    let mut y1 = set_float_word((is as u32) & 0xfffff000u32);
    let p_l = (y - y1) * t1 + y * t2;
    let p_h = y1 * t1;
    let z = p_l + p_h;
    let j = get_float_word(z) as i32;
    let i = j & 0x7fffffff;

    if j > 0 {
        if i > FLT_UWORD_EXP_MAX_ as i32 {
            return raise_overflowf(s);
        } else if i == FLT_UWORD_EXP_MAX_ as i32 {
            if p_l + ovt > z - p_h {
                return raise_overflowf(s);
            }
        }
    } else {
        if i > FLT_UWORD_EXP_MIN_ as i32 {
            return raise_underflowf(s);
        } else if i == FLT_UWORD_EXP_MIN_ as i32 {
            if p_l <= z - p_h {
                return raise_underflowf(s);
            }
        }
    }

    let k = (i >> 23) - 0x7f;
    let mut n = 0i32;

    if i > 0x3f000000 {
        n = j + (0x00800000i32 >> (k + 1));
        let k2 = ((n & 0x7fffffff) >> 23) - 0x7f;
        let t_val = set_float_word((n as u32) & !((0x007fffffu32) >> k2 as u32));
        n = ((n & 0x007fffff) | 0x00800000) >> (23 - k2);
        if j < 0 { n = -n; }
        let mut p_h2 = p_h - t_val;
        // use p_h2 onwards
        let t2_ = p_l + p_h2;
        let is2 = get_float_word(t2_) as i32;
        let t3 = set_float_word((is2 as u32) & 0xffff8000u32);
        let u = t3 * lg2_h;
        let v = (p_l - (t3 - p_h2)) * lg2 + t3 * lg2_l;
        let z2 = u + v;
        let w = v - (z2 - u);
        let t4 = z2 * z2;
        let t5 = z2 - t4 * (p1 + t4 * (p2 + t4 * (p3 + t4 * (p4 + t4 * p5))));
        let r2 = (z2 * t5) / (t5 - two) - (w + z2 * w);
        let z3 = one - (r2 - z2);
        let mut j2 = get_float_word(z3) as i32;
        j2 += n << 23;
        if (j2 >> 23) <= 0 {
            return s * scalbnf(z3, n);
        } else {
            return s * set_float_word(j2 as u32);
        }
    }

    let t2_ = p_l + p_h;
    let is2 = get_float_word(t2_) as i32;
    let t3 = set_float_word((is2 as u32) & 0xffff8000u32);
    let u = t3 * lg2_h;
    let v = (p_l - (t3 - p_h)) * lg2 + t3 * lg2_l;
    let z2 = u + v;
    let w = v - (z2 - u);
    let t4 = z2 * z2;
    let t5 = z2 - t4 * (p1 + t4 * (p2 + t4 * (p3 + t4 * (p4 + t4 * p5))));
    let r2 = (z2 * t5) / (t5 - two) - (w + z2 * w);
    let z3 = one - (r2 - z2);
    let mut j2 = get_float_word(z3) as i32;
    j2 += n << 23;
    if (j2 >> 23) <= 0 {
        s * scalbnf(z3, n)
    } else {
        s * set_float_word(j2 as u32)
    }
}

pub fn remainderf(x: f32, y: f32) -> f32 {
    let hx = get_float_word(x) as i32;
    let hy = get_float_word(y) as i32;
    let sx = (hx as u32) & 0x80000000u32;
    let hy2 = hy & 0x7fffffff;
    let hx2 = hx & 0x7fffffff;

    if flt_uword_is_nan(hx2 as u32) || flt_uword_is_nan(hy2 as u32) {
        return x + y;
    }
    if flt_uword_is_zero(hy2 as u32) || flt_uword_is_infinite(hx2 as u32) {
        return raise_invalidf();
    }

    let mut x2 = x;
    let mut y2 = y;

    if hy2 <= FLT_UWORD_HALF_MAX as i32 {
        x2 = fmodf(x2, 2.0f32 * y2);
    }

    if (hx2 - hy2) == 0 { return 0.0f32 * x2; }

    x2 = fabsf(x2);
    y2 = fabsf(y2);

    if hy2 < 0x01000000 {
        if x2 + x2 > y2 {
            x2 -= y2;
            if x2 + x2 >= y2 { x2 -= y2; }
        }
    } else {
        let y_half = 0.5f32 * y2;
        if x2 > y_half {
            x2 -= y2;
            if x2 >= y_half { x2 -= y2; }
        }
    }

    let hx3 = get_float_word(x2) as i32;
    set_float_word((hx3 as u32) ^ sx)
}

pub fn remquof(x: f32, y: f32, quo: &mut i32) -> f32 {
    *quo = 0;

    let hx = get_float_word(x) as i32;
    let hy = get_float_word(y) as i32;
    let sx = (hx as u32) & 0x80000000u32;
    let sq = sx ^ ((hy as u32) & 0x80000000u32);
    let hy2 = hy & 0x7fffffff;
    let hx2 = hx & 0x7fffffff;

    if flt_uword_is_nan(hx2 as u32) || flt_uword_is_nan(hy2 as u32) {
        return x + y;
    }
    if flt_uword_is_zero(hy2 as u32) || flt_uword_is_infinite(hx2 as u32) {
        return raise_invalidf();
    }

    let mut x2 = x;
    let mut y2 = y;

    if hy2 <= 0x7dffffff {
        x2 = fmodf(x2, 8.0f32 * y2);
    }

    if (hx2 - hy2) == 0 {
        *quo = if sq != 0 { -1 } else { 1 };
        return 0.0f32 * x2;
    }

    x2 = fabsf(x2);
    y2 = fabsf(y2);
    let mut q = 0i32;

    if x2 >= 4.0f32 * y2 { x2 -= 4.0f32 * y2; q += 4; }
    if x2 >= 2.0f32 * y2 { x2 -= 2.0f32 * y2; q += 2; }

    if hy2 < 0x01000000 {
        if x2 + x2 > y2 {
            x2 -= y2; q += 1;
            if x2 + x2 >= y2 { x2 -= y2; q += 1; }
        }
    } else {
        let y_half = 0.5f32 * y2;
        if x2 > y_half {
            x2 -= y2; q += 1;
            if x2 >= y_half { x2 -= y2; q += 1; }
        }
    }

    q &= 0x7;
    *quo = if sq != 0 { -q } else { q };

    let hx3 = get_float_word(x2) as i32;
    set_float_word((hx3 as u32) ^ sx)
}

pub fn rintf(x: f32) -> f32 {
    const TWO23: [f32; 2] = [8.3886080000e+06f32, -8.3886080000e+06f32];

    let mut i0 = get_float_word(x) as i32;
    let sx = (i0 >> 31) & 1;
    let ix = (i0 & 0x7fffffff) as u32;
    let j0 = (ix >> 23) as i32 - 0x7f;

    if j0 < 23 {
        if flt_uword_is_zero(ix) { return x; }

        if j0 < 0 {
            let i1 = i0 & 0x07fffff;
            i0 &= 0xfff00000u32 as i32;
            // signed negation trick: (i1 | -i1) >> 9
            let neg_i1 = (-(i1 as i64)) as i32;
            i0 |= ((i1 | neg_i1) >> 9) & 0x400000;
            let x2 = set_float_word(i0 as u32);
            let w: f32 = TWO23[sx as usize] + x2;
            let t = w - TWO23[sx as usize];
            let i02 = get_float_word(t) as i32;
            return set_float_word(((i02 as u32) & 0x7fffffffu32) | ((sx as u32) << 31));
        } else {
            let mask = 0x007fffffu32 >> j0;
            if ((i0 as u32) & mask) == 0 { return x; }
            let half_mask = mask >> 1;
            if ((i0 as u32) & half_mask) != 0 {
                i0 = (i0 & !(mask as i32)) | ((0x200000i32) >> j0);
            }
        }
    } else {
        if !flt_uword_is_finite(ix) { return x + x; }
        return x;
    }

    let x2 = set_float_word(i0 as u32);
    let w: f32 = TWO23[sx as usize] + x2;
    w - TWO23[sx as usize]
}

pub fn roundf(x: f32) -> f32 {
    let mut w = get_float_word(x) as u32;
    let exp = (((w & 0x7f800000) >> 23) as i32) - 127;

    if exp < 23 {
        if exp < 0 {
            w &= 0x80000000u32;
            if exp == -1 {
                w |= (127u32) << 23;
            }
        } else {
            let exp_mask = 0x007fffffu32 >> exp;
            if (w & exp_mask) == 0 { return x; }
            w = w.wrapping_add(0x00400000u32 >> exp as u32);
            w &= !exp_mask;
        }
    } else {
        if exp == 128 { return x + x; }
        return x;
    }

    set_float_word(w)
}

pub fn scalblnf(x: f32, n: i64) -> f32 {
    const TWO25: f32 = 3.355443200e+07f32;
    const TWOM25: f32 = 2.9802322388e-08f32;

    let mut ix = get_float_word(x) as i32;
    let mut k = ((ix & 0x7f800000) >> 23) as i32;

    if k == 0 {
        if (ix & 0x7fffffff) == 0 { return x; }
        let x2 = x * TWO25;
        ix = get_float_word(x2) as i32;
        k = ((ix & 0x7f800000) >> 23) - 25;
    }

    if k == 0xff { return x + x; }

    if n > 50000 { return raise_overflowf(x); }

    let k2 = k as i64 + n;

    if k2 > 0xfe { return raise_overflowf(x); }
    if n < -50000 { return raise_underflowf(x); }

    if k2 > 0 {
        return set_float_word(((ix as u32) & 0x807fffffu32) | ((k2 as u32) << 23u32));
    }

    if k2 <= -25 { return raise_underflowf(x); }

    let k3 = k2 as i32 + 25;
    let x3 = set_float_word(((ix as u32) & 0x807fffffu32) | ((k3 as u32) << 23u32));
    x3 * TWOM25
}

pub fn scalbnf(x: f32, n: i32) -> f32 {
    const TWO25: f32 = 3.355443200e+07f32;
    const TWOM25: f32 = 2.9802322388e-08f32;
    const OVERFLOW_INT: i32 = 50000;

    let mut ix = get_float_word(x) as i32;
    let hx = (ix as u32) & 0x7fffffffu32;
    let mut k = (hx >> 23) as i32;

    if flt_uword_is_zero(hx) { return x; }
    if !flt_uword_is_finite(hx) { return x + x; }

    if flt_uword_is_subnormal(hx) {
        let x2 = x * TWO25;
        ix = get_float_word(x2) as i32;
        k = (((ix as u32) & 0x7f800000u32) >> 23) as i32 - 25;
        if n < -50000 { return raise_underflowf(x); }
    }

    if n > OVERFLOW_INT { return raise_overflowf(x); }

    k = k + n;

    if k > FLT_LARGEST_EXP as i32 { return raise_overflowf(x); }

    if k > 0 {
        return set_float_word(((ix as u32) & 0x807fffffu32) | ((k as u32) << 23u32));
    }

    if k < FLT_SMALLEST_EXP { return raise_underflowf(x); }

    let k2 = k + 25;
    let x2 = set_float_word(((ix as u32) & 0x807fffffu32) | ((k2 as u32) << 23u32));
    x2 * TWOM25
}

pub fn sinf(x: f32) -> f32 {
    let mut y = [0.0f32; 2];
    let z = 0.0f32;
    let ix = (get_float_word(x) as i32) & 0x7fffffff;

    if ix <= 0x3f490fd8 {
        if ix < 0x39800000 {
            if flt_uword_is_zero(ix as u32) { return x; }
            return raise_inexactf(x);
        }
        return sinf_kern(x, z, 0);
    } else if !flt_uword_is_finite(ix as u32) {
        if x.is_nan() { return x + x; }
        return raise_invalidf();
    } else {
        let n = rem_pio2f_fn(x, &mut y);
        match n & 3 {
            0 => sinf_kern(y[0], y[1], 1),
            1 => cosf_kern(y[0], y[1]),
            2 => -sinf_kern(y[0], y[1], 1),
            _ => -cosf_kern(y[0], y[1]),
        }
    }
}

pub fn sinhf(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    let jx = get_float_word(x) as i32;
    let ix = jx & 0x7fffffff;

    if !flt_uword_is_finite(ix as u32) { return x + x; }

    let mut h = 0.5f32;
    if jx < 0 { h = -h; }

    if ix < 0x41b00000 {
        if ix < 0x31800000 {
            if flt_uword_is_zero(ix as u32) { return x; }
            return raise_inexactf(x);
        }
        let t = expm1f(fabsf(x));
        if ix < 0x3f800000 {
            return h * (2.0f32 * t - t * t / (t + ONE));
        }
        return h * (t + t / (t + ONE));
    }

    if ix <= FLT_UWORD_LOG_MAX as i32 { return h * expf(fabsf(x)); }
    if ix <= FLT_UWORD_LOG_2MAX as i32 {
        let w = expf(0.5f32 * fabsf(x));
        let t = h * w;
        return t * w;
    }

    raise_overflowf(x)
}

pub fn sqrtf(x: f32) -> f32 {
    let ix = get_float_word(x) as i32;
    let hx = (ix as u32) & 0x7fffffffu32;

    if !flt_uword_is_finite(hx) {
        if flt_uword_is_nan(hx) { return x + x; }
        if ix > 0 { return x; }
        return raise_invalidf();
    }

    if flt_uword_is_zero(hx) { return x; }
    if ix < 0 { return raise_invalidf(); }

    let mut m = ix >> 23;
    let mut ix2 = ix;

    if flt_uword_is_subnormal(hx) {
        let mut i = 0i32;
        while (ix2 & 0x00800000) == 0 {
            ix2 <<= 1;
            i += 1;
        }
        m -= i - 1;
    }

    m -= 127;
    ix2 = (ix2 & 0x007fffff) | 0x00800000;

    if (m & 1) > 0 { ix2 += ix2; }
    m >>= 1;

    ix2 += ix2;
    let mut q: i32 = 0;
    let mut s: i32 = 0;
    let mut r: u32 = 0x01000000u32;

    while r != 0 {
        let t = s + r as i32;
        if t <= ix2 {
            s = t + r as i32;
            ix2 -= t;
            q += r as i32;
        }
        ix2 += ix2;
        r >>= 1;
    }

    if ix2 != 0 {
        let _ = raise_inexactf(x);
        q += q & 1;
    }

    let iz = (q >> 1) + 0x3f000000i32;
    let iz2 = iz + (m << 23);
    set_float_word(iz2 as u32)
}

pub fn tanf(x: f32) -> f32 {
    let mut y = [0.0f32; 2];
    let z = 0.0f32;
    let ix = (get_float_word(x) as i32) & 0x7fffffff;

    if ix <= 0x3f490fda {
        if ix < 0x39800000 {
            if flt_uword_is_zero(ix as u32) { return x; }
            return raise_inexactf(x);
        }
        return tanf_kern(x, z, 1);
    } else if !flt_uword_is_finite(ix as u32) {
        if x.is_nan() { return x + x; }
        return raise_invalidf();
    } else {
        let n = rem_pio2f_fn(x, &mut y);
        return tanf_kern(y[0], y[1], 1 - ((n & 1) << 1));
    }
}

pub fn tanhf(x: f32) -> f32 {
    const ONE: f32 = 1.0f32;
    const TWO: f32 = 2.0f32;
    let jx = get_float_word(x) as i32;
    let ix = jx & 0x7fffffff;

    if !flt_uword_is_finite(ix as u32) {
        if x.is_nan() { return x + x; }
        if jx >= 0 { return ONE; }
        return -ONE;
    }

    if ix < 0x41b00000 {
        if ix < 0x24000000 {
            if flt_uword_is_zero(ix as u32) { return x; }
            return raise_inexactf(x);
        }
        let z: f32;
        if ix >= 0x3f800000 {
            let t = expm1f(TWO * fabsf(x));
            z = ONE - TWO / (t + TWO);
        } else {
            let t = expm1f(-TWO * fabsf(x));
            z = -t / (t + TWO);
        }
        return if jx >= 0 { z } else { -z };
    }

    let z = raise_inexactf(ONE);
    if jx >= 0 { z } else { -z }
}

pub fn tgammaf(x: f32) -> f32 {
    if x.is_nan() { return x + x; }
    if x == 0.0f32 { return raise_div_by_zerof(x); }
    if floorf(x) == x && x < 0.0f32 { return raise_invalidf(); }

    let mut signgam_local = 0i32;
    let y = expf(lgammaf_r(x, &mut signgam_local));
    if signgam_local < 0 { -y } else { y }
}

pub fn truncf(x: f32) -> f32 {
    let mut w = get_float_word(x) as i32;
    let sb = (w as u32) & 0x80000000u32;
    let exp = (((w as u32 & 0x7f800000u32) >> 23) as i32) - 127;

    if exp < 23 {
        if exp < 0 {
            return set_float_word(sb);
        } else {
            return set_float_word(sb | ((w as u32) & !((0x007fffffu32) >> exp as u32)));
        }
    } else {
        if exp == 128 { return x + x; }
        return x;
    }
}

pub fn __fpclassifyf(x: f32) -> i32 {
    let w = get_float_word(x) & 0x7fffffffu32;
    if w == 0x00000000u32 { return 2; }        // FP_ZERO
    if w >= 0x00800000u32 && w <= 0x7f7fffffu32 { return 4; } // FP_NORMAL
    if w <= 0x007fffffu32 { return 3; }        // FP_SUBNORMAL
    if w == 0x7f800000u32 { return 1; }        // FP_INFINITE
    0                                           // FP_NAN
}

pub fn __signbitf(x: f32) -> i32 {
    let w = get_float_word(x);
    if (w & 0x80000000u32) != 0 { 1 } else { 0 }
}
