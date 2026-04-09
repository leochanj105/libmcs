/* wc_driver.c — Read hex-float inputs from stdin, call a math function,
 * print results in %a format for bitwise diffing.
 *
 * Fault isolation: signal handlers + setjmp/longjmp catch crashes (SIGSEGV,
 * SIGFPE, SIGBUS, SIGABRT) and alarm() catches hangs. On fault, the failing
 * input is logged to stderr and execution continues with the next line.
 *
 * Usage:  ./wc_driver <func_name> < inputs.dat
 *
 * Input format:
 *   Unary:  one hex float per line        (e.g., "0x1.fp+10")
 *   Binary: two hex floats comma-separated (e.g., "0x1.fp+10,0x1.0p+0")
 *
 * AUTO-GENERATED test data comes from core-math worst-case files.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

/* ---- fault isolation ---- */

static sigjmp_buf jump_buf;
static volatile sig_atomic_t in_test = 0;
static const char *current_func = "";
static const char *current_input = "";

/* Per-test timeout in seconds (0 = disabled).
 * Disabled by default for performance; enable via -DTEST_TIMEOUT=5 at compile. */
#ifndef TEST_TIMEOUT
#define TEST_TIMEOUT 0
#endif

static void fault_handler(int sig) {
    if (in_test) {
        /* Log to stderr so it doesn't pollute the diffable stdout */
        const char *signame = "UNKNOWN";
        switch (sig) {
        case SIGSEGV: signame = "SIGSEGV"; break;
        case SIGFPE:  signame = "SIGFPE";  break;
        case SIGBUS:  signame = "SIGBUS";  break;
        case SIGABRT: signame = "SIGABRT"; break;
        case SIGALRM: signame = "SIGALRM(timeout)"; break;
        }
        /* Use write() — async-signal-safe, unlike fprintf */
        write(STDERR_FILENO, "FAULT: ", 7);
        write(STDERR_FILENO, signame, strlen(signame));
        write(STDERR_FILENO, " in ", 4);
        write(STDERR_FILENO, current_func, strlen(current_func));
        write(STDERR_FILENO, " input=", 7);
        write(STDERR_FILENO, current_input, strlen(current_input));
        write(STDERR_FILENO, "\n", 1);

        siglongjmp(jump_buf, sig);
    }
    /* If not in a test, re-raise for default behavior */
    signal(sig, SIG_DFL);
    raise(sig);
}

static void install_handlers(void) {
    struct sigaction sa;
    sa.sa_handler = fault_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;  /* No SA_RESTART — we want longjmp, not restart */

    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGFPE,  &sa, NULL);
    sigaction(SIGBUS,  &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);
}

/* ---- function table ---- */

typedef double (*unary_d_fn)(double);
typedef double (*binary_d_fn)(double, double);
typedef float  (*unary_f_fn)(float);
typedef float  (*binary_f_fn)(float, float);

enum sig_type { UNARY_D, BINARY_D, UNARY_F, BINARY_F };

struct func_entry {
    const char   *name;
    enum sig_type sig;
    union {
        unary_d_fn  ud;
        binary_d_fn bd;
        unary_f_fn  uf;
        binary_f_fn bf;
    } fn;
};

/* Macro helpers to keep the table compact */
#define UD(n, f) { n, UNARY_D,  { .ud = f } }
#define BD(n, f) { n, BINARY_D, { .bd = f } }
#define BF(n, f) { n, BINARY_F, { .bf = f } }

static const struct func_entry funcs[] = {
    /* unary double */
    UD("acos",   acos),   UD("acosh",  acosh),  UD("asin",   asin),
    UD("asinh",  asinh),  UD("atan",   atan),   UD("atanh",  atanh),
    UD("cbrt",   cbrt),   UD("cos",    cos),    UD("cosh",   cosh),
    UD("erf",    erf),    UD("erfc",   erfc),   UD("exp",    exp),
    UD("exp2",   exp2),   UD("expm1",  expm1),  UD("lgamma", lgamma),
    UD("log",    log),    UD("log10",  log10),  UD("log1p",  log1p),
    UD("log2",   log2),   UD("sin",    sin),    UD("sinh",   sinh),
    UD("tan",    tan),    UD("tanh",   tanh),   UD("tgamma", tgamma),
    /* binary double */
    BD("atan2",  atan2),  BD("hypot",  hypot),  BD("pow",    pow),
    /* binary float */
    BF("atan2f", atan2f), BF("hypotf", hypotf), BF("powf",   powf),
    { NULL, 0, { .ud = NULL } }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <func_name>\n", argv[0]);
        return 1;
    }

    const char *name = argv[1];
    const struct func_entry *e = NULL;
    for (int i = 0; funcs[i].name; i++) {
        if (strcmp(funcs[i].name, name) == 0) {
            e = &funcs[i];
            break;
        }
    }
    if (!e) {
        fprintf(stderr, "Unknown function: %s\n", name);
        return 1;
    }

    install_handlers();
    current_func = name;

    char line[512];
    int faults = 0;

    while (fgets(line, sizeof(line), stdin)) {
        /* strip newline */
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';
        if (line[0] == '\0') continue;

        current_input = line;

        /* Set recovery point — if a signal fires, we land here */
        if (sigsetjmp(jump_buf, 1) != 0) {
            /* Returned from fault handler */
            faults++;
            /* Re-install handlers (some systems reset to SIG_DFL after catch) */
            install_handlers();
            /* Print a fault marker so the diff line count stays consistent */
            printf("%s %s = FAULT\n", name, line);
            continue;
        }

        in_test = 1;
        if (TEST_TIMEOUT > 0)
            alarm(TEST_TIMEOUT);

        switch (e->sig) {
        case UNARY_D: {
            double x;
            if (sscanf(line, "%la", &x) != 1) { in_test = 0; continue; }
            double r = e->fn.ud(x);
            printf("%s %a = %a\n", name, x, r);
            break;
        }
        case BINARY_D: {
            double x, y;
            if (sscanf(line, "%la,%la", &x, &y) != 2) { in_test = 0; continue; }
            double r = e->fn.bd(x, y);
            printf("%s %a %a = %a\n", name, x, y, r);
            break;
        }
        case UNARY_F: {
            float x;
            if (sscanf(line, "%a", &x) != 1) { in_test = 0; continue; }
            float r = e->fn.uf(x);
            printf("%s %a = %a\n", name, (double)x, (double)r);
            break;
        }
        case BINARY_F: {
            double dx, dy;
            if (sscanf(line, "%la,%la", &dx, &dy) != 2) { in_test = 0; continue; }
            float x = (float)dx, y = (float)dy;
            float r = e->fn.bf(x, y);
            printf("%s %a %a = %a\n", name, (double)x, (double)y, (double)r);
            break;
        }
        }

        alarm(0);  /* cancel timeout */
        in_test = 0;
    }

    if (faults > 0)
        fprintf(stderr, "%s: %d faults out of total inputs\n", name, faults);

    return 0;
}
