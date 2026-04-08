# Testgen Token Usage Summary (S1–S5)

| Scenario | Rounds | Output Tokens | Cache Read | Cache Create | Total Tokens | Cost |
|----------|--------|--------------|------------|-------------|-------------|------|
| S1 | 1 | 43,721 | 177,042 | 52,319 | 273K | $0.91 |
| S2 | 1 | 45,422 | 842,404 | 69,745 | 958K | $1.20 |
| S3 | 1 | 62,827 | 339,510 | 76,706 | 479K | $1.33 |
| S4 | 1 | 57,712 | 2,430,391 | 103,993 | 2.6M | $1.99 |
| S5 | 5 | 435,255 | 15,945,081 | 807,094 | 17.2M | $21.52 |

All scenarios use claude-sonnet-4-6. S5 rounds 1–3 and 5 also used claude-haiku-4-5 for subtasks.

## S5 Per-Round Breakdown

| Round | Output Tokens | Cache Read | Cache Create | Cost |
|-------|--------------|------------|-------------|------|
| R1 | 70,258 | 3,002,710 | 140,256 | $2.67 |
| R2 | 117,613 | 1,627,152 | 161,961 | $3.96 |
| R3 | 168,649 | 4,819,426 | 280,030 | $6.00 |
| R4 | 4,635 | 307,969 | 30,300 | $3.57 |
| R5 | 74,100 | 6,187,824 | 194,547 | $5.32 |

Note: R4 hit rate limits and produced minimal output ($3.57 mostly from retry delays, not tokens).

## Notes

- S1–S3: single-shot test generation (~$1 each)
- S4: 1 round with function coverage feedback (~$2)
- S5: 5 rounds with branch coverage feedback, building on S4's test suite ($21.52 total)
- Token counts include all tool use (file reads, greps, etc.) within each AI session
