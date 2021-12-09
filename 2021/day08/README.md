<!--
  Copyright (c) 2021 Michael Federczuk
  SPDX-License-Identifier: CC-BY-SA-4.0
-->

# Day 8 - Part 2 Notes #

This document quickly explains how all segments of the given entry patterns can be deduced.  
I'm well aware that there might be other, more efficient, ways to deduced them, but this method is what I came up with,
so I'll just stick with it.

---

The first four digits that are known are `1`, `4`, `7` and `8`, since each of them has a unique amount of segments (the
AoC description even says so), which are 2, 4, 3 and 7, respectively.

The first segment, `a`, can be deduced from digits `1` and `7`; since `7` shares two same segments with `1` and has only
one extra segment: `a`.

	 aaaa
	.    .
	.    .
	 ....
	.    .
	.    .
	 ....

The two next segments that can be *somewhat* deduced are `c` and `f`.  
As previously stated, digits `1` and `7` share two same segments (`c` and `f`), but at this point it is not possible to
determine which one is at which position.

	 aaaa
	.    cf
	.    cf
	 ....
	.    fc
	.    fc
	 ....

Even though, at this point, it is now known which exact mapping are for `c` and `f`,
**it is still possible to figure out which pattern is digit `3`.**  
Digits `2`, `3` and `5` all have 5 segments - **but only digit `3` has both `c` AND `f` segments**, digits `2` and `5`
only have either the `c` OR `f` segment.  
This makes it now possible to know that the pattern with 5 segments and both the `c` and `f` segments is digit `3`.

Now, it is possible to deduce the `d` segment via digits `3` and `4`, since it is the only segment (that isn't `c` or `f`)
that is shared between the two digits.

	 aaaa
	.    cf
	.    cf
	 dddd
	.    fc
	.    fc
	 ....

Segment `g` is also now known thanks to digit `3`, because that is the only unknown segment contained in digit `3`.

	 aaaa
	.    cf
	.    cf
	 dddd
	.    fc
	.    fc
	 gggg

Same thing with segment `b` and digit `4`.

	 aaaa
	b    cf
	b    cf
	 dddd
	.    fc
	.    fc
	 gggg

And yet again, segment `e` and digit `8`.

	 aaaa
	b    cf
	b    cf
	 dddd
	e    fc
	e    fc
	 gggg

The only unknown now are segments `c` and `f`.  
These two can now be deduced through digit `6`:

Digits `0`, `6` and `9` all have 6 segments, but only digit `6` has **one** of segments `c` and `f`, namely the segment
`f`.  
Which means that know, all segments and digits have been deduced.

	 aaaa
	b    c
	b    c
	 dddd
	e    f
	e    f
	 gggg
