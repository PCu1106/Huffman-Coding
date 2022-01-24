# Huffman-Coding
implement Huffman coding
## Development Environment
Visual Studio

C++

Win10
## Design flow
Use an array with size=26 to count the number of letters

<img src=./design_flow/1.png width=80% />

Make it a min-heap tree

<img src=./design_flow/2.png width=80% />

Use min-heap tree to create a huffman tree

<img src=./design_flow/3.png width=80% />

Encoding: Every nodes except root have the code(left:1,right:0). Use preorder to encode.

Decoding: follow the code by pointer from root. If pointer is nullptr, then print the letter and go back to root.

<img src=./design_flow/4.png width=80% />

## Demo
<img src=./demo/1.png width=80% />
<img src=./demo/2.png width=80% />
