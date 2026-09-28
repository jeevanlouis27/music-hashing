# Complexity Analysis

## Hashing

Division-method hashing computes an index in O(1).

With linear probing:
- Average insertion: O(1)
- Average successful search: O(1)
- Average unsuccessful search: O(1) under typical assumptions
- Worst-case insertion: O(n)
- Worst-case search: O(n)
- Space: O(m)

The worst case occurs when collisions create a long probe sequence.

## Linear Search

For an array of n song IDs:
- Best case: O(1)
- Average case: O(n)
- Worst case: O(n)
- Extra space: O(1)

## Load Factor

For 8 records and 11 slots:

alpha = n / m = 8 / 11 = 0.7273

The table is therefore 72.73% occupied.

## Observed Search Counts

Hashing:
- 105: 1 operation
- 420: 1 operation
- 735: 1 operation
- 840: 1 operation
- 999: 2 operations
- Average: 1.2 operations

Linear search:
- 105: 1 comparison
- 420: 4 comparisons
- 735: 7 comparisons
- 840: 8 comparisons
- 999: 8 comparisons
- Average: 5.6 comparisons

The supplied IDs produce no insertion collisions with m=11, so the experiment mainly demonstrates the low-collision case. The implementation nevertheless supports linear probing for collision cases.
