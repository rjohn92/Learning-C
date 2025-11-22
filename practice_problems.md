# Beginner-Friendly C Mini Projects: Concepts, Use Cases, and CLI Examples

This guide lists a progressive set of small C programs designed to reinforce pointers, memory ownership, and file handling—**without** requiring complex frameworks. For each tool you’ll see: fundamentals & purpose, how it runs, what it does, why it exists, common verification tests, and the C patterns/idioms it exercises.

---

## How to read this guide
- **Run order:** 1 → 7 (builds difficulty gradually).
- **Inputs:** You can use real files or piped stdin (`-` means stdin).
- **No implementation shown:** This is a planning & reasoning document to keep you focused on *why* and *how*, not just code.

---

## 0) Baseline (already done)
### echo-args — sanity-check argv parsing
**Purpose:** Confirm your CLI parsing mental model (how `argv` tokenizes shell words).  
**Runs:** `echo-args foo "bar baz" --flag`  
**Why:** Establishes predictable CLI behavior for later tools with options.

### wc-bytes — byte counter via streaming
**Purpose:** Reinforce streaming I/O and EOF handling.  
**Runs:** `wc-bytes README.md` or `curl -s URL | wc-bytes`  
**Why:** Builds intuition for buffered reads and short writes you’ll use repeatedly.

---

## 1) cat-nl — line-numbered viewer
**Fundamentals & Purpose**  
Add stable line numbers to any text stream so you can reference exact lines when debugging or editing configs/logs.

**What it does**  
- Reads a file or stdin as a stream.  
- Writes each line with a fixed-width, right-aligned line number prefix.  
- Preserves original content.

**How it runs (examples)**  
- `cat-nl app.log`  
- `journalctl -u nginx | cat-nl`  

**Why do this**  
- Surfacing line numbers helps triage errors and communicate precise locations to teammates.  
- Teaches how to maintain line state across buffered chunks.

**Verification tests**  
- Empty file; huge file (>1 MiB); files where a newline falls across a 4 KiB boundary; files without trailing newline.

**Patterns & Idioms**  
- **Buffered read loop** (streaming `FILE*` reads in fixed chunks).  
- **Short-write retry** loop for stdout.  
- **Line-state flag** persisted between chunks.

---

## 2) hexdump16 — hex + ASCII viewer (16 bytes/row)
**Fundamentals & Purpose**  
Let you inspect raw bytes to confirm file signatures, non-printables, and offsets—critical for debugging binary protocols and corrupt files.

**What it does**  
- Prints offset, 16 bytes of hex, and printable ASCII (dots otherwise).  
- Handles partial final rows cleanly.

**How it runs (examples)**  
- `hexdump16 msg.bin`  
- `curl -s https://example.com/file | hexdump16`  

**Why do this**  
- Builds byte-level intuition for encodings and binary layouts.  
- Practical for verifying serialization, network captures, and embedded artifacts.

**Verification tests**  
- Empty file; 1, 15, 16, 17 bytes; binary data containing NULs.

**Patterns & Idioms**  
- **Offset accounting** (`size_t`/`uint64_t`).  
- **Unsigned char** for byte semantics.  
- **Windowing inside a larger buffer** (no seeks).

---

## 3) getline_dyn tools
### 3a) wc-lines — robust line counter
**Fundamentals & Purpose**  
Count lines even when individual lines are extremely long (≫4 KiB).

**What it does**  
- Grows a dynamic line buffer as needed.  
- Distinguishes EOF vs I/O error.

**How it runs (examples)**  
- `wc-lines huge.txt`  
- `wc-lines -` (read from stdin)

**Why do this**  
- Teaches dynamic memory growth with **realloc** and ownership.  
- Prepares you to handle unbounded inputs safely.

**Verification tests**  
- Single massive line (1–5 MiB); many short lines; file without trailing newline.

**Patterns & Idioms**  
- **Capacity-doubling** strategy with overflow checks.  
- **Caller-owns-buffer** contract; null-termination discipline.  
- **EOF vs error** discrimination.

### 3b) longest-line — report max line length (+ content)
**How it runs (examples)**  
- `longest-line mixed.txt`  
- `cat data.txt | longest-line`

**Why do this**  
- Detects pathological inputs that break UIs/parsers.  
- Reinforces the same dynamic buffer idioms as above.

---

## 4) strtrim and normspace — in-place text cleanup
**Fundamentals & Purpose**  
Normalize free-form text (user input, scraped HTML) before indexing or parsing.

**What they do**  
- **strtrim:** remove leading/trailing ASCII whitespace, in place.  
- **normspace:** collapse internal whitespace runs to a single space.

**How they run (examples)**  
- `strtrim < dirty.txt`  
- `normspace < dirty.txt`  
- `echo "   a   b   c   " | normspace | strtrim`

**Why do this**  
- Real inputs are messy; normalizing simplifies downstream logic and improves accuracy in matching/searching.

**Verification tests**  
- All-space string; empty string; no spaces; mixed tabs/spaces; Unicode left as-is.

**Patterns & Idioms**  
- **Two-pointer scans** from head/tail.  
- **In-place compaction** using **memmove** (safe for overlap).  
- Careful **off-by-one** handling of terminators.

---

