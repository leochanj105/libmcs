#![allow(warnings)]

pub mod mathd;
pub mod mathf;
pub mod complexd;
pub mod complexf;
mod test_bridge;

use complexd::DoubleComplex;
use complexf::FloatComplex;

// ─── fenv (all stubs returning -1) ──────────────────────────────────────────

#[repr(C)] pub struct FexceptT(u32);
#[repr(C)] pub struct FenvT(u64);

#[no_mangle] pub extern "C" fn feclearexcept(excepts: i32) -> i32 { -1 }
#[no_mangle] pub extern "C" fn feraiseexcept(excepts: i32) -> i32 { -1 }
#[no_mangle] pub unsafe extern "C" fn fegetexceptflag(flagp: *mut FexceptT, excepts: i32) -> i32 { -1 }
#[no_mangle] pub unsafe extern "C" fn fesetexceptflag(flagp: *const FexceptT, excepts: i32) -> i32 { -1 }
#[no_mangle] pub extern "C" fn fegetround() -> i32 { -1 }
#[no_mangle] pub extern "C" fn fesetround(rdir: i32) -> i32 { -1 }
#[no_mangle] pub unsafe extern "C" fn fegetenv(envp: *mut FenvT) -> i32 { -1 }
#[no_mangle] pub unsafe extern "C" fn fesetenv(envp: *const FenvT) -> i32 { -1 }
#[no_mangle] pub unsafe extern "C" fn feholdexcept(envp: *mut FenvT) -> i32 { -1 }
#[no_mangle] pub unsafe extern "C" fn feupdateenv(envp: *const FenvT) -> i32 { -1 }
#[no_mangle] pub extern "C" fn fetestexcept(excepts: i32) -> i32 { -1 }

// ─── signgam global ─────────────────────────────────────────────────────────
// C math.h defines: #define signgam (__signgam) and extern int __signgam;
// Tests read __signgam, so we must export that symbol.
#[no_mangle] pub static mut __signgam: i32 = 1;
#[no_mangle] pub static mut signgam: i32 = 1;

// ─── double-precision math (mathd) ──────────────────────────────────────────

