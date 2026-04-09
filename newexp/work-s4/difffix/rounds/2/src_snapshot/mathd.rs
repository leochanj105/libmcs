#[allow(warnings)]
use std::cell::Cell;
thread_local! { pub static SIGNGAM: Cell<i32> = Cell::new(1); }

// ---------------------------------------------------------------------------
// Utility: scalbn implemented via bit manipulation (no libm dependency)
// ---------------------------------------------------------------------------

pub fn scalbn_inner(x: f64, n: i32) -> f64 {
    let mut n = n;
    let mut x = x;

    if n > 1023 {
        x *= f64::from_bits(0x7FE0000000000000u64); // 0x1p1023
        n -= 1023;
        if n > 1023 {
            x *= f64::from_bits(0x7FE0000000000000u64);
            n -= 1023;
            if n > 1023 {
                n = 1023;
            }
        }
    } else if n < -1022 {
        x *= f64::from_bits(0x0010000000000000u64); // 0x1p-1022
        n += 1022;
        if n < -1022 {
            x *= f64::from_bits(0x0010000000000000u64);
            n += 1022;
            if n < -1022 {
                n = -1022;
            }
        }
    }

    // multiply by 2^n
    let factor = f64::from_bits((((1023i32 + n) as u64) & 0x7FF) << 52);
    x * factor
}

// ---------------------------------------------------------------------------
// rem_pio2_internal  (the large table-based Payne-Hanek reduction)
// ---------------------------------------------------------------------------

static PIO2: [f64; 8] = [
    1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
    7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
    5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
    3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
    1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
    1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
    2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
    2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
];

static IPIO2: [i32; 66] = [
    0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62, 0x95993C, 0x439041, 0xFE5163,
    0xABDEBB, 0xC561B7, 0x246E3A, 0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
    0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41, 0x3991D6, 0x398353, 0x39F49C,
    0x845F8B, 0xBDF928, 0x3B1FF8, 0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
    0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5, 0xF17B3D, 0x0739F7, 0x8A5292,
    0xEA6BFB, 0x5FB11F, 0x8D5D08, 0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
    0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880, 0x4D7327, 0x310606, 0x1556CA,
    0x73A8C9, 0x60E27B, 0xC08C6B,
];

const TWO24: f64  = 16777216.0;  // 0x1p24
const TWON24: f64 = 5.960464477539062500e-08; // 0x1p-24

/// Internal Payne-Hanek range reduction.
/// Returns n & 7, writes result into y[0] and y[1].
pub fn rem_pio2_internal(x: &[f64], y: &mut [f64], e0: i32, nx: usize) -> i32 {
    let jk: i32 = 4;
    let jp: i32 = jk;

    let mut q:  [f64; 20] = [0.0; 20];
    let mut iq: [i32; 20] = [0;   20];
    let mut f:  [f64; 20] = [0.0; 20];
    let mut fq: [f64; 20] = [0.0; 20];

    let jx = nx as i32 - 1;
    let jv = (e0 - 3) / 24;
    let mut q0 = e0 - 24 * (jv + 1);

    // set up f[0] to f[jx+jk]
    let j_start = jv - jx;
    let m = (jx + jk) as usize;
    for i in 0..=m {
        let j = j_start + i as i32;
        f[i] = if j < 0 { 0.0 } else { IPIO2[j as usize] as f64 };
    }

    // compute q[0]..q[jk]
    let mut jz = jk as usize;
    for i in 0..=(jk as usize) {
        let mut fw = 0.0f64;
        for j in 0..=(jx as usize) {
            fw += x[j] * f[(jx as usize) + i - j];
        }
        q[i] = fw;
    }

    // hoist z, n, ih outside the loop so they are accessible after it
    let mut z: f64 = 0.0;
    let mut n: i32 = 0;
    let mut ih: i32 = 0;

    // main loop
    loop {
        let mut recompute = false;
        let mut exhausted = false;

        // distill lower part of q[] into iq[], leave higher part in z
        z = q[jz];
        let mut ii: usize = 0;
        let mut jj = jz;
        while jj > 0 {
            let fw = (TWON24 * z) as i32 as f64;
            iq[ii] = (z - TWO24 * fw) as i32;
            z = q[jj - 1] + fw;
            ii += 1;
            jj -= 1;
        }

        // compute n
        z = scalbn_inner(z, q0);
        z -= 8.0 * (z * 0.125).floor();
        n = z as i32;
        z -= n as f64;
        ih = 0;

        if q0 > 0 {
            let i_val = (iq[jz - 1] >> (24 - q0)) as i32;
            n += i_val;
            iq[jz - 1] -= i_val << (24 - q0);
            ih = iq[jz - 1] >> (23 - q0);
        } else if q0 == 0 {
            ih = iq[jz - 1] >> 23;
        } else if z >= 0.5 {
            ih = 2;
        }

        // for angles in upper half of quadrant, compute complement
        if ih > 0 {
            n += 1;
            let mut carry: i32 = 0;

            for i in 0..jz {
                let j = iq[i];
                if carry == 0 {
                    if j != 0 {
                        carry = 1;
                        iq[i] = 0x1000000 - j;
                    }
                } else {
                    iq[i] = 0xffffff - j;
                }
            }

            if q0 > 0 {
                match q0 {
                    2 => { iq[jz - 1] &= 0x3fffff; }
                    _ => { iq[jz - 1] &= 0x7fffff; } // covers case 1 and default
                }
            }

            if ih == 2 {
                z = 1.0 - z;
                if carry != 0 {
                    z -= scalbn_inner(1.0, q0);
                }
            }
        }

        // check for recomputation needed
        if z == 0.0 {
            let mut j_acc: i32 = 0;
            for i in (jk as usize)..jz {
                j_acc |= iq[i];
            }

            if j_acc == 0 {
                // find k = number of extra terms needed
                let mut k = 1usize;
                while k <= jk as usize && iq[(jk as usize) - k] == 0 {
                    k += 1;
                }

                for i in (jz + 1)..=(jz + k) {
                    if (jv as usize + i) < 66 && (jx as usize + i) < 20 {
                        f[jx as usize + i] = IPIO2[jv as usize + i] as f64;
                    } else {
                        exhausted = true;
                    }

                    let mut fw = 0.0f64;
                    for j in 0..=(jx as usize) {
                        fw += x[j] * f[jx as usize + i - j];
                    }
                    q[i] = fw;
                }

                jz += k;
                recompute = true;
            }
        }

        if !recompute || exhausted {
            break;
        }
    }

    // chop off zero terms
    if z == 0.0 {
        q0 -= 24;
        loop {
            if jz == 0 { break; }
            jz -= 1;
            if iq[jz] != 0 {
                break;
            }
            q0 -= 24;
        }
    } else {
        // break z into 24-bit chunks if necessary
        z = scalbn_inner(z, -q0);
        if z >= TWO24 {
            let fw = (TWON24 * z) as i32 as f64;
            iq[jz] = (z - TWO24 * fw) as i32;
            jz += 1;
            q0 += 24;
            iq[jz] = fw as i32;
        } else {
            iq[jz] = z as i32;
        }
    }

    // convert integer "bit" chunks to floating-point
    let mut fw = scalbn_inner(1.0, q0);
    let mut i = jz as i32;
    while i >= 0 {
        q[i as usize] = fw * (iq[i as usize] as f64);
        fw *= TWON24;
        i -= 1;
    }

    // compute PIo2[0..jp] * q[jz..0]
    let jp_usize = jp as usize;
    let mut i = jz as i32;
    while i >= 0 {
        let mut fw = 0.0f64;
        let mut k: usize = 0;
        while k <= jp_usize && k <= jz - (i as usize) {
            fw += PIO2[k] * q[(i as usize) + k];
            k += 1;
        }
        fq[jz - (i as usize)] = fw;
        i -= 1;
    }

    // compress fq[] into y[]
    let mut fw = 0.0f64;
    let mut i = jz as i32;
    while i >= 0 {
        fw += fq[i as usize];
        i -= 1;
    }
    y[0] = if ih == 0 { fw } else { -fw };
    fw = fq[0] - fw;
    for i in 1..=(jz) {
        fw += fq[i];
    }
    y[1] = if ih == 0 { fw } else { -fw };

    n & 7
}

// ---------------------------------------------------------------------------
// rem_pio2 wrapper
// ---------------------------------------------------------------------------

const HALF:    f64 = 5.00000000000000000000e-01;
const INVPIO2: f64 = 6.36619772367581382433e-01;
const PIO2_1:  f64 = 1.57079632673412561417e+00;
const PIO2_1T: f64 = 6.07710050650619224932e-11;
const PIO2_2:  f64 = 6.07710050630396597660e-11;
const PIO2_2T: f64 = 2.02226624879595063154e-21;
const PIO2_3:  f64 = 2.02226624871116645580e-21;
const PIO2_3T: f64 = 8.47842766036889956997e-32;

