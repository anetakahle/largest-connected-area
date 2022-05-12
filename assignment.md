Finally, the day has come when the space probe sent out to Mars a few years ago is about to land. Due to budget cuts, the probe hasn't got enough computing power to determine the optimal landing site. Instead, it will take a satellite image of Mars's surface and send it to Earth for processing.

The satellite image can be imagined as a black and white raster image of size 2^30 x 2^30, where black pixels (with value 0) denote one can't land at this place, and white pixesl (with value 1) mark a place where landing is possible. The NASA engineers want to find the largest connected area suitable for landing, i. e. the connected area consisting of white squares only whose total surface is maximum possible. Two pixels are said to be neighbouring if they share an edge.

Since the image is too big to fit in memory, let alone be sent from Mars to Earth, before sending it, we compress it using quadrant compression, which works as follows: As input it gets an image of size 2^k x 2^k and it outputs a string. If the whole image is black or white, the output is 0 or 1, respectively. Otherwise we split the image into four smaller quadrants (each of same size), we encode these separately, and use ([LU][RU][LD][RD]) as output, where [LU] is the encoding of the left-upper quadrant, [RU] the encoding of the right-upper quadrant etc. For example, a 4 × 4 picture whose only black pixel is the second pixel of the first row is encoded as ((1011)111), a 4 × 4 picture with all pixels black is encoded as 0.

You will get a 2^30 x 2^30 image encoded with _quadrant compression_. Output the total surface of its largest connected white area.

### Input format
The only line of input contains the string representing image in the manner described above, without whitespace and followed by a single end-of-line character.

The length of the string will not exceed 1000000 characters.

### Output format
Output a single number: the total surface of the largest connected white area.

### Example input
```
((1110)(1101)(1011)(0111))
```
### Example output
```
864691128455135232
```
The image consists of 16 blocks of size 2^28 x 2^28
```
1111
1001
1001
1111
```
The largest connected area has therefore a total surface of 12 x 2^28 = 86469112845513523212×2 
28
 =864691128455135232.
