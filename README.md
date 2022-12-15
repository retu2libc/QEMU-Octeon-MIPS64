# How to use:

At the time of writing this is the intended build process:

```bash
./build.sh
scuba clean
scuba patch
scuba configure
scuba build
```

I make no guarantees beyond what the initial paper did for this.

The paper, while impressive, produced unusable artifacts for a variety of reasons.

As a result I set out to fix the problems with the original repo.

I feel I have done that and produced a repeatable and stable build system.

You may be wondering why I have included the unpacked qemu-1.0.1 files...

The answer is that I am backporting fixes I deem necessary to core functionality  
not present in the tar archives online.  
  
You could *theoretically* just use the tar file

# TODO:
1.) Fix the paper's linux patch as well  
2.) Move the backported fixes to separate branch?  