/// Return remainder of x rem pi/2 in y[0]+y[1].
pub fn rem_pio2(x: f64, y: &mut [f64]) -> i32 {
    let bits = x.to_bits();
    let hx = (bits >> 32) as i32;
    let ix = hx & 0x7fffffff;

    // |x| ~<= pi/4 — no reduction needed
    if ix <= 0x3fe921fb {
        y[0] = x;
        y[1] = 0.0;
        return 0;
    }

    // |x| < 3pi/4 — special case n = +-1
    if ix < 0x4002d97c {
        if hx > 0 {
            let mut z = x - PIO2_1;
            if ix != 0x3ff921fb {
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
            if ix != 0x3ff921fb {
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

    // medium size: |x| ~<= 2^19*(pi/2)
    if ix <= 0x413921fb {
        let t = x.abs();
        let n = (t * INVPIO2 + HALF) as i32;
        let fn_ = n as f64;
        let mut r = t - fn_ * PIO2_1;
        let mut w = fn_ * PIO2_1T;

        let j = ix >> 20;
        y[0] = r - w;
        let high = (y[0].to_bits() >> 32) as i32;
        let mut i = j - ((high >> 20) & 0x7ff);

        if i > 16 {
            let t2 = r;
            w = fn_ * PIO2_2;
            r = t2 - w;
            w = fn_ * PIO2_2T - ((t2 - r) - w);
            y[0] = r - w;
            let high2 = (y[0].to_bits() >> 32) as i32;
            i = j - ((high2 >> 20) & 0x7ff);

            if i > 49 {
                let t3 = r;
                w = fn_ * PIO2_3;
                r = t3 - w;
                w = fn_ * PIO2_3T - ((t3 - r) - w);
                y[0] = r - w;
            }
        }

        y[1] = (r - y[0]) - w;

        if hx < 0 {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        }
        return n;
    }

    // x is inf or NaN
    if ix >= 0x7ff00000 {
        // raise invalid / produce NaN
        let nan = x - x;
        y[0] = nan;
        y[1] = nan;
        return 0;
    }

    // all other large arguments — use Payne-Hanek
    let low = (bits & 0xffffffff) as u32;
    let e0 = (ix >> 20) as i32 - 1046; // ilogb(z) - 23
    let new_hi = ((ix as u64) - ((e0 as u64) << 20)) << 32;
    let mut z = f64::from_bits(new_hi | (low as u64));

    let mut tx = [0.0f64; 3];
    for i in 0..2 {
        tx[i] = (z as i64) as f64;
        z = (z - tx[i]) * TWO24;
    }
    tx[2] = z;

    let mut nx: usize = 3;
    while nx > 1 && tx[nx - 1] == 0.0 {
        nx -= 1;
    }

    let n = rem_pio2_internal(&tx, y, e0, nx);

    if hx < 0 {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }
    n
}

// ---------------------------------------------------------------------------
// cos_kern  (__cos polynomial kernel)
// ---------------------------------------------------------------------------

const C1: f64 =  4.16666666666666019037e-02; /* 0x3FA55555, 0x5555554C */
const C2: f64 = -1.38888888888741095749e-03; /* 0xBF56C16C, 0x16C15177 */
const C3: f64 =  2.48015872894767294178e-05; /* 0x3EFA01A0, 0x19CB1590 */
const C4: f64 = -2.75573143513906633035e-07; /* 0xBE927E4F, 0x809C52AD */
const C5: f64 =  2.08757232129817482790e-09; /* 0x3E21EE9E, 0xBDB4B1C4 */
const C6: f64 = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */

/// Cosine kernel — x+y bounded to [-pi/4, pi/4].
#[inline]
pub fn cos_kern(x: f64, y: f64) -> f64 {
    let z  = x * x;
    let r  = z * (C1 + z * (C2 + z * (C3 + z * (C4 + z * (C5 + z * C6)))));
    let hz = 0.5 * z;
    let w  = 1.0 - hz;
    w + (((1.0 - w) - hz) + (z * r - x * y))
}

// ---------------------------------------------------------------------------
// sin_kern  (__sin polynomial kernel)
// ---------------------------------------------------------------------------

const S1: f64 = -1.66666666666666324348e-01; /* 0xBFC55555, 0x55555549 */
const S2: f64 =  8.33333333332248946124e-03; /* 0x3F811111, 0x1110F8A6 */
const S3: f64 = -1.98412698298579493134e-04; /* 0xBF2A01A0, 0x19C161D5 */
const S4: f64 =  2.75573137070700676789e-06; /* 0x3EC71DE3, 0x57B1FE7D */
const S5: f64 = -2.50507602534068634195e-08; /* 0xBE5AE5E6, 0x8A2B9CEB */
const S6: f64 =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */

/// Sine kernel — x+y bounded to [-pi/4, pi/4], iy signals if y==0.
#[inline]
pub fn sin_kern(x: f64, y: f64, iy: i32) -> f64 {
    let z = x * x;
    let v = z * x;
    let r = S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));
    if iy == 0 {
        x + v * (S1 + z * r)
    } else {
        x - ((z * (0.5 * y - v * r) - y) - v * S1)
    }
}

// ---------------------------------------------------------------------------
// tan_kern  (__tan polynomial kernel)
// ---------------------------------------------------------------------------

pub(crate) fn tan_kern(x: f64, y: f64, iy: i32) -> f64 {
    const PIO4:   f64 = 7.85398163397448278999e-01;
    const PIO4LO: f64 = 3.06161699786838301793e-17;
    const T: [f64; 13] = [
         3.33333333333334091986e-01,
         1.33333333333201242699e-01,
         5.39682539762260521377e-02,
         2.18694882948595424599e-02,
         8.86323982359930005737e-03,
         3.59207910759131235356e-03,
         1.45620945432529025516e-03,
         5.88041240820264096874e-04,
         2.46463134818469906812e-04,
         7.81794442939557092300e-05,
         7.14072491382608190305e-05,
        -1.85586374855275456654e-05,
         2.59073051863633712884e-05,
    ];

    let hx = (x.to_bits() >> 32) as i32;
    let ix = hx & 0x7fffffff;
    let (mut x, mut y) = (x, y);
    if ix >= 0x3fe59428 {
        if hx < 0 { x = -x; y = -y; }
        let z = PIO4 - x;
        let w = PIO4LO - y;
        x = z + w; y = 0.0;
    }
    let z = x * x; let w = z * z;
    let r = T[1] + w*(T[3] + w*(T[5] + w*(T[7] + w*(T[9] + w*T[11]))));
    let v = z*(T[2] + w*(T[4] + w*(T[6] + w*(T[8] + w*(T[10] + w*T[12])))));
    let s = z * x;
    let r = y + z*(s*(r+v) + y);
    let r = r + T[0]*s;
    let w = x + r;

    if ix >= 0x3fe59428 {
        let vv = iy as f64;
        let sgn = (1 - ((hx >> 30) & 2)) as f64;
        return sgn * (vv - 2.0*(x - (w*w/(w+vv) - r)));
    }
    if iy == 1 { return w; }
    let z2 = f64::from_bits(w.to_bits() & 0xffffffff00000000u64);
    let v2 = r - (z2 - x);
    let t = -1.0 / w;
    let t_hi = f64::from_bits(t.to_bits() & 0xffffffff00000000u64);
    let ss = 1.0 + t_hi * z2;
    t_hi + t * (ss + t_hi * v2)
}

// ---------------------------------------------------------------------------
// gamma helpers (gammad.c)
// ---------------------------------------------------------------------------

const GAMMA_TWO52: f64 = 4.50359962737049600000e+15;
const GAMMA_HALF:  f64 = 5.00000000000000000000e-01;
const GAMMA_ONE:   f64 = 1.00000000000000000000e+00;
const GAMMA_PI:    f64 = 3.14159265358979311600e+00;
const GA0:  f64 =  7.72156649015328655494e-02;
const GA1:  f64 =  3.22467033424113591611e-01;
const GA2:  f64 =  6.73523010531292681824e-02;
const GA3:  f64 =  2.05808084325167332806e-02;
const GA4:  f64 =  7.38555086081402883957e-03;
const GA5:  f64 =  2.89051383673415629091e-03;
const GA6:  f64 =  1.19270763183362067845e-03;
const GA7:  f64 =  5.10069792153511336608e-04;
const GA8:  f64 =  2.20862790713908385557e-04;
const GA9:  f64 =  1.08011567247583939954e-04;
const GA10: f64 =  2.52144565451257326939e-05;
const GA11: f64 =  4.48640949618915160150e-05;
const TC:   f64 =  1.46163214496836224576e+00;
const TF:   f64 = -1.21486290535849611461e-01;
const TT:   f64 = -3.63867699703950536541e-18;
const GT0:  f64 =  4.83836122723810047042e-01;
const GT1:  f64 = -1.47587722994593911752e-01;
const GT2:  f64 =  6.46249402391333854778e-02;
const GT3:  f64 = -3.27885410759859649565e-02;
const GT4:  f64 =  1.79706750811820387126e-02;
const GT5:  f64 = -1.03142241298341437450e-02;
const GT6:  f64 =  6.10053870246291332635e-03;
const GT7:  f64 = -3.68452016781138256760e-03;
const GT8:  f64 =  2.25964780900612472250e-03;
const GT9:  f64 = -1.40346469989232843813e-03;
const GT10: f64 =  8.81081882437654011382e-04;
const GT11: f64 = -5.38595305356740546715e-04;
const GT12: f64 =  3.15632070903625950361e-04;
const GT13: f64 = -3.12754168375120860518e-04;
const GT14: f64 =  3.35529192635519073543e-04;
const GU0:  f64 = -7.72156649015328655494e-02;
const GU1:  f64 =  6.32827064025093366517e-01;
const GU2:  f64 =  1.45492250137234768737e+00;
const GU3:  f64 =  9.77717527963372745603e-01;
const GU4:  f64 =  2.28963728064692451092e-01;
const GU5:  f64 =  1.33810918536787660377e-02;
const GV1:  f64 =  2.45597793713041134822e+00;
const GV2:  f64 =  2.12848976379893395361e+00;
const GV3:  f64 =  7.69285150456672783825e-01;
const GV4:  f64 =  1.04222645593369134254e-01;
const GV5:  f64 =  3.21709242282423911810e-03;
const GS0:  f64 = -7.72156649015328655494e-02;
const GS1:  f64 =  2.14982415960608852501e-01;
const GS2:  f64 =  3.25778796408930981787e-01;
const GS3:  f64 =  1.46350472652464452805e-01;
const GS4:  f64 =  2.66422703033638609560e-02;
const GS5:  f64 =  1.84028451407337715652e-03;
const GS6:  f64 =  3.19475326584100867617e-05;
const GR1:  f64 =  1.39200533467621045958e+00;
const GR2:  f64 =  7.21935547567138069525e-01;
const GR3:  f64 =  1.71933865632803078993e-01;
const GR4:  f64 =  1.86459191715652901344e-02;
const GR5:  f64 =  7.77942496381893596434e-04;
const GR6:  f64 =  7.32668430744625636189e-06;
const GW0:  f64 =  4.18938533204672725052e-01;
const GW1:  f64 =  8.33333333333329678849e-02;
const GW2:  f64 = -2.77777777728775536470e-03;
const GW3:  f64 =  7.93650558643019558500e-04;
const GW4:  f64 = -5.95187557450339963135e-04;
const GW5:  f64 =  8.36339918996282139126e-04;
const GW6:  f64 = -1.63092934096575273989e-03;

/// Internal helper: sin(pi*x), x assumed negative, for gamma computation.
pub(crate) fn sin_pi(x: f64) -> f64 {
    let bits = x.to_bits();
    let ix = ((bits >> 32) as i32) & 0x7fffffff;

    if ix < 0x3fd00000 {
        return sin_kern(GAMMA_PI * x, 0.0, 0);
    }

    let mut y = -x; // x is assumed negative

    let z = y.floor();
    let n: i32;
    if z != y {
        // inexact
        y *= 0.5;
        y = 2.0 * (y - y.floor()); // y = |x| mod 2.0
        n = (y * 4.0) as i32;
    } else {
        // exact integer: use two52 trick
        let z2 = y + GAMMA_TWO52;
        let n_low = (z2.to_bits() & 0xffffffff) as i32;
        let n_bit = n_low & 1;
        y = n_bit as f64;
        n = n_bit << 2;
    }

    let result = match n {
        0 => sin_kern(GAMMA_PI * y, 0.0, 0),
        1 | 2 => cos_kern(GAMMA_PI * (0.5 - y), 0.0),
        3 | 4 => sin_kern(GAMMA_PI * (GAMMA_ONE - y), 0.0, 0),
        5 | 6 => -cos_kern(GAMMA_PI * (y - 1.5), 0.0),
        _ =>     sin_kern(GAMMA_PI * (y - 2.0), 0.0, 0),
    };

    -result
}

/// lgamma with sign pointer — matches __lgamma(x, signgamp).
pub fn lgamma_r(x: f64, signgamp: &mut i32) -> f64 {
    let bits = x.to_bits();
    let hx = (bits >> 32) as i32;
    let lx = (bits & 0xffffffff) as i32;
    let ix = hx & 0x7fffffff;

    *signgamp = 1;

    // inf or NaN: return x*x (inf for inf, NaN for NaN)
    if ix >= 0x7ff00000 {
        return x * x;
    }

    // +-0: pole, return +inf (div-by-zero exception semantics)
    if (ix | lx) == 0 {
        if hx < 0 {
            *signgamp = -1;
        }
        return f64::INFINITY;
    }

    // |x| < 2^-70: return -log(|x|)
    if ix < 0x3b900000 {
        if hx < 0 {
            *signgamp = -1;
            return -(-x).ln();
        } else {
            return -x.ln();
        }
    }

    let mut nadj = 0.0f64;
    let mut x = x;

    if hx < 0 {
        if ix >= 0x43300000 {
            // |x| >= 2^52 — must be negative integer
            return f64::INFINITY;
        }

        let t = sin_pi(x);

        if t == 0.0 {
            // -integer
            return f64::INFINITY;
        }

        nadj = (GAMMA_PI / (t * x).abs()).ln();

        if t < 0.0 {
            *signgamp = -1;
        }

        x = -x;
    }

    let ix2 = ((x.to_bits() >> 32) as i32) & 0x7fffffff;
    let lx2 = (x.to_bits() & 0xffffffff) as i32;

    let r: f64;

    // x == 1 or x == 2
    if (((ix2 - 0x3ff00000) | lx2) == 0) || (((ix2 - 0x40000000) | lx2) == 0) {
        r = 0.0;
    } else if ix2 < 0x40000000 {
        // x < 2.0
        let (i, y_val, r_base): (i32, f64, f64);
        if ix2 <= 0x3feccccc {
            // lgamma(x) = lgamma(x+1) - log(x)
            let r0 = -x.ln();
            if ix2 >= 0x3FE76944 {
                y_val = 1.0 - x;
                i = 0;
            } else if ix2 >= 0x3FCDA661 {
                y_val = x - (TC - 1.0);
                i = 1;
            } else {
                y_val = x;
                i = 2;
            }
            r_base = r0;
        } else {
            r_base = 0.0;
            if ix2 >= 0x3FFBB4C3 {
                y_val = 2.0 - x;
                i = 0;
            } else if ix2 >= 0x3FF3B4C4 {
                y_val = x - TC;
                i = 1;
            } else {
                y_val = x - 1.0;
                i = 2;
            }
        }

        let poly = match i {
            0 => {
                let z = y_val * y_val;
                let p1 = GA0 + z * (GA2 + z * (GA4 + z * (GA6 + z * (GA8 + z * GA10))));
                let p2 = z * (GA1 + z * (GA3 + z * (GA5 + z * (GA7 + z * (GA9 + z * GA11)))));
                let p  = y_val * p1 + p2;
                p - 0.5 * y_val
            }
            1 => {
                let z = y_val * y_val;
                let w = z * y_val;
                let p1 = GT0 + w * (GT3 + w * (GT6 + w * (GT9  + w * GT12)));
                let p2 = GT1 + w * (GT4 + w * (GT7 + w * (GT10 + w * GT13)));
                let p3 = GT2 + w * (GT5 + w * (GT8 + w * (GT11 + w * GT14)));
                let p  = z * p1 - (TT - w * (p2 + y_val * p3));
                TF + p
            }
            _ => {
                let p1 = y_val * (GU0 + y_val * (GU1 + y_val * (GU2 + y_val * (GU3 + y_val * (GU4 + y_val * GU5)))));
                let p2 = 1.0  + y_val * (GV1 + y_val * (GV2 + y_val * (GV3 + y_val * (GV4 + y_val * GV5))));
                -0.5 * y_val + p1 / p2
            }
        };

        r = r_base + poly;
    } else if ix2 < 0x40200000 {
        // 2 <= x < 8
        let i = x as i32;
        let y_val = x - i as f64;
        let p = y_val * (GS0 + y_val * (GS1 + y_val * (GS2 + y_val * (GS3 + y_val * (GS4 + y_val * (GS5 + y_val * GS6))))));
        let q = 1.0  + y_val * (GR1 + y_val * (GR2 + y_val * (GR3 + y_val * (GR4 + y_val * (GR5 + y_val * GR6)))));
        let mut r_val = GAMMA_HALF * y_val + p / q;

        // lgamma(1+s) = log(s) + lgamma(s) — accumulate log factor by fallthrough
        // C: case 7 falls through to 6, 5, 4, 3, default
        let mut z = 1.0f64;
        // replicate C switch-with-fallthrough using >= comparisons
        if i >= 7 { z *= y_val + 6.0; }
        if i >= 6 { z *= y_val + 5.0; }
        if i >= 5 { z *= y_val + 4.0; }
        if i >= 4 { z *= y_val + 3.0; }
        if i >= 3 { z *= y_val + 2.0; }
        r_val += z.ln();

        r = r_val;
    } else if ix2 < 0x43900000 {
        // 8 <= x < 2^58
        let t = x.ln();
        let z = 1.0 / x;
        let y_val = z * z;
        let w = GW0 + z * (GW1 + y_val * (GW2 + y_val * (GW3 + y_val * (GW4 + y_val * (GW5 + y_val * GW6)))));
        r = (x - GAMMA_HALF) * (t - 1.0) + w;
    } else {
        // 2^58 <= x <= inf
        r = x * (x.ln() - 1.0);
    }

    if hx < 0 {
        nadj - r
    } else {
        r
    }
}

// ---------------------------------------------------------------------------
// fpclassifyd
// ---------------------------------------------------------------------------

// FP class constants matching C99 / glibc values
pub const FP_NAN:       i32 = 0;
pub const FP_INFINITE:  i32 = 1;
pub const FP_ZERO:      i32 = 2;
pub const FP_SUBNORMAL: i32 = 3;
pub const FP_NORMAL:    i32 = 4;

pub fn __fpclassifyd(x: f64) -> i32 {
    let bits = x.to_bits();
    let msw = ((bits >> 32) as u32) & 0x7fffffffu32;
    let lsw = (bits & 0xffffffff) as u32;

    if msw == 0x00000000u32 && lsw == 0x00000000u32 {
        FP_ZERO
    } else if msw >= 0x00100000u32 && msw <= 0x7fefffffu32 {
        FP_NORMAL
    } else if msw <= 0x000fffffu32 {
        // zero already handled above; this covers subnormals
        FP_SUBNORMAL
    } else if msw == 0x7ff00000u32 && lsw == 0x00000000u32 {
        FP_INFINITE
    } else {
        FP_NAN
    }
}

// ---------------------------------------------------------------------------
// signbitd
// ---------------------------------------------------------------------------

pub fn __signbitd(x: f64) -> i32 {
    let msw = (x.to_bits() >> 32) as u32;
    if (msw & 0x80000000u32) != 0 { 1 } else { 0 }
}

// ---------------------------------------------------------------------------
// Bessel helpers (besseld.h) — j0_p, j0_q, j1_p, j1_q
// ---------------------------------------------------------------------------

const BESSEL_ONE: f64 = 1.0;
pub const INVSQRTPI: f64 = 5.64189583547756279280e-01; /* 0x3FE20DD7, 0x50429B6D */
pub const TPI:       f64 = 6.36619772367581382433e-01; /* 0x3FE45F30, 0x6DC9C883 */

// --- j0_p tables ---
static J0_PR8: [f64; 6] = [
     0.00000000000000000000e+00,
    -7.03124999999900357484e-02,
    -8.08167041275349795626e+00,
    -2.57063105679704847262e+02,
    -2.48521641009428822144e+03,
    -5.25304380490729545272e+03,
];
static J0_PS8: [f64; 5] = [
    1.16534364619668181717e+02,
    3.83374475364121826715e+03,
    4.05978572648472545552e+04,
    1.16752972564375915681e+05,
    4.76277284146730962675e+04,
];
static J0_PR5: [f64; 6] = [
    -1.14125464691894502584e-11,
    -7.03124940873599280078e-02,
    -4.15961064470587782438e+00,
    -6.76747652265167261021e+01,
    -3.31231299649172967747e+02,
    -3.46433388365604912451e+02,
];
static J0_PS5: [f64; 5] = [
    6.07539382692300335975e+01,
    1.05125230595704579173e+03,
    5.97897094333855784498e+03,
    9.62544514357774460223e+03,
    2.40605815922939109441e+03,
];
static J0_PR3: [f64; 6] = [
    -2.54704601771951915620e-09,
    -7.03119616381481654654e-02,
    -2.40903221549529611423e+00,
    -2.19659774734883086467e+01,
    -5.80791704701737572236e+01,
    -3.14479470594888503854e+01,
];
static J0_PS3: [f64; 5] = [
    3.58560338055209726349e+01,
    3.61513983050303863820e+02,
    1.19360783792111533330e+03,
    1.12799679856907414432e+03,
    1.73580930813335754692e+02,
];
static J0_PR2: [f64; 6] = [
    -8.87534333032526411254e-08,
    -7.03030995483624743247e-02,
    -1.45073846780952986357e+00,
    -7.63569613823527770791e+00,
    -1.11931668860356747786e+01,
    -3.23364579351335335033e+00,
];
static J0_PS2: [f64; 5] = [
    2.22202997532088808441e+01,
    1.36206794218215208048e+02,
    2.70470278658083486789e+02,
    1.53875394208320329881e+02,
    1.46576176948256193810e+01,
];

#[inline]
pub fn j0_p(x: f64) -> f64 {
    let ix = ((x.to_bits() >> 32) as i32) & 0x7fffffff;

    if ix >= 0x41b00000 {
        return BESSEL_ONE;
    }

    let (p, q): (&[f64; 6], &[f64; 5]) = if ix >= 0x40200000 {
        (&J0_PR8, &J0_PS8)
    } else if ix >= 0x40122E8B {
        (&J0_PR5, &J0_PS5)
    } else if ix >= 0x4006DB6D {
        (&J0_PR3, &J0_PS3)
    } else {
        (&J0_PR2, &J0_PS2)
    };

    let z = BESSEL_ONE / (x * x);
    let r = p[0] + z * (p[1] + z * (p[2] + z * (p[3] + z * (p[4] + z * p[5]))));
    let s = BESSEL_ONE + z * (q[0] + z * (q[1] + z * (q[2] + z * (q[3] + z * q[4]))));
    BESSEL_ONE + r / s
}

// --- j0_q tables ---
static J0_QR8: [f64; 6] = [
     0.00000000000000000000e+00,
     7.32421874999935051953e-02,
     1.17682064682252693899e+01,
     5.57673380256401856059e+02,
     8.85919720756468632317e+03,
     3.70146267776887834771e+04,
];
static J0_QS8: [f64; 6] = [
     1.63776026895689824414e+02,
     8.09834494656449805916e+03,
     1.42538291419120476348e+05,
     8.03309257119514397345e+05,
     8.40501579819060512818e+05,
    -3.43899293537866615225e+05,
];
static J0_QR5: [f64; 6] = [
     1.84085963594515531381e-11,
     7.32421766612684765896e-02,
     5.83563508962056953777e+00,
     1.35111577286449829671e+02,
     1.02724376596164097464e+03,
     1.98997785864605384631e+03,
];
static J0_QS5: [f64; 6] = [
     8.27766102236537761883e+01,
     2.07781416421392987104e+03,
     1.88472887785718085070e+04,
     5.67511122894947329769e+04,
     3.59767538425114471465e+04,
    -5.35434275601944773371e+03,
];
static J0_QR3: [f64; 6] = [
     4.37741014089738620906e-09,
     7.32411180042911447163e-02,
     3.34423137516170720929e+00,
     4.26218440745412650017e+01,
     1.70808091340565596283e+02,
     1.66733948696651168575e+02,
];
static J0_QS3: [f64; 6] = [
     4.87588729724587182091e+01,
     7.09689221056606015736e+02,
     3.70414822620111362994e+03,
     6.46042516752568917582e+03,
     2.51633368920368957333e+03,
    -1.49247451836156386662e+02,
];
static J0_QR2: [f64; 6] = [
     1.50444444886983272379e-07,
     7.32234265963079278272e-02,
     1.99819174093815998816e+00,
     1.44956029347885735348e+01,
     3.16662317504781540833e+01,
     1.62527075710929267416e+01,
];
static J0_QS2: [f64; 6] = [
     3.03655848355219184498e+01,
     2.69348118608049844624e+02,
     8.44783757595320139444e+02,
     8.82935845112488550512e+02,
     2.12666388511798828631e+02,
    -5.31095493882666946917e+00,
];

#[inline]
pub fn j0_q(x: f64) -> f64 {
    let ix = ((x.to_bits() >> 32) as i32) & 0x7fffffff;

    if ix >= 0x41b00000 {
        return -0.125 / x;
    }

    let (p, q): (&[f64; 6], &[f64; 6]) = if ix >= 0x40200000 {
        (&J0_QR8, &J0_QS8)
    } else if ix >= 0x40122E8B {
        (&J0_QR5, &J0_QS5)
    } else if ix >= 0x4006DB6D {
        (&J0_QR3, &J0_QS3)
    } else {
        (&J0_QR2, &J0_QS2)
    };

    let z = BESSEL_ONE / (x * x);
    let r = p[0] + z * (p[1] + z * (p[2] + z * (p[3] + z * (p[4] + z * p[5]))));
    let s = BESSEL_ONE + z * (q[0] + z * (q[1] + z * (q[2] + z * (q[3] + z * (q[4] + z * q[5])))));
    (-0.125 + r / s) / x
}

// --- j1_p tables ---
static J1_PR8: [f64; 6] = [
     0.00000000000000000000e+00,
     1.17187499999988647970e-01,
     1.32394806593073575129e+01,
     4.12051854307378562225e+02,
     3.87474538913960532227e+03,
     7.91447954031891731574e+03,
];
static J1_PS8: [f64; 5] = [
    1.14207370375678408436e+02,
    3.65093083420853463394e+03,
    3.69562060269033463555e+04,
    9.76027935934950801311e+04,
    3.08042720627888811578e+04,
];
static J1_PR5: [f64; 6] = [
     1.31990519556243522749e-11,
     1.17187493190614097638e-01,
     6.80275127868432871736e+00,
     1.08308182990189109773e+02,
     5.17636139533199752805e+02,
     5.28715201363337541807e+02,
];
static J1_PS5: [f64; 5] = [
    5.92805987221131331921e+01,
    9.91401418733614377743e+02,
    5.35326695291487976647e+03,
    7.84469031749551231769e+03,
    1.50404688810361062679e+03,
];
static J1_PR3: [f64; 6] = [
    3.02503916137373618024e-09,
    1.17186865567253592491e-01,
    3.93297750033315640650e+00,
    3.51194035591636932736e+01,
    9.10550110750781271918e+01,
    4.85590685197364919645e+01,
];
static J1_PS3: [f64; 5] = [
    3.47913095001251519989e+01,
    3.36762458747825746741e+02,
    1.04687139975775130551e+03,
    8.90811346398256432622e+02,
    1.03787932439639277504e+02,
];
static J1_PR2: [f64; 6] = [
    1.07710830106873743082e-07,
    1.17176219462683348094e-01,
    2.36851496667608785174e+00,
    1.22426109148261232917e+01,
    1.76939711271687727390e+01,
    5.07352312588818499250e+00,
];
static J1_PS2: [f64; 5] = [
    2.14364859363821409488e+01,
    1.25290227168402751090e+02,
    2.32276469057162813669e+02,
    1.17679373287147100768e+02,
    8.36463893371618283368e+00,
];

#[inline]
pub fn j1_p(x: f64) -> f64 {
    let ix = ((x.to_bits() >> 32) as i32) & 0x7fffffff;

    if ix >= 0x41b00000 {
        return BESSEL_ONE;
    }

    let (p, q): (&[f64; 6], &[f64; 5]) = if ix >= 0x40200000 {
        (&J1_PR8, &J1_PS8)
    } else if ix >= 0x40122E8B {
        (&J1_PR5, &J1_PS5)
    } else if ix >= 0x4006DB6D {
        (&J1_PR3, &J1_PS3)
    } else {
        (&J1_PR2, &J1_PS2)
    };

    let z = BESSEL_ONE / (x * x);
    let r = p[0] + z * (p[1] + z * (p[2] + z * (p[3] + z * (p[4] + z * p[5]))));
    let s = BESSEL_ONE + z * (q[0] + z * (q[1] + z * (q[2] + z * (q[3] + z * q[4]))));
    BESSEL_ONE + r / s
}

// --- j1_q tables ---
static J1_QR8: [f64; 6] = [
     0.00000000000000000000e+00,
    -1.02539062499992714161e-01,
    -1.62717534544589987888e+01,
    -7.59601722513950107896e+02,
    -1.18498066702429587167e+04,
    -4.84385124285750353010e+04,
];
static J1_QS8: [f64; 6] = [
     1.61395369700722909556e+02,
     7.82538599923348465381e+03,
     1.33875336287249578163e+05,
     7.19657723683240939863e+05,
     6.66601232617776375264e+05,
    -2.94490264303834643215e+05,
];
static J1_QR5: [f64; 6] = [
    -2.08979931141764104297e-11,
    -1.02539050241375426231e-01,
    -8.05644828123936029840e+00,
    -1.83669607474888380239e+02,
    -1.37319376065508163265e+03,
    -2.61244440453215656817e+03,
];
static J1_QS5: [f64; 6] = [
     8.12765501384335777857e+01,
     1.99179873460485964642e+03,
     1.74684851924908907677e+04,
     4.98514270910352279316e+04,
     2.79480751638918118260e+04,
    -4.71918354795128470869e+03,
];
static J1_QR3: [f64; 6] = [
    -5.07831226461766561369e-09,
    -1.02537829820837089745e-01,
    -4.61011581139473403113e+00,
    -5.78472216562783643212e+01,
    -2.28244540737631695038e+02,
    -2.19210128478909325622e+02,
];
static J1_QS3: [f64; 6] = [
     4.76651550323729509273e+01,
     6.73865112676699709482e+02,
     3.38015286679526343505e+03,
     5.54772909720722782367e+03,
     1.90311919338810798763e+03,
    -1.35201191444307340817e+02,
];
static J1_QR2: [f64; 6] = [
    -1.78381727510958865572e-07,
    -1.02517042607985553460e-01,
    -2.75220568278187460720e+00,
    -1.96636162643703720221e+01,
    -4.23253133372830490089e+01,
    -2.13719211703704061733e+01,
];
static J1_QS2: [f64; 6] = [
     2.95333629060523854548e+01,
     2.52981549982190529136e+02,
     7.57502834868645436472e+02,
     7.39393205320467245656e+02,
     1.55949003336666123687e+02,
    -4.95949898822628210127e+00,
];

#[inline]
pub fn j1_q(x: f64) -> f64 {
    let ix = ((x.to_bits() >> 32) as i32) & 0x7fffffff;

    if ix >= 0x41b00000 {
        return 0.375 / x;
    }

    let (p, q): (&[f64; 6], &[f64; 6]) = if ix >= 0x40200000 {
        (&J1_QR8, &J1_QS8)
    } else if ix >= 0x40122E8B {
        (&J1_QR5, &J1_QS5)
    } else if ix >= 0x4006DB6D {
        (&J1_QR3, &J1_QS3)
    } else {
        (&J1_QR2, &J1_QS2)
    };

    let z = BESSEL_ONE / (x * x);
    let r = p[0] + z * (p[1] + z * (p[2] + z * (p[3] + z * (p[4] + z * p[5]))));
    let s = BESSEL_ONE + z * (q[0] + z * (q[1] + z * (q[2] + z * (q[3] + z * (q[4] + z * q[5])))));
    (0.375 + r / s) / x
}

// ---------------------------------------------------------------------------
// Error-function helpers (errorfunctiond.h)
// ---------------------------------------------------------------------------

const ERF_ONE: f64 = 1.00000000000000000000e+00;

// Coefficients for approximation to erf on [0, 0.84375]
const PP0: f64 =  1.28379167095512558561e-01;
const PP1: f64 = -3.25042107247001499370e-01;
const PP2: f64 = -2.84817495755985104766e-02;
const PP3: f64 = -5.77027029648944159157e-03;
const PP4: f64 = -2.37630166566501626084e-05;
const QQ1: f64 =  3.97917223959155352819e-01;
const QQ2: f64 =  6.50222499887672944485e-02;
const QQ3: f64 =  5.08130628187576562776e-03;
const QQ4: f64 =  1.32494738004321644526e-04;
const QQ5: f64 = -3.96022827877536812320e-06;

// Coefficients for approximation to erf on [0.84375, 1.25]
const PA0: f64 = -2.36211856075265944077e-03;
const PA1: f64 =  4.14856118683748331666e-01;
const PA2: f64 = -3.72207876035701323847e-01;
const PA3: f64 =  3.18346619901161753674e-01;
const PA4: f64 = -1.10894694282396677476e-01;
const PA5: f64 =  3.54783043256182359371e-02;
const PA6: f64 = -2.16637559486879084300e-03;
const QA1: f64 =  1.06420880400844228286e-01;
const QA2: f64 =  5.40397917702171048937e-01;
const QA3: f64 =  7.18286544141962662868e-02;
const QA4: f64 =  1.26171219808761642112e-01;
const QA5: f64 =  1.36370839120290507362e-02;
const QA6: f64 =  1.19844998467991074170e-02;

// Coefficients for approximation to erfc in [1.25, 1/0.35]
const RA0: f64 = -9.86494403484714822705e-03;
const RA1: f64 = -6.93858572707181764372e-01;
const RA2: f64 = -1.05586262253232909814e+01;
const RA3: f64 = -6.23753324503260060396e+01;
const RA4: f64 = -1.62396669462573470355e+02;
const RA5: f64 = -1.84605092906711035994e+02;
const RA6: f64 = -8.12874355063065934246e+01;
const RA7: f64 = -9.81432934416914548592e+00;
const SA1: f64 =  1.96512716674392571292e+01;
const SA2: f64 =  1.37657754143519042600e+02;
const SA3: f64 =  4.34565877475229228821e+02;
const SA4: f64 =  6.45387271733267880336e+02;
const SA5: f64 =  4.29008140027567833386e+02;
const SA6: f64 =  1.08635005541779435134e+02;
const SA7: f64 =  6.57024977031928170135e+00;
const SA8: f64 = -6.04244152148580987438e-02;

// Coefficients for approximation to erfc in [1/0.35, 28]
const RB0: f64 = -9.86494292470009928597e-03;
const RB1: f64 = -7.99283237680523006574e-01;
const RB2: f64 = -1.77579549177547519889e+01;
const RB3: f64 = -1.60636384855821916062e+02;
const RB4: f64 = -6.37566443368389627722e+02;
const RB5: f64 = -1.02509513161107724954e+03;
const RB6: f64 = -4.83519191608651397019e+02;
const SB1: f64 =  3.03380607434824582924e+01;
const SB2: f64 =  3.25792512996573918826e+02;
const SB3: f64 =  1.53672958608443695994e+03;
const SB4: f64 =  3.19985821950859553908e+03;
const SB5: f64 =  2.55305040643316442583e+03;
const SB6: f64 =  4.74528541206955367215e+02;
const SB7: f64 = -2.24409524465858183362e+01;

#[inline]
pub fn erf_y(x: f64) -> f64 {
    let z = x * x;
    let r = PP0 + z * (PP1 + z * (PP2 + z * (PP3 + z * PP4)));
    let s = ERF_ONE + z * (QQ1 + z * (QQ2 + z * (QQ3 + z * (QQ4 + z * QQ5))));
    r / s
}

#[inline]
pub fn erf_p(s: f64) -> f64 {
    PA0 + s * (PA1 + s * (PA2 + s * (PA3 + s * (PA4 + s * (PA5 + s * PA6)))))
}

#[inline]
pub fn erf_q(s: f64) -> f64 {
    ERF_ONE + s * (QA1 + s * (QA2 + s * (QA3 + s * (QA4 + s * (QA5 + s * QA6)))))
}

#[inline]
pub fn erf_ra(s: f64) -> f64 {
    RA0 + s * (RA1 + s * (RA2 + s * (RA3 + s * (RA4 + s * (RA5 + s * (RA6 + s * RA7))))))
}

#[inline]
pub fn erf_sa(s: f64) -> f64 {
    ERF_ONE + s * (SA1 + s * (SA2 + s * (SA3 + s * (SA4 + s * (SA5 + s * (SA6 + s * (SA7 + s * SA8)))))))
}

#[inline]
pub fn erf_rb(s: f64) -> f64 {
    RB0 + s * (RB1 + s * (RB2 + s * (RB3 + s * (RB4 + s * (RB5 + s * RB6)))))
}

#[inline]
pub fn erf_sb(s: f64) -> f64 {
    ERF_ONE + s * (SB1 + s * (SB2 + s * (SB3 + s * (SB4 + s * (SB5 + s * (SB6 + s * SB7))))))
}

// ---------------------------------------------------------------------------
// log1pmf helper (log1pmfd.h)
// Return log(1+f) - f for 1+f in ~[sqrt(2)/2, sqrt(2)].
// ---------------------------------------------------------------------------

const LG1: f64 = 6.666666666666735130e-01; /* 0x3FE5555555555593 */
const LG2: f64 = 3.999999999940941908e-01; /* 0x3FD999999997FA04 */
const LG3: f64 = 2.857142874366239149e-01; /* 0x3FD2492494229359 */
const LG4: f64 = 2.222219843214978396e-01; /* 0x3FCC71C51D8E78AF */
const LG5: f64 = 1.818357216161805012e-01; /* 0x3FC7466496CB03DE */
const LG6: f64 = 1.531383769920937332e-01; /* 0x3FC39A09D078C69F */
const LG7: f64 = 1.479819860511658591e-01; /* 0x3FC2F112DF3E5244 */

#[inline]
pub fn log1pmf(f: f64) -> f64 {
    let s = f / (2.0 + f);
    let z = s * s;
    let w = z * z;
    let t1 = w * (LG2 + w * (LG4 + w * LG6));
    let t2 = z * (LG1 + w * (LG3 + w * (LG5 + w * LG7)));
    let r  = t2 + t1;
    let hfsq = 0.5 * f * f;
    s * (hfsq + r)
}

/// Alias for log1pmf, used by log2d/log10d/log1pd from batch2.
#[inline]
fn log1pmf_d(f: f64) -> f64 { log1pmf(f) }

// ===========================================================================
// Public functions — from batch1 (acosd through erfcd)
// ===========================================================================

// ============================================================
// acosd.c → acosd
// ============================================================

pub fn acosd(x: f64) -> f64 {
    const ONE: f64      =  1.00000000000000000000e+00;
    const PI: f64       =  3.14159265358979311600e+00;
    const PIO2_HI: f64  =  1.57079632679489655800e+00;
    const PIO2_LO: f64  =  6.12323399573676603587e-17;
    const PS0: f64      =  1.66666666666666657415e-01;
    const PS1: f64      = -3.25565818622400915405e-01;
    const PS2: f64      =  2.01212532134862925881e-01;
    const PS3: f64      = -4.00555345006794114027e-02;
    const PS4: f64      =  7.91534994289814532176e-04;
    const PS5: f64      =  3.47933107596021167570e-05;
    const QS1: f64      = -2.40339491173441421878e+00;
    const QS2: f64      =  2.02094576023350569471e+00;
    const QS3: f64      = -6.88283971605453293030e-01;
    const QS4: f64      =  7.70381505559019352791e-02;

    let hx = (x.to_bits() >> 32) as u32 as i32;
    let ix = hx & 0x7fffffff;

    if ix >= 0x3ff00000 {
        let lx = (x.to_bits() & 0xffffffff) as u32;
        if ((ix - 0x3ff00000) as u32 | lx) == 0 {
            if hx > 0 {
                return 0.0;
            } else {
                return PI;
            }
        }
        if x.is_nan() {
            return x + x;
        }
        return f64::NAN;
    }

    if ix < 0x3fe00000 {
        if ix <= 0x3c600000 {
            return PIO2_HI;
        }
        let z = x * x;
        let p = z * (PS0 + z * (PS1 + z * (PS2 + z * (PS3 + z * (PS4 + z * PS5)))));
        let q = ONE + z * (QS1 + z * (QS2 + z * (QS3 + z * QS4)));
        let r = p / q;
        return PIO2_HI - (x - (PIO2_LO - x * r));
    } else if hx < 0 {
        let z = (ONE + x) * 0.5;
        let p = z * (PS0 + z * (PS1 + z * (PS2 + z * (PS3 + z * (PS4 + z * PS5)))));
        let q = ONE + z * (QS1 + z * (QS2 + z * (QS3 + z * QS4)));
        let s = z.sqrt();
        let r = p / q;
        let w = r * s - PIO2_LO;
        return PI - 2.0 * (s + w);
    } else {
        let z = (ONE - x) * 0.5;
        let s = z.sqrt();
        let mut df = s;
        df = f64::from_bits(df.to_bits() & 0xffffffff00000000);
        let c = (z - df * df) / (s + df);
        let p = z * (PS0 + z * (PS1 + z * (PS2 + z * (PS3 + z * (PS4 + z * PS5)))));
        let q = ONE + z * (QS1 + z * (QS2 + z * (QS3 + z * QS4)));
        let r = p / q;
        let w = r * s + c;
        return 2.0 * (df + w);
    }
}

// ============================================================
// acoshd.c → acoshd
// ============================================================

pub fn acoshd(x: f64) -> f64 {
    const ONE: f64 = 1.0;
    const LN2: f64 = 6.93147180559945286227e-01;

    let bits = x.to_bits();
    let hx = (bits >> 32) as u32 as i32;
    let lx = (bits & 0xffffffff) as u32;

    if hx < 0x3ff00000_u32 as i32 {
        if x.is_nan() {
            return x + x;
        } else {
            return f64::NAN;
        }
    } else if hx >= 0x41b00000_u32 as i32 {
        if hx >= 0x7ff00000_u32 as i32 {
            return x + x;
        } else {
            return x.ln() + LN2;
        }
    } else if ((hx - 0x3ff00000) as u32 | lx) == 0 {
        return 0.0;
    } else if hx > 0x40000000_u32 as i32 {
        let t = x * x;
        return (2.0 * x - ONE / (x + (t - ONE).sqrt())).ln();
    } else {
        let t = x - ONE;
        return (t + (2.0 * t + t * t).sqrt()).ln_1p();
    }
}

// ============================================================
// asind.c → asind
// ============================================================

pub fn asind(x: f64) -> f64 {
    const ONE: f64     =  1.00000000000000000000e+00;
    const PIO2_HI: f64 =  1.57079632679489655800e+00;
    const PIO2_LO: f64 =  6.12323399573676603587e-17;
    const PIO4_HI: f64 =  7.85398163397448278999e-01;
    const PS0: f64     =  1.66666666666666657415e-01;
    const PS1: f64     = -3.25565818622400915405e-01;
    const PS2: f64     =  2.01212532134862925881e-01;
    const PS3: f64     = -4.00555345006794114027e-02;
    const PS4: f64     =  7.91534994289814532176e-04;
    const PS5: f64     =  3.47933107596021167570e-05;
    const QS1: f64     = -2.40339491173441421878e+00;
    const QS2: f64     =  2.02094576023350569471e+00;
    const QS3: f64     = -6.88283971605453293030e-01;
    const QS4: f64     =  7.70381505559019352791e-02;

    let hx = (x.to_bits() >> 32) as u32 as i32;
    let ix = hx & 0x7fffffff;

    if ix >= 0x3ff00000 {
        let lx = (x.to_bits() & 0xffffffff) as u32;
        if ((ix - 0x3ff00000) as u32 | lx) == 0 {
            return x * PIO2_HI + x * PIO2_LO;
        }
        if x.is_nan() {
            return x + x;
        }
        return f64::NAN;
    } else if ix < 0x3fe00000 {
        if ix < 0x3e500000 {
            if x == 0.0 {
                return x;
            } else {
                return x;
            }
        } else {
            let t = x * x;
            let p = t * (PS0 + t * (PS1 + t * (PS2 + t * (PS3 + t * (PS4 + t * PS5)))));
            let q = ONE + t * (QS1 + t * (QS2 + t * (QS3 + t * QS4)));
            let w = p / q;
            return x + x * w;
        }
    }

    // 1 > |x| >= 0.5
    let w = ONE - x.abs();
    let t = w * 0.5;
    let p = t * (PS0 + t * (PS1 + t * (PS2 + t * (PS3 + t * (PS4 + t * PS5)))));
    let q = ONE + t * (QS1 + t * (QS2 + t * (QS3 + t * QS4)));
    let s = t.sqrt();

    let t2;
    if ix >= 0x3FEF3333 {
        let w2 = p / q;
        t2 = PIO2_HI - (2.0 * (s + s * w2) - PIO2_LO);
    } else {
        let mut w2 = s;
        w2 = f64::from_bits(w2.to_bits() & 0xffffffff00000000);
        let c = (t - w2 * w2) / (s + w2);
        let r = p / q;
        let pp = 2.0 * s * r - (PIO2_LO - 2.0 * c);
        let qq = PIO4_HI - 2.0 * w2;
        t2 = PIO4_HI - (pp - qq);
    }

    if hx > 0 { t2 } else { -t2 }
}

// ============================================================
// asinhd.c → asinhd
// ============================================================

pub fn asinhd(x: f64) -> f64 {
    const ONE: f64 = 1.00000000000000000000e+00;
    const LN2: f64 = 6.93147180559945286227e-01;

    let hx = (x.to_bits() >> 32) as u32 as i32;
    let ix = hx & 0x7fffffff;

    if ix >= 0x7ff00000 {
        return x + x;
    }

    if ix < 0x3e300000 {
        if x == 0.0 {
            return x;
        } else {
            return x;
        }
    }

    let w;
    if ix > 0x41b00000 {
        w = x.abs().ln() + LN2;
    } else if ix > 0x40000000 {
        let t = x.abs();
        w = (2.0 * t + ONE / ((x * x + ONE).sqrt() + t)).ln();
    } else {
        let t = x * x;
        w = (x.abs() + t / (ONE + (ONE + t).sqrt())).ln_1p();
    }

    if hx > 0 { w } else { -w }
}

// ============================================================
// atand.c → atand
// ============================================================

pub fn atand(x: f64) -> f64 {
    const ATANHI: [f64; 4] = [
        4.63647609000806093515e-01,
        7.85398163397448278999e-01,
        9.82793723247329054082e-01,
        1.57079632679489655800e+00,
    ];
    const ATANLO: [f64; 4] = [
        2.26987774529616870924e-17,
        3.06161699786838301793e-17,
        1.39033110312309984516e-17,
        6.12323399573676603587e-17,
    ];
    const AT: [f64; 11] = [
         3.33333333333329318027e-01,
        -1.99999999998764832476e-01,
         1.42857142725034663711e-01,
        -1.11111104054623557880e-01,
         9.09088713343650656196e-02,
        -7.69187620504482999495e-02,
         6.66107313738753120669e-02,
        -5.83357013379057348645e-02,
         4.97687799461593236017e-02,
        -3.65315727442169155270e-02,
         1.62858201153657823623e-02,
    ];
    const ONE: f64 = 1.0;

    let hx = (x.to_bits() >> 32) as u32 as i32;
    let ix = hx & 0x7fffffff;
    let mut x = x;

    if ix >= 0x44100000 {
        let low = (x.to_bits() & 0xffffffff) as u32;
        if ix > 0x7ff00000 || (ix == 0x7ff00000 && low != 0) {
            return x + x; // NaN
        }
        if hx > 0 {
            return ATANHI[3];
        } else {
            return -ATANHI[3];
        }
    }

    let id: i32;
    if ix < 0x3fdc0000 {
        if ix < 0x3e400000 {
            if x == 0.0 {
                return x;
            } else {
                return x;
            }
        }
        id = -1;
    } else {
        x = x.abs();
        if ix < 0x3ff30000 {
            if ix < 0x3fe60000 {
                id = 0;
                x = (2.0 * x - ONE) / (2.0 + x);
            } else {
                id = 1;
                x = (x - ONE) / (x + ONE);
            }
        } else {
            if ix < 0x40038000 {
                id = 2;
                x = (x - 1.5) / (ONE + 1.5 * x);
            } else {
                id = 3;
                x = -1.0 / x;
            }
        }
    }

    let z = x * x;
    let w = z * z;
    let s1 = z * (AT[0] + w * (AT[2] + w * (AT[4] + w * (AT[6] + w * (AT[8] + w * AT[10])))));
    let s2 = w * (AT[1] + w * (AT[3] + w * (AT[5] + w * (AT[7] + w * AT[9]))));

    if id < 0 {
        return x - x * (s1 + s2);
    } else {
        let z = ATANHI[id as usize] - ((x * (s1 + s2) - ATANLO[id as usize]) - x);
        return if hx < 0 { -z } else { z };
    }
}

// ============================================================
// atan2d.c → atan2d
// ============================================================

pub fn atan2d(y: f64, x: f64) -> f64 {
    const ZERO: f64  = 0.0;
    const PI_O_4: f64 = 7.8539816339744827900e-01;
    const PI_O_2: f64 = 1.5707963267948965580e+00;
    const PI: f64    = 3.1415926535897931160e+00;
    const PI_LO: f64 = 1.2246467991473531772e-16;

    let hx = (x.to_bits() >> 32) as u32 as i32;
    let lx = (x.to_bits() & 0xffffffff) as u32;
    let ix = hx & 0x7fffffff;
    let hy = (y.to_bits() >> 32) as u32 as i32;
    let ly = (y.to_bits() & 0xffffffff) as u32;
    let iy = hy & 0x7fffffff;

    let lx_nz = ((lx as i32).wrapping_neg() as u32 | lx) >> 31;
    let ly_nz = ((ly as i32).wrapping_neg() as u32 | ly) >> 31;
    if (ix as u32 | lx_nz) > 0x7ff00000 || (iy as u32 | ly_nz) > 0x7ff00000 {
        return x + y;
    }

    if hx == 0x3ff00000_u32 as i32 && lx == 0 {
        return atand(y);
    }

    let m = ((hy >> 31) & 1) | ((hx >> 30) & 2);

    if (iy as u32 | ly) == 0 {
        match m {
            0 | 1 => return y,
            2     => return PI,
            _     => return -PI,
        }
    }

    if (ix as u32 | lx) == 0 {
        return if hy < 0 { -PI_O_2 } else { PI_O_2 };
    }

    if ix == 0x7ff00000 {
        if iy == 0x7ff00000 {
            match m {
                0 => return  PI_O_4,
                1 => return -PI_O_4,
                2 => return  3.0 * PI_O_4,
                _ => return -3.0 * PI_O_4,
            }
        } else {
            match m {
                0 => return  ZERO,
                1 => return -ZERO,
                2 => return  PI,
                _ => return -PI,
            }
        }
    }

    if iy == 0x7ff00000 {
        return if hy < 0 { -PI_O_2 } else { PI_O_2 };
    }

    let k = (iy - ix) >> 20;
    let z;
    let mut m2 = m;
    if k > 60 {
        z = PI_O_2;
        m2 &= 1;
    } else if hx < 0 && k < -60 {
        z = 0.0;
    } else {
        z = atand((y / x).abs());
    }

    match m2 {
        0 => z,
        1 => -z,
        2 => PI - (z - PI_LO),
        _ => (z - PI_LO) - PI,
    }
}

// ============================================================
// atanhd.c → atanhd
// ============================================================

pub fn atanhd(x: f64) -> f64 {
    const ONE: f64 = 1.0;

    let bits = x.to_bits();
    let hx = (bits >> 32) as u32 as i32;
    let lx = (bits & 0xffffffff) as u32;
    let ix = hx & 0x7fffffff;

    let lx_nz = (lx as u32 | (lx as i32).wrapping_neg() as u32) >> 31;
    if (ix as u32 | lx_nz) > 0x3ff00000 {
        if x.is_nan() {
            return x + x;
        } else {
            return f64::NAN;
        }
    }

    if ix == 0x3ff00000 {
        return if x.is_sign_negative() { f64::NEG_INFINITY } else { f64::INFINITY };
    }

    if ix < 0x3e300000 {
        if x == 0.0 {
            return x;
        } else {
            return x;
        }
    }

    let mut x2 = f64::from_bits((x.to_bits() & 0xffffffff) | ((ix as u64) << 32));

    let t;
    if ix < 0x3fe00000 {
        let tt = x2 + x2;
        t = 0.5 * (tt + tt * x2 / (ONE - x2)).ln_1p();
    } else {
        t = 0.5 * ((x2 + x2) / (ONE - x2)).ln_1p();
    }

    if hx >= 0 { t } else { -t }
}

// ============================================================
// cbrtd.c → cbrtd
// ============================================================

pub fn cbrtd(x: f64) -> f64 {
    const B1: u32 = 715094163;
    const B2: u32 = 696219795;
    const C: f64  =  5.42857142857142815906e-01;
    const D: f64  = -7.05306122448979611050e-01;
    const E: f64  =  1.41428571428571436819e+00;
    const F: f64  =  1.60714285714285720630e+00;
    const G: f64  =  3.57142857142857150787e-01;

    let hx_raw = (x.to_bits() >> 32) as u32;
    let sign = hx_raw & 0x80000000u32;
    let hx = (hx_raw ^ sign) as u32;

    if hx >= 0x7ff00000 {
        return x + x;
    }

    let low = (x.to_bits() & 0xffffffff) as u32;
    if (hx | low) == 0 {
        return x;
    }

    let mut x2 = f64::from_bits((x.to_bits() & 0xffffffff) | ((hx as u64) << 32));

    let mut t: f64;
    if hx < 0x00100000 {
        t = f64::from_bits((0x43500000u64) << 32);
        t *= x2;
        let high2 = (t.to_bits() >> 32) as u32;
        t = f64::from_bits(((high2 / 3 + B2) as u64) << 32);
    } else {
        t = f64::from_bits(((hx / 3 + B1) as u64) << 32);
    }

    let r = t * t / x2;
    let s = C + r * t;
    t *= G + F / (s + E + D / s);

    let high3 = (t.to_bits() >> 32) as u32;
    t = f64::from_bits(((high3 + 0x00000001u32) as u64) << 32);

    let s2 = t * t;
    let r2 = x2 / s2;
    let w = t + t;
    let r3 = (r2 - t) / (w + r2);
    t = t + t * r3;

    let high4 = (t.to_bits() >> 32) as u32;
    t = f64::from_bits(((high4 | sign) as u64) << 32 | (t.to_bits() & 0xffffffff));
    t
}

// ============================================================
// ceild.c → ceild
// ============================================================

pub fn ceild(x: f64) -> f64 {
    let bits = x.to_bits();
    let mut _i0 = (bits >> 32) as u32 as i32;
    let mut _i1 = (bits & 0xffffffff) as u32 as i32;
    let _j0 = ((_i0 >> 20) & 0x7ff) - 0x3ff;

    if _j0 < 20 {
        if _j0 < 0 {
            if ((_i0 & 0x7fffffff) | _i1) == 0 {
                return x;
            }
            let _ = x;
            if _i0 < 0 {
                _i0 = 0x80000000u32 as i32;
                _i1 = 0;
            } else {
                _i0 = 0x3ff00000;
                _i1 = 0;
            }
        } else {
            let i: u32 = 0x000fffff >> _j0;
            if ((_i0 as u32 & i) | (_i1 as u32)) == 0 {
                return x;
            }
            let _ = x;
            if _i0 > 0 {
                _i0 += (0x00100000i32) >> _j0;
            }
            _i0 &= !(i as i32);
            _i1 = 0;
        }
    } else if _j0 > 51 {
        if _j0 == 0x400 {
            return x + x;
        } else {
            return x;
        }
    } else {
        let i: u32 = (0xffffffffu32) >> (_j0 - 20);
        if (_i1 as u32 & i) == 0 {
            return x;
        }
        let _ = x;
        if _i0 > 0 {
            if _j0 == 20 {
                _i0 += 1;
            } else {
                let j: u32 = (_i1 as u32).wrapping_add(1u32 << (52 - _j0));
                if j < _i1 as u32 {
                    _i0 += 1;
                }
                _i1 = j as i32;
            }
        }
        _i1 &= !(i as i32);
    }

    f64::from_bits(((_i0 as u64) << 32) | (_i1 as u64 & 0xffffffff))
}

// ============================================================
// copysignd.c → copysignd
// ============================================================

pub fn copysignd(x: f64, y: f64) -> f64 {
    let hx = (x.to_bits() >> 32) as u32;
    let hy = (y.to_bits() >> 32) as u32;
    let new_hi = (hx & 0x7fffffffu32) | (hy & 0x80000000u32);
    f64::from_bits(((new_hi as u64) << 32) | (x.to_bits() & 0xffffffff))
}

// ============================================================
// cosd.c → cosd
// ============================================================

pub fn cosd(x: f64) -> f64 {
    let mut y = [0.0f64; 2];
    let z: f64 = 0.0;

    let ix = ((x.to_bits() >> 32) as u32 as i32) & 0x7fffffff;

    if ix <= 0x3fe921fb {
        if ix < 0x3e46a09e {
            if x == 0.0 {
                return 1.0;
            } else {
                return 1.0;
            }
        }
        return cos_kern(x, z);
    } else if ix >= 0x7ff00000 {
        if x.is_nan() {
            return x + x;
        } else {
            return f64::NAN;
        }
    } else {
        let n = rem_pio2(x, &mut y);
        match n & 3 {
            0 =>  cos_kern(y[0], y[1]),
            1 => -sin_kern(y[0], y[1], 1),
            2 => -cos_kern(y[0], y[1]),
            _ =>  sin_kern(y[0], y[1], 1),
        }
    }
}

// ============================================================
// coshd.c → coshd
// ============================================================

pub fn coshd(x: f64) -> f64 {
    const ONE: f64  = 1.0;
    const HALF: f64 = 0.5;

    let ix = ((x.to_bits() >> 32) as u32 as i32) & 0x7fffffff;

    if ix >= 0x7ff00000 {
        return x * x;
    }

    if ix < 0x3fd62e43 {
        let t = x.abs().exp_m1();
        let w = ONE + t;
        if ix < 0x3c800000 {
            return w;
        }
        return ONE + (t * t) / (w + w);
    }

    if ix < 0x40360000 {
        let t = x.abs().exp();
        return HALF * t + HALF / t;
    }

    if ix < 0x40862E42 {
        return HALF * x.abs().exp();
    }

    let lx = (x.to_bits() & 0xffffffff) as u32;
    if ix < 0x408633CE || (ix == 0x408633ce_u32 as i32 && lx <= 0x8fb9f87du32) {
        let w = (HALF * x.abs()).exp();
        let t = HALF * w;
        return t * w;
    }

    f64::INFINITY
}

// ============================================================
// erfd.c → erfd
// ============================================================

pub fn erfd(x: f64) -> f64 {
    const ERX: f64  =  8.45062911510467529297e-01;
    const EFX: f64  =  1.28379167095512586316e-01;
    const EFX8: f64 =  1.02703333676410069053e+00;
    const ONE: f64  =  1.00000000000000000000e+00;

    let hx = (x.to_bits() >> 32) as u32 as i32;
    let ix = hx & 0x7fffffff;

    if ix >= 0x7ff00000 {
        if x.is_nan() {
            return x + x;
        } else if hx > 0 {
            return 1.0;
        } else {
            return -1.0;
        }
    }

    if ix < 0x3feb0000 {
        if ix < 0x3e300000 {
            if ix < 0x00800000 {
                return 0.125 * (8.0 * x + EFX8 * x);
            }
            return x + EFX * x;
        }
        return x + x * erf_y(x);
    }

    if ix < 0x3ff40000 {
        let s = x.abs() - ONE;
        let p = erf_p(s);
        let q = erf_q(s);
        if hx >= 0 {
            return ERX + p / q;
        } else {
            return -ERX - p / q;
        }
    }

    if ix >= 0x40180000 {
        if hx >= 0 {
            return ONE;
        } else {
            return -ONE;
        }
    }

    let x2 = x.abs();
    let s = ONE / (x2 * x2);
    let r_val;
    let s_val;
    if ix < 0x4006DB6E {
        r_val = erf_ra(s);
        s_val = erf_sa(s);
    } else {
        r_val = erf_rb(s);
        s_val = erf_sb(s);
    }

    let mut z = x2;
    z = f64::from_bits(z.to_bits() & 0xffffffff00000000);
    let r2 = (-z * z - 0.5625f64).exp() * ((z - x2) * (z + x2) + r_val / s_val).exp();

    if hx >= 0 {
        ONE - r2 / x2
    } else {
        r2 / x2 - ONE
    }
}

// ============================================================
// erfcd.c → erfcd
// ============================================================

pub fn erfcd(x: f64) -> f64 {
    const HALF: f64 =  5.00000000000000000000e-01;
    const TWO: f64  =  2.00000000000000000000e+00;
    const ERX: f64  =  8.45062911510467529297e-01;
    const ONE: f64  =  1.00000000000000000000e+00;

    let hx = (x.to_bits() >> 32) as u32 as i32;
    let ix = hx & 0x7fffffff;

    if ix >= 0x7ff00000 {
        if x.is_nan() {
            return x + x;
        } else if hx > 0 {
            return 0.0;
        } else {
            return TWO;
        }
    }

    if ix < 0x3feb0000 {
        if ix < 0x3c700000 {
            return ONE;
        }
        let y = erf_y(x);
        if hx < 0x3fd00000_u32 as i32 {
            return ONE - (x + x * y);
        } else {
            let r = x * y;
            let r2 = r + (x - HALF);
            return HALF - r2;
        }
    }

    if ix < 0x3ff40000 {
        let s = x.abs() - ONE;
        let p = erf_p(s);
        let q = erf_q(s);
        if hx >= 0 {
            let z = ONE - ERX;
            return z - p / q;
        } else {
            let z = ERX + p / q;
            return ONE + z;
        }
    }

    if ix < 0x403c0000 {
        let x2 = x.abs();
        let s = ONE / (x2 * x2);
        let r_val;
        let s_val;
        if ix < 0x4006DB6D {
            r_val = erf_ra(s);
            s_val = erf_sa(s);
        } else {
            if hx < 0 && ix >= 0x40180000 {
                return TWO;
            }
            r_val = erf_rb(s);
            s_val = erf_sb(s);
        }
        let mut z = x2;
        z = f64::from_bits(z.to_bits() & 0xffffffff00000000);
        let r2 = (-z * z - 0.5625f64).exp() * ((z - x2) * (z + x2) + r_val / s_val).exp();
        if hx > 0 {
            r2 / x2
        } else {
            TWO - r2 / x2
        }
    } else {
        if hx > 0 {
            0.0f64
        } else {
            TWO
        }
    }
}

// ===========================================================================
// Public functions — from batch2 (exp2d through logbd)
// ===========================================================================

// ── exp2d ────────────────────────────────────────────────────────────────────

pub fn exp2d(x: f64) -> f64 {
    powd(2.0, x)
}

// ── expd ─────────────────────────────────────────────────────────────────────

pub fn expd(x: f64) -> f64 {
    const ONE: f64 = 1.0;
    const ZERO: f64 = 0.0;
    const HALF: [f64; 2] = [0.5, -0.5];
    const TWOM1000: f64 = 9.33263618503218878990e-302;
    const O_THRESHOLD: f64 = 7.09782712893383973096e+02;
    const U_THRESHOLD: f64 = -7.45133219101941108420e+02;
    const LN2HI: [f64; 2] = [6.93147180369123816490e-01, -6.93147180369123816490e-01];
    const LN2LO: [f64; 2] = [1.90821492927058770002e-10, -1.90821492927058770002e-10];
    const INVLN2: f64 = 1.44269504088896338700e+00;
    const P1: f64 = 1.66666666666666019037e-01;
    const P2: f64 = -2.77777777770155933842e-03;
    const P3: f64 = 6.61375632143793436117e-05;
    const P4: f64 = -1.65339022054652515390e-06;
    const P5: f64 = 4.13813679705723846039e-08;

    let bits = x.to_bits();
    let hx = (bits >> 32) as u32;
    let xsb = ((hx >> 31) & 1) as usize;
    let hx = hx & 0x7fffffff;

    if hx >= 0x40862E42 {
        if hx >= 0x7ff00000 {
            let lx = (bits & 0xffffffff) as u32;
            if ((hx & 0xfffff) | lx) != 0 {
                return x + x;
            } else {
                return if xsb == 0 { x } else { ZERO };
            }
        }
        if x > O_THRESHOLD {
            return f64::INFINITY;
        }
        if x < U_THRESHOLD {
            return 0.0f64;
        }
    }

    let mut x = x;
    let mut hi = 0.0f64;
    let mut lo = 0.0f64;
    let mut k: i32 = 0;

    if hx > 0x3fd62e42 {
        if hx < 0x3FF0A2B2 {
            hi = x - LN2HI[xsb];
            lo = LN2LO[xsb];
            k = 1 - (xsb as i32) - (xsb as i32);
        } else {
            k = (INVLN2 * x + HALF[xsb]) as i32;
            let t = k as f64;
            hi = x - t * LN2HI[0];
            lo = t * LN2LO[0];
        }
        x = hi - lo;
    } else if hx < 0x3df00000 {
        if x == 0.0 {
            return ONE;
        } else {
            return ONE + x;
        }
    }

    let t = x * x;
    let c = x - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));

    if k == 0 {
        return ONE - ((x * c) / (c - 2.0) - x);
    }

    let mut y = ONE - ((lo - (x * c) / (2.0 - c)) - hi);

    if k >= -1021 {
        let hy = (y.to_bits() >> 32) as u32;
        let new_hy = hy.wrapping_add((k as u32) << 20);
        y = f64::from_bits((y.to_bits() & 0xffffffff) | ((new_hy as u64) << 32));
        return y;
    } else {
        let hy = (y.to_bits() >> 32) as u32;
        let new_hy = hy.wrapping_add(((k as u32).wrapping_add(1000u32)) << 20);
        y = f64::from_bits((y.to_bits() & 0xffffffff) | ((new_hy as u64) << 32));
        return y * TWOM1000;
    }
}

