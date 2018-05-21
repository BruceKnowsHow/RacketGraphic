## What is this?
This is just a little project I made for an assignment in my C++ class. Near the end of the semester we had to do a few small projects in the Racket language. Our final assignment was to write a program that draws a little image with just the few primitive shape tools that the draw.rkt language teachpack provides. I wanted to do something cool, so I wrote a C++ program that reads an image, and writes Racket code that will draw the image pixel-by-pixel.

Basically, I wrote a C++ program that will do my final assignment for me.

draw.rkt only provides you with a few options for choosing colors. All of the colors are referred to by some English name, and there is no listed documentation of the exact names. I tracked down the source file that lists to full colorset, about 180 colors, and I converted it into a c++ map of <name, color> pairs.

To choose which color for each pixel, I just find the color with the minimum RGB component-wise difference.

I used C++ STL maps, which we learned about this semester in this C++ class, so I was really happy to find something to incorporate them into.


### Racket probably has tools to import bitmap images, what's the point?
I wanted my final output to utilize only the tools that our teacher gave us. This includes only using the sparse colorset provided by draw.rkt.


### Anything that bothered you?
I wanted to display a full 600x600 image, but that would be 360,000 pixels, and DrRacket craps the bed at 5,000 lines of code (each pixel corresponds to one line of code)


### Any good ideas you didn't use?
The colorset provided by draw.rkt is very sparse. To improve color representation, I could implement some sort of dithering.

Alternatively, I could use opacity to unlock a wider colorset. by layering pixels on-top of each other. This would, however, increase the line-count substantially, as multiple lines of code would be required to draw each final pixel.

Also I could have done something more interesting and incorporated the little bitmap into some primitive image, but I already did what I was interested in, and I'm not feeling very creative.