## 5) sngrep — substring grep (handles chunk boundaries)
**Fundamentals & Purpose**  
Find fixed substrings in large files/streams where matches may span chunk boundaries—something a naive per-chunk search misses.

**What it does**  
- Scans a stream for `NEEDLE`.  
- Supports carry-over of the last `len(NEEDLE)-1` bytes between reads so boundary-spanning matches are found.  
- Emits matching line numbers or lines.

**How it runs (examples)**  
- `sngrep /api/v1/users server.log`  
- `zcat logs-2025-11-*.gz | sngrep ERROR`

**Why do this**  
- Builds mental model for streaming parsers and boundary-aware algorithms.

**Verification tests**  
- Needle exactly at buffer boundary; needle longer than chunk; empty needle (error); no matches.

**Patterns & Idioms**  
- **Chunk-boundary carry-over** logic.  
- **Naive search** baseline (upgrade path: KMP/BMH).  
- **Line-number tracking** while streaming.

---

## 6) csvcut — extract the Nth CSV column
**Fundamentals & Purpose**  
Quickly pull one column from CSV without a spreadsheet or DB, starting simple then handling RFC 4180 quotes.

**What it does**  
- Stage A: unquoted fields only.  
- Stage B: quoted fields with commas, double quotes, and embedded newlines.

**How it runs (examples)**  
- `csvcut -n 3 users.csv`  (prints the email column)  
- `cat users.csv | csvcut -n 2`

**Why do this**  
- Teaches tokenizer design and small state machines.  
- Very transferable to log parsing and ETL glue tools.

**Verification tests**  
- Commas in quotes; escaped quotes (`""`); empty fields; trailing comma; newlines inside quotes.

**Patterns & Idioms**  
- **Finite-state machine**: `IN_FIELD` → `IN_QUOTED` → `AFTER_QUOTE`.  
- **Dynamic field buffer** growth.  
- **Graceful error** on malformed input (don’t crash).

---

## 7) wordfreq — tiny frequency map (linear probing)
**Fundamentals & Purpose**  
Summarize the most common words quickly. Good for quick EDA of logs, notes, or document sets.

**What it does**  
- Scans text; tokenizes on letters; normalizes case.  
- Uses a simple open-addressed hash table to count frequencies.  
- Prints top-N (by count).

**How it runs (examples)**  
- `wordfreq notes.txt`  
- `wordfreq -n 10 < large_corpus.txt`

**Why do this**  
- Teaches dynamic containers, hashing, and load-factor-driven resizing.  
- Forces you to think about memory ownership and lifetime.

**Verification tests**  
- Large text; repeated words; mixed case; non-ASCII (treat as separators unless extended).

**Patterns & Idioms**  
- **Open addressing** with linear probing; rehash on resize.  
- **Load factor** threshold (e.g., 0.7).  
- **No delete** (avoid tombstones at first).

---

## Core C idioms you’ll reuse across all tools
1. **Buffered read loop (streaming)** — read fixed-size chunks; stop on 0; check `ferror`.  
2. **Short-write retry** — loop until all bytes are written (stdout can be partial).  
3. **Dynamic buffer growth** — capacity-doubling with overflow checks; `realloc` may move memory.  
4. **In-place edits with memmove** — safe when source and destination overlap.  
5. **Boundary carry-over** — preserve `k-1` bytes across chunks for cross-boundary matches.  
6. **State machines** — a few states + transitions beat brittle ad-hoc logic (CSV, tokenizers).  
7. **CLI parsing pattern** — scan `argv`, accept `-` as stdin, emit usage on invalid args, return proper exit codes.  
8. **Error handling** — print actionable messages (program: file: message) using `perror` or `strerror(errno)`, then non-zero exit.  
9. **Bit flags (concept)** — compactly model options or parser state (e.g., `FLAG_IN_QUOTE | FLAG_ESCAPE`).  
10. **Testing via shell** — pipes, redirection, `truncate`, `head`, `dd`, `zcat` to craft edge cases.  
11. **Observability** — run with `-g` + sanitizers; use `GDB` displays to watch counters, offsets, and buffer slices.

---

## Suggested build & debug discipline (applies to all)
- **Compiler:** `-std=c17 -Wall -Wextra -Wpedantic -O0 -g`  
- **Sanitizers:** Address + UB + no-omit-frame-pointer (development builds).  
- **Exit codes:** 0 on success; 2 for usage errors; 1 for runtime errors.  
- **Logs:** minimal, clear, actionable.

---

## Quick index of commands (copy/paste)
- `cat-nl app.log`  
- `journalctl -u nginx | cat-nl`  
- `hexdump16 msg.bin`  
- `curl -s https://example.com/file | hexdump16`  
- `wc-lines huge.txt`  
- `cat data.txt | longest-line`  
- `strtrim < dirty.txt`  
- `normspace < dirty.txt`  
- `echo "   a   b   c   " | normspace | strtrim`  
- `sngrep /api/v1/users server.log`  
- `zcat logs-2025-11-*.gz | sngrep ERROR`  
- `csvcut -n 3 users.csv`  
- `cat users.csv | csvcut -n 2`  
- `wordfreq notes.txt`  
- `wordfreq -n 10 < large_corpus.txt`

---

**Next step**  
Pick **1–3** and implement with rigorous tests. Only then move on. Keep this doc as your spec/checklist.