// ── expm1d ───────────────────────────────────────────────────────────────────

pub fn expm1d(x: f64) -> f64 {
    const ONE: f64 = 1.0;
    const O_THRESHOLD: f64 = 7.09782712893383973096e+02;
    const LN2_HI: f64 = 6.93147180369123816490e-01;
    const LN2_LO: f64 = 1.90821492927058770002e-10;
    const INVLN2: f64 = 1.44269504088896338700e+00;
    const Q1: f64 = -3.33333333333331316428e-02;
    const Q2: f64 = 1.58730158725481460165e-03;
    const Q3: f64 = -7.93650757867487942473e-05;
    const Q4: f64 = 4.00821782732936239552e-06;
    const Q5: f64 = -2.01099218183624371326e-07;

    let bits = x.to_bits();
    let hx_orig = (bits >> 32) as u32;
    let xsb = hx_orig & 0x80000000u32;
    let hx = hx_orig & 0x7fffffff;

    if hx >= 0x4043687A {
        if hx >= 0x40862E42 {
            if hx >= 0x7ff00000 {
                let low = (bits & 0xffffffff) as u32;
                if ((hx & 0xfffff) | low) != 0 {
                    return x + x;
                } else {
                    return if xsb == 0 { x } else { -1.0 };
                }
            }
            if x > O_THRESHOLD {
                return f64::INFINITY;
            }
        }
        if xsb != 0 {
            return -(ONE);
        }
    }

    let mut x = x;
    let mut hi = 0.0f64;
    let mut lo = 0.0f64;
    let mut c = 0.0f64;
    let mut k: i32;

    if hx > 0x3fd62e42 {
        if hx < 0x3FF0A2B2 {
            if xsb == 0 {
                hi = x - LN2_HI;
                lo = LN2_LO;
                k = 1;
            } else {
                hi = x + LN2_HI;
                lo = -LN2_LO;
                k = -1;
            }
        } else {
            k = (INVLN2 * x + if xsb == 0 { 0.5 } else { -0.5 }) as i32;
            let t = k as f64;
            hi = x - t * LN2_HI;
            lo = t * LN2_LO;
        }
        x = hi - lo;
        c = (hi - x) - lo;
    } else if hx < 0x3c900000 {
        if x == 0.0 {
            return x;
        } else {
            return x;
        }
    } else {
        k = 0;
    }

    let hfx = 0.5 * x;
    let hxs = x * hfx;
    let r1 = ONE + hxs * (Q1 + hxs * (Q2 + hxs * (Q3 + hxs * (Q4 + hxs * Q5))));
    let t = 3.0 - r1 * hfx;
    let e = hxs * ((r1 - t) / (6.0 - x * t));

    if k == 0 {
        return x - (x * e - hxs);
    }

    let e2 = (x * (e - c) - c) - hxs;

    if k == -1 {
        return 0.5 * (x - e2) - 0.5;
    }

    if k == 1 {
        if x < -0.25 {
            return -2.0 * (e2 - (x + 0.5));
        } else {
            return ONE + 2.0 * (x - e2);
        }
    }

    let mut y: f64;
    if k <= -2 || k > 56 {
        y = ONE - (e2 - x);
        let high = (y.to_bits() >> 32) as u32;
        let new_high = high.wrapping_add((k as u32) << 20);
        y = f64::from_bits((y.to_bits() & 0xffffffff) | ((new_high as u64) << 32));
        return y - ONE;
    }

    let mut t_val: f64;
    if k < 20 {
        let hw = 0x3ff00000u32 - (0x200000u32 >> k);
        t_val = f64::from_bits((hw as u64) << 32);
        y = t_val - (e2 - x);
        let high = (y.to_bits() >> 32) as u32;
        let new_high = high.wrapping_add((k as u32) << 20);
        y = f64::from_bits((y.to_bits() & 0xffffffff) | ((new_high as u64) << 32));
    } else {
        let hw = ((0x3ff - k) as u32) << 20;
        t_val = f64::from_bits((hw as u64) << 32);
        y = x - (e2 + t_val);
        y += ONE;
        let high = (y.to_bits() >> 32) as u32;
        let new_high = high.wrapping_add((k as u32) << 20);
        y = f64::from_bits((y.to_bits() & 0xffffffff) | ((new_high as u64) << 32));
    }

    y
}

