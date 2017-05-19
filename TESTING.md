To test my *counters* module I wrote a test program, [counterstest](counterstest.c), to explore the capabilities of the *counters* data structure.

This test program inserts a bunch of keys and values into the counters data structure and then tests the functionality of all methods and edge cases.

It tests some corner cases by calling `counters_set()` on a variety of special cases.

It then tests `counters_print()` and `counters_iterate()` with simple printing tasks, and a simple iteration function that just tracks a counter as it passes over the items.

Finally, I run this test program from the `Makefile` with a dedicated rule run by `make counterstest`. 


### Login and collect the files we need for testing.

abh@flume.cs.dartmouth.edu's password: 
Last login: Tue Apr 18 20:49:51 2017 from 10.31.226.9
[abh@flume ~]$ cd cs50/labs/lab3/counters
[abh@flume ~/cs50/labs/lab3/counters]$ ls
counters.c  counters.h	counters.o  counterstest*  counterstest.c  counterstest.o  Makefile  README  TESTING
[abh@flume ~/cs50/labs/lab3/counters]$ head -10 counterstest.c
/* 
 * counterstest.c - test program for CS50 counters module
 *
 * usage:
 *   track frequencies of integer keys
 *
 *   tets functionality of methods outlined in counters.h
 *
 * Anders Bando-Hess, 2017
 */

 ### Compiling

 [abh@flume ~/cs50/labs/lab3/counters]$ make counterstest
gcc -Wall -pedantic -std=c11 -ggdb  -I../common   -c -o counterstest.o counterstest.c
gcc -Wall -pedantic -std=c11 -ggdb  -I../common   -c -o counters.o counters.c
gcc -Wall -pedantic -std=c11 -ggdb  -I../common counterstest.o counters.o ../common/readlinep.o ../common/memory.o  -o counterstest

 ### running settest.c to test functionality of set module and edge cases.

[abh@flume ~/cs50/labs/lab3/counters]$ ./counterstest
adding nodes...
printing counter...
(1:5)(2:9)(3:1)(4:1)(5:4)(9:5)
finding 5s; we should find four of them...
we have found 5 fives
attempting to set count of fives to 1000...
reprinting tree...
(1:5)(2:9)(3:1)(4:1)(5:1000)(9:5)
attempting to increment count of threes...
reprinting tree...
(1:5)(2:9)(3:2)(4:1)(5:1000)(9:5)
testing counters_iterate...should print all numbers with counts greater than 5
holy moly, item with key:2 has a high count of 9!
holy moly, item with key:5 has a high count of 1000!

 ### Checking for memory leaks with valgrind...

 [abh@flume ~/cs50/labs/lab3/counters]$ valgrind --leak-check=full -v ./counterstest
