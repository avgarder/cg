#pragma once

#include <cg/primitives/point.h>

namespace cg
{
   template <class Scalar>
   struct circle_2t;

   typedef circle_2t<double> circle_2;

   template <class Scalar>
   struct circle_2t
   {
      circle_2t() {}
      circle_2t(point_2t<Scalar> const & center, Scalar const & radius)
         : center(center), radius(radius) {}

      // taken from algolist.manual.ru
      circle_2t(point_2 &p1, point_2 &p2, point_2 &p3) {
         double ma = (p2.y - p1.y) / (p2.x - p1.x);
         double mb = (p3.y - p2.y) / (p3.x - p2.x);
         double x = (ma * mb * (p1.y - p3.y) + mb * (p1.x + p2.x) - ma * (p2.x + p3.x)) / (2 * (mb - ma));
         double y = -1 / ma * (x - (p1.x + p2.x) / 2) + (p1.y + p2.y) / 2;
         center = point_2(x, y);
         radius = center.distance(p1);
      }

      circle_2t(point_2 &p1, point_2 &p2) {
         double x = (p1.x + p2.x) / 2;
         double y = (p1.y + p2.y) / 2;
         center = point_2(x, y);
         radius = center.distance(p1);
      }

      bool contains(point_2 p)
      {
         return ((p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y)) <= (radius * radius);
      }

      std::vector<point_2> points()
      {
         std::vector<point_2> ans;
         for (double x = center.x - radius; x <= center.x + radius; x += 0.01)
         {
            double y1 = center.y + sqrt(radius * radius - (x - center.x) * (x - center.x));
            double y2 = center.y - sqrt(radius * radius - (x - center.x) * (x - center.x));
            ans.push_back(point_2(x, y1));
            ans.push_back(point_2(x, y2));
         }
         return ans;
      }

      point_2t<Scalar> center;
      Scalar radius;
   };
}