// ── fabsd ────────────────────────────────────────────────────────────────────

pub fn fabsd(x: f64) -> f64 {
    let bits = x.to_bits();
    let high = (bits >> 32) as u32 & 0x7fffffffu32;
    f64::from_bits(((high as u64) << 32) | (bits & 0xffffffff))
}

// ── fdimd ────────────────────────────────────────────────────────────────────

pub fn fdimd(x: f64, y: f64) -> f64 {
    if x.is_nan() || y.is_nan() {
        return x * y;
    }
    if x > y { x - y } else { 0.0 }
}

// ── floord ───────────────────────────────────────────────────────────────────

pub fn floord(x: f64) -> f64 {
    let bits = x.to_bits();
    let i0 = (bits >> 32) as i32;
    let i1 = (bits & 0xffffffff) as u32;
    let j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;

    let mut _i0 = i0;
    let mut _i1 = i1;

    if j0 < 20 {
        if j0 < 0 {
            if ((_i0 & 0x7fffffff) | _i1 as i32) == 0 {
                return x;
            }
            if _i0 >= 0 {
                _i0 = 0;
                _i1 = 0;
            } else {
                _i0 = 0xbff00000u32 as i32;
                _i1 = 0;
            }
        } else {
            let i: u32 = 0x000fffffu32 >> j0;
            if ((_i0 as u32 & i) | _i1) == 0 {
                return x;
            }
            if _i0 < 0 {
                _i0 = _i0.wrapping_add((0x00100000i32) >> j0);
            }
            _i0 &= !(i as i32);
            _i1 = 0;
        }
    } else if j0 > 51 {
        if j0 == 0x400 {
            return x + x;
        } else {
            return x;
        }
    } else {
        let i: u32 = 0xffffffffu32 >> (j0 - 20);
        if (_i1 & i) == 0 {
            return x;
        }
        if _i0 < 0 {
            if j0 == 20 {
                _i0 += 1;
            } else {
                let j = _i1.wrapping_add(1u32 << (52 - j0));
                if j < _i1 {
                    _i0 += 1;
                }
                _i1 = j;
            }
        }
        _i1 &= !i;
    }

    f64::from_bits(((_i0 as u32 as u64) << 32) | (_i1 as u64))
}

