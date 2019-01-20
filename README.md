# printf_extension_example
### GNU Glibc printf extension passing a structure

The example in the glibc documentation only passes a pointer to a structure


See <https://www.gnu.org/software/libc/manual/html_node/Printf-Extension-Example.html#Printf-Extension-Example>

The only documentation for passing struct types appears to be the test code in the glibc source

eg <code>glibc/2.28/stdio-common/tst-vfprintf-user-type.c</code>

See <https://github.com/lattera/glibc/blob/master/stdio-common/tst-vfprintf-user-type.c>

This test code takes a format specifier that consumes two printf args and prints a struct 

### Example passing widget by value to printf()

The example in src/widget.c is an extension to the example in the glibc manual.
Instead of passing a pointer to the Widget to *printf()* 
the widget struct is passed by value.


While it appears that only the \**printf(FILE\* )*  functions are supported,
glibc must use string streams *fmemopen(3)*
to implement the \**s[n]printf()*  functions as these also <em>work</em> with format extensions.

See <https://www.gnu.org/software/libc/manual/html_node/String-Streams.html#String-Streams>
