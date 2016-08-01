# Adaptive-Huffman-Coding

Extra coursework for UCSD CSE100 SP16. 

The task is to implement an Adaptive Huffman Tree, to handle the variance in frequency distribution of symbols. A dynamic Huffman tree will perform better locally than the static one since it can adjust its structures automatically.

To use:

`$ make`
`$ ./compress <input filename> <output filename>`

It will generate encoded file. 

To decode:

`$ ./uncompress <input filename> <output filename>`