// ── fmad ─────────────────────────────────────────────────────────────────────

pub fn fmad(x: f64, y: f64, z: f64) -> f64 {
    x * y + z
}

// ── fmaxd ────────────────────────────────────────────────────────────────────

pub fn fmaxd(x: f64, y: f64) -> f64 {
    if x.is_nan() {
        let xbits = x.to_bits();
        let ybits = y.to_bits();
        let x_sig = (xbits & (1u64 << 51)) == 0 && (xbits & 0x7ff0000000000000u64) == 0x7ff0000000000000u64 && (xbits & 0x000fffffffffffffu64) != 0;
        let y_sig = y.is_nan() && (ybits & (1u64 << 51)) == 0 && (ybits & 0x7ff0000000000000u64) == 0x7ff0000000000000u64 && (ybits & 0x000fffffffffffffu64) != 0;
        if x_sig || y_sig {
            return x * y;
        }
        return y;
    }
    if y.is_nan() {
        let ybits = y.to_bits();
        let y_sig = (ybits & (1u64 << 51)) == 0 && (ybits & 0x7ff0000000000000u64) == 0x7ff0000000000000u64 && (ybits & 0x000fffffffffffffu64) != 0;
        if y_sig {
            return x * y;
        }
        return x;
    }
    if x > y { x } else { y }
}

// ── fmind ────────────────────────────────────────────────────────────────────

pub fn fmind(x: f64, y: f64) -> f64 {
    if x.is_nan() {
        let xbits = x.to_bits();
        let ybits = y.to_bits();
        let x_sig = (xbits & (1u64 << 51)) == 0 && (xbits & 0x7ff0000000000000u64) == 0x7ff0000000000000u64 && (xbits & 0x000fffffffffffffu64) != 0;
        let y_sig = y.is_nan() && (ybits & (1u64 << 51)) == 0 && (ybits & 0x7ff0000000000000u64) == 0x7ff0000000000000u64 && (ybits & 0x000fffffffffffffu64) != 0;
        if x_sig || y_sig {
            return x * y;
        }
        return y;
    }
    if y.is_nan() {
        let ybits = y.to_bits();
        let y_sig = (ybits & (1u64 << 51)) == 0 && (ybits & 0x7ff0000000000000u64) == 0x7ff0000000000000u64 && (ybits & 0x000fffffffffffffu64) != 0;
        if y_sig {
            return x * y;
        }
        return x;
    }
    if x < y { x } else { y }
}

// ── fmodd ────────────────────────────────────────────────────────────────────

pub fn fmodd(x: f64, y: f64) -> f64 {
    let zero_arr: [f64; 2] = [0.0, -0.0];

    let xbits = x.to_bits();
    let ybits = y.to_bits();

    let mut hx = (xbits >> 32) as i32;
    let mut lx = (xbits & 0xffffffff) as u32;
    let mut hy = (ybits >> 32) as i32;
    let mut ly = (ybits & 0xffffffff) as u32;

    let sx = (hx as u32) & 0x80000000u32;
    hx ^= sx as i32;
    hy &= 0x7fffffff;

    if (hx as u32) >= 0x7ff00000 || (hy as u32) >= 0x7ff00000 {
        if hx as u32 == 0x7ff00000 && lx == 0 {
            return f64::NAN;
        } else if x.is_nan() || y.is_nan() {
            return x + y;
        }
    } else if (hy as u32 | ly) == 0 {
        return f64::NAN;
    }

    if hx <= hy {
        if (hx < hy) || (lx < ly) {
            return x;
        }
        if lx == ly {
            return zero_arr[(sx >> 31) as usize];
        }
    }

    let mut ix: i32;
    if (hx as u32) < 0x00100000 {
        if hx == 0 {
            ix = -1043;
            let mut i = lx;
            while i > 0 {
                ix -= 1;
                i <<= 1;
            }
        } else {
            ix = -1022;
            let mut i = (hx as u32) << 11;
            while (i as i32) > 0 {
                ix -= 1;
                i <<= 1;
            }
        }
    } else {
        ix = ((hx as u32) >> 20) as i32 - 1023;
    }

    let mut iy: i32;
    if (hy as u32) < 0x00100000 {
        if hy == 0 {
            iy = -1043;
            let mut i = ly;
            while i > 0 {
                iy -= 1;
                i <<= 1;
            }
        } else {
            iy = -1022;
            let mut i = (hy as u32) << 11;
            while (i as i32) > 0 {
                iy -= 1;
                i <<= 1;
            }
        }
    } else {
        iy = ((hy as u32) >> 20) as i32 - 1023;
    }

    if ix >= -1022 {
        hx = (0x00100000 | (0x000fffff & hx as u32)) as i32;
    } else {
        let n = -1022 - ix;
        if n <= 31 {
            hx = ((hx as u32) << n | lx >> (32 - n)) as i32;
            lx <<= n;
        } else {
            hx = (lx << (n - 32)) as i32;
            lx = 0;
        }
    }

    if iy >= -1022 {
        hy = (0x00100000 | (0x000fffff & hy as u32)) as i32;
    } else {
        let n = -1022 - iy;
        if n <= 31 {
            hy = ((hy as u32) << n | ly >> (32 - n)) as i32;
            ly <<= n;
        } else {
            hy = (ly << (n - 32)) as i32;
            ly = 0;
        }
    }

    let mut n = ix - iy;

    while n > 0 {
        n -= 1;
        let hz = hx - hy;
        let lz = lx.wrapping_sub(ly);
        let borrow = if lx < ly { 1i32 } else { 0i32 };
        let hz = hz - borrow;
        if hz < 0 {
            hx = hx + hx + (lx >> 31) as i32;
            lx = lx + lx;
        } else {
            if (hz | lz as i32) == 0 {
                return zero_arr[(sx >> 31) as usize];
            }
            hx = hz + hz + (lz >> 31) as i32;
            lx = lz + lz;
        }
    }

    let hz = hx - hy;
    let lz = lx.wrapping_sub(ly);
    let borrow = if lx < ly { 1i32 } else { 0i32 };
    let hz = hz - borrow;

    if hz >= 0 {
        hx = hz;
        lx = lz;
    }

    if (hx as u32 | lx) == 0 {
        return zero_arr[(sx >> 31) as usize];
    }

    while (hx as u32) < 0x00100000 {
        hx = hx + hx + (lx >> 31) as i32;
        lx = lx + lx;
        iy -= 1;
    }

    if iy >= -1022 {
        let hx2 = ((hx as u32 - 0x00100000) | (((iy + 1023) as u32) << 20)) | sx;
        return f64::from_bits(((hx2 as u64) << 32) | lx as u64);
    } else {
        let n = -1022 - iy;
        if n <= 20 {
            lx = (lx >> n) | ((hx as u32) << (32 - n));
            hx = (hx as u32 >> n) as i32;
        } else if n <= 31 {
            lx = ((hx as u32) << (32 - n)) | (lx >> n);
            hx = sx as i32;
        } else {
            lx = (hx as u32) >> (n - 32);
            hx = sx as i32;
        }
        let hx2 = (hx as u32) | sx;
        return f64::from_bits(((hx2 as u64) << 32) | lx as u64);
    }
}

// ── frexpd ───────────────────────────────────────────────────────────────────

pub fn frexpd(x: f64, exp: &mut i32) -> f64 {
    const TWO54: f64 = 1.80143985094819840000e+16;

    let bits = x.to_bits();
    let hx = (bits >> 32) as i32;
    let lx = (bits & 0xffffffff) as i32;
    let ix = 0x7fffffff & hx;

    *exp = 0;

    if ix >= 0x7ff00000 || ((ix | lx) == 0) {
        return x + x;
    }

    let mut x = x;
    let mut hx = hx;
    let mut ix = ix;

    if ix < 0x00100000 {
        x *= TWO54;
        hx = (x.to_bits() >> 32) as i32;
        ix = hx & 0x7fffffff;
        *exp = -54;
    }

    *exp += (ix >> 20) - 1022;
    let new_hx = ((hx as u32) & 0x800fffffu32) | 0x3fe00000u32;
    let new_bits = ((new_hx as u64) << 32) | (x.to_bits() & 0xffffffff);
    f64::from_bits(new_bits)
}

// ── hypotd ───────────────────────────────────────────────────────────────────

pub fn hypotd(x: f64, y: f64) -> f64 {
    let ha_orig = ((x.to_bits() >> 32) as i32) & 0x7fffffff;
    let hb_orig = ((y.to_bits() >> 32) as i32) & 0x7fffffff;

    let (mut a, mut b, mut ha, mut hb) = if hb_orig > ha_orig {
        (y, x, hb_orig, ha_orig)
    } else {
        (x, y, ha_orig, hb_orig)
    };

    a = f64::from_bits(((ha as u32 as u64) << 32) | (a.to_bits() & 0xffffffff));
    b = f64::from_bits(((hb as u32 as u64) << 32) | (b.to_bits() & 0xffffffff));

    if (ha - hb) > 0x3c00000 {
        return a + b;
    }

    let mut k = 0i32;

    if ha > 0x5f300000 {
        if ha >= 0x7ff00000 {
            let mut w = a + b;
            let low_a = (a.to_bits() & 0xffffffff) as u32;
            if ((ha as u32) & 0xfffff) | low_a == 0 {
                w = a;
            }
            let low_b = (b.to_bits() & 0xffffffff) as u32;
            if ((hb as u32) ^ 0x7ff00000) | low_b == 0 {
                w = b;
            }
            return w;
        }
        ha -= 0x25800000;
        hb -= 0x25800000;
        k += 600;
        a = f64::from_bits(((ha as u32 as u64) << 32) | (a.to_bits() & 0xffffffff));
        b = f64::from_bits(((hb as u32 as u64) << 32) | (b.to_bits() & 0xffffffff));
    }

    if hb < 0x20b00000 {
        if hb <= 0x000fffff {
            let low = (b.to_bits() & 0xffffffff) as u32;
            if ((hb as u32) | low) == 0 {
                return a;
            }
            let t1 = f64::from_bits(0x7fd00000u64 << 32);
            b *= t1;
            a *= t1;
            k -= 1022;
        } else {
            ha += 0x25800000;
            hb += 0x25800000;
            k -= 600;
            a = f64::from_bits(((ha as u32 as u64) << 32) | (a.to_bits() & 0xffffffff));
            b = f64::from_bits(((hb as u32 as u64) << 32) | (b.to_bits() & 0xffffffff));
        }
    }

    let w2 = a - b;
    let result_w: f64;

    if w2 > b {
        let t1 = f64::from_bits(((ha as u32 as u64) << 32));
        let t2 = a - t1;
        result_w = (t1 * t1 - (b * (-b) - t2 * (a + t1))).sqrt();
    } else {
        let a2 = a + a;
        let y1 = f64::from_bits(((hb as u32 as u64) << 32));
        let y2 = b - y1;
        let t1 = f64::from_bits((((ha as u32).wrapping_add(0x00100000)) as u64) << 32);
        let t2 = a2 - t1;
        result_w = (t1 * y1 - (w2 * (-w2) - (t1 * y2 + t2 * b))).sqrt();
    }

    if k != 0 {
        let scale = f64::from_bits((((0x3FFu32 + k as u32) << 20) as u64) << 32);
        scale * result_w
    } else {
        result_w
    }
}

