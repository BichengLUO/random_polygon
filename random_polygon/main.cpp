#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <random>
#include <ctime>

typedef struct _point
{
	double x;
	double y;
	_point() : x(0.0), y(0.0) {}
	_point(double xp, double yp) : x(xp), y(yp){}
} point;

double randf();
void random_points(point ps[], int count, double min, double max);
point random_point_on_segment(const point &s, const point &e);
bool to_left(const point &s, const point &e, const point &p);
void swap(point ps[], int i, int j);
void space_partion_rec(point ps[], int count, int l, int r);
void space_partition(point ps[], int count);

const char *usage = "Usage: random_polygon.exe [count] [mean] [stddev] [output_file]";

//Usage: random_polygon.exe [count] [mean] [stddev] [output_file]
// [count] means the number of the points
// [mean] the mean value for normal-distributed random points
// [stddev] the standard devirants for normal-distributed random points
// [output_file] the output file path for simple polygon points
int main(int argc, char *argv[])
{
	srand(time(NULL));
	if (argc != 5)
	{
		std::cout << usage << std::endl;
		return -1;
	}

	int count = atoi(argv[1]);
	double mean = atof(argv[2]);
	double stddev = atof(argv[3]);
	std::ofstream file(argv[4], std::ofstream::out);

	point *ps = new point[count];
	random_points(ps, count, mean, stddev);
	space_partition(ps, count);
	for (int i = 0; i < count; i++)
		file << ps[i].x << " " << ps[i].y << std::endl;
	delete[] ps;
	return 0;
}

//Space Partitioning algorithm from "Heuristics for the Generation of Random Polygons, T. Auer & M. Held"
// The worst case is O(n^2)
// The best case is O(nlgn)
void space_partition(point ps[], int count)
{
	int first = 0;
	int second = rand() % (count - 1) + 1;
	point f = ps[first];
	point s = ps[second];
	swap(ps, 1, second);
	int i = 2;
	int j = count - 1;
	while (i <= j)
	{
		while (i < count && to_left(f, s, ps[i])) i++;
		while (j > 1 && !to_left(f, s, ps[j])) j--;
		if (i <= j)
		{
			swap(ps, i, j);
			i++;
			j--;
		}
	}
	swap(ps, 1, j);
	space_partion_rec(ps, count, 0, j);
	space_partion_rec(ps, count, j, count);
}

void space_partion_rec(point ps[], int count, int l, int r)
{
	if (r > l + 1)
	{
		int rp = rand() % (r - l - 1) + l + 1;
		point f = ps[l];
		point s = r == count ? ps[0] : ps[r];
		point rps = random_point_on_segment(f, s);
		point rpe = ps[rp];
		swap(ps, l + 1, rp);
		int i = l + 2;
		int j = r - 1;
		bool l_dir = to_left(rps, rpe, ps[l]);
		while (i <= j)
		{
			while (i < r && to_left(rps, rpe, ps[i]) == l_dir) i++;
			while (j > l + 1 && to_left(rps, rpe, ps[j]) != l_dir) j--;
			if (i <= j)
			{
				swap(ps, i, j);
				i++;
				j--;
			}
		}
		swap(ps, l + 1, j);
		space_partion_rec(ps, count, l, j);
		space_partion_rec(ps, count, j, r);
	}
}

void swap(point ps[], int i, int j)
{
	point temp = ps[i];
	ps[i] = ps[j];
	ps[j] = temp;
}

bool to_left(const point &s, const point &e, const point &p)
{
	return (e.x - s.x) * (p.y - s.y) - (e.y - s.y) * (p.x - s.x) <= 0;
}

point random_point_on_segment(const point &s, const point &e)
{
	double rand_ratio = randf();
	return point(s.x + (e.x - s.x) * rand_ratio, s.y + (e.y - s.y) * rand_ratio);
}

//Random ponints generated according to normal distribution
void random_points(point ps[], int count, double mean, double stddev)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(mean, stddev);
	for (int i = 0; i < count; i++)
		ps[i] = point(d(gen), d(gen));
}

double randf()
{
	return rand() / (double)RAND_MAX;
}