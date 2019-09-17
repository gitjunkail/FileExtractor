# FileExtractor
Able to extract multiple files from a single file that was combined. try the demo file

There are programs that combine multiple files into a single file via parsing by binary but every file type have a different header, for PDF files, it's "0x25, 0x50, 0x44, 0x46, 0x2D, 0x31, 0x2E, 0x37" which translates into %PDF-1.7, means PDF version 1.7, if the header is known, this program can be utilized to extract all the files from the combined file, like a decompressor.