// ── ilogbd ───────────────────────────────────────────────────────────────────

pub fn ilogbd(x: f64) -> i32 {
    let bits = x.to_bits();
    let mut hx = (bits >> 32) as i32 & 0x7fffffff;
    let mut lx = (bits & 0xffffffff) as u32;

    if (hx as u32) < 0x00100000 {
        if (hx as u32 | lx) == 0 {
            return i32::MIN;
        } else if hx == 0 {
            let mut ix = -1043i32;
            while lx > 0 {
                ix -= 1;
                lx <<= 1;
            }
            return ix;
        } else {
            let mut ix = -1022i32;
            let mut hx2 = (hx as u32) << 11;
            while (hx2 as i32) > 0 {
                ix -= 1;
                hx2 <<= 1;
            }
            return ix;
        }
    } else if (hx as u32) < 0x7ff00000 {
        return (hx >> 20) - 1023;
    } else if (hx as u32) > 0x7ff00000 {
        return i32::MAX;
    } else {
        return i32::MAX;
    }
}

// ── ldexpd ───────────────────────────────────────────────────────────────────

pub fn ldexpd(x: f64, exp: i32) -> f64 {
    if !x.is_finite() || x == 0.0 {
        return x + x;
    }
    scalbn_inner(x, exp)
}

// ── logd ─────────────────────────────────────────────────────────────────────

pub fn logd(x: f64) -> f64 {
    const LN2_HI: f64 = 6.93147180369123816490e-01;
    const LN2_LO: f64 = 1.90821492927058770002e-10;
    const TWO54: f64 = 1.80143985094819840000e+16;
    const ZERO: f64 = 0.0;

    let mut xbits = x.to_bits();
    let mut hx = (xbits >> 32) as i32;
    let lx = (xbits & 0xffffffff) as u32;
    let mut x = x;
    let mut k: i32 = 0;

    if hx < 0x00100000 {
        if ((hx & 0x7fffffff) as u32 | lx) == 0 {
            return f64::NEG_INFINITY;
        }
        if hx < 0 {
            if x.is_nan() {
                return x + x;
            } else {
                return f64::NAN;
            }
        }
        k -= 54;
        x *= TWO54;
        xbits = x.to_bits();
        hx = (xbits >> 32) as i32;
    }

    if hx >= 0x7ff00000 {
        return x + x;
    }

    k += (hx >> 20) - 1023;
    hx &= 0x000fffff;
    let i = (hx + 0x95f64) & 0x100000;
    x = f64::from_bits((((hx as u32 | (i as u32 ^ 0x3ff00000)) as u64) << 32) | (x.to_bits() & 0xffffffff));
    k += i >> 20;
    let f = x - 1.0;

    if (0x000fffff & (2 + hx)) < 3 {
        if f == ZERO {
            if k == 0 {
                return ZERO;
            } else {
                let dk = k as f64;
                return dk * LN2_HI + dk * LN2_LO;
            }
        }
        let r2 = f * f * (0.5 - 0.33333333333333333 * f);
        if k == 0 {
            return f - r2;
        } else {
            let dk = k as f64;
            return dk * LN2_HI - ((r2 - dk * LN2_LO) - f);
        }
    }

    let s = f / (2.0 + f);
    let dk = k as f64;
    let z = s * s;
    let i2 = hx - 0x6147a;
    let w = z * z;
    let j = 0x6b851 - hx;
    let t1 = w * (LG2 + w * (LG4 + w * LG6));
    let t2 = z * (LG1 + w * (LG3 + w * (LG5 + w * LG7)));
    let i3 = i2 | j;
    let r3 = t2 + t1;

    if i3 > 0 {
        let hfsq = 0.5 * f * f;
        if k == 0 {
            return f - (hfsq - s * (hfsq + r3));
        } else {
            return dk * LN2_HI - ((hfsq - (s * (hfsq + r3) + dk * LN2_LO)) - f);
        }
    } else {
        if k == 0 {
            return f - s * (f - r3);
        } else {
            return dk * LN2_HI - ((s * (f - r3) - dk * LN2_LO) - f);
        }
    }
}

// ── log2d ────────────────────────────────────────────────────────────────────

pub fn log2d(x: f64) -> f64 {
    const TWO54: f64 = 1.80143985094819840000e+16;
    const IVLN2HI: f64 = 1.44269504072144627571e+00;
    const IVLN2LO: f64 = 1.67517131648865118353e-10;
    const ZERO: f64 = 0.0;

    let mut xbits = x.to_bits();
    let mut hx = (xbits >> 32) as i32;
    let lx = (xbits & 0xffffffff) as u32;
    let mut x = x;
    let mut k: i32 = 0;

    if hx < 0x00100000 {
        if ((hx & 0x7fffffff) as u32 | lx) == 0 {
            return f64::NEG_INFINITY;
        }
        if hx < 0 {
            if x.is_nan() {
                return x + x;
            } else {
                return f64::NAN;
            }
        }
        k -= 54;
        x *= TWO54;
        xbits = x.to_bits();
        hx = (xbits >> 32) as i32;
    }

    if hx >= 0x7ff00000 {
        return x + x;
    }

    if hx == 0x3ff00000 && lx == 0 {
        return ZERO;
    }

    k += (hx >> 20) - 1023;
    hx &= 0x000fffff;
    let i = (hx + 0x95f64) & 0x100000;
    x = f64::from_bits((((hx as u32 | (i as u32 ^ 0x3ff00000)) as u64) << 32) | (x.to_bits() & 0xffffffff));
    k += i >> 20;
    let y = k as f64;
    let f = x - 1.0;
    let hfsq = 0.5 * f * f;
    let r = log1pmf_d(f);

    let mut hi = f - hfsq;
    hi = f64::from_bits(hi.to_bits() & 0xffffffff00000000u64);
    let lo = (f - hi) - hfsq + r;
    let val_hi = hi * IVLN2HI;
    let val_lo = (lo + hi) * IVLN2LO + lo * IVLN2HI;

    let w = y + val_hi;
    let val_lo2 = val_lo + (y - w) + val_hi;
    let val_hi2 = w;

    val_lo2 + val_hi2
}

// ── log10d ───────────────────────────────────────────────────────────────────

pub fn log10d(x: f64) -> f64 {
    const TWO54: f64 = 1.80143985094819840000e+16;
    const IVLN10HI: f64 = 4.34294481878168880939e-01;
    const IVLN10LO: f64 = 2.50829467116452752298e-11;
    const LOG10_2HI: f64 = 3.01029995663611771306e-01;
    const LOG10_2LO: f64 = 3.69423907715893078616e-13;
    const ZERO: f64 = 0.0;

    let mut xbits = x.to_bits();
    let mut hx = (xbits >> 32) as i32;
    let lx = (xbits & 0xffffffff) as u32;
    let mut x = x;
    let mut k: i32 = 0;

    if hx < 0x00100000 {
        if ((hx & 0x7fffffff) as u32 | lx) == 0 {
            return f64::NEG_INFINITY;
        }
        if hx < 0 {
            if x.is_nan() {
                return x + x;
            } else {
                return f64::NAN;
            }
        }
        k -= 54;
        x *= TWO54;
        xbits = x.to_bits();
        hx = (xbits >> 32) as i32;
    }

    if hx >= 0x7ff00000 {
        return x + x;
    }

    if hx == 0x3ff00000 && lx == 0 {
        return ZERO;
    }

    k += (hx >> 20) - 1023;
    hx &= 0x000fffff;
    let i = (hx + 0x95f64) & 0x100000;
    x = f64::from_bits((((hx as u32 | (i as u32 ^ 0x3ff00000)) as u64) << 32) | (x.to_bits() & 0xffffffff));
    k += i >> 20;
    let y = k as f64;
    let f = x - 1.0;
    let hfsq = 0.5 * f * f;
    let r = log1pmf_d(f);

    let mut hi = f - hfsq;
    hi = f64::from_bits(hi.to_bits() & 0xffffffff00000000u64);
    let lo = (f - hi) - hfsq + r;
    let val_hi = hi * IVLN10HI;
    let y2 = y * LOG10_2HI;
    let val_lo = y * LOG10_2LO + (lo + hi) * IVLN10LO + lo * IVLN10HI;

    let w = y2 + val_hi;
    let val_lo2 = val_lo + (y2 - w) + val_hi;
    let val_hi2 = w;

    val_lo2 + val_hi2
}

// ── log1pd ───────────────────────────────────────────────────────────────────

pub fn log1pd(x: f64) -> f64 {
    const LN2_HI: f64 = 6.93147180369123816490e-01;
    const LN2_LO: f64 = 1.90821492927058770002e-10;
    const ZERO: f64 = 0.0;

    let xbits = x.to_bits();
    let hx = (xbits >> 32) as i32;
    let ax = hx & 0x7fffffff;

    let mut k: i32 = 1;
    let mut c = 0.0f64;
    let mut f = 0.0f64;
    let mut hu: i32 = i32::MAX;

    if hx >= 0x7ff00000 {
        return x + x;
    }

    if hx < 0x3FDA827A {
        if (ax as u32) >= 0x3ff00000 {
            if x.is_nan() {
                return x + x;
            } else if x == -1.0 {
                return f64::NEG_INFINITY;
            } else {
                return f64::NAN;
            }
        }

        if (ax as u32) < 0x3e200000 {
            if (ax as u32) < 0x3c900000 {
                return x;
            } else {
                return x - x * x * 0.5;
            }
        }

        if hx > 0 || hx <= (0xbfd2bec3u32 as i32) {
            k = 0;
            f = x;
            hu = 1;
        }
    }

    let mut x = x;
    if k != 0 {
        if hx < 0x43400000 {
            let u = 1.0 + x;
            hu = (u.to_bits() >> 32) as i32;
            k = (hu >> 20) - 1023;
            c = if k > 0 { 1.0 - (u - x) } else { x - (u - 1.0) };
            c /= u;
            x = u;
        } else {
            hu = (x.to_bits() >> 32) as i32;
            k = (hu >> 20) - 1023;
            c = 0.0;
        }

        hu &= 0x000fffff;

        if hu < 0x6a09e {
            x = f64::from_bits((((hu as u32 | 0x3ff00000u32) as u64) << 32) | (x.to_bits() & 0xffffffff));
        } else {
            k += 1;
            x = f64::from_bits((((hu as u32 | 0x3fe00000u32) as u64) << 32) | (x.to_bits() & 0xffffffff));
            hu = (0x00100000 - hu as u32) as i32 >> 2;
        }

        f = x - 1.0;
    }

    let hfsq = 0.5 * f * f;

    if hu == 0 {
        if f == ZERO {
            c += (k as f64) * LN2_LO;
            return (k as f64) * LN2_HI + c;
        }
        let r = hfsq * (1.0 - 0.66666666666666666 * f);
        return (k as f64) * LN2_HI - ((r - ((k as f64) * LN2_LO + c)) - f);
    }

    if k == 0 {
        return f - (hfsq - log1pmf_d(f));
    } else {
        return (k as f64) * LN2_HI - ((hfsq - (log1pmf_d(f) + ((k as f64) * LN2_LO + c))) - f);
    }
}

// ── logbd ────────────────────────────────────────────────────────────────────

pub fn logbd(x: f64) -> f64 {
    let bits = x.to_bits();
    let mut hx = (bits >> 32) as i32 & 0x7fffffff;
    let mut lx = (bits & 0xffffffff) as u32;

    if (hx as u32) < 0x00100000 {
        if ((hx as u32) | lx) == 0 {
            return f64::NEG_INFINITY;
        } else if hx == 0 {
            let mut ix = -1043i32;
            while lx > 0 {
                ix -= 1;
                lx <<= 1;
            }
            return ix as f64;
        } else {
            let mut ix = -1022i32;
            let mut hx2 = (hx as u32) << 11;
            while (hx2 as i32) > 0 {
                ix -= 1;
                hx2 <<= 1;
            }
            return ix as f64;
        }
    } else if (hx as u32) < 0x7ff00000 {
        return ((hx >> 20) - 1023) as f64;
    } else {
        return x * x;
    }
}

// ===========================================================================
// Public functions — from batch3 (j0d through ynd)
// ===========================================================================

pub fn j0d(x: f64) -> f64 {
    const R02: f64 =  1.56249999999999947958e-02;
    const R03: f64 = -1.89979294238854721751e-04;
    const R04: f64 =  1.82954049532700665670e-06;
    const R05: f64 = -4.61832688532103189199e-09;
    const S01: f64 =  1.56191029464890010492e-02;
    const S02: f64 =  1.16926784663337450260e-04;
    const S03: f64 =  5.13546550207318111446e-07;
    const S04: f64 =  1.16614003333790000205e-09;

    let hx = (x.to_bits() >> 32) as i32;
    let ix = hx & 0x7fffffff;
    if ix >= 0x7ff00000 { return 1.0 / (x * x); }
    let x = x.abs();
    if ix >= 0x40000000 {
        let s = x.sin(); let c = x.cos();
        let mut ss = s - c; let mut cc = s + c;
        if ix < 0x7fe00000 {
            let z = -(x + x).cos();
            if s * c < 0.0 { cc = z / ss; } else { ss = z / cc; }
        }
        return if ix > 0x48000000 {
            (INVSQRTPI * cc) / x.sqrt()
        } else {
            INVSQRTPI * (j0_p(x) * cc - j0_q(x) * ss) / x.sqrt()
        };
    }
    if ix < 0x3f200000 {
        return if ix < 0x3e400000 { 1.0 } else { 1.0 - 0.25 * x * x };
    }
    let z = x * x;
    let r = z * (R02 + z*(R03 + z*(R04 + z*R05)));
    let s = 1.0 + z*(S01 + z*(S02 + z*(S03 + z*S04)));
    if ix < 0x3ff00000 {
        1.0 + z * (-0.25 + r / s)
    } else {
        let u = 0.5 * x;
        (1.0 + u) * (1.0 - u) + z * (r / s)
    }
}

pub fn j1d(x: f64) -> f64 {
    const R00: f64 = -6.25000000000000000000e-02;
    const R01: f64 =  1.40705666955189706048e-03;
    const R02: f64 = -1.59955631084035597520e-05;
    const R03: f64 =  4.96727999609584448412e-08;
    const S01: f64 =  1.91537599538363460805e-02;
    const S02: f64 =  1.85946785588630915560e-04;
    const S03: f64 =  1.17718464042623683263e-06;
    const S04: f64 =  5.04636257076217042715e-09;
    const S05: f64 =  1.23542274426137913908e-11;

    let hx = (x.to_bits() >> 32) as i32;
    let ix = hx & 0x7fffffff;
    if ix >= 0x7ff00000 { return 1.0 / x; }
    let y = x.abs();
    if ix >= 0x40000000 {
        let s = y.sin(); let c = y.cos();
        let mut ss = -s - c; let mut cc = s - c;
        if ix < 0x7fe00000 {
            let z = (y + y).cos();
            if s * c > 0.0 { cc = z / ss; } else { ss = z / cc; }
        }
        let z = if ix > 0x48000000 {
            (INVSQRTPI * cc) / y.sqrt()
        } else {
            INVSQRTPI * (j1_p(y) * cc - j1_q(y) * ss) / y.sqrt()
        };
        return if hx < 0 { -z } else { z };
    }
    if ix < 0x3e400000 { return 0.5 * x; }
    let z = x * x;
    let r = z * (R00 + z*(R01 + z*(R02 + z*R03)));
    let s = 1.0 + z*(S01 + z*(S02 + z*(S03 + z*(S04 + z*S05))));
    x * 0.5 + (r * x) / s
}

pub fn jnd(n: i32, x: f64) -> f64 {
    let bits = x.to_bits();
    let mut hx = (bits >> 32) as i32;
    let lx = (bits & 0xffffffff) as u32;
    let ix = 0x7fffffff & hx;

    if ((ix as u32) | (lx | lx.wrapping_neg()) >> 31) > 0x7ff00000 {
        return x + x;
    }

    let mut n = n;
    let mut x = x;

    if n < 0 {
        n = -n;
        x = -x;
        hx ^= 0x80000000u32 as i32;
    }

    if n == 0 { return j0d(x); }
    if n == 1 { return j1d(x); }

    let sgn = (n & 1) & (hx >> 31);
    let x = x.abs();

    let b = if (ix as u32 | lx) == 0 || ix >= 0x7ff00000 {
        0.0f64
    } else if (n as f64) <= x {
        if ix >= 0x52d00000 {
            let temp = match n & 3 {
                0 => x.cos() + x.sin(),
                1 => -x.cos() + x.sin(),
                2 => -x.cos() - x.sin(),
                _ => x.cos() - x.sin(),
            };
            INVSQRTPI * temp / x.sqrt()
        } else {
            let mut a = j0d(x);
            let mut b = j1d(x);
            for i in 1..n {
                let temp = b;
                b = b * ((2 * i) as f64 / x) - a;
                a = temp;
            }
            b
        }
    } else if ix < 0x3e100000 {
        if n > 33 {
            0.0f64
        } else {
            let temp = x * 0.5;
            let mut b = temp;
            let mut a = 1.0f64;
            for i in 2..=n {
                a *= i as f64;
                b *= temp;
            }
            b / a
        }
    } else {
        let w = (n + n) as f64 / x;
        let h = 2.0 / x;
        let mut q0 = w;
        let z = w + h;
        let mut q1 = w * z - 1.0;
        let mut k = 1i32;
        loop {
            if q1 >= 1.0e9 { break; }
            k += 1;
            let z2 = w + (k as f64) * h;
            let tmp = z2 * q1 - q0;
            q0 = q1;
            q1 = tmp;
        }

        let m = n + n;
        let mut t = 0.0f64;
        let mut i = 2 * (n + k);
        while i >= m {
            t = 1.0 / (i as f64 / x - t);
            i -= 2;
        }

        let mut a = t;
        let mut b_val = 1.0f64;

        let tmp_n = n as f64;
        let v = 2.0 / x;
        let tmp_val = tmp_n * (v * tmp_n).abs().ln();

        if tmp_val < 7.09782712893383973096e+02 {
            let mut di = ((n - 1) * 2) as f64;
            let mut ii = n - 1;
            while ii > 0 {
                let temp = b_val;
                b_val = b_val * di / x - a;
                a = temp;
                di -= 2.0;
                ii -= 1;
            }
        } else {
            let mut di = ((n - 1) * 2) as f64;
            let mut ii = n - 1;
            while ii > 0 {
                let temp = b_val;
                b_val = b_val * di / x - a;
                a = temp;
                di -= 2.0;
                if b_val > 1e100 { a /= b_val; t /= b_val; b_val = 1.0; }
                ii -= 1;
            }
        }

        t * j0d(x) / b_val
    };

    if sgn != 0 { -b } else { b }
}

