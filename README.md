# Data Compressor

A console application which simulates an archiver that uses Huffman coding to compress and decompress a data file.

## Usage
Compress source_file.txt to result.bin. The original file size, the compressed file size and the size of additional data will be shown after the source file is compressed.
```
$ ./archiver -c -f source_file.txt -o result.bin
15678
6172
482
```
Decompress result.bin to result_file.txt. The compressed file size, the original file size and the size of additional data will be shown after the source file is compressed.
```
$ ./archiver -u -f result.bin -o result_file.txt
6172
15678
482
```





 
