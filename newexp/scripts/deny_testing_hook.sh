#!/usr/bin/env bash
# deny_testing_hook.sh — PreToolUse hook that blocks any Bash command
# referencing the testing/ directory (judger oracle tests, held-out tests).
#
# Reads hook input JSON from stdin, exits 0 to allow, 2 to block.
# Claude Code passes tool_input.command in the hook payload; we inspect
# the raw command string and match against testing-path patterns.
#
# Matches:
#   - /home/leochanj/Desktop/libmcs/testing   (absolute)
#   - libmcs/testing                          (any prefix)
#   - ../testing/                             (relative)
#   - ../../testing/                          (deeper relative)
#   - testing/judger*, testing/newlib*, testing/sdd*, testing/coremath*
#
# Does NOT match:
#   - newexp/scripts/deny_testing_hook.sh itself
#   - the word "testing" in unrelated contexts (e.g. "testing the build")

set -u

payload=$(cat)
cmd=$(printf '%s' "$payload" | python3 -c '
import json, sys
try:
    d = json.load(sys.stdin)
    print(d.get("tool_input", {}).get("command", ""))
except Exception:
    pass
' 2>/dev/null)

[ -z "$cmd" ] && exit 0

# Patterns that indicate testing/ access
if printf '%s' "$cmd" | grep -qE '(/libmcs/testing|\.\./testing|\.\./\.\./testing|(^|[^a-zA-Z_])testing/(judger|newlib|sdd|coremath|run_|build_|gen_))'; then
    echo "Blocked: Bash command references testing/ (held-out judger oracle). If you need build scripts, use those in newexp/." >&2
    exit 2
fi

exit 0