pub fn lgammad(x: f64) -> f64 {
    let mut s = 0i32;
    let r = lgamma_r(x, &mut s);
    SIGNGAM.with(|sg| sg.set(s));
    r
}

pub fn llrintd(x: f64) -> i64 {
    const TWO52P: f64 = 4.50359962737049600000e+15;
    const TWO52N: f64 = -4.50359962737049600000e+15;

    let bits = x.to_bits();
    let mut i0 = (bits >> 32) as i32;
    let mut i1 = (bits & 0xffffffff) as u32;
    let sx = ((i0 >> 31) & 1) as usize;
    let two52 = if sx == 0 { TWO52P } else { TWO52N };
    let mut j0 = ((i0 & 0x7ff00000) >> 20) - 1023;

    if j0 < 20 {
        if j0 < -1 { return 0; }
        let w = two52 + x;
        let t = w - two52;
        i0 = (t.to_bits() >> 32) as i32;
        if (i0 & !(1i32 << 31)) == 0 { return 0; }
        j0 = ((i0 & 0x7ff00000) >> 20) - 1023;
        i0 &= 0x000fffff;
        i0 |= 0x00100000;
        let result = (i0 >> (20 - j0)) as i64;
        return if sx != 0 { -result } else { result };
    } else if (j0 as u32) < 63 {
        if j0 >= 52 {
            let result = ((((i0 & 0x000fffff) | 0x00100000) as i64) << (j0 - 20))
                | ((i1 as i64) << (j0 - 52));
            return if sx != 0 { -result } else { result };
        } else {
            let w = two52 + x;
            let t = w - two52;
            let tb = t.to_bits();
            i0 = (tb >> 32) as i32;
            i1 = (tb & 0xffffffff) as u32;
            j0 = ((i0 & 0x7ff00000) >> 20) - 1023;
            i0 &= 0x000fffff;
            i0 |= 0x00100000;
            let shift_r = 52 - j0;
            let i1s = if shift_r >= 32 { 0u32 } else { i1 >> shift_r };
            let result = ((i0 as i64) << (j0 - 20)) | (i1s as i64);
            return if sx != 0 { -result } else { result };
        }
    } else {
        return if sx != 0 { i64::MIN } else { i64::MAX };
    }
}

pub fn llroundd(x: f64) -> i64 {
    let bits = x.to_bits();
    let msw_orig = (bits >> 32) as u32;
    let lsw = (bits & 0xffffffff) as u32;
    let sign: i64 = if (msw_orig & 0x80000000) != 0 { -1 } else { 1 };
    let exp = ((msw_orig & 0x7ff00000) >> 20) as i32 - 1023;
    let mut msw = (msw_orig & 0x000fffff) | 0x00100000;

    if exp < 20 {
        if exp < 0 { return if exp < -1 { 0 } else { sign }; }
        msw = msw.wrapping_add(0x80000 >> exp);
        ((msw >> (20 - exp)) as i64) * sign
    } else if (exp as u32) < 63 {
        if exp >= 52 {
            let result = ((msw as i64) << (exp - 20)) | ((lsw as i64) << (exp - 52));
            result * sign
        } else {
            let mut lsw2 = lsw;
            let tmp = lsw2.wrapping_add(0x80000000u32 >> (exp - 20));
            if tmp < lsw2 { msw = msw.wrapping_add(1); }
            lsw2 = tmp;
            let shift_r = 52 - exp;
            let lsw_s = if shift_r >= 32 { 0u32 } else { lsw2 >> shift_r };
            let result = ((msw as i64) << (exp - 20)) | (lsw_s as i64);
            result * sign
        }
    } else {
        if sign < 0 { i64::MIN } else { i64::MAX }
    }
}

pub fn lrintd(x: f64) -> i64 { llrintd(x) }

pub fn lroundd(x: f64) -> i64 { llroundd(x) }

pub fn modfd(x: f64, iptr: &mut f64) -> f64 {
    let bits = x.to_bits();
    let i0 = (bits >> 32) as i32;
    let i1 = (bits & 0xffffffff) as u32;
    let j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
    let sign_bits = (i0 as u32 & 0x80000000u32) as u64;

    if j0 < 20 {
        if j0 < 0 {
            *iptr = f64::from_bits(sign_bits << 32);
            return x;
        } else {
            let mask = 0x000fffffu32 >> j0;
            if ((i0 as u32 & mask) | i1) == 0 {
                *iptr = x;
                return f64::from_bits(sign_bits << 32);
            }
            *iptr = f64::from_bits(((i0 as u32 & !mask) as u64) << 32);
            return x - *iptr;
        }
    } else if j0 > 51 {
        *iptr = if x.is_nan() { x + x } else { x };
        return f64::from_bits(sign_bits << 32);
    } else {
        let mask = 0xffffffffu32 >> (j0 - 20);
        if (i1 & mask) == 0 {
            *iptr = x;
            return f64::from_bits(sign_bits << 32);
        }
        *iptr = f64::from_bits(((i0 as u64) << 32) | ((i1 & !mask) as u64));
        return x - *iptr;
    }
}

pub fn nand(_tagp: *const i8) -> f64 { f64::NAN }

pub fn nearbyintd(x: f64) -> f64 { rintd(x) }

pub fn nextafterd(x: f64, y: f64) -> f64 {
    let xb = x.to_bits();
    let yb = y.to_bits();
    let mut hx = (xb >> 32) as i32;
    let mut lx = (xb & 0xffffffff) as u32;
    let hy = (yb >> 32) as i32;
    let ly = (yb & 0xffffffff) as u32;
    let ix = hx & 0x7fffffff;

    if x.is_nan() || y.is_nan() { return x + y; }
    if hx == hy && lx == ly { return y; }
    if (ix as u32 | lx) == 0 {
        if ix == (hy & 0x7fffffff) && ly == 0 { return y; }
        let new_x = f64::from_bits(((hy as u32 & 0x80000000u32) as u64) << 32 | 1u64);
        return new_x;
    }

    if hx >= 0 {
        if hx > hy || (hx == hy && lx > ly) {
            if lx == 0 { hx -= 1; }
            lx = lx.wrapping_sub(1);
        } else {
            lx = lx.wrapping_add(1);
            if lx == 0 { hx += 1; }
        }
    } else {
        if hy >= 0 || hx > hy || (hx == hy && lx > ly) {
            if lx == 0 { hx -= 1; }
            lx = lx.wrapping_sub(1);
        } else {
            lx = lx.wrapping_add(1);
            if lx == 0 { hx += 1; }
        }
    }

    let hy2 = hx & 0x7ff00000;
    if hy2 >= 0x7ff00000 {
        return if x.is_sign_negative() { f64::NEG_INFINITY } else { f64::INFINITY };
    }
    f64::from_bits(((hx as u64) << 32) | (lx as u64))
}

pub fn nexttowardd(x: f64, y: f64) -> f64 { nextafterd(x, y) }

pub fn powd(x: f64, y: f64) -> f64 {
    const BP: [f64; 2]   = [1.0, 1.5];
    const DP_H: [f64; 2] = [0.0, 5.84962487220764160156e-01];
    const DP_L: [f64; 2] = [0.0, 1.35003920212974897128e-08];
    const TWO53: f64  = 9007199254740992.0;
    const L1: f64 = 5.99999999999994648725e-01;
    const L2: f64 = 4.28571428578550184252e-01;
    const L3: f64 = 3.33333329818377432918e-01;
    const L4: f64 = 2.72728123808534006489e-01;
    const L5: f64 = 2.30660745775561754067e-01;
    const L6: f64 = 2.06975017800338417784e-01;
    const P1: f64 =  1.66666666666666019037e-01;
    const P2: f64 = -2.77777777770155933842e-03;
    const P3: f64 =  6.61375632143793436117e-05;
    const P4: f64 = -1.65339022054652515390e-06;
    const P5: f64 =  4.13813679705723846039e-08;
    const LG2: f64   = 6.93147180559945286227e-01;
    const LG2_H: f64 = 6.93147182464599609375e-01;
    const LG2_L: f64 = -1.90465429995776804525e-09;
    const OVT: f64   = 8.0085662595372944372e-17;
    const CP: f64    = 9.61796693925975554329e-01;
    const CP_H: f64  = 9.61796700954437255859e-01;
    const CP_L: f64  = -7.02846165095275826516e-09;
    const IVLN2: f64   = 1.44269504088896338700e+00;
    const IVLN2_H: f64 = 1.44269502162933349609e+00;
    const IVLN2_L: f64 = 1.92596299112661746887e-08;

    let xb = x.to_bits(); let yb = y.to_bits();
    let hx = (xb >> 32) as i32; let lx = (xb & 0xffffffff) as u32;
    let hy = (yb >> 32) as i32; let ly = (yb & 0xffffffff) as u32;
    let ix = hx & 0x7fffffff; let iy = hy & 0x7fffffff;

    if (iy as u32 | ly) == 0 { return 1.0; }

    if ix > 0x7ff00000 || (ix == 0x7ff00000 && lx != 0)
    || iy > 0x7ff00000 || (iy == 0x7ff00000 && ly != 0) {
        if ((hx - 0x3ff00000) as u32 | lx) == 0 { return 1.0; }
        return x + y;
    }

    let mut yisint = 0i32;
    if hx < 0 {
        if iy >= 0x43400000 {
            yisint = 2;
        } else if iy >= 0x3ff00000 {
            let k = (iy >> 20) - 0x3ff;
            if k > 20 {
                let j = (ly >> (52 - k)) as i32;
                if ((j as u32) << (52 - k)) == ly { yisint = 2 - (j & 1); }
            } else if ly == 0 {
                let j = (iy >> (20 - k)) as i32;
                if (j << (20 - k)) == iy { yisint = 2 - (j & 1); }
            }
        }
    }

    if ly == 0 {
        if iy == 0x7ff00000 {
            if ((ix - 0x3ff00000) as u32 | lx) == 0 { return 1.0; }
            return if ix >= 0x3ff00000 { if hy >= 0 { y } else { 0.0 } }
                   else                { if hy < 0  { -y} else { 0.0 } };
        }
        if iy == 0x3ff00000 { return if hy < 0 { 1.0/x } else { x }; }
        if hy == 0x40000000 { return x * x; }
        if hy == 0x3fe00000 && hx >= 0 { return x.sqrt(); }
    }

    let ax = x.abs();

    if lx == 0 && (ix == 0x7ff00000 || ix == 0 || ix == 0x3ff00000) {
        let mut z = ax;
        if hy < 0 {
            if ix == 0x7ff00000 { z = 0.0; }
            else if ix == 0 { z = if z.is_sign_negative() { f64::NEG_INFINITY } else { f64::INFINITY }; }
        }
        if hx < 0 {
            if ((ix - 0x3ff00000) as u32 | (yisint as u32)) == 0 { z = f64::NAN; }
            else if yisint == 1 { z = -z; }
        }
        return z;
    }

    let n_sign = ((hx as u32) >> 31) as i32;
    let n_val = n_sign - 1;
    if (n_val | yisint) == 0 { return f64::NAN; }

    let mut sign = 1.0f64;
    if (n_val | (yisint - 1)) == 0 { sign = -1.0; }

    let t1: f64; let t2: f64; let mut n: i32;

    if iy > 0x42000000 {
        if iy > 0x43f00000 {
            return if ix <= 0x3fefffff {
                if hy < 0 { f64::INFINITY } else { 0.0 }
            } else {
                if hy > 0 { f64::INFINITY } else { 0.0 }
            };
        }
        if ix < 0x3fefffff { return if hy < 0 { sign * f64::INFINITY } else { sign * 0.0 }; }
        if ix > 0x3ff00000 { return if hy > 0 { sign * f64::INFINITY } else { sign * 0.0 }; }
        let t = ax - 1.0;
        let w = (t*t) * (0.5 - t*(0.3333333333333333333333 - t*0.25));
        let u = IVLN2_H * t;
        let v = t*IVLN2_L - w*IVLN2;
        let t1v = u + v;
        let t1v = f64::from_bits(t1v.to_bits() & 0xffffffff00000000u64);
        t1 = t1v; t2 = v - (t1 - u); n = 0;
    } else {
        let mut ax = ax;
        n = 0;
        if ix < 0x00100000 { ax *= TWO53; n -= 53; }
        n += ((ax.to_bits() >> 32) as i32 & 0x7fffffff) >> 20;
        n -= 0x3ff;
        let mut j = (ax.to_bits() >> 32) as i32 & 0x000fffff;
        let mut ix2 = j | 0x3ff00000;
        let k: usize;
        if j <= 0x3988e      { k = 0; }
        else if j < 0xbb67a  { k = 1; }
        else                 { k = 0; n += 1; ix2 -= 0x00100000; }
        let ax_lo = (ax.to_bits() & 0xffffffff) as u32;
        ax = f64::from_bits(((ix2 as u64) << 32) | (ax_lo as u64));

        let u = ax - BP[k];
        let v = 1.0 / (ax + BP[k]);
        let s = u * v;
        let s_h = f64::from_bits(s.to_bits() & 0xffffffff00000000u64);
        let t_h_hx = ((ix2 >> 1) | 0x20000000) + 0x00080000 + ((k as i32) << 18);
        let t_h = f64::from_bits(((t_h_hx as u64) << 32));
        let t_l = ax - (t_h - BP[k]);
        let s_l = v * ((u - s_h * t_h) - s_h * t_l);
        let s2 = s * s;
        let r = s2*s2*(L1 + s2*(L2 + s2*(L3 + s2*(L4 + s2*(L5 + s2*L6)))));
        let r = r + s_l*(s_h + s);
        let s2 = s_h * s_h;
        let t_h2 = 3.0 + s2 + r;
        let t_h2 = f64::from_bits(t_h2.to_bits() & 0xffffffff00000000u64);
        let t_l2 = r - ((t_h2 - 3.0) - s2);
        let u2 = s_h * t_h2;
        let v2 = s_l * t_h2 + t_l2 * s;
        let p_h = u2 + v2;
        let p_h = f64::from_bits(p_h.to_bits() & 0xffffffff00000000u64);
        let p_l = v2 - (p_h - u2);
        let z_h = CP_H * p_h;
        let z_l = CP_L * p_h + p_l * CP + DP_L[k];
        let tn = n as f64;
        let t1v = (z_h + z_l) + DP_H[k] + tn;
        let t1v = f64::from_bits(t1v.to_bits() & 0xffffffff00000000u64);
        t1 = t1v; t2 = z_l - (((t1 - tn) - DP_H[k]) - z_h);
    }

    let y1 = f64::from_bits(y.to_bits() & 0xffffffff00000000u64);
    let p_l = (y - y1)*t1 + y*t2;
    let mut p_h = y1 * t1;
    let z = p_l + p_h;
    let zb = z.to_bits();
    let j = (zb >> 32) as i32;
    let i = (zb & 0xffffffff) as i32;

    if j >= 0x40900000 {
        if ((j - 0x40900000) | i) != 0 { return if sign < 0.0 { f64::NEG_INFINITY } else { f64::INFINITY }; }
        if p_l + OVT > z - p_h { return if sign < 0.0 { f64::NEG_INFINITY } else { f64::INFINITY }; }
    } else if (j & 0x7fffffff) >= 0x4090cc00 {
        if ((j as u32).wrapping_sub(0xc090cc00u32) | (i as u32)) != 0 {
            return sign * 0.0;
        }
        if p_l <= z - p_h { return sign * 0.0; }
    }

    let i2 = j & 0x7fffffff;
    let k = (i2 >> 20) - 0x3ff;
    n = 0;
    if i2 > 0x3fe00000 {
        n = j + (0x00100000 >> (k + 1));
        let k2 = ((n & 0x7fffffff) >> 20) - 0x3ff;
        let t_bits: u64 = ((n as u64) & !((0x000fffffu64) >> (k2 as u32))) << 32;
        let t_var = f64::from_bits(t_bits);
        n = (((n & 0x000fffff) | 0x00100000) >> (20 - k2)) as i32;
        if j < 0 { n = -n; }
        p_h -= t_var;
    }

    let mut tt = p_l + p_h;
    tt = f64::from_bits(tt.to_bits() & 0xffffffff00000000u64);
    let u3 = tt * LG2_H;
    let v3 = (p_l - (tt - p_h)) * LG2 + tt * LG2_L;
    let mut z2 = u3 + v3;
    let w2 = v3 - (z2 - u3);
    let tt2 = z2 * z2;
    let t1v2 = z2 - tt2*(P1 + tt2*(P2 + tt2*(P3 + tt2*(P4 + tt2*P5))));
    let r2 = (z2 * t1v2) / (t1v2 - 2.0) - (w2 + z2 * w2);
    z2 = 1.0 - (r2 - z2);
    let j2 = (z2.to_bits() >> 32) as i32;
    let j3 = j2 + (n << 20);
    let result = if (j3 >> 20) <= 0 {
        scalbn_inner(z2, n)
    } else {
        let z2_lo = z2.to_bits() & 0xffffffff;
        f64::from_bits(((j3 as u64) << 32) | z2_lo)
    };
    sign * result
}

pub fn remainderd(x: f64, y: f64) -> f64 {
    let xb = x.to_bits(); let yb = y.to_bits();
    let mut hx = (xb >> 32) as i32; let lx = (xb & 0xffffffff) as u32;
    let mut hy = (yb >> 32) as i32; let ly = (yb & 0xffffffff) as u32;
    let sx = hx as u32 & 0x80000000u32;
    hy &= 0x7fffffff; hx &= 0x7fffffff;

    if (hx >= 0x7ff00000) || (hy >= 0x7ff00000) {
        if x.is_nan() || y.is_nan() { return x + y; }
        if hx == 0x7ff00000 { return f64::NAN; }
    } else if (hy as u32 | ly) == 0 { return f64::NAN; }

    let mut x = x; let mut y = y;
    if hy <= 0x7fdfffff { x = x % (2.0 * y); }
    let xb2 = x.to_bits(); let hx2 = (xb2>>32) as i32 & 0x7fffffff;
    let lx2 = (xb2&0xffffffff) as u32;
    if ((hx2 - hy) as u32 | lx2.wrapping_sub(ly)) == 0 { return 0.0 * x; }
    x = x.abs(); y = y.abs();
    if hy < 0x00200000 {
        if x + x > y { x -= y; if x + x >= y { x -= y; } }
    } else {
        let yh = 0.5 * y;
        if x > yh { x -= y; if x >= yh { x -= y; } }
    }
    let hx3 = (x.to_bits() >> 32) as u32;
    let lx3 = (x.to_bits() & 0xffffffff) as u32;
    f64::from_bits((((hx3 ^ sx) as u64) << 32) | (lx3 as u64))
}

