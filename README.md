# Music Application – Hashing Assignment

## Assignment Topic

A music application stores the following song IDs:

`105, 210, 315, 420, 525, 630, 735, 840`

This project implements a hash table using the **Division Method**, searches song IDs using **Hashing** and **Linear Search**, records trace tables, analyses collisions, calculates the load factor, and compares theoretical and observed performance.

---

## 1. Objective

The objectives of this assignment are to:

1. Implement a hash table in C using the Division Method.
2. Insert the given song IDs and display the table after every insertion.
3. Identify and record collisions.
4. Search for selected song IDs using hashing.
5. Search for the same IDs using linear search.
6. Record the number of operations/comparisons.
7. Analyse the effect of collisions on search performance.
8. Calculate the load factor.
9. Compare observed performance with theoretical complexity.
10. Determine whether hashing is suitable for the music application.

---

## 2. Hashing Method Used

The **Division Method** is:

`h(k) = k mod m`

where:

- `k` = song ID
- `m` = hash-table size

For this implementation:

- Hash-table size `m = 11`
- Collision resolution = **Linear Probing**
- Hash function = `h(k) = k mod 11`

### Why table size 11?

A prime table size gives a simple and effective division-method example and makes the collision behaviour visible for the supplied IDs.

---

## 3. Collision Analysis

For the supplied song IDs:

| Song ID | h(k) = k mod 11 |
|---:|---:|
| 105 | 6 |
| 210 | 1 |
| 315 | 7 |
| 420 | 2 |
| 525 | 8 |
| 630 | 3 |
| 735 | 9 |
| 840 | 4 |

The initial hash positions are therefore different for these eight IDs. **No collision occurs during insertion for this particular data set.**

The final occupied slots are:

`1, 2, 3, 4, 6, 7, 8, 9`

Empty slots are:

`0, 5, 10`

This is important: although the implementation supports collisions through linear probing, the supplied input does not actually create an insertion collision with table size 11.

---

## 4. Insertion Trace

The detailed insertion trace is in:

`trace/insertion_trace.csv`

The program prints the table after every insertion.

### Final table

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Value | - | 210 | 420 | 630 | 840 | - | 105 | 315 | 525 | 735 | - |

---

## 5. Search Tests

The following search IDs are used:

`105, 420, 735, 840, 999`

The first four are present in the database. `999` is absent and is included to demonstrate unsuccessful-search behaviour.

### Hashing search

Hashing search follows the same linear-probing sequence used during insertion.

| Search ID | Hash | Hash operations | Result |
|---:|---:|---:|---|
| 105 | 6 | 1 | Found |
| 420 | 2 | 1 | Found |
| 735 | 9 | 1 | Found |
| 840 | 4 | 1 | Found |
| 999 | 9 | 2 | Not Found |

For `999`:

`999 mod 11 = 9`

Slot 9 contains 735, so one additional slot is checked. Slot 10 is empty, so the search stops after 2 slot checks.

### Linear search

Linear search checks the original array from the beginning:

| Search ID | Comparisons | Result |
|---:|---:|---|
| 105 | 1 | Found |
| 420 | 4 | Found |
| 735 | 7 | Found |
| 840 | 8 | Found |
| 999 | 8 | Not Found |

Detailed CSV files are provided in `trace/`.

---

## 6. Load Factor

The load factor is:

`α = n / m`

where:

- `n = 8` stored song IDs
- `m = 11` hash-table slots

Therefore:

`α = 8 / 11 ≈ 0.7273`

So the hash table is approximately **72.73% full**.

A higher load factor generally increases the probability of collisions and increases the number of probes needed during open-addressing searches.

---

## 7. Complexity Analysis

### Hashing

With a well-distributed hash function and a controlled load factor:

- Average insertion: **O(1)**
- Average successful search: **O(1)**
- Average unsuccessful search: **O(1)** under typical assumptions
- Worst-case insertion/search: **O(n)**
- Space: **O(m)**

The worst case occurs when many keys collide and form a long probe sequence.

### Linear Search

For `n` elements:

- Best-case search: **O(1)**
- Average-case search: **O(n)**
- Worst-case search: **O(n)**
- Extra space: **O(1)**

---

## 8. Observed Performance

For the tested data:

- Hashing found each present ID in 1 operation because the IDs mapped to distinct initial slots.
- Hashing required only 2 slot checks for the unsuccessful search of 999.
- Linear search required between 1 and 8 comparisons.
- The average number of hashing operations for the five searches was **1.2**.
- The average number of linear-search comparisons was **5.6**.

