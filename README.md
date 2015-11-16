# task-dbase

VK Application task: string database

## Description
Simple string database is implemented as a hashtable with open addressing and linear probing.

### Why hashtable?

* Lookup takes `O(m)`, where `m` is length of string
* Requires little memory (in comparison with [trie](https://en.wikipedia.org/wiki/Trie), for example)
* Easy to implement

### Why open addressing and linear probing?

* Very few cache misses
* Though open addressing has particular problems with element deletion, it doesn't matter in terms of task (we don't need to be able to delete element)
* Super easy to implement


### Features
There's some tricks which help to achieve good performance

1. Use `mmap` to read file contents instead of subsequent `scanf`'s (or similar). This allows us to reduce memory usage (because lines from file are not copied to separate buffer) and greatly reduce amount of syscalls.
2. Estimate the maximum possible number of *unique* words in file, given information about minimum and maximum words length. This helps to avoid building a huge hashtable when file contains a huge number of small words (1-3 chars)
3. The size of hashtable is chosen to be prime substantially larger than number of words stored (`p >= 1.5*n`). This results in very good distribution of elements in table, so the average cluster length is about 3. Since hashtable entry is 12 bytes long, and typical cache line size is 64 bytes or more, the whole cluster almost always fits in 1 cache line, so only 1 memory fetch is performed by lookup.


### What could be better?
* [Cuckoo hashing](https://en.wikipedia.org/wiki/Cuckoo_hashing). 2 string comparisons per lookup in worst case.
* [Perfect hashing](https://en.wikipedia.org/wiki/Perfect_hash_function). 1 string comparison per lookup in worst case + less memory in use if perfect hashing is minimal.

Both of these take more time on insertion/preprocessing, and certainly harder to implement. Moreover, cuckoo hashing checks two completely different positions in memory, which in most cases leads to 2 memory fetches, while current simple implementation makes 1 fetch on average.

### Using
1. `make`
2. `./dbase <file_name>`

### Testing
When compiled with `DEBUG` macro, program prints some statistical information to stderr. Use `make debug` for this.

A simple program `randtest` generates random test and prints it to stdout. Usage:

1. `make randtest`
2. `./randtest <number_of_lines> <min_line_length> <max_line_length> > <test_file>`