pub fn remquod(x: f64, y: f64, quo: &mut i32) -> f64 {
    *quo = 0;
    let xb = x.to_bits(); let yb = y.to_bits();
    let mut hx = (xb >> 32) as i32; let lx = (xb & 0xffffffff) as u32;
    let mut hy = (yb >> 32) as i32; let ly = (yb & 0xffffffff) as u32;
    let sx = hx as u32 & 0x80000000u32;
    let sq = sx ^ (hy as u32 & 0x80000000u32);
    hy &= 0x7fffffff; hx &= 0x7fffffff;

    if (hx >= 0x7ff00000) || (hy >= 0x7ff00000) {
        if x.is_nan() || y.is_nan() { return x + y; }
        if hx == 0x7ff00000 { return f64::NAN; }
    } else if (hy as u32 | ly) == 0 { return f64::NAN; }

    let mut x = x; let mut y = y;
    if hy <= 0x7fbfffff { x = x % (8.0 * y); }
    let xb2 = x.to_bits(); let hx2 = (xb2>>32) as i32 & 0x7fffffff;
    let lx2 = (xb2&0xffffffff) as u32;
    if ((hx2 - hy) as u32 | lx2.wrapping_sub(ly)) == 0 {
        *quo = if sq != 0 { -1 } else { 1 };
        return 0.0 * x;
    }
    x = x.abs(); y = y.abs();
    let mut q = 0i32;
    if x >= 4.0*y { x -= 4.0*y; q += 4; }
    if x >= 2.0*y { x -= 2.0*y; q += 2; }
    if hy < 0x00200000 {
        if x + x > y { x -= y; q += 1; if x + x >= y { x -= y; q += 1; } }
    } else {
        let yh = 0.5 * y;
        if x > yh { x -= y; q += 1; if x >= yh { x -= y; q += 1; } }
    }
    q &= 0x7;
    *quo = if sq != 0 { -q } else { q };
    let hx3 = (x.to_bits() >> 32) as u32;
    let lx3 = (x.to_bits() & 0xffffffff) as u32;
    f64::from_bits((((hx3 ^ sx) as u64) << 32) | (lx3 as u64))
}

pub fn rintd(x: f64) -> f64 {
    const TWO52P: f64 = 4.50359962737049600000e+15;
    const TWO52N: f64 = -4.50359962737049600000e+15;

    let bits = x.to_bits();
    let mut i0 = (bits >> 32) as i32;
    let mut i1 = (bits & 0xffffffff) as u32;
    let sx = ((i0 >> 31) & 1) as usize;
    let two52 = if sx == 0 { TWO52P } else { TWO52N };
    let j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;

    if j0 < 20 {
        if j0 < 0 {
            if ((i0 as u32 & 0x7fffffff) | i1) == 0 { return x; }
            i1 |= (i0 as u32) & 0x0fffff;
            i0 &= 0xfffe0000u32 as i32;
            i0 |= (((i1 | i1.wrapping_neg()) >> 12) & 0x80000) as i32;
            let x2 = f64::from_bits(((i0 as u64) << 32) | (i1 as u64));
            let w = two52 + x2;
            let t = w - two52;
            let t_hx = (t.to_bits() >> 32) as i32;
            let new_hx = ((t_hx & 0x7fffffff) | ((sx as i32) << 31)) as u64;
            return f64::from_bits((new_hx << 32) | (t.to_bits() & 0xffffffff));
        } else {
            let mask = 0x000fffffu32 >> j0;
            if ((i0 as u32 & mask) | i1) == 0 { return x; }
            let half_mask = mask >> 1;
            if ((i0 as u32 & half_mask) | i1) != 0 {
                i1 = if j0 == 19 { 0x80000000u32 } else { 0 };
                i0 = (i0 as u32 & !half_mask) as i32 | (0x40000u32 >> j0) as i32;
            }
        }
    } else if j0 > 51 {
        return if j0 == 0x400 { x + x } else { x };
    } else {
        let mask = 0xffffffffu32 >> (j0 - 20);
        if (i1 & mask) == 0 { return x; }
        let half_mask = mask >> 1;
        if (i1 & half_mask) != 0 {
            i1 = (i1 & !half_mask) | (0x40000000u32 >> (j0 - 20));
        }
    }

    let x2 = f64::from_bits(((i0 as u64) << 32) | (i1 as u64));
    let w = two52 + x2;
    w - two52
}

pub fn roundd(x: f64) -> f64 {
    let bits = x.to_bits();
    let mut msw = (bits >> 32) as i32;
    let mut lsw = (bits & 0xffffffff) as u32;
    let exp = ((msw & 0x7ff00000) >> 20) - 1023;

    if exp < 20 {
        if exp < 0 {
            msw &= 0x80000000u32 as i32;
            if exp == -1 { msw |= 1023 << 20; }
            lsw = 0;
        } else {
            let emask = 0x000fffffu32 >> exp;
            if (msw as u32 & emask) == 0 && lsw == 0 { return x; }
            msw = (msw as u32).wrapping_add(0x00080000 >> exp) as i32;
            msw &= !(emask as i32);
            lsw = 0;
        }
    } else if exp > 51 {
        return if exp == 1024 { x + x } else { x };
    } else {
        let emask = 0xffffffffu32 >> (exp - 20);
        if (lsw & emask) == 0 { return x; }
        let tmp = lsw.wrapping_add(1u32 << (51 - exp));
        if tmp < lsw { msw = msw.wrapping_add(1); }
        lsw = tmp & !emask;
    }

    f64::from_bits(((msw as u64) << 32) | (lsw as u64))
}

pub fn scalblnd(x: f64, n: i64) -> f64 {
    let n32 = if n > i32::MAX as i64 { i32::MAX } else if n < i32::MIN as i64 { i32::MIN } else { n as i32 };
    scalbn_inner(x, n32)
}

pub fn scalbnd(x: f64, n: i32) -> f64 { scalbn_inner(x, n) }

pub fn sind(x: f64) -> f64 {
    let ix = (x.to_bits() >> 32) as i32 & 0x7fffffff;
    if ix <= 0x3fe921fb {
        if ix < 0x3e500000 { return x; }
        return sin_kern(x, 0.0, 0);
    }
    if ix >= 0x7ff00000 {
        return if x.is_nan() { x + x } else { f64::NAN };
    }
    let mut y = [0.0f64; 2];
    let n = rem_pio2(x, &mut y);
    match n & 3 {
        0 =>  sin_kern(y[0], y[1], 1),
        1 =>  cos_kern(y[0], y[1]),
        2 => -sin_kern(y[0], y[1], 1),
        _ => -cos_kern(y[0], y[1]),
    }
}

pub fn sinhd(x: f64) -> f64 {
    let jx = (x.to_bits() >> 32) as i32;
    let ix = jx & 0x7fffffff;
    if ix >= 0x7ff00000 { return x + x; }
    let mut h = 0.5f64;
    if jx < 0 { h = -h; }
    if ix < 0x40360000 {
        if ix < 0x3e300000 { return x; }
        let t = x.abs().exp_m1();
        if ix < 0x3ff00000 { return h * (2.0*t - t*t/(t+1.0)); }
        return h * (t + t/(t+1.0));
    }
    if ix < 0x40862e42 { return h * x.abs().exp(); }
    let lx = (x.to_bits() & 0xffffffff) as u32;
    if ix < 0x408633ce || (ix == 0x408633ce && lx <= 0x8fb9f87du32) {
        let w = (0.5 * x.abs()).exp();
        return h * w * w;
    }
    if x.is_sign_negative() { f64::NEG_INFINITY } else { f64::INFINITY }
}

pub fn sqrtd(x: f64) -> f64 {
    let sign: u32 = 0x80000000u32;
    let bits = x.to_bits();
    let mut ix0 = (bits >> 32) as i32;
    let mut ix1 = (bits & 0xffffffff) as u32;

    if (ix0 & 0x7ff00000) == 0x7ff00000 {
        if x.is_nan() { return x + x; }
        if ix0 > 0 { return x; }
        return f64::NAN;
    }
    if ix0 <= 0 {
        if (ix0 & !(sign as i32)) | ix1 as i32 == 0 { return x; }
        if ix0 < 0 { return f64::NAN; }
    }

    let mut m = ix0 >> 20;
    if m == 0 {
        while ix0 == 0 { m -= 21; ix0 |= (ix1 >> 11) as i32; ix1 <<= 21; }
        let mut i = 0;
        while (ix0 & 0x00100000) == 0 { ix0 <<= 1; i += 1; }
        m -= i - 1;
        if i != 0 { ix0 |= (ix1 >> (32 - i)) as i32; ix1 <<= i; }
    }
    m -= 1023;
    ix0 = (ix0 & 0x000fffff) | 0x00100000;
    if (m & 1) != 0 { ix0 += ix0 + ((ix1 & sign) >> 31) as i32; ix1 += ix1; }
    m >>= 1;
    ix0 += ix0 + ((ix1 & sign) >> 31) as i32; ix1 += ix1;
    let mut q = 0i32; let mut q1 = 0u32;
    let mut s0 = 0i32; let mut s1 = 0u32;
    let mut r: u32 = 0x00200000u32;

    while r != 0 {
        let t = s0 + r as i32;
        if t <= ix0 { s0 = t + r as i32; ix0 -= t; q += r as i32; }
        ix0 += ix0 + ((ix1 & sign) >> 31) as i32; ix1 += ix1;
        r >>= 1;
    }
    r = sign;
    while r != 0 {
        let t1 = s1.wrapping_add(r);
        let t = s0;
        if t < ix0 || (t == ix0 && t1 <= ix1) {
            s1 = t1.wrapping_add(r);
            if (t1 as i32 & sign as i32) == sign as i32 && (s1 as i32 & sign as i32) == 0 { s0 += 1; }
            ix0 -= t;
            if ix1 < t1 { ix0 -= 1; }
            ix1 = ix1.wrapping_sub(t1);
            q1 = q1.wrapping_add(r);
        }
        ix0 += ix0 + ((ix1 & sign) >> 31) as i32; ix1 += ix1;
        r >>= 1;
    }
    if (ix0 as u32 | ix1) != 0 {
        if q1 == 0xffffffffu32 { q1 = 0; q += 1; }
        else { q1 += q1 & 1; }
    }
    let ix0_out = (q >> 1) + 0x3fe00000;
    let mut ix1_out = q1 >> 1;
    if (q & 1) != 0 { ix1_out |= sign; }
    let ix0_out = ix0_out + (m << 20);
    f64::from_bits(((ix0_out as u64) << 32) | (ix1_out as u64))
}

pub fn tand(x: f64) -> f64 {
    let ix = (x.to_bits() >> 32) as i32 & 0x7fffffff;
    if ix <= 0x3fe921fb {
        if ix < 0x3e400000 { return x; }
        return tan_kern(x, 0.0, 1);
    }
    if ix >= 0x7ff00000 {
        return if x.is_nan() { x + x } else { f64::NAN };
    }
    let mut y = [0.0f64; 2];
    let n = rem_pio2(x, &mut y);
    tan_kern(y[0], y[1], 1 - ((n & 1) << 1))
}

pub fn tanhd(x: f64) -> f64 {
    let jx = (x.to_bits() >> 32) as i32;
    let ix = jx & 0x7fffffff;
    if ix >= 0x7ff00000 {
        if x.is_nan() { return x + x; }
        return if jx >= 0 { 1.0 } else { -1.0 };
    }
    let z: f64;
    if ix < 0x40360000 {
        if ix < 0x3c800000 { return x; }
        if ix >= 0x3ff00000 {
            let t = (2.0 * x.abs()).exp_m1();
            z = 1.0 - 2.0 / (t + 2.0);
        } else {
            let t = (-2.0 * x.abs()).exp_m1();
            z = -t / (t + 2.0);
        }
    } else {
        z = 1.0;
    }
    if jx >= 0 { z } else { -z }
}

pub fn tgammad(x: f64) -> f64 {
    if x.is_nan() { return x + x; }
    if x == 0.0 { return if x.is_sign_negative() { f64::NEG_INFINITY } else { f64::INFINITY }; }
    if x.floor() == x && x < 0.0 { return f64::NAN; }
    let mut signgam = 0i32;
    let y = lgamma_r(x, &mut signgam).exp();
    if signgam < 0 { -y } else { y }
}

pub fn truncd(x: f64) -> f64 {
    let bits = x.to_bits();
    let mut msw = (bits >> 32) as u32;
    let mut lsw = (bits & 0xffffffff) as u32;
    let sb = msw & 0x80000000u32;
    let exp = ((msw & 0x7ff00000) >> 20) as i32 - 1023;
    if exp < 20 {
        if exp < 0 { msw = sb; lsw = 0; }
        else {
            let mask = 0x000fffffu32 >> exp;
            if (msw & mask) == 0 && lsw == 0 { return x; }
            msw &= !mask; lsw = 0;
        }
    } else if exp > 51 {
        if exp == 1024 { return x + x; }
        return x;
    } else {
        let mask = 0xffffffffu32 >> (exp - 20);
        if (lsw & mask) == 0 { return x; }
        lsw &= !mask;
    }
    f64::from_bits(((msw as u64) << 32) | (lsw as u64))
}

pub fn y0d(x: f64) -> f64 {
    const U00: f64 = -7.38042951086872317523e-02;
    const U01: f64 =  1.76666452509181115538e-01;
    const U02: f64 = -1.38185671945596898896e-02;
    const U03: f64 =  3.47453432093683650238e-04;
    const U04: f64 = -3.81407053724364161125e-06;
    const U05: f64 =  1.95590137035022920206e-08;
    const U06: f64 = -3.98205194132103398453e-11;
    const V01: f64 =  1.27304834834123699328e-02;
    const V02: f64 =  7.60068627350353253702e-05;
    const V03: f64 =  2.59150851840457805467e-07;
    const V04: f64 =  4.41110311332675467403e-10;

    let xb = x.to_bits();
    let hx = (xb >> 32) as i32; let lx = (xb & 0xffffffff) as u32;
    let ix = 0x7fffffff & hx;

    if ix >= 0x7ff00000 {
        if x.is_nan() { return x + x; }
        if hx > 0 { return 0.0; }
    }
    if (ix as u32 | lx) == 0 { return f64::NEG_INFINITY; }
    if hx < 0 { return f64::NAN; }

    if ix >= 0x40000000 {
        let s = x.sin(); let c = x.cos();
        let mut ss = s - c; let mut cc = s + c;
        if ix < 0x7fe00000 {
            let z = -(x+x).cos();
            if s*c < 0.0 { cc = z/ss; } else { ss = z/cc; }
        }
        return if ix > 0x48000000 { (INVSQRTPI*ss)/x.sqrt() }
               else { INVSQRTPI*(j0_p(x)*ss + j0_q(x)*cc)/x.sqrt() };
    }
    if ix <= 0x3e400000 { return U00 + TPI * x.ln(); }
    let z = x * x;
    let u = U00 + z*(U01 + z*(U02 + z*(U03 + z*(U04 + z*(U05 + z*U06)))));
    let v = 1.0 + z*(V01 + z*(V02 + z*(V03 + z*V04)));
    u/v + TPI * (j0d(x) * x.ln())
}

pub fn y1d(x: f64) -> f64 {
    const U0: [f64; 5] = [
        -1.96057090646238940668e-01,
         5.04438716639811282616e-02,
        -1.91256895875763547298e-03,
         2.35252600561610495928e-05,
        -9.19099158039878874504e-08,
    ];
    const V0: [f64; 5] = [
        1.99167318236649903973e-02,
        2.02552581025135171496e-04,
        1.35608801097516229404e-06,
        6.22741452364621501295e-09,
        1.66559246207992079114e-11,
    ];

    let xb = x.to_bits();
    let hx = (xb >> 32) as i32; let lx = (xb & 0xffffffff) as u32;
    let ix = 0x7fffffff & hx;

    if ix >= 0x7ff00000 {
        if x.is_nan() { return x + x; }
        if hx > 0 { return 0.0; }
    }
    if (ix as u32 | lx) == 0 { return f64::NEG_INFINITY; }
    if hx < 0 { return f64::NAN; }

    if ix >= 0x40000000 {
        let s = x.sin(); let c = x.cos();
        let mut ss = -s - c; let mut cc = s - c;
        if ix < 0x7fe00000 {
            let z = (x+x).cos();
            if s*c > 0.0 { cc = z/ss; } else { ss = z/cc; }
        }
        return if ix > 0x48000000 { (INVSQRTPI*ss)/x.sqrt() }
               else { INVSQRTPI*(j1_p(x)*ss + j1_q(x)*cc)/x.sqrt() };
    }
    if ix <= 0x3c900000 { return -TPI / x; }
    let z = x * x;
    let u = U0[0] + z*(U0[1] + z*(U0[2] + z*(U0[3] + z*U0[4])));
    let v = 1.0 + z*(V0[0] + z*(V0[1] + z*(V0[2] + z*(V0[3] + z*V0[4]))));
    x*(u/v) + TPI*(j1d(x)*x.ln() - 1.0/x)
}

pub fn ynd(n: i32, x: f64) -> f64 {
    let xb = x.to_bits();
    let hx = (xb >> 32) as i32; let lx = (xb & 0xffffffff) as u32;
    let ix = 0x7fffffff & hx;

    if x.is_nan() { return x + x; }
    if (ix as u32 | lx) == 0 { return f64::NEG_INFINITY; }
    if hx < 0 { return f64::NAN; }

    let mut n = n; let mut sign = 1i32;
    if n < 0 { n = -n; sign = 1 - ((n & 1) << 1); }
    if n == 0 { return y0d(x); }
    if n == 1 { return (sign as f64) * y1d(x); }
    if ix == 0x7ff00000 { return 0.0; }

    let b = if ix >= 0x52d00000 {
        let temp = match n & 3 {
            0 =>  x.sin() - x.cos(),
            1 => -x.sin() - x.cos(),
            2 => -x.sin() + x.cos(),
            _ =>  x.sin() + x.cos(),
        };
        INVSQRTPI * temp / x.sqrt()
    } else {
        let mut a = y0d(x);
        let mut b = y1d(x);
        let mut i = 1i32;
        let mut high = (b.to_bits() >> 32) as u32;
        while i < n && high != 0xfff00000u32 {
            let temp = b;
            b = (2*i) as f64 / x * b - a;
            high = (b.to_bits() >> 32) as u32;
            a = temp;
            i += 1;
        }
        b
    };
    if sign > 0 { b } else { -b }
}