#[no_mangle] pub extern "C" fn acos(x: f64) -> f64 { mathd::acosd(x) }
#[no_mangle] pub extern "C" fn acosh(x: f64) -> f64 { mathd::acoshd(x) }
#[no_mangle] pub extern "C" fn asin(x: f64) -> f64 { mathd::asind(x) }
#[no_mangle] pub extern "C" fn asinh(x: f64) -> f64 { mathd::asinhd(x) }
#[no_mangle] pub extern "C" fn atan(x: f64) -> f64 { mathd::atand(x) }
#[no_mangle] pub extern "C" fn atan2(y: f64, x: f64) -> f64 { mathd::atan2d(y, x) }
#[no_mangle] pub extern "C" fn atanh(x: f64) -> f64 { mathd::atanhd(x) }
#[no_mangle] pub extern "C" fn cbrt(x: f64) -> f64 { mathd::cbrtd(x) }
#[no_mangle] pub extern "C" fn ceil(x: f64) -> f64 { mathd::ceild(x) }
#[no_mangle] pub extern "C" fn copysign(x: f64, y: f64) -> f64 { mathd::copysignd(x, y) }
#[no_mangle] pub extern "C" fn cos(x: f64) -> f64 { mathd::cosd(x) }
#[no_mangle] pub extern "C" fn cosh(x: f64) -> f64 { mathd::coshd(x) }
#[no_mangle] pub extern "C" fn erf(x: f64) -> f64 { mathd::erfd(x) }
#[no_mangle] pub extern "C" fn erfc(x: f64) -> f64 { mathd::erfcd(x) }
#[no_mangle] pub extern "C" fn exp(x: f64) -> f64 { mathd::expd(x) }
#[no_mangle] pub extern "C" fn exp2(x: f64) -> f64 { mathd::exp2d(x) }
#[no_mangle] pub extern "C" fn expm1(x: f64) -> f64 { mathd::expm1d(x) }
#[no_mangle] pub extern "C" fn fabs(x: f64) -> f64 { mathd::fabsd(x) }
#[no_mangle] pub extern "C" fn fdim(x: f64, y: f64) -> f64 { mathd::fdimd(x, y) }
#[no_mangle] pub extern "C" fn floor(x: f64) -> f64 { mathd::floord(x) }
#[no_mangle] pub extern "C" fn fma(x: f64, y: f64, z: f64) -> f64 { mathd::fmad(x, y, z) }
#[no_mangle] pub extern "C" fn fmax(x: f64, y: f64) -> f64 { mathd::fmaxd(x, y) }
#[no_mangle] pub extern "C" fn fmin(x: f64, y: f64) -> f64 { mathd::fmind(x, y) }
#[no_mangle] pub extern "C" fn fmod(x: f64, y: f64) -> f64 { mathd::fmodd(x, y) }
#[no_mangle] pub unsafe extern "C" fn frexp(x: f64, exp: *mut i32) -> f64 {
    let mut e = 0i32;
    let r = mathd::frexpd(x, &mut e);
    *exp = e;
    r
}
#[no_mangle] pub extern "C" fn hypot(x: f64, y: f64) -> f64 { mathd::hypotd(x, y) }
#[no_mangle] pub extern "C" fn ilogb(x: f64) -> i32 { mathd::ilogbd(x) }
#[no_mangle] pub extern "C" fn j0(x: f64) -> f64 { mathd::j0d(x) }
#[no_mangle] pub extern "C" fn j1(x: f64) -> f64 { mathd::j1d(x) }
#[no_mangle] pub extern "C" fn jn(n: i32, x: f64) -> f64 { mathd::jnd(n, x) }
#[no_mangle] pub extern "C" fn ldexp(x: f64, exp: i32) -> f64 { mathd::ldexpd(x, exp) }
#[no_mangle] pub extern "C" fn lgamma(x: f64) -> f64 {
    let r = mathd::lgammad(x);
    unsafe {
        let s = mathd::SIGNGAM.with(|sg| sg.get());
        signgam = s;
        __signgam = s;
    }
    r
}
#[no_mangle] pub extern "C" fn llrint(x: f64) -> i64 { mathd::llrintd(x) }
#[no_mangle] pub extern "C" fn llround(x: f64) -> i64 { mathd::llroundd(x) }
#[no_mangle] pub extern "C" fn log(x: f64) -> f64 { mathd::logd(x) }
#[no_mangle] pub extern "C" fn log10(x: f64) -> f64 { mathd::log10d(x) }
#[no_mangle] pub extern "C" fn log1p(x: f64) -> f64 { mathd::log1pd(x) }
#[no_mangle] pub extern "C" fn log2(x: f64) -> f64 { mathd::log2d(x) }
#[no_mangle] pub extern "C" fn logb(x: f64) -> f64 { mathd::logbd(x) }
#[no_mangle] pub extern "C" fn lrint(x: f64) -> i64 { mathd::lrintd(x) }
#[no_mangle] pub extern "C" fn lround(x: f64) -> i64 { mathd::lroundd(x) }
#[no_mangle] pub unsafe extern "C" fn modf(x: f64, iptr: *mut f64) -> f64 {
    let mut ip = 0.0f64;
    let r = mathd::modfd(x, &mut ip);
    *iptr = ip;
    r
}
#[no_mangle] pub unsafe extern "C" fn nan(tagp: *const i8) -> f64 { mathd::nand(tagp) }
#[no_mangle] pub extern "C" fn nearbyint(x: f64) -> f64 { mathd::nearbyintd(x) }
#[no_mangle] pub extern "C" fn nextafter(x: f64, y: f64) -> f64 { mathd::nextafterd(x, y) }
// nexttoward: long double == f64 on platforms where __LIBMCS_LONG_DOUBLE_IS_64BITS
#[no_mangle] pub extern "C" fn nexttoward(x: f64, y: f64) -> f64 { mathd::nexttowardd(x, y) }
#[no_mangle] pub extern "C" fn pow(x: f64, y: f64) -> f64 { mathd::powd(x, y) }
#[no_mangle] pub extern "C" fn remainder(x: f64, y: f64) -> f64 { mathd::remainderd(x, y) }
#[no_mangle] pub unsafe extern "C" fn remquo(x: f64, y: f64, quo: *mut i32) -> f64 {
    let mut q = 0i32;
    let r = mathd::remquod(x, y, &mut q);
    *quo = q;
    r
}
#[no_mangle] pub extern "C" fn rint(x: f64) -> f64 { mathd::rintd(x) }
#[no_mangle] pub extern "C" fn round(x: f64) -> f64 { mathd::roundd(x) }
#[no_mangle] pub extern "C" fn scalbln(x: f64, n: i64) -> f64 { mathd::scalblnd(x, n) }
#[no_mangle] pub extern "C" fn scalbn(x: f64, n: i32) -> f64 { mathd::scalbnd(x, n) }
#[no_mangle] pub extern "C" fn sin(x: f64) -> f64 { mathd::sind(x) }
#[no_mangle] pub extern "C" fn sinh(x: f64) -> f64 { mathd::sinhd(x) }
#[no_mangle] pub extern "C" fn sqrt(x: f64) -> f64 { mathd::sqrtd(x) }
#[no_mangle] pub extern "C" fn tan(x: f64) -> f64 { mathd::tand(x) }
#[no_mangle] pub extern "C" fn tanh(x: f64) -> f64 { mathd::tanhd(x) }
#[no_mangle] pub extern "C" fn tgamma(x: f64) -> f64 { mathd::tgammad(x) }
#[no_mangle] pub extern "C" fn trunc(x: f64) -> f64 { mathd::truncd(x) }
#[no_mangle] pub extern "C" fn y0(x: f64) -> f64 { mathd::y0d(x) }
#[no_mangle] pub extern "C" fn y1(x: f64) -> f64 { mathd::y1d(x) }
#[no_mangle] pub extern "C" fn yn(n: i32, x: f64) -> f64 { mathd::ynd(n, x) }
#[no_mangle] pub extern "C" fn __fpclassify(x: f64) -> i32 { mathd::__fpclassifyd(x) }
#[no_mangle] pub extern "C" fn __signbit(x: f64) -> i32 { mathd::__signbitd(x) }