This experiment therefore demonstrates the expected practical advantage of direct hashing for lookup operations.

However, the input set does **not** demonstrate an insertion collision. The program still contains complete linear-probing collision handling so that collisions can be tested with other data.

---

## 9. Effect of Collisions

A collision occurs when two different keys produce the same hash index.

With linear probing, a collision causes the algorithm to inspect the next slot:

`h(k), h(k)+1, h(k)+2, ...`

wrapping around the table when necessary.

Consequences:

1. More collisions produce longer probe sequences.
2. Longer probe sequences increase insertion time.
3. Longer probe sequences increase successful-search time.
4. Unsuccessful searches can become especially expensive.
5. As the load factor approaches 1, open-addressing performance can degrade significantly.

For the supplied eight IDs and table size 11, no insertion collision occurs. Therefore, the observed search results represent a low-collision case rather than a collision-heavy case.

---

## 10. Hashing vs Linear Search

| Criterion | Hashing | Linear Search |
|---|---|---|
| Average search | O(1) | O(n) |
| Worst-case search | O(n) | O(n) |
| Extra table space | O(m) | O(1) |
| Depends on collisions | Yes | No |
| Ordered traversal | Not naturally ordered | Preserves array order |
| Typical lookup performance | Very fast | Becomes slower as n grows |

---

## 11. Suitability for the Music Application

For an application that frequently needs to locate a song by a unique song ID, hashing is a suitable data structure because its expected lookup time is constant, **O(1)**, when the hash function distributes keys reasonably and the load factor is controlled.

The experiment supports this conclusion:

- Hashing used 1 operation for every successful lookup in the supplied data.
- Linear search needed up to 8 comparisons.
- The load factor was 8/11 ≈ 0.7273.
- The implementation handles collisions using linear probing.

The conclusion is therefore based on the **lookup requirement**. If the application also required sorted output, ordered traversal, or range queries, another data structure could be considered depending on those requirements.

---

## 12. Program Files

### `src/music_hashing.c`

Complete C implementation containing:

- Division-method hash function
- Linear-probing insertion
- Table display after every insertion
- Collision counting
- Hashing search
- Linear search
- Search-operation comparison

### `input/song_ids.txt`

Contains the supplied song IDs and search IDs.

### `output/sample_output.txt`

Contains a sample execution output corresponding to the supplied input.

### `trace/insertion_trace.csv`

Insertion-by-insertion trace table.

### `trace/hash_search_trace.csv`

Hashing search trace.

### `trace/linear_search_trace.csv`

Linear-search trace.

### `analysis/complexity_analysis.md`

Detailed time and space complexity analysis.

### `analysis/comparison_table.csv`

Performance comparison between hashing and linear search.

---

## 13. How to Compile and Run

### GCC

Open a terminal in the project directory and run:

```bash
gcc src/music_hashing.c -o music_hashing
```

Then execute:

```bash
./music_hashing
```

### Windows MinGW

```bash
gcc src/music_hashing.c -o music_hashing.exe
music_hashing.exe
```

---

## 14. Suggested GitHub Repository Structure

```text
music-hashing-assignment/
│
├── README.md
├── src/
│   └── music_hashing.c
│
├── input/
│   └── song_ids.txt
│
├── output/
│   └── sample_output.txt
│
├── trace/
│   ├── insertion_trace.csv
│   ├── hash_search_trace.csv
│   └── linear_search_trace.csv
│
└── analysis/
    ├── complexity_analysis.md
    └── comparison_table.csv
```

---

## 15. GitHub Upload Commands

After creating an empty GitHub repository, run:

```bash
git init
git add .
git commit -m "Complete hashing assignment"
git branch -M main
git remote add origin YOUR_GITHUB_REPOSITORY_URL
git push -u origin main
```

Replace `YOUR_GITHUB_REPOSITORY_URL` with the URL of your own GitHub repository.

Then submit the GitHub repository link as required by the assignment.

---

## 16. Final Conclusion

The Division Method hash table successfully stores the eight song IDs. With a table size of 11 and linear probing as the collision-resolution method, the supplied IDs occupy distinct initial hash positions, so no insertion collision occurs.

The measured search operations show fewer checks for hashing than linear search for the selected test cases. The load factor is approximately 0.7273.

Theoretical analysis indicates expected **O(1)** hashing lookup versus **O(n)** linear search. Hashing can therefore provide efficient song-ID lookup, while its performance depends on the quality of the hash distribution and the load factor.

**Final conclusion:** For frequent direct lookup of songs by unique song ID, hashing is an appropriate approach, provided the table is sized appropriately and collisions are managed effectively.
