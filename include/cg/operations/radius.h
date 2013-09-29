#pragma once
#include <cg/primitives/circle.h>
#include <vector>
#include <algorithm>

namespace cg {
   circle_2 radius_impl(std::vector<point_2> &points, int n, std::vector<point_2> &border, int step) {
      circle_2 ans;

      if (step == 3) {
         ans = circle_2(border[0], border[1], border[2]);
      } else if (n == 1 && step == 0) {
         ans = circle_2(points[0], 0);
      } else if (n == 0 && step == 2) {
         ans = circle_2(border[0], border[1]);
      } else if (n == 1 && step == 1) {
         ans = circle_2(border[0], points[0]);
      } else {
         ans = radius_impl(points, n - 1, border, step);
         if (!ans.contains(points[n - 1])) {
            border[step++] = points[n - 1];
            ans = radius_impl(points, n - 1, border, step);
         }
      }
      return ans;
   }

   template <class BidIter>
   circle_2 radius(BidIter p, BidIter q) {
      std::vector<point_2> points;
      std::vector<point_2> border(3);
      srand(time(NULL));
      for (BidIter it = p; it != q; it++) {
         points.push_back(*it);
      }
      std::random_shuffle(points.begin(), points.end());
      return radius_impl(points, points.size(), border, 0);
   }
}
