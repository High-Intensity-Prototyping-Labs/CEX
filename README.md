![CEX Logo](/img/cex.jpg)

# CEX.DEV
The C-Extended Standard Library.

## Purpose
To satisfy the need for a centralized collection of high-quality types and methods for the C language.

### Hasn't this been tried before?
Spurious attempts have been made to provide custom string support to C or even collect community-made C libraries in one place with CLI tooling.

But...

1. There is no uniformity in convention or quality whatsoever – some are excellent and well-documented, others are broken and even memory leak hells. Even if they were somehow all made to be top-notch in quality and stability, I still wouldn’t have the confidence that libraries will resemble to each other or work cohesively. This issue seems intrinsic to the fact that they are the result of the development of disjoint developers, all with different needs, goals, visions and standards for their code.

2. The lack of consistency and predictability among the libraries offers no opportunity for an intuition to be built around higher-level constructs like strings. Different naming conventions, different memory allocation schemes and custom error handling methods all need to be learned and applied separately to components of the same code. 

3. Even if (1) and (2) can be overcome or tolerated, this does not prevent the pollution of the C code’s namespace. Up to 3-4 different developers may have come up with their own ‘str’ method or type, and the confusion of the similarities aside it may just straight up collide in the symbol table. Few to none of the efforts dare try to use short and catchy representations of types and methods since if they are not already taken they are certain to cause a collision sooner or later.
