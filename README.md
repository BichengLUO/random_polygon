Random Simple Polygon Generator
====================================
This is a random simple polygon generator which adopted the Space Partitioning method from the paper [Heuristics for the Generation of Random Polygons][1].

Methodology
-----------------
Space Partitioning recursively partitions **S** into subsets which have disjoint convex hulls. Let **S'** be a such a subset of **S**. (Thus, **CH(S')** does not contain any point of **S-S'**.) When generating a polygon **P** we will guarantee that the intersection of **P** with **CH(S')** consists of one single chain.

> **Usage:**
```
random_polygon.exe [count] [mean] [stddev] [output_file]
```
> - [count] means the number of the points
> - [mean] the mean value for normal-distributed random points
> - [stddev] the standard devirants for normal-distributed random points
> - [output_file] the output file path for simple polygon points

Examples
------------------
Here are several examples which showing the results of this random simple polygon generator:
![Examples](/images/random_polygon.png)

[1]:http://www.cccg.ca/proceedings/1996/cccg1996_0007.pdf