// ─── single-precision math (mathf) ──────────────────────────────────────────

#[no_mangle] pub extern "C" fn acosf(x: f32) -> f32 { mathf::acosf(x) }
#[no_mangle] pub extern "C" fn acoshf(x: f32) -> f32 { mathf::acoshf(x) }
#[no_mangle] pub extern "C" fn asinf(x: f32) -> f32 { mathf::asinf(x) }
#[no_mangle] pub extern "C" fn asinhf(x: f32) -> f32 { mathf::asinhf(x) }
#[no_mangle] pub extern "C" fn atanf(x: f32) -> f32 { mathf::atanf(x) }
#[no_mangle] pub extern "C" fn atan2f(y: f32, x: f32) -> f32 { mathf::atan2f(y, x) }
#[no_mangle] pub extern "C" fn atanhf(x: f32) -> f32 { mathf::atanhf(x) }
#[no_mangle] pub extern "C" fn cbrtf(x: f32) -> f32 { mathf::cbrtf(x) }
#[no_mangle] pub extern "C" fn ceilf(x: f32) -> f32 { mathf::ceilf(x) }
#[no_mangle] pub extern "C" fn copysignf(x: f32, y: f32) -> f32 { mathf::copysignf(x, y) }
#[no_mangle] pub extern "C" fn cosf(x: f32) -> f32 { mathf::cosf(x) }
#[no_mangle] pub extern "C" fn coshf(x: f32) -> f32 { mathf::coshf(x) }
#[no_mangle] pub extern "C" fn erff(x: f32) -> f32 { mathf::erff(x) }
#[no_mangle] pub extern "C" fn erfcf(x: f32) -> f32 { mathf::erfcf(x) }
#[no_mangle] pub extern "C" fn expf(x: f32) -> f32 { mathf::expf(x) }
#[no_mangle] pub extern "C" fn exp2f(x: f32) -> f32 { mathf::exp2f(x) }
#[no_mangle] pub extern "C" fn expm1f(x: f32) -> f32 { mathf::expm1f(x) }
#[no_mangle] pub extern "C" fn fabsf(x: f32) -> f32 { mathf::fabsf(x) }
#[no_mangle] pub extern "C" fn fdimf(x: f32, y: f32) -> f32 { mathf::fdimf(x, y) }
#[no_mangle] pub extern "C" fn floorf(x: f32) -> f32 { mathf::floorf(x) }
#[no_mangle] pub extern "C" fn fmaf(x: f32, y: f32, z: f32) -> f32 { mathf::fmaf(x, y, z) }
#[no_mangle] pub extern "C" fn fmaxf(x: f32, y: f32) -> f32 { mathf::fmaxf(x, y) }
#[no_mangle] pub extern "C" fn fminf(x: f32, y: f32) -> f32 { mathf::fminf(x, y) }
#[no_mangle] pub extern "C" fn fmodf(x: f32, y: f32) -> f32 { mathf::fmodf(x, y) }
#[no_mangle] pub unsafe extern "C" fn frexpf(x: f32, exp: *mut i32) -> f32 {
    let mut e = 0i32;
    let r = mathf::frexpf(x, &mut e);
    *exp = e;
    r
}
#[no_mangle] pub extern "C" fn hypotf(x: f32, y: f32) -> f32 { mathf::hypotf(x, y) }
#[no_mangle] pub extern "C" fn ilogbf(x: f32) -> i32 { mathf::ilogbf(x) }
#[no_mangle] pub extern "C" fn ldexpf(x: f32, exp: i32) -> f32 { mathf::ldexpf(x, exp) }
#[no_mangle] pub extern "C" fn lgammaf(x: f32) -> f32 {
    let r = mathf::lgammaf(x);
    unsafe {
        let s = mathf::SIGNGAM.with(|sg| sg.get());
        signgam = s;
        __signgam = s;
    }
    r
}
#[no_mangle] pub extern "C" fn llrintf(x: f32) -> i64 { mathf::llrintf(x) }
#[no_mangle] pub extern "C" fn llroundf(x: f32) -> i64 { mathf::llroundf(x) }
#[no_mangle] pub extern "C" fn logf(x: f32) -> f32 { mathf::logf(x) }
#[no_mangle] pub extern "C" fn log10f(x: f32) -> f32 { mathf::log10f(x) }
#[no_mangle] pub extern "C" fn log1pf(x: f32) -> f32 { mathf::log1pf(x) }
#[no_mangle] pub extern "C" fn log2f(x: f32) -> f32 { mathf::log2f(x) }
#[no_mangle] pub extern "C" fn logbf(x: f32) -> f32 { mathf::logbf(x) }
#[no_mangle] pub extern "C" fn lrintf(x: f32) -> i64 { mathf::lrintf(x) }
#[no_mangle] pub extern "C" fn lroundf(x: f32) -> i64 { mathf::lroundf(x) }
#[no_mangle] pub unsafe extern "C" fn modff(x: f32, iptr: *mut f32) -> f32 {
    let mut ip = 0.0f32;
    let r = mathf::modff(x, &mut ip);
    *iptr = ip;
    r
}
#[no_mangle] pub unsafe extern "C" fn nanf(tagp: *const i8) -> f32 { mathf::nanf(tagp) }
#[no_mangle] pub extern "C" fn nearbyintf(x: f32) -> f32 { mathf::nearbyintf(x) }
#[no_mangle] pub extern "C" fn nextafterf(x: f32, y: f32) -> f32 { mathf::nextafterf(x, y) }
#[no_mangle] pub extern "C" fn nexttowardf(x: f32, y: f64) -> f32 { mathf::nexttowardf(x, y) }
#[no_mangle] pub extern "C" fn powf(x: f32, y: f32) -> f32 { mathf::powf(x, y) }
#[no_mangle] pub extern "C" fn remainderf(x: f32, y: f32) -> f32 { mathf::remainderf(x, y) }
#[no_mangle] pub unsafe extern "C" fn remquof(x: f32, y: f32, quo: *mut i32) -> f32 {
    let mut q = 0i32;
    let r = mathf::remquof(x, y, &mut q);
    *quo = q;
    r
}
#[no_mangle] pub extern "C" fn rintf(x: f32) -> f32 { mathf::rintf(x) }
#[no_mangle] pub extern "C" fn roundf(x: f32) -> f32 { mathf::roundf(x) }
#[no_mangle] pub extern "C" fn scalblnf(x: f32, n: i64) -> f32 { mathf::scalblnf(x, n) }
#[no_mangle] pub extern "C" fn scalbnf(x: f32, n: i32) -> f32 { mathf::scalbnf(x, n) }
#[no_mangle] pub extern "C" fn sinf(x: f32) -> f32 { mathf::sinf(x) }
#[no_mangle] pub extern "C" fn sinhf(x: f32) -> f32 { mathf::sinhf(x) }
#[no_mangle] pub extern "C" fn sqrtf(x: f32) -> f32 { mathf::sqrtf(x) }
#[no_mangle] pub extern "C" fn tanf(x: f32) -> f32 { mathf::tanf(x) }
#[no_mangle] pub extern "C" fn tanhf(x: f32) -> f32 { mathf::tanhf(x) }
#[no_mangle] pub extern "C" fn tgammaf(x: f32) -> f32 { mathf::tgammaf(x) }
#[no_mangle] pub extern "C" fn truncf(x: f32) -> f32 { mathf::truncf(x) }
#[no_mangle] pub extern "C" fn __fpclassifyf(x: f32) -> i32 { mathf::__fpclassifyf(x) }
#[no_mangle] pub extern "C" fn __signbitf(x: f32) -> i32 { mathf::__signbitf(x) }

