### Visual-Cryptography

This is a C++ implementation of Naor's work on Visual Cryptography ([VC](https://link.springer.com/content/pdf/10.1007/BFb0053419.pdf))
It implements 2 out of 2 secret sharing and 2 out of n secret sharing.

For example the below image (key) can be broken into separate images that could be shared amongst n people. 
According to the image generation, any k people can come together and overlap the images to retireve the original key

An example key:-


![Key](bmpfiles/image5.bmp)


Here is one of the hashed out images distributed amongst the members of the sharing problem

![share](bmpfiles/share__0.bmp)


On overlapping any set of k such distinct images (out of n), the original key can be retrieved.
The main files are `Source_2on.cpp` and `Source_kok.cpp`, depending on the problem setting
