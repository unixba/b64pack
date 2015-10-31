# b64pack

B64pack compresses short text messages using simple
character encoding followed by a base64 decoding pass.
It was originally written to help squeeze more than
160 characters into a single SMS message. Depending on
the content, text messages up to 213 characters long
can be compressed to fit into the 160-character limit.

For messages shorter than 213 characters, b64pack will
usually give you better compression than `compress`,
`gzip`, `bzip2` or `xz`. It is also faster and less
resource-hungry than any of these programs (even in
its present non-optimized form). This makes it
suitable for processing of short messages, such as
SMSs, tweets and instant messages.

## Documentation

The method used by b64pack is described in detail
in the following paper:

> Kenan Kalajdzic, Samaher Hussein Ali and Ahmed Patel.
> [Rapid Lossless Compression of Short Text Messages](http://dx.doi.org/10.1016/j.csi.2014.05.005).
> *Computer Standards & Interfaces*, Elsevier, January 2015.

The program itself is too simple to require any elaborate
documentation. A simple man page provided in the `doc`
directory should be sufficiently informative. To view
the man page without installing it, type:

```sh
$ nroff -man doc/b64pack.1 | less -r
```

## Building and Installing

B64pack doesn't depend on any libraries besides *libc*,
so you should be able to build it on any UNIX system by
typing:

```sh
$ make
```

This will generate the executable named `b64pack` in the
`src` directory and a gzipped version of the man page in
the `doc` directory.

For installing, type as *root*:

```sh
# make install
```

You may have to adjust the installation directories for
the `b64pack` command and the corresponding man page in
`src/Makefile` and `doc/Makefile`, respectivelly.

## Running

If executed without any options `b64pack` reads a text
message from *stdin* and writes the compressed message to
*stdout*.

If the option `-d` is specified, `b64pack` runs in the
decompression mode, reading a compressed message from
*stdin* and writing the decompressed message to *stdout*.
Note that the decompressed message may contain trailing
spaces, which are used for padding during compression.

## License

Copyright &copy; 2015
[Kenan Kalajdzic](mailto:kenan@unix.ba).

Licensed under GPLv3+:
[GNU GPL version 3](http://gnu.org/licenses/gpl.html)
or later.