// ─── complex double (complexd) ───────────────────────────────────────────────

#[no_mangle] pub extern "C" fn cabs(z: DoubleComplex) -> f64 { complexd::cabsd(z) }
#[no_mangle] pub extern "C" fn carg(z: DoubleComplex) -> f64 { complexd::cargd(z) }
#[no_mangle] pub extern "C" fn creal(z: DoubleComplex) -> f64 { complexd::creald(z) }
#[no_mangle] pub extern "C" fn cimag(z: DoubleComplex) -> f64 { complexd::cimagd(z) }
#[no_mangle] pub extern "C" fn conj(z: DoubleComplex) -> DoubleComplex { complexd::conjd(z) }
#[no_mangle] pub extern "C" fn cproj(z: DoubleComplex) -> DoubleComplex { complexd::cprojd(z) }
#[no_mangle] pub extern "C" fn cexp(z: DoubleComplex) -> DoubleComplex { complexd::cexpd(z) }
#[no_mangle] pub extern "C" fn clog(z: DoubleComplex) -> DoubleComplex { complexd::clogd(z) }
#[no_mangle] pub extern "C" fn csqrt(z: DoubleComplex) -> DoubleComplex { complexd::csqrtd(z) }
#[no_mangle] pub extern "C" fn ccosh(z: DoubleComplex) -> DoubleComplex { complexd::ccoshd(z) }
#[no_mangle] pub extern "C" fn csinh(z: DoubleComplex) -> DoubleComplex { complexd::csinhd(z) }
#[no_mangle] pub extern "C" fn ctanh(z: DoubleComplex) -> DoubleComplex { complexd::ctanhd(z) }
#[no_mangle] pub extern "C" fn ccos(z: DoubleComplex) -> DoubleComplex { complexd::ccosd(z) }
#[no_mangle] pub extern "C" fn csin(z: DoubleComplex) -> DoubleComplex { complexd::csind(z) }
#[no_mangle] pub extern "C" fn ctan(z: DoubleComplex) -> DoubleComplex { complexd::ctand(z) }
#[no_mangle] pub extern "C" fn casin(z: DoubleComplex) -> DoubleComplex { complexd::casind(z) }
#[no_mangle] pub extern "C" fn cacos(z: DoubleComplex) -> DoubleComplex { complexd::cacosd(z) }
#[no_mangle] pub extern "C" fn cacosh(z: DoubleComplex) -> DoubleComplex { complexd::cacoshd(z) }
#[no_mangle] pub extern "C" fn casinh(z: DoubleComplex) -> DoubleComplex { complexd::casinhd(z) }
#[no_mangle] pub extern "C" fn catan(z: DoubleComplex) -> DoubleComplex { complexd::catand(z) }
#[no_mangle] pub extern "C" fn catanh(z: DoubleComplex) -> DoubleComplex { complexd::catanhd(z) }
#[no_mangle] pub extern "C" fn cpow(x: DoubleComplex, y: DoubleComplex) -> DoubleComplex { complexd::cpowd(x, y) }