==26612== Memcheck, a memory error detector
==26612== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==26612== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==26612== Command: ./counterstest
==26612== 
--26612-- Valgrind options:
--26612--    --leak-check=full
--26612--    -v
--26612-- Contents of /proc/version:
--26612--   Linux version 4.10.8-100.fc24.x86_64 (mockbuild@bkernel02.phx2.fedoraproject.org) (gcc version 6.3.1 20161221 (Red Hat 6.3.1-1) (GCC) ) #1 SMP Fri Mar 31 13:20:57 UTC 2017
--26612-- 
--26612-- Arch and hwcaps: AMD64, LittleEndian, amd64-cx16-lzcnt-rdtscp-sse3-avx-avx2-bmi
--26612-- Page sizes: currently 4096, max supported 4096
--26612-- Valgrind library directory: /usr/lib64/valgrind
--26612-- Reading syms from /net/tahoe3/abh/cs50/labs/lab3/counters/counterstest
--26612-- Reading syms from /usr/lib64/ld-2.23.so
--26612--   Considering /usr/lib/debug/.build-id/6c/db31aa0b069eeeaf58d2b31cfde9ad91681534.debug ..
--26612--   .. build-id is valid
--26612-- Reading syms from /usr/lib64/valgrind/memcheck-amd64-linux
--26612--    object doesn't have a symbol table
--26612--    object doesn't have a dynamic symbol table
--26612-- Scheduler: using generic scheduler lock implementation.
--26612-- Reading suppressions file: /usr/lib64/valgrind/default.supp
==26612== embedded gdbserver: reading from /tmp/vgdb-pipe-from-vgdb-to-26612-by-abh-on-flume.cs.dartmouth.edu
==26612== embedded gdbserver: writing to   /tmp/vgdb-pipe-to-vgdb-from-26612-by-abh-on-flume.cs.dartmouth.edu
==26612== embedded gdbserver: shared mem   /tmp/vgdb-pipe-shared-mem-vgdb-26612-by-abh-on-flume.cs.dartmouth.edu
==26612== 
==26612== TO CONTROL THIS PROCESS USING vgdb (which you probably
==26612== don't want to do, unless you know exactly what you're doing,
==26612== or are doing some strange experiment):
==26612==   /usr/lib64/valgrind/../../bin/vgdb --pid=26612 ...command...
==26612== 
==26612== TO DEBUG THIS PROCESS USING GDB: start GDB like this
==26612==   /path/to/gdb ./counterstest
==26612== and then give GDB the following command
==26612==   target remote | /usr/lib64/valgrind/../../bin/vgdb --pid=26612
==26612== --pid is optional if only one valgrind process is running
==26612== 
--26612-- REDIR: 0x401c060 (ld-linux-x86-64.so.2:strlen) redirected to 0x3809d591 (???)
--26612-- REDIR: 0x401a9b0 (ld-linux-x86-64.so.2:index) redirected to 0x3809d5ab (???)
--26612-- Reading syms from /usr/lib64/valgrind/vgpreload_core-amd64-linux.so
--26612-- Reading syms from /usr/lib64/valgrind/vgpreload_memcheck-amd64-linux.so
==26612== WARNING: new redirection conflicts with existing -- ignoring it
--26612--     old: 0x0401c060 (strlen              ) R-> (0000.0) 0x3809d591 ???
--26612--     new: 0x0401c060 (strlen              ) R-> (2007.0) 0x04c2ec80 strlen
--26612-- REDIR: 0x401abd0 (ld-linux-x86-64.so.2:strcmp) redirected to 0x4c2fd80 (strcmp)
--26612-- REDIR: 0x401cf70 (ld-linux-x86-64.so.2:mempcpy) redirected to 0x4c33110 (mempcpy)
--26612-- Reading syms from /usr/lib64/libc-2.23.so
--26612--   Considering /usr/lib/debug/.build-id/46/2159b144229758ac6b654ddfbc23a2cdfbeafd.debug ..
--26612--   .. build-id is valid
--26612-- REDIR: 0x4ec4740 (libc.so.6:strcasecmp) redirected to 0x4a26772 (_vgnU_ifunc_wrapper)
--26612-- REDIR: 0x4ebfe70 (libc.so.6:strcspn) redirected to 0x4a26772 (_vgnU_ifunc_wrapper)
--26612-- REDIR: 0x4ec6a30 (libc.so.6:strncasecmp) redirected to 0x4a26772 (_vgnU_ifunc_wrapper)
--26612-- REDIR: 0x4ec22e0 (libc.so.6:strpbrk) redirected to 0x4a26772 (_vgnU_ifunc_wrapper)
--26612-- REDIR: 0x4ec2670 (libc.so.6:strspn) redirected to 0x4a26772 (_vgnU_ifunc_wrapper)
--26612-- REDIR: 0x4ec3e90 (libc.so.6:memcpy@GLIBC_2.2.5) redirected to 0x4a26772 (_vgnU_ifunc_wrapper)
--26612-- REDIR: 0x4ec1ff0 (libc.so.6:rindex) redirected to 0x4c2e610 (rindex)
--26612-- REDIR: 0x4eb9060 (libc.so.6:malloc) redirected to 0x4c2bb3f (malloc)
--26612-- REDIR: 0x4ec0310 (libc.so.6:strlen) redirected to 0x4c2ebc0 (strlen)
adding nodes...
--26612-- REDIR: 0x4ec40f0 (libc.so.6:__GI_mempcpy) redirected to 0x4c32e40 (__GI_mempcpy)
printing counter...
--26612-- REDIR: 0x4ecb450 (libc.so.6:strchrnul) redirected to 0x4c32c40 (strchrnul)
(1:5)(2:9)(3:1)(4:1)(5:4)(9:5)
finding 5s; we should find four of them...
we have found 5 fives
attempting to set count of fives to 1000...
--26612-- REDIR: 0x4eb93c0 (libc.so.6:free) redirected to 0x4c2ccec (free)
reprinting tree...
(1:5)(2:9)(3:1)(4:1)(5:1000)(9:5)
attempting to increment count of threes...
reprinting tree...
(1:5)(2:9)(3:2)(4:1)(5:1000)(9:5)
testing counters_iterate...should print all numbers with counts greater than 5
holy moly, item with key:2 has a high count of 9!
holy moly, item with key:5 has a high count of 1000!

deleting counters...
==26612== 
==26612== HEAP SUMMARY:
==26612==     in use at exit: 0 bytes in 0 blocks
==26612==   total heap usage: 22 allocs, 22 frees, 1,280 bytes allocated
==26612== 
==26612== All heap blocks were freed -- no leaks are possible
==26612== 
==26612== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==26612== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)