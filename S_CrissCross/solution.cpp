#include<bits/stdc++.h>
using namespace std;

typedef pair<double, double> point;
typedef pair<point,point> segment;

const double INF = 1000005;
const double DOUBLE_ERROR = 1e-9;

double get_m(segment s) {
	return (s.second.second - s.first.second) / (s.second.first - s.first.first);
}

double get_q(segment s, double m) {
	return s.first.second - m * s.first.first;
}

bool same_line(segment s1, segment s2) {
	double m1 = get_m(s1);
	double m2 = get_m(s2);
	if (isnan(m1) && isnan(m2)) {
		return max(s1.first, s2.first) < min(s1.second, s2.second);
	}
	if (abs(m1-m2) >= DOUBLE_ERROR) return false;
	
	double q1 = get_q(s1,m1);
	double q2 = get_q(s2, m2);
	if (abs(q1-q2) >= DOUBLE_ERROR) return false;
	return max(s1.first, s2.first) < min(s1.second, s2.second);
}

bool equal(point p1, point p2) {
	return abs(p1.first - p2.first) <= DOUBLE_ERROR
		&& abs(p1.second - p2.second) <= DOUBLE_ERROR;
}

void print_point(point p) {
	cout << "Point x: " << p.first << ", y: " << p.second << endl;
}

point intersection1d_point(segment s1, segment s2) {
	if ((equal(s1.first, s2.first) && get_m(s1) != get_m(s2)) || equal(s1.first, s2.second)) {
		return make_pair(s1.first.first, s1.first.second);
	}
	if (equal(s1.second, s2.first) || (equal(s1.second, s2.second) && get_m(s1) != get_m(s2))) {
		return make_pair(s1.second.first, s1.second.second);
	}
	return make_pair(INF,INF);
}

point intersection2d_point(segment s1, segment s2) {
	point a = s1.first;
	point b = s1.second;
	point c = s2.first;
	point d = s2.second;

	double a1 = b.second - a.second;
	double b1 = a.first - b.first;
	double c1 = a1 * a.first + b1 * a.second;

	double a2 = d.second - c.second;
	double b2 = c.first - d.first;
	double c2 = a2 * c.first + b2 * c.second;

	double determinant = a1 * b2 - a2 * b1;

	double x = (b2 * c1 - b1 * c2) / determinant;
	double y = (a1 * c2 - a2 * c1) / determinant;

	point intersec = make_pair(x,y);

	if (abs(determinant) < DOUBLE_ERROR
			|| !(intersec >= a && intersec <= b && intersec >=c && intersec <=d))
		return make_pair(INF,INF);
	
	return intersec;
}

point intersection_point(segment s1, segment s2) {
	point intersection1D = intersection1d_point(s1,s2);
	if (intersection1D.first < INF) return intersection1D;
	
	point intersection2D = intersection2d_point(s1,s2);
	if (intersection2D.first < INF) return intersection2D;

	return intersection2D; // here it means that the point is (INF,INF);
}

int solve(int N, vector<segment> segments) {
	set<point> points;
	for(int i=0;i<segments.size()-1;i++) {
		for(int j=i+1;j<segments.size();j++) {
			point intersection = intersection_point(segments[i], segments[j]);
			if (intersection.first < INF) {
				// valid intersection
				points.insert(intersection);
			} else if (same_line(segments[i], segments[j])) {
				return -1;
			}
		}
	}
	return points.size();
}

int main() {
	int N; cin >> N;
	vector<segment> segments;
	for(int i=0;i<N;i++) {
		point p1, p2;
		cin >> p1.first >> p1.second >> p2.first >> p2.second;
		segment s;
		s.first = min(p1,p2);
		s.second = max(p1,p2);
		segments.push_back(s);
	}
	cout << solve(N, segments) << endl;
	return 0;
}
