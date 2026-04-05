# project2/src Documentation

This directory currently contains one core program: `bst.c`.

This program performs the following tasks:

- Reads two binary search trees, T1 and T2 (array indices are used as node IDs; each input row contains key and parentIndex).
- Checks whether there exists any pair such that `A + B = N`, where `A` comes from T1 and `B` comes from T2.
- If matches exist, prints all valid equations (each distinct A is printed only once).
- Finally prints preorder traversals of T1 and T2.

---

## 1. File Structure

- `bst.c`: main program.
- `stress_input.txt`: large-scale stress test input sample (optional).
- `stress_small.txt`: small-scale test input sample (optional).

---

## 2. Input Format

The program reads from standard input:

1. `n1`: number of nodes in the first tree.
2. Next `n1` lines: each line is `key parentIndex`.
3. `n2`: number of nodes in the second tree.
4. Next `n2` lines: each line is `key parentIndex`.
5. `N`: target sum.

Notes:

- `parentIndex = -1` means this node is the root.
- If `child.key < parent.key`, it is attached as the left child; otherwise, as the right child.

---

## 3. Output Format

First prints whether at least one solution exists:

- No solution: print `false`
- Has solution: print `true`, then print one equation per line: `N = A + B`

Then prints two more lines:

- Line 1: preorder traversal of T1
- Line 2: preorder traversal of T2

---

## 4. Build and Run

### Windows (MinGW / GCC)

```bash
gcc bst.c -O2 -o bst
bst < input.txt
```

or run interactively:
.\bst.exe
[type input manually, then press Enter to end input]

### Linux / macOS (GCC/Clang)

```bash
gcc bst.c -O2 -o bst
./bst < input.txt
```

or run interactively:
.\bst.exe
[type input manually, then press Enter to end input]

---

## 5. Algorithm Overview

1. Build two BSTs using array representation.
2. Perform iterative inorder traversal on T1 to get an ordered key sequence.
3. Insert keys from T2 into a hash table (open addressing with linear probing).
4. Enumerate distinct keys in T1, and check whether `N - A` exists in the hash table.
5. Print all matched equations, then print preorder traversals of both trees.

---

## 6. Complexity

- Time complexity: average `O(n1 + n2)`
- Space complexity: `O(n1 + n2 + HASH_SIZE)`

Here `HASH_SIZE = 2^20`; under `n <= 2e5`, the load factor remains low, so average insertion and lookup are efficient.

---

## 7. Stability and Memory Notes

- Large temporary arrays have been moved away from function stack frames to reduce stack overflow risk for large inputs.
- Hash tables and helper stacks are released after use to avoid memory leaks.
- Key `scanf` calls are validated; the program exits safely on incomplete input.

---

## 8. FAQ(Frequently Asked Questions)

### Q1: Why does the program exit right after I enter the first line?

(Exclude the case of stack overflow)
Usually because the input is incomplete. Make sure the full format is provided:

- After `n1`, there must be exactly `n1` node lines.
- After `n2`, there must be exactly `n2` node lines.
- The final target `N` must be present.

### Q2: Why are duplicate equations removed?

The program skips consecutive duplicate keys in T1's inorder sequence, ensuring each distinct `A` contributes at most one equation and avoiding repeated output.