// ─── complex float (complexf) ────────────────────────────────────────────────

#[no_mangle] pub extern "C" fn cabsf(z: FloatComplex) -> f32 { complexf::cabsf(z) }
#[no_mangle] pub extern "C" fn cargf(z: FloatComplex) -> f32 { complexf::cargf(z) }
#[no_mangle] pub extern "C" fn crealf(z: FloatComplex) -> f32 { complexf::crealf(z) }
#[no_mangle] pub extern "C" fn cimagf(z: FloatComplex) -> f32 { complexf::cimagf(z) }
#[no_mangle] pub extern "C" fn conjf(z: FloatComplex) -> FloatComplex { complexf::conjf(z) }
#[no_mangle] pub extern "C" fn cprojf(z: FloatComplex) -> FloatComplex { complexf::cprojf(z) }
#[no_mangle] pub extern "C" fn cexpf(z: FloatComplex) -> FloatComplex { complexf::cexpf(z) }
#[no_mangle] pub extern "C" fn clogf(z: FloatComplex) -> FloatComplex { complexf::clogf(z) }
#[no_mangle] pub extern "C" fn csqrtf(z: FloatComplex) -> FloatComplex { complexf::csqrtf(z) }
#[no_mangle] pub extern "C" fn ccoshf(z: FloatComplex) -> FloatComplex { complexf::ccoshf(z) }
#[no_mangle] pub extern "C" fn csinhf(z: FloatComplex) -> FloatComplex { complexf::csinhf(z) }
#[no_mangle] pub extern "C" fn ctanhf(z: FloatComplex) -> FloatComplex { complexf::ctanhf(z) }
#[no_mangle] pub extern "C" fn ccosf(z: FloatComplex) -> FloatComplex { complexf::ccosf(z) }
#[no_mangle] pub extern "C" fn csinf(z: FloatComplex) -> FloatComplex { complexf::csinf(z) }
#[no_mangle] pub extern "C" fn ctanf(z: FloatComplex) -> FloatComplex { complexf::ctanf(z) }
#[no_mangle] pub extern "C" fn casinf(z: FloatComplex) -> FloatComplex { complexf::casinf(z) }
#[no_mangle] pub extern "C" fn cacosf(z: FloatComplex) -> FloatComplex { complexf::cacosf(z) }
#[no_mangle] pub extern "C" fn cacoshf(z: FloatComplex) -> FloatComplex { complexf::cacoshf(z) }
#[no_mangle] pub extern "C" fn casinhf(z: FloatComplex) -> FloatComplex { complexf::casinhf(z) }
#[no_mangle] pub extern "C" fn catanf(z: FloatComplex) -> FloatComplex { complexf::catanf(z) }
#[no_mangle] pub extern "C" fn catanhf(z: FloatComplex) -> FloatComplex { complexf::catanhf(z) }
#[no_mangle] pub extern "C" fn cpowf(x: FloatComplex, y: FloatComplex) -> FloatComplex { complexf::cpowf(x, y) }
