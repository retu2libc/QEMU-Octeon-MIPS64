How to use:

At the time of writing this is the intended build process:

```bash
./configure --target-list=mips64-softmmu
patch -p1 < host.patch
make -j`nproc`
```

I make no guarantees beyond what the initial paper did for this.

The paper while impressive produced unusable artifacts for a variety of reasons.

As a result I set out to fix the problems with the original repo.

I feel I have done that and produced a repeatable and stable build system.

You may be wondering why I have included the unpacked qemu-1.0.1 files...

The answer is that I am backporting fixes I deem necessary to core functionality
not present in the tar archives online. You could use the tar files
although I am unsure how critical the effects some of the bugs were.

TODO:
1.) Add a Dockerfile with a tagged version of debian that this can build in
2.) Add scuba build support
3.) Fix the paper's linux patch as well
4.) Move the backported fixes to separate branch?
