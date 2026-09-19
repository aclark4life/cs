# CS 420 - Computer Science Research

Independent research in software construction methods, under Dr. Keith Gallagher. Coursework involved surveying development methodologies (clean-room, iterative enhancement, rapid prototyping, decomposition-based) and trying several out in sample implementations.

## Contents

### readme.txt
Archived email from Dr. Gallagher with the original course description.

### tri/
A triangle classifier: reads three side lengths and reports whether they form an equilateral, isosceles, scalene, or invalid triangle.
```bash
gcc tri/main.c tri/is_triangle.c tri/my_atoi.c tri/prelim_check.c -o tri/tri
./tri/tri <side1> <side2> <side3>
```
See `tri/asn.tri` for the original assignment text.

> Note: the CS 364 knock-out-merge assignment (`ko.c`) was previously misfiled here and has since been consolidated into `364/`, where it belongs.
