#pragma once
#include <cg/primitives/segment.h>
#include <cg/primitives/vector.h>


namespace cg
{
   // a, b - segment points
   double point_segment_dist(point_2 o, point_2 a, point_2 b) {
      double r1 = sqrt((o.x - a.x) * (o.x - a.x) + (o.y - a.y) * (o.y - a.y));
      double r2 = sqrt((o.x - b.x) * (o.x - b.x) + (o.y - b.y) * (o.y - b.y));
      double r12 = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
      if (r1 >= sqrt(r2 * r2 + r12 * r12)) {
         return r2;
      }
      if (r2 >= sqrt(r1 * r1 + r12 * r12)) {
         return r1;
      }
      double vp = (b.x - a.x) * (a.y - o.y) - (b.y - a.y) * (a.x - o.x);
      return std::abs(vp / r12);
   }

   template<class BidIter, class OutIter>
   OutIter simplify_impl(BidIter st, BidIter en, double eps, OutIter out) {
      double mmax = 0;
      BidIter id;
      for (BidIter i = st; (++i) != en;) {
         double distance = point_segment_dist(*i, *st, *en);
         if (distance > mmax && distance > eps) {
            mmax = distance;
            id = i;
         }
      }
      if (mmax != 0) { 
         out = simplify_impl(st, id, eps, out);
         out = simplify_impl(id, en, eps, out);
      } else {
         *out++ = *en;
      }
      return out;
   }

   template<class BidIter, class OutIter>
   OutIter simplify(BidIter st, BidIter en, double eps, OutIter out) {
      --en;
      *out++ = *st;
      return simplify_impl(st, en, eps, out);
   }
}
